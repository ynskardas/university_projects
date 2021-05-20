import numpy as np
import matplotlib.pyplot as plt
from PIL import Image

def create_sphere(N):
    objectList = []
    for i in range(N):
    
        print("Red value of color of sphere " + str(i+1) + " for RGB: ")
        r1 = int(input())
        r = r1 / 255.0

        print("Green value of color of sphere " + str(i+1) + " for RGB: ")
        g1 = int(input())
        g = g1 / 255.0

        print("Blue value of color of sphere " + str(i+1) + " for RGB: ")
        b1 = int(input())
        b = b1 / 255.0

        print("X coordinate of pozition of sphere " + str(i+1) + ":")
        x = int(input())

        print("Y coordinate of pozition of sphere " + str(i+1) + ":")
        y = int(input())
        
        testZ = True
        z = 200
        while(testZ):
            print("Z coordinate of pozition of sphere " + str(i+1) + " (Must be between 200 and 1000):")
            z = int(input())
            if z > 200 and z < 1000:
                testZ = False
            else:
                print("Z coordinate of pozition of sphere must be between 200 and 1000")

        print("Radius of sphere " + str(i+1))
        rad = int(input())

        createdObject = {'center': np.array([x, y, z]), 'radius': rad, 'rgb': np.array([r, g, b]), 'reflection': 1 }
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

width = 1000
height = 1000

max_depth = 4

camera = np.array([0, 0, 0])

# screen (-50,-50,100) -> (50,50,100)
# left, top, right, bottom
screen = (-50, 50, 50, -50) 

#light position and color define
light = { 'position': np.array([500, 500, 500]), 'rgb': np.array([1, 1, 1])}

shadow_constant = 0.1

objects = []

print("Number of spheres: ")
N = int(input())

objects = create_sphere(N)

image = np.zeros((height, width, 3))
for i, y in enumerate(np.linspace(screen[1], screen[3], height)):
    for j, x in enumerate(np.linspace(screen[0], screen[2], width)):
        # center of screen is on (0, 0, 100)
        pixel = np.array([x, y, 100])
        origin = camera
        direction = normalVector(pixel - origin)

        color = np.zeros((3))

        for k in range(max_depth):
            
            nearestObject, min_dist = nearest_intersected_object(objects, origin, direction)
            if nearestObject is None:
                break

            intersection = origin + min_dist * direction
            normal_to_surface = normalVector(intersection - nearestObject['center'])
            tricky_point = intersection + 1e-5 * normal_to_surface                          # 1e - 5 = 10 ^ -5 (that is eligible value)
            light_intersection = normalVector(light['position'] - tricky_point)             # tricky_point -> to don't find same sphere when nearest point, that was common method for it.

            _, min_dist = nearest_intersected_object(objects, tricky_point, light_intersection)
            light_intersection_distance = np.linalg.norm(light['position'] - intersection)
            is_shadowed = min_dist < light_intersection_distance

            if is_shadowed:
                break

            illumination = np.zeros((3))
            illumination += nearestObject['rgb']
            color += illumination
      
            origin = tricky_point
            direction = reflectionVector(direction, normal_to_surface)

        image[i, j] = np.clip(color, 0, 1)

plt.imsave('shadow_balls.png', image)


with Image.open('shadow_balls.png') as img:
    img.show()