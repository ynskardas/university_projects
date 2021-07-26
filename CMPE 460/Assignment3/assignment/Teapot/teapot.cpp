#include <cstdio>
#include <cstdlib>
#include <memory>
#include <vector>
#include <utility>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
#include <chrono>

#include <random>

#include "geometry.h"
#include "TeaPotRayTrace.cpp"

using namespace std;

#ifndef M_PI
#define M_PI 3.14159265358979323846  /* pi */........
#endif

static const float kInfinity = std::numeric_limits<float>::max();
static const float kEpsilon = 1e-8;
static const Vec3f kDefaultBackgroundColor = Vec3f(0.235294, 0.67451, 0.843137);
template <> const Matrix44f Matrix44f::kIdentity = Matrix44f();

inline
float clamp(const float &lo, const float &hi, const float &v)
{ return std::max(lo, std::min(hi, v)); }

inline
float deg2rad(const float &deg)
{ return deg * M_PI / 180; }

inline
Vec3f mix(const Vec3f &a, const Vec3f& b, const float &mixValue)
{ return a * (1 - mixValue) + b * mixValue; }

struct Options
{
    int width = 640;
    int height = 480;
    float fov = 90;
    Vec3f backgroundColor = kDefaultBackgroundColor;
    Matrix44f cameraToWorld;
    float bias = 0.0001;
    uint32_t maxDepth = 2;
};

enum MaterialType { kDiffuse, kNothing };

class Object
{
public:

    Object(const Matrix44f &o2w) : objectToWorld(o2w), worldToObject(o2w.inverse()) {}
    virtual ~Object() {}
    virtual bool intersect(const Vec3f &, const Vec3f &, float &, uint32_t &, Vec2f &) const = 0;
    virtual void getSurfaceProperties(const Vec3f &, const Vec3f &, const uint32_t &, const Vec2f &, Vec3f &, Vec2f &) const = 0;
    virtual void displayInfo() const = 0;
    Matrix44f objectToWorld, worldToObject;
    Vec3f albedo = 0.18;
    float Kd = 0.8; // phong model diffuse weight
    float Ks = 0.2; // phong model specular weight
    float n = 10;   // phong specular exponent
    Vec3f BBox[2] = {kInfinity, -kInfinity};
};

bool rayTriangleIntersect(
        const Vec3f &orig, const Vec3f &dir,
        const Vec3f &v0, const Vec3f &v1, const Vec3f &v2,
        float &t, float &u, float &v)
{
    Vec3f v0v1 = v1 - v0;
    Vec3f v0v2 = v2 - v0;
    Vec3f pvec = dir.crossProduct(v0v2);
    float det = v0v1.dotProduct(pvec);

    if (fabs(det) < kEpsilon) return false;

    float invDet = 1 / det;

    Vec3f tvec = orig - v0;
    u = tvec.dotProduct(pvec) * invDet;
    if (u < 0 || u > 1) return false;

    Vec3f qvec = tvec.crossProduct(v0v1);
    v = dir.dotProduct(qvec) * invDet;
    if (v < 0 || u + v > 1) return false;

    t = v0v2.dotProduct(qvec) * invDet;

    return (t > 0) ? true : false;
}

class TriangleMesh : public Object
{
public:
     
    TriangleMesh(
            const Matrix44f &o2w,
            const uint32_t nfaces,
            const std::unique_ptr<uint32_t []> &faceIndex,
            const std::unique_ptr<uint32_t []> &vertsIndex,
            const std::unique_ptr<Vec3f []> &verts,
            std::unique_ptr<Vec3f []> &normals,
            std::unique_ptr<Vec2f []> &st,
            bool singleVertAttr = true) :
            Object(o2w),
            numTris(0),
            isSingleVertAttr(singleVertAttr)
    {
        uint32_t k = 0, maxVertIndex = 0;
        for (uint32_t i = 0; i < nfaces; ++i) {
            numTris += faceIndex[i] - 2;
            for (uint32_t j = 0; j < faceIndex[i]; ++j)
                if (vertsIndex[k + j] > maxVertIndex)
                    maxVertIndex = vertsIndex[k + j];
            k += faceIndex[i];
        }
        maxVertIndex += 1;

        P = std::unique_ptr<Vec3f []>(new Vec3f[maxVertIndex]);
        for (uint32_t i = 0; i < maxVertIndex; ++i) {
            objectToWorld.multVecMatrix(verts[i], P[i]);
        }

        trisIndex = std::unique_ptr<uint32_t []>(new uint32_t [numTris * 3]);
        Matrix44f transformNormals = worldToObject.transpose();

        if (isSingleVertAttr) {
            N = std::unique_ptr<Vec3f []>(new Vec3f[maxVertIndex]);
            texCoordinates = std::unique_ptr<Vec2f []>(new Vec2f[maxVertIndex]);
            for (uint32_t i = 0; i < maxVertIndex; ++i) {
                texCoordinates[i] = st[i];
                transformNormals.multDirMatrix(normals[i], N[i]);
            }
        }
        else {
            N = std::unique_ptr<Vec3f []>(new Vec3f[numTris * 3]);
            texCoordinates = std::unique_ptr<Vec2f []>(new Vec2f[numTris * 3]);
            for (uint32_t i = 0, k = 0, l = 0; i < nfaces; ++i) { 
                for (uint32_t j = 0; j < faceIndex[i] - 2; ++j) {
                    transformNormals.multDirMatrix(normals[k], N[l]);
                    transformNormals.multDirMatrix(normals[k + j + 1], N[l + 1]);
                    transformNormals.multDirMatrix(normals[k + j + 2], N[l + 2]);
                    N[l].normalize();
                    N[l + 1].normalize();
                    N[l + 2].normalize();
                    texCoordinates[l] = st[k];
                    texCoordinates[l + 1] = st[k + j + 1];
                    texCoordinates[l + 2] = st[k + j + 2];
                }
                k += faceIndex[i];
            }
        }

         
        for (uint32_t i = 0, k = 0, l = 0; i < nfaces; ++i) { 
            for (uint32_t j = 0; j < faceIndex[i] - 2; ++j) {  
                trisIndex[l] = vertsIndex[k];
                trisIndex[l + 1] = vertsIndex[k + j + 1];
                trisIndex[l + 2] = vertsIndex[k + j + 2];
                l += 3;
            }
            k += faceIndex[i];
        }
    }
     
    bool intersect(const Vec3f &orig, const Vec3f &dir, float &tNear, uint32_t &triIndex, Vec2f &uv) const
    {
        uint32_t j = 0;
        bool isect = false;
        for (uint32_t i = 0; i < numTris; ++i) {
            const Vec3f &v0 = P[trisIndex[j]];
            const Vec3f &v1 = P[trisIndex[j + 1]];
            const Vec3f &v2 = P[trisIndex[j + 2]];
            float t = kInfinity, u, v;
            if (rayTriangleIntersect(orig, dir, v0, v1, v2, t, u, v) && t < tNear) {
                tNear = t;
                uv.x = u;
                uv.y = v;
                triIndex = i;
                isect = true;
            }
            j += 3;
        }

        return isect;
    }
    void getSurfaceProperties(
            const Vec3f &hitPoint,
            const Vec3f &viewDirection,
            const uint32_t &triIndex,
            const Vec2f &uv,
            Vec3f &hitNormal,
            Vec2f &hitTextureCoordinates) const
    {
        uint32_t vai[3]; 
        if (isSingleVertAttr) {
            vai[0] = trisIndex[triIndex * 3];
            vai[1] = trisIndex[triIndex * 3 + 1];
            vai[2] = trisIndex[triIndex * 3 + 2];
        }
        else {
            vai[0] = triIndex * 3;
            vai[1] = triIndex * 3 + 1;
            vai[2] = triIndex * 3 + 2;
        }
        if (smoothShading) {
            // vertex normal
            const Vec3f &n0 = N[vai[0]];
            const Vec3f &n1 = N[vai[1]];
            const Vec3f &n2 = N[vai[2]];
            hitNormal = (1 - uv.x - uv.y) * n0 + uv.x * n1 + uv.y * n2;
        }
        else {
            // face normal
            const Vec3f &v0 = P[trisIndex[triIndex * 3]];
            const Vec3f &v1 = P[trisIndex[triIndex * 3 + 1]];
            const Vec3f &v2 = P[trisIndex[triIndex * 3 + 2]];
            hitNormal = (v1 - v0).crossProduct(v2 - v0);
        }

         
        hitNormal.normalize();

        const Vec2f &st0 = texCoordinates[vai[0]];
        const Vec2f &st1 = texCoordinates[vai[1]];
        const Vec2f &st2 = texCoordinates[vai[2]];
        hitTextureCoordinates = (1 - uv.x - uv.y) * st0 + uv.x * st1 + uv.y * st2;
    }
    void displayInfo() const
    {
        std::cerr << "Number of triangles in this mesh: " << numTris << std::endl;
        std::cerr << BBox[0] << ", " << BBox[1] << std::endl;
    }
    uint32_t numTris;                        
    std::unique_ptr<Vec3f []> P;               
    std::unique_ptr<uint32_t []> trisIndex;   
    std::unique_ptr<Vec3f []> N;              
    std::unique_ptr<Vec2f []> texCoordinates;  
    bool smoothShading = true;                 
    bool isSingleVertAttr = true;
};

class Light
{
public:
    Light(const Matrix44f &l2w, const Vec3f &c = 1, const float &i = 1) : lightToWorld(l2w), color(c), intensity(i) {}
    virtual ~Light() {}
    virtual void illuminate(const Vec3f &P, Vec3f &, Vec3f &, float &) const = 0;
    Vec3f color = 1.0;
    float intensity;
    Matrix44f lightToWorld = Matrix44f(0.897258, 0, -0.441506, 0, -0.288129, 0.757698, -0.585556, 0, 0.334528, 0.652606, 0.679851, 0, 5.439442, 11.080794, 10.381341, 1);   
};

struct IsectInfo
{
    const Object *hitObject = nullptr;
    float tNear = kInfinity;
    Vec2f uv;
    uint32_t index = 0;
};

bool trace(
        const Vec3f &orig, const Vec3f &dir,
        const std::vector<std::unique_ptr<Object>> &objects,
        IsectInfo &isect)
{
    isect.hitObject = nullptr;
    for (uint32_t k = 0; k < objects.size(); ++k) {
        float tNearTriangle = kInfinity;
        uint32_t indexTriangle;
        Vec2f uvTriangle;
        if (objects[k]->intersect(orig, dir, tNearTriangle, indexTriangle, uvTriangle) && tNearTriangle < isect.tNear) {
            isect.hitObject = objects[k].get();
            isect.tNear = tNearTriangle;
            isect.index = indexTriangle;
            isect.uv = uvTriangle;
        }
    }

    return (isect.hitObject != nullptr);
}

Vec3f castRay(
        const Vec3f &orig, const Vec3f &dir,
        const std::vector<std::unique_ptr<Object>> &objects,
        const std::vector<std::unique_ptr<Light>> &lights,
        const Options &options,
        const uint32_t & depth = 0)
{
    if (depth > options.maxDepth) return 0;
    Vec3f hitColor = 0;
    IsectInfo isect;
    if (trace(orig, dir, objects, isect)) {
        Vec3f hitPoint = orig + dir * isect.tNear;
        Vec3f hitNormal;
        Vec2f hitTexCoordinates;
        isect.hitObject->getSurfaceProperties(hitPoint, dir, isect.index, isect.uv, hitNormal, hitTexCoordinates);
        
        hitColor = std::max(0.f, -hitNormal.dotProduct(dir)) ;//* Vec3f(hitTexCoordinates.x, hitTexCoordinates.y, 1);
    }
    else {
        hitColor = 0.3;
    }
    return hitColor;
}


 
 

void render(
        const Options &options,
        const std::vector<std::unique_ptr<Object>> &objects,
        const std::vector<std::unique_ptr<Light>> &lights)
{
    Vec3f *framebuffer  = new Vec3f[options.width * options.height];
    Vec3f *pix = framebuffer;
    float scale = tan(deg2rad(options.fov * 0.5));
    float imageAspectRatio = options.width / (float)options.height;
    Vec3f orig;
    options.cameraToWorld.multVecMatrix(Vec3f(0), orig);
    auto timeStart = std::chrono::high_resolution_clock::now();
    for (uint32_t j = 0; j < options.height; ++j) {
        for (uint32_t i = 0; i < options.width; ++i) {
             
            float x = (2 * (i + 0.5) / (float)options.width - 1) * imageAspectRatio * scale;
            float y = (1 - 2 * (j + 0.5) / (float)options.height) * scale;
            Vec3f dir;
            options.cameraToWorld.multDirMatrix(Vec3f(x, y, -1), dir);
            dir.normalize();
            *(pix++) = castRay(orig, dir, objects, lights, options);
        }
        fprintf(stderr, "\r%3d%c", uint32_t(j / (float)options.height * 100), '%');
    }
    auto timeEnd = std::chrono::high_resolution_clock::now();
    auto passedTime = std::chrono::duration<double, std::milli>(timeEnd - timeStart).count();
    fprintf(stderr, "\rDone: %.2f (sec)\n", passedTime / 1000);

    float gamma = 1;
    std::ofstream ofs;
    ofs.open("out.ppm");
    ofs << "P6\n" << options.width << " " << options.height << "\n255\n";
    for (uint32_t i = 0; i < options.height * options.width; ++i) {
        char r = (char)(255 * clamp(0, 1, powf(framebuffer[i].x, 1 / gamma)));
        char g = (char)(255 * clamp(0, 1, powf(framebuffer[i].y, 1 / gamma)));
        char b = (char)(255 * clamp(0, 1, powf(framebuffer[i].z, 1 / gamma)));
        
        ofs << r << g << b;
    }
    ofs.close();
    delete [] framebuffer;
}


 

Vec3f evalBezierCurve(const Vec3f *P, const float &t)
{
    float b0 = (1 - t) * (1 - t) * (1 - t);
    float b1 = 3 * t * (1 - t) * (1 - t);
    float b2 = 3 * t * t * (1 - t);
    float b3 = t * t * t;

    return P[0] * b0 + P[1] * b1 + P[2] * b2 + P[3] * b3;
}

Vec3f evalBezierPatch(const Vec3f *controlPoints, const float &u, const float &v)
{
    Vec3f uCurve[4];
    for (int i = 0; i < 4; ++i)
        uCurve[i] = evalBezierCurve(controlPoints + 4 * i, u);

    return evalBezierCurve(uCurve, v);
}

Vec3f derivBezier(const Vec3f *P, const float &t)
{
    return -3 * (1 - t) * (1 - t) * P[0] +
           (3 * (1 - t) * (1 - t) - 6 * t * (1 - t)) * P[1] +
           (6 * t * (1 - t) - 3 * t * t) * P[2] +
           3 * t * t * P[3];
}

 

Vec3f dUBezier(const Vec3f *controlPoints, const float &u, const float &v)
{
    Vec3f P[4];
    Vec3f vCurve[4];
    for (int i = 0; i < 4; ++i) {
        P[0] = controlPoints[i];
        P[1] = controlPoints[4 + i];
        P[2] = controlPoints[8 + i];
        P[3] = controlPoints[12 + i];
        vCurve[i] = evalBezierCurve(P, v);
    }

    return derivBezier(vCurve, u);
}

 

Vec3f dVBezier(const Vec3f *controlPoints, const float &u, const float &v)
{
    Vec3f uCurve[4];
    for (int i = 0; i < 4; ++i) {
        uCurve[i] = evalBezierCurve(controlPoints + 4 * i, u);
    }

    return derivBezier(uCurve, v);
}

 

void createPolyTeapot(const Matrix44f& o2w, std::vector<std::unique_ptr<Object>> &objects)
{
    uint32_t divs = 8;
    std::unique_ptr<Vec3f []> P(new Vec3f[(divs + 1) * (divs + 1)]);
    std::unique_ptr<uint32_t []> nvertices(new uint32_t[divs * divs]);
    std::unique_ptr<uint32_t []> vertices(new uint32_t[divs * divs * 4]);
    std::unique_ptr<Vec3f []> N(new Vec3f[(divs + 1) * (divs + 1)]);
    std::unique_ptr<Vec2f []> st(new Vec2f[(divs + 1) * (divs + 1)]);

     
     
    for (uint16_t j = 0, k = 0; j < divs; ++j) {
        for (uint16_t i = 0; i < divs; ++i, ++k) {
            nvertices[k] = 4;
            vertices[k * 4    ] = (divs + 1) * j + i;
            vertices[k * 4 + 1] = (divs + 1) * j + i + 1;
            vertices[k * 4 + 2] = (divs + 1) * (j + 1) + i + 1;
            vertices[k * 4 + 3] = (divs + 1) * (j + 1) + i;
        }
    }

    Vec3f controlPoints[16];
    for (int np = 0; np < TEAPOT_NB_PATCHES; ++np) { 
         
        for (uint32_t i = 0; i < 16; ++i){

            uint32_t ind_i = i % 4;
            uint32_t ind_j = i / 4;
            controlPoints[i][0] = teapot_cp_vertices[teapot_patches[np][ind_i][ind_j] - 1].x,
            controlPoints[i][1] = teapot_cp_vertices[teapot_patches[np][ind_i][ind_j] - 1].y,
            controlPoints[i][2] = teapot_cp_vertices[teapot_patches[np][ind_i][ind_j] - 1].z;
        }
        // generate grid
        for (uint16_t j = 0, k = 0; j <= divs; ++j) {
            float v = j / (float)divs;
            for (uint16_t i = 0; i <= divs; ++i, ++k) {
                float u = i / (float)divs;
                P[k] = evalBezierPatch(controlPoints, u, v);
                Vec3f dU = dUBezier(controlPoints, u, v);
                Vec3f dV = dVBezier(controlPoints, u, v);
                N[k] = dU.crossProduct(dV).normalize();
                st[k].x = u;
                st[k].y = v;
            }
        }

        objects.push_back(std::unique_ptr<TriangleMesh>(new TriangleMesh(o2w, divs * divs, nvertices, vertices, P, N, st)));
    }
}

 

constexpr uint32_t curveNumPts = 22;
Vec3f curveData[curveNumPts] = {
        {-0.0029370324, 0.0297554422, 0},
        {-0.1556627219, 0.3293327560, 0},
        {-0.2613958914, 0.9578577085, 0},
        {-0.2555218265, 1.3044275420, 0},
        {-0.2496477615, 1.6509973760, 0},
        {-0.1262923970, 2.0445597290, 0},
        { 0.1791589818, 2.2853963930, 0},
        { 0.4846103605, 2.5262330570, 0},
        { 0.9427874287, 2.2560260680, 0},
        { 1.0132762080, 1.9212043650, 0},
        { 1.0837649880, 1.5863826610, 0},
        { 0.9369133637, 1.2750572170, 0},
        { 0.6667063748, 1.2691831520, 0},
        { 0.3964993859, 1.2633090870, 0},
        { 0.2320255666, 1.3514200620, 0},
        { 0.1850330468, 1.5276420110, 0},
        { 0.1380405269, 1.7038639600, 0},
        { 0.2026552417, 1.8918340400, 0},
        { 0.4082475158, 1.9564487540, 0},
        { 0.6138397900, 2.0210634690, 0},
        { 0.7606914144, 1.8800859100, 0},
        { 0.7606914144, 1.7038639600, 0}
};

 

void createCurveGeometry(std::vector<std::unique_ptr<Object>> &objects)
{
    uint32_t ndivs = 16;
    uint32_t ncurves = 1 + (curveNumPts - 4) / 3;
    Vec3f pts[4];
    std::unique_ptr<Vec3f []> P(new Vec3f[(ndivs + 1) * ndivs * ncurves + 1]);
    std::unique_ptr<Vec3f []> N(new Vec3f[(ndivs + 1) * ndivs * ncurves + 1]);
    std::unique_ptr<Vec2f []> st(new Vec2f[(ndivs + 1) * ndivs * ncurves + 1]);
    for (uint32_t i = 0; i < ncurves; ++i) {
        for (uint32_t j = 0; j < ndivs; ++j) {
            pts[0] = curveData[i * 3];
            pts[1] = curveData[i * 3 + 1];
            pts[2] = curveData[i * 3 + 2];
            pts[3] = curveData[i * 3 + 3];
            float s = j / (float)ndivs;
            Vec3f pt = evalBezierCurve(pts, s);
            Vec3f tangent = derivBezier(pts, s).normalize();
            bool swap = false;

            uint8_t maxAxis;
            if (std::abs(tangent.x) > std::abs(tangent.y))
                if (std::abs(tangent.x) > std::abs(tangent.z))
                    maxAxis = 0;
                else
                    maxAxis = 2;
            else if (std::abs(tangent.y) > std::abs(tangent.z))
                maxAxis = 1;
            else
                maxAxis = 2;

            Vec3f up, forward, right;

            switch (maxAxis) {
                case 0:
                case 1:
                    up = tangent;
                    forward = Vec3f(0, 0, 1);
                    right = up.crossProduct(forward);
                    forward = right.crossProduct(up);
                    break;
                case 2:
                    up = tangent;
                    right = Vec3f(0, 0, 1);
                    forward = right.crossProduct(up);
                    right = up.crossProduct(forward);
                    break;
                default:
                    break;
            };

            float sNormalized = (i * ndivs + j) / float(ndivs * ncurves);
            float rad = 0.1 * (1 - sNormalized);
            for (uint32_t k = 0; k <= ndivs; ++k) {
                float t = k / (float)ndivs;
                float theta = t * 2 * M_PI;
                Vec3f pc(cos(theta) * rad, 0, sin(theta) * rad);
                float x = pc.x * right.x + pc.y * up.x + pc.z * forward.x;
                float y = pc.x * right.y + pc.y * up.y + pc.z * forward.y;
                float z = pc.x * right.z + pc.y * up.z + pc.z * forward.z;
                P[i * (ndivs + 1) * ndivs + j * (ndivs + 1) + k] = Vec3f(pt.x + x, pt.y + y, pt.z + z);
                N[i * (ndivs + 1) * ndivs + j * (ndivs + 1) + k] = Vec3f(x, y, z).normalize();
                st[i * (ndivs + 1) * ndivs + j * (ndivs + 1) + k] = Vec2f(sNormalized, t);
            }
        }
    }
    P[(ndivs + 1) * ndivs * ncurves] = curveData[curveNumPts - 1];
    N[(ndivs + 1) * ndivs * ncurves] = (curveData[curveNumPts - 2] - curveData[curveNumPts - 1]).normalize();
    st[(ndivs + 1) * ndivs * ncurves] = Vec2f(1, 0.5);
    uint32_t numFaces = ndivs * ndivs * ncurves;
    std::unique_ptr<uint32_t []> verts(new uint32_t[numFaces]);
    for (uint32_t i = 0; i < numFaces; ++i)
        verts[i] = (i < (numFaces - ndivs)) ? 4 : 3;
    std::unique_ptr<uint32_t []> vertIndices(new uint32_t[ndivs * ndivs * ncurves * 4 + ndivs * 3]);
    uint32_t nf = 0, ix = 0;
    for (uint32_t k = 0; k < ncurves; ++k) {
        for (uint32_t j = 0; j < ndivs; ++j) {
            if (k == (ncurves - 1) && j == (ndivs - 1)) { break; }
            for (uint32_t i = 0; i < ndivs; ++i) {
                vertIndices[ix] = nf;
                vertIndices[ix + 1] = nf + (ndivs + 1);
                vertIndices[ix + 2] = nf + (ndivs + 1) + 1;
                vertIndices[ix + 3] = nf + 1;
                ix += 4;
                ++nf;
            }
            nf++;
        }
    }

    for (uint32_t i = 0; i < ndivs; ++i) {
        vertIndices[ix] = nf;
        vertIndices[ix + 1] = (ndivs + 1) * ndivs * ncurves;
        vertIndices[ix + 2] = nf + 1;
        ix += 3;
        nf++;
    }

    objects.push_back(std::unique_ptr<TriangleMesh>(new TriangleMesh(Matrix44f::kIdentity, numFaces, verts, vertIndices, P, N, st)));
}

 
 

int main(int argc, char **argv)
{
    
    std::vector<std::unique_ptr<Object>> objects;

    createPolyTeapot(Matrix44f(1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1), objects);
    // lights
    std::vector<std::unique_ptr<Light>> lights;

    Options options;
    options.fov = 39.89;
    options.width = 512;
    options.height = 512;
    options.maxDepth = 1;

    options.cameraToWorld = Matrix44f(0.897258, 0, -0.441506, 0, -0.288129, 0.757698, -0.585556, 0, 0.334528, 0.652606, 0.679851, 0, 5.439442, 11.080794, 10.381341, 1);

    render(options, objects, lights);
    return 0;
}
