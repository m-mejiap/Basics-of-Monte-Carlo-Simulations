import numpy as np
import matplotlib.pylab as plt
from scipy.special import gamma, factorial

def volume(N,n_total):
    R = 1
    n_inside = 0
    suma = 0
    for i in range(0,n_total):
        sq = 0
        for i in range(0,N):
            xi = R*(2*np.random.random()-1)
            sq += xi**2
        if(sq < R**2):
            f = np.sqrt(R**2 - sq)
            suma += f
            n_inside += 1
    mean = suma / n_inside
    r1 = 2*np.pi*(R**2)*mean
    return (2**N)*(n_inside/n_total)

for i in range (1,15):
    print(i,volume(i,100000))
print(15,volume(15,1000000))