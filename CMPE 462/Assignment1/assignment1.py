import matplotlib.pyplot as plt
import numpy.matlib 
import numpy as np 
import random
from sys import exit
import sys
import csv
import time


b = 1

def display(M):
    for i in range(len(M)):
        print(M[i])


def update_weight(w, A, c):

    for i in range(len(w)):

        w[i] = w[i] + A[i] * c

    return w


def plotGraph(w, x0, y0, x1, y1, i):

    id_x = [-50, 50]
    id_y = [151, -149]

    plt.scatter(x0, y0, label= "0", color= "red", marker= "*", s=30)
    plt.scatter(x1, y1, label= "1", color= "blue", marker= "*", s=30)

    # the equation is =>    y = -(w[0] / w[1]) * x - (b / w[1])

    y_x0 = -(1.0)  * w[0]/w[1] * 50 + (-1.0) * b / w[1]
    x_y0 = (151 + (b / w[1])) / ((-1.0) * (w[0] / w[1]))

    x_plot = [50, x_y0]
    y_plot = [y_x0, 151]

    plt.plot(x_plot, y_plot, label = "line " + str(i), color= "purple")
    plt.plot(id_x, id_y, label= "line f", color= "green")

    plt.legend()

    plt.savefig('part1_step'+str(i+1)+'.png')

# ----------------------------------------------MAIN----------------------------------------------------------

step = 0
part = 0


if len(sys.argv) > 4:
    print("Wrong Input")
else:
    part = int(sys.argv[1][4])
    step = int(sys.argv[2][4])

if part == 1:


    range_x = [-50, 50]
    range_y = [-149, 150]
    steps = [50, 100, 5000]
    set_w = []

    break_point = []
   
    part1_x = []
    part1_y = []
    w = [0, 0]

    x1 = []
    y1 = []
    x0 = []
    y0 = []

    i = step - 1

    for j in range(steps[i]):
        
        rx = random.randint(-50, 50)
        ry = random.randint(-149, 151)

        part1_x.append(rx)
        part1_y.append(ry) 

    c = 0

    stop = True
    # totalTurn = 0
    
    while stop:
        stop_count = 0
        for j in range(steps[i]):

            x = part1_x[j]
            y = part1_y[j]

            A = [x, y]

            if y < (-3) * x + 1:
                c = -1

                x0.append(x)
                y0.append(y)
            
            elif y > (-3) * x + 1:
                c = 1

                x1.append(x)
                y1.append(y)

            else:
                c = 0
            
            if c * (w[0] * x + w[1] * y) <= 0:

                w = update_weight(w, A, c)

                stop_count += 1

        if stop_count == 0:
            stop = False
    
        if break_point == A:
            stop = False

        break_point = A

    plotGraph(w, x0, y0, x1, y1, i)

if part == 2:
    start_time = time.time()
    data_files = ['ds1.csv', 'ds2.csv']

    t = []
    X = []
    all_data = []
    w = []

    eigen_value = 0
    index = 0

    if step == 1:

        eigen_value = 0
        index = 0

    elif step == 2:

        eigen_value = 0
        index = 1

    elif step == 3:

        eigen_value = 1e-8
        index = 1


    with open(data_files[index], 'r') as file:
        reader = csv.reader(file)
        for row in reader:

            temp = []
            for i in range(len(row) - 1):
                temp.append(float(row[i]))
            
            X.append(temp)
            temp_in = [float(row[len(row) - 1])]
            t.append(temp_in)

            all_data.append(row)
            
    
    x_np = np.array(X)
    x_transpose = x_np.transpose()
    x_2 = np.matmul(x_transpose, X)
   
    identity_X = np.identity(len(x_2))
    add_identity = np.array(identity_X)
    add_identity = add_identity * eigen_value
    in_paranthesis = np.add(x_2, add_identity)   
    
    inverse_p = np.linalg.inv(in_paranthesis)
    multi_1 = np.matmul(inverse_p, x_transpose)
    w = np.matmul(multi_1, t)            
    
    print("Time to complete step" + str(step) + ": " + str((time.time() - start_time) * 1000)  + " msec")



