import numpy as np
import matplotlib.pyplot as plt
from PIL import Image


#------------------------------INITIALIZE---------------------------

width = 1000
height = 1000

max_depth = 3

camera = np.array([0, 0, 0])

# screen (-50,-50,100) -> (50,50,100)
# left, top, right, bottom
screen = (-50, 50, 50, -50) 

#light position and color define
light = { 'position': np.array([500, 500, 500]), 'ambient': np.array([1, 1, 1]), 'diffuse': np.array([1, 1, 1])}

shadow_constant = 0.1

objects = []



#-------------------------------FUNCTIONS-------------------------------

def create_sphere(N):
    objectList = []

    rgb_list = []
    for i in range(N):

        r1, g1, b1 = input("color of sphere "+str(i+1)+": (R,G,B)= ").replace('(', ' ').replace(')', ' ').split(',')
    
        r = float(r1) / 255.0   
        g = float(g1) / 255.0 
        b = float(b1) / 255.0

        rgb_list.append(np.array([r, g, b]))

    xyz_list = []
    radius_list = []
    for i in range(N):

        test = True
        while test:
        
            x1, y1, z1 = input("Position (x,y,z) of sphere "+str(i+1)+": ").replace('(', ' ').replace(')', ' ').split(',')

            x = float(x1)
            y = float(y1)
            z = float(z1)

            if z > 200 and z < 1000 and abs(x) < z/2 and abs(y) < z/2:
                test = False
                xyz_list.append(np.array([x, y, z]))
            else:
                print("z must be between 200 and 1000")
                print("x and y must be smaller than z/2")

        

        rad1 = input("Radius of sphere " + str(i+1)+": ")
        rad = float(rad1)
        radius_list.append(rad)

    for i in range(N):    
        
        createdObject = {'center': xyz_list[i], 'radius': radius_list[i], 'ambient': rgb_list[i], 'diffuse': rgb_list[i], 'reflection': 1 }
        objectList.append(createdObject)
    
    return objectList

def normalVector(vector):
    normal = vector / np.linalg.norm(vector)
    return normal

def reflectionVector(vector, normal):
    reflect = vector - 2 * np.dot(vector, normal) * normal
    return reflect

def intersectionSphere(center, radius, ray_origin, ray_direction):
    b = 2 * np.dot(ray_direction, ray_origin - center)
    c = np.linalg.norm(ray_origin - center) ** 2 - radius ** 2
    a = 1.0
    delta = b ** 2 - 4 * a * c
    if delta > 0:
        root1 = (-b + np.sqrt(delta)) / 2
        root2 = (-b - np.sqrt(delta)) / 2
        if root1 > 0 and root2 > 0:
            return min(root1, root2)
    return None

def nearest_intersected_object(objects, ray_origin, ray_direction):
    distances = [intersectionSphere(obj['center'], obj['radius'], ray_origin, ray_direction) for obj in objects]
    nearestObject = None
    min_dist = np.inf
    for index, distance in enumerate(distances):
        if distance and distance < min_dist:
            min_dist = distance
            nearestObject = objects[index]
    return nearestObject, min_dist



def illumination_calculator(nearestObject, light_intersection, normal_to_surface):

    illumination = np.zeros((3))
    ambient_color = nearestObject['ambient'] * light['ambient']
    diffuse_color= nearestObject['diffuse'] * light['diffuse'] * np.dot(light_intersection, normal_to_surface)
    illumination = ambient_color + diffuse_color
    
    return illumination


def cast_ray(direction, color, depth, origin, reflection):

    nearestObject, min_dist = nearest_intersected_object(objects, origin, direction)
    if nearestObject is None:
        return color / depth                      

    intersection = origin + min_dist * direction
    normal_to_surface = normalVector(intersection - nearestObject['center'])
    tricky_point = intersection + 1e-5 * normal_to_surface                          # 1e - 5 = 10 ^ -5 (that is eligible value)
    light_intersection = normalVector(light['position'] - tricky_point)             # tricky_point -> to don't find same sphere when nearest point, that was common method for it.

    _, min_dist = nearest_intersected_object(objects, tricky_point, light_intersection)
    light_intersection_distance = np.linalg.norm(light['position'] - intersection)
    is_shadowed = min_dist < light_intersection_distance

    if is_shadowed:
        return color / depth                       

    illumination = illumination_calculator(nearestObject, light_intersection, normal_to_surface)
    # reflection
    color += reflection * illumination
    reflection *= nearestObject['reflection']

    # color += illumination
    origin = tricky_point

    direction = reflectionVector(direction, normal_to_surface)

    if depth <= max_depth:
        return cast_ray(direction, color, depth+1, origin, reflection)
    
    else: 
        return color / depth                       

#--------------------------------MAIN----------------------------------

print("Number of spheres: ")
N = int(input())

objects = create_sphere(N)
plane = { 'center': np.array([0, -50000, 0]), 'radius': 50000 - 400, 'ambient': np.array([0.5, 0.5, 0.5]), 'diffuse': np.array([0.7, 0.7, 0.7]), 'reflection': 1 }

objects.append(plane)

image = np.zeros((height, width, 3))
for i, y in enumerate(np.linspace(screen[1], screen[3], height)):
    for j, x in enumerate(np.linspace(screen[0], screen[2], width)):
        # center of screen is on (0, 0, 100)
        pixel = np.array([x, y, 100])
        origin = camera
        direction = normalVector(pixel - origin)

        color = np.zeros((3))
        reflection = 1
        current_depth = 1

        color = cast_ray(direction, color, current_depth, origin, reflection)
        image[i, j] = np.clip(color, 0, 1)

plt.imsave('shadow_balls.png', image)


with Image.open('shadow_balls.png') as img:
    img.show()