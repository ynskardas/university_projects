import numpy as geek 
import matplotlib.pyplot as plot 
   
# 1D Array as per Gaussian Distribution 
mean = 15 
std = 16
size = 256
array = geek.random.normal(mean, std, size) 
print("1D Array filled with random values "
      "as per gaussian distribution : \n", array); 
  
# Source Code :  
# https://docs.scipy.org/doc/numpy-1.13.0/reference/ 
# generated/numpy-random-normal-1.py 
count, bins, ignored = plot.hist(array, 30, density=True) 
plot.plot(bins, 1/(std * geek.sqrt(2 * geek.pi)) *
          geek.exp( - (bins - mean)**2 / (2 * std**2) ), 
          linewidth=2, color='r') 
plot.show() 