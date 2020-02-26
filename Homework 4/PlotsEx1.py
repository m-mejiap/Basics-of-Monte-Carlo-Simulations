import numpy as np
import matplotlib.pylab as plt

data = np.genfromtxt("data.dat",delimiter=",")

plt.figure()
plt.plot(data[:,0],data[:,1],color="grey",marker=".")
plt.xlabel("ΔEmax.")
plt.ylabel("Rrms.")
plt.title("Graph 1:  Rrms as a function of ΔEmax.")
plt.savefig("plot1.png")

data2 = np.genfromtxt("data2.dat",delimiter=",")

plt.figure()
plt.plot(data2[:,0],data2[:,1],color="grey",marker=".")
plt.xscale('log')
plt.yscale('log')
plt.xlabel("N_points.")
plt.ylabel("Rrms.")
plt.title("Graph 2:  Rrms as a function of N_points in log scale.")
plt.savefig("plot2.png")