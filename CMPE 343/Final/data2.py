import numpy as np

a1 = np.load('before.npy')
a2 = np.load('after.npy')
a3 = np.load('measurements.npy')
a4 = np.load('sample1.npy')
a5 = np.load('sample2.npy')


n4 = len(a4)
n5 = len(a5)

total4 = 0
total5 = 0

for i in range(len(a4)):
    total4 += a4[i]

for i in range(len(a5)):
    total5 += a5[i]

avg4 = total4 / len(a4)
avg5 = total5 / len(a5)

k4 = 0
for i in range(len(a4)):
    k4 += ((a4[i] - avg4)**2)

sd4 = (k4 / (len(a4) - 1))**(1/2)


k5 = 0
for i in range(len(a5)):
    k5 += ((a5[i] - avg5)**2)

sd5 = (k5 / (len(a5) - 1))**(1/2)

print(n4, n5)
print(sd4, sd5)
print(sd4**2, sd5**2)

f = 2.3579

left = (sd4**2 / sd5**2) * (1 / f)
right = (sd4**2 / sd5**2) * (f)


print(left, right)
