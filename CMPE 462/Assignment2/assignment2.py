import matplotlib.pyplot as plt
import numpy.matlib 
import numpy as np 
import random
from sys import exit
import sys
import csv
import time
import math
from random import seed
from random import randrange


# ----------------------------------------------FUNCTIONS----------------------------------------------------------


b = 1

def display(M):
    for i in range(len(M)):
        print(M[i])


def update_weight(w, art_n, vt):

    for i in range(len(w)):

        w[i] = w[i] + art_n * vt[i]

    return w


def plotGraph(loss, step):

    ylabel = 'loss function for step '
    color_palet = ["red", "green", "blue"]
    
    for i in range(len(loss)):
        if i == 0:
            size = 'small'
        elif i == 1:
            size = 'medium'
        elif i == 2:
            size = 'big'
        plt.plot(loss[i], label=size + ' step size', color=color_palet[i])
    
    plt.ylabel(ylabel + str(step))
    plt.legend()
    plt.savefig('part1_step' + str(step) + '.png')
    plt.close()


# Split a dataset into k folds
def cross_validation_split(dataset, folds):
	dataset_split = list()
	dataset_copy = list(dataset)
	fold_size = int(len(dataset) / folds)
	for i in range(folds):
		fold = list()
		while len(fold) < fold_size:
			index = randrange(len(dataset_copy))
			fold.append(dataset_copy.pop(index))
		dataset_split.append(fold)
	return dataset_split

# test cross validation split



# ----------------------------------------------MAIN----------------------------------------------------------

part = 0
step = 0

if len(sys.argv) > 4:
    print("Wrong Input")
else:
    part = int(sys.argv[1][4])
    step = int(sys.argv[2][4])

y = []
X = []
all_data = []
w = []
sample_size = 0

fold = 5
start_time = time.time()
with open('vehicle.csv', 'r') as file:
        reader = csv.reader(file)
        for row in reader:
            if row[len(row)-1] == 'saab' or row[len(row)-1] == 'van':
                sample_size += 1
                all_data.append(row)



sample_volume = len(all_data[0])
fold_value = 5
all_data_cv = cross_validation_split(all_data, fold_value)

if step == 1:
    
    for cv_i in range(len(all_data_cv)):
        
        for cv_j in range(len(all_data_cv[0])):
            data_x = []
            data_y = []
            for cv_k in range(len(all_data_cv[0][0])):
                
                if cv_k < sample_volume-1:
                    data_x.append(float(all_data_cv[cv_i][cv_j][cv_k]))
                else:
                    

                    if all_data_cv[cv_i][cv_j][cv_k] == 'saab':
                        data_y.append(-1.0)
                    elif all_data_cv[cv_i][cv_j][cv_k] == 'van':
                        data_y.append(1.0)

            X.append(data_x)
            y.append(data_y)

elif step == 2:
    
    mini_batch = random.choice(all_data_cv)        

    for cv_j in range(len(mini_batch)):
        data_x = []
        data_y = []
        for cv_k in range(len(mini_batch[0])):
            
            if cv_k < sample_volume-1:
                data_x.append(float(mini_batch[cv_j][cv_k]))
            else:
                
                if mini_batch[cv_j][cv_k] == 'saab':
                    data_y.append(-1.0)
                elif mini_batch[cv_j][cv_k] == 'van':
                    data_y.append(1.0)

        X.append(data_x)
        y.append(data_y)


for i in range(len(X)):
    for j in range(len(X[0])):
        min_column = min(a[j] for a in X)
        max_column = max(a[j] for a in X)
        X[i][j] = (X[i][j] - min_column) / (max_column - min_column)


N = len(y)
small_n = 0.1
medium_n = 0.5
big_n = 0.9
step_size_list = [small_n, medium_n, big_n]
plot_loss = []
number_of_iter = []

for j in range(len(step_size_list)):

    w = [0] * (sample_volume-1)
    stop = False
    
    step_count = 0
    art_n = step_size_list[j]
    loss_function_list = []
    while not stop:

        init_gt = []        
        pre_gt = 0 
        pre_loss_function = 0
        for i in range(N):
            # print(pre_loss_function)
            x_np = np.array(X[i])
            y_np = np.array(y[i])
            w_np = np.array(w)

            top = y_np * x_np
            w_transpose = w_np.transpose()
            y_wt = y_np * w_transpose
            power = np.matmul(y_wt, x_np)            
            epsilon_power = 0
            epsilon_power = math.exp(power)
            bot = 1 + epsilon_power
            negative_epsilon_power = math.exp((-1.0) * power)
            loss_bot = 1 + negative_epsilon_power
            pre_gt = np.add(pre_gt, (1.0/bot) * top)
            pre_loss_function += math.log(loss_bot)

        loss_function = (1.0/N) * pre_loss_function
        loss_function_list.append(loss_function)
        gt = (-1.0/N) * pre_gt
        vt = -gt
        w = update_weight(w, art_n, vt)        
        step_size = np.linalg.norm(art_n * vt)
        step_count += 1

        if step_size < 0.001:
            stop = True

    plot_loss.append(loss_function_list)
    number_of_iter.append(step_count)


steps_sizes = ["small", "medium", "big"]
for i in range(len(number_of_iter)):
    print("Number of iteration of the step" + str(step) + " for " + steps_sizes[i] +" step size = " + str(number_of_iter[i]))

plotGraph(plot_loss, step)
print("Time to complete step" + str(step) + ": " + str((time.time() - start_time))  + " sec")


