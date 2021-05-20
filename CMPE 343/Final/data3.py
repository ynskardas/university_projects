import numpy as np

a1 = np.load('before.npy')
a2 = np.load('after.npy')
a3 = np.load('measurements.npy')
a4 = np.load('sample1.npy')
a5 = np.load('sample2.npy')

n = 40
d = []

print(a3)

total = 0
for i in range(len(a3)):
    total += a3[i]

avg = total / len(a3)

k = 0
for i in range(len(a3)):
    k += ((a3[i] - avg)**2)

sd = (k / (len(a3) - 1))**(1/2)

print(len(a3))

print(avg, sd)

n = len(a3)

t = 2.02

left = avg - t * sd * ((1 + (1 / n))**2)
right = avg + t * sd * ((1 + (1 / n))**2)

print(left, right)