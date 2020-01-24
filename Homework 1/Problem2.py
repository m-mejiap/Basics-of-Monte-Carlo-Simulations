import numpy as np

def LCG_Seed():
    return np.random.randint(113829760)

seed = LCG_Seed()

def LCG(seed):
    m = 113829760
    a = 3557181
    c = 2583473
    rand = ((a*seed)+c)%m
    return rand/m
    
def PM_Seed():
    return np.random.randint(113829760)

seed2 = PM_Seed()

def PM(seed):
    a = 7**5
    m = (2**31) - 1
    q = 127773
    r = 2836
    rand = a*(seed%q) - r*(seed/q)
    if(rand>=0):
        return rand/m
    else:
        return (rand+m)/m

def MersenneTwister_Seed():
    return np.random.randint(2**32 - 1)

seed3 = MersenneTwister_Seed()

def MersenneTwister(seed):
    return np.random.random()

a = LCG(seed)
b = PM(seed2)
c = MersenneTwister(seed3)
print ("LCG value:", a, "- Park-Miller value:", b, "- Mersenne Twister value:", c);

num1 = 0
seed = LCG(seed)*113829760
compare1 = LCG(seed)

while(compare1 != a):
    num1 += 1
    seed = LCG(seed)*113829760
    compare1 = LCG(seed)
    
num2 = 0
seed2 = PM(seed2)*2147483647
compare2 = PM(seed2)

while(compare2 != b):
    num2 += 1
    seed2 = PM(seed2)*2147483647
    compare2 = PM(seed2)
    
num3 = 0
seed3 = MersenneTwister(seed3)* 113829760
compare3 = MersenneTwister(seed3)

while(compare3 != c):
    num3 += 1
    seed3 = MersenneTwister(seed3)* 113829760
    compare3 = MersenneTwister(seed3)
    
print("The number of  random numbers generated in the sequence before it starts repeating itself is: LCG value:", num1, "- Park-Miller value:", num2, "- Mersenne Twister value:", num3)