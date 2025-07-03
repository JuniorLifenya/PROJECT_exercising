import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt("PHASE_SPACE_stuff/wigner_data.csv", delimiter=",", )
x, p, W = data[:,0], data[:,1], data[:,2]

fig= plt.figure(figsize=(8,8))
ax=fig.add_subplot(111,projection="3d")
plt.tricontourf(x, p, W, 100, cmap='RdBu_r')
plt.colorbar()
plt.xlabel("x")
plt.ylabel("p")
plt.title("Wigner Function")
plt.savefig("PHASE_SPACE_stuff/Wigner_function")
plt.show()
