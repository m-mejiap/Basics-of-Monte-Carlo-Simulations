import numpy as np
import matplotlib.pylab as plt

#One.
#Read in know shape of distribution fi(x) with Nf points.
data = np.genfromtxt("distr1.dat")
Nf = 39
#Calculate "true mean" xtrue from fi(x).
true_mean = np.sum(data[:,1])/Nf

#Two.
#Select number of counts to generate Nc in one distribution.
Nc = 100
#Select the number of distributions to generate Nd.
Nd = 10
#Deduce the maximun possible index in hj, call it Nh.
Nh = Nc

#Three.
#Form the cumulative distribution Fk(x).
suma = 0
Fk = []
for i in range(Nf):
    suma += data[i,1]
    Fk.append(suma)
Fk = Fk/max(Fk)

#Four.
#Set hj = 0 for all j = 1, ..., Nh, select delta(mean).
hj = np.zeros((Nh,1))
delta_mean = 1

#Five.
#Do loop over distributions i=1,Nd.
for i in range(0,Nd):
    #Six.
    #Set Dk = 0 for all k = 1, ..., Nf.
    Dk = np.zeros((Nf,1))
    #Seven.
    #Do loop over counts j = 1, Nc.
    for j in range(0,Nc):
        #Eight.
        #Generate a uniformaly distributed number u = Pu(0,1).
        u = np.random.random()
        #Nine.
        #Find k such that Fk-1 < u < Fk.
        for i in range(Nf):
            if(Fk[i-1] < u and Fk[i] > u):
                k = i
        #Ten.
        #Generate one count: set Dk = Dk + 1.
        Dk[k] += 1
        #Eleven.
        #End loop over count j = 1, Nc.
    #Twelve.
    #Calculate weighted mean x of distribution Dk.
    w_mean = np.sum(Dk)/Nc
    #Thirteen.
    #For position j = mean/delta(mean) do hj = hj + 1.
    pos_j = w_mean / delta_mean
    hj[int(pos_j)] = hj[int(pos_j)] + 1
    #Fourteen.
    #End loop over distributions i = 1, Nd.
    
#Fifteen.
#Form the comulative distribution Hk(x).
otra_suma = 0
Hk = []
for i in range(Nh):
    otra_suma += hj[i]
    Hk.append(otra_suma)
    
#Sixteen.
#Find the points xl and xu where Hk(x) = 0.16 and = 0.84.
xl = 0
xu = 0
for i in range(len(Hk)):
    if(Hk[i] == 0.16):
        xl = hj[i]
    if(Hk[i] == 0.84):
        xu = hj[i]
        
#Seventeen.
#Report the lower bound uncertainty xtrue - xl and upper xu - xtrue.
lower = true_mean - xl
upper = xu - true_mean

means = []
for i in range(0,10):
    dist = np.random.poisson(3,100)
    means.append(np.sum(dist)/100)