import numpy as np
import matplotlib.pylab as plt
import math

def VanDerCorput(index, base):
    result = 0
    f = 1
    i = index
    while(i>0):
        f = f / base
        result += f * (i % base)
        i = math.floor(i/base)
    return result
    
print("Base 7:")
for i in range(501,511):
    print(i, VanDerCorput(i,7))
    
print("Base 13:")
for i in range(501,511):
    print(i, VanDerCorput(i,13))
