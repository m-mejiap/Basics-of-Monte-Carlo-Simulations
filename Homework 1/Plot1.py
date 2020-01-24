import numpy as np
import matplotlib.pylab as plt

data = np.genfromtxt("averages.dat",delimiter=",")

plt.figure()
plt.plot(data[:,0],data[:,1],color="grey",marker=".")
plt.xlabel("Number needles used in the simulations. (n)")
plt.ylabel("Average error.")
plt.title("Graph 1: Average error vs. Number needles.")
plt.savefig("plot1.png")