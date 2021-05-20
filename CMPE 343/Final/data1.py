import numpy as np

a1 = np.load('before.npy')
a2 = np.load('after.npy')
a3 = np.load('measurements.npy')
a4 = np.load('sample1.npy')
a5 = np.load('sample2.npy')

n = 40
d = []

for i in range(len(a1)):
    x = a1[i] - a2[i]
    d.append(x)

total = 0
for i in range(len(d)):
    total += d[i]

avg = total / len(d)

k = 0
for i in range(len(d)):
    k += ((d[i] - avg)**2)

sd = (k / (len(d) - 1))**(1/2)

print(avg, sd)
print("----------------")

t = (avg - 40) / (sd / (len(d) ** (1/2)))

print(t)

print(a1)
print(a2)
print(len(d))