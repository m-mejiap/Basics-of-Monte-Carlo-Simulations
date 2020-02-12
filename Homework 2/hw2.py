import numpy as np
a = 85
b = a
c = 91
m = 289
def QCG(yn):
    yn1 = (a*(yn**2) + b*yn + c) % m
    return yn1 / m
def seed():
    return np.random.randint(m)
def mod_inv(yn):
    x = 0
    while((yn*x-1) % m != 0):
        x += 1
    return x
r1 = QCG(seed())
r2 = QCG(r1*289)
r = QCG(r2*289)
n = 1
while(r != r1):
    r = QCG(r*289)
    n+=1
    
    mod_inv(seed())
