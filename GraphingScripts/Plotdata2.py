import sys
import numpy as np
import matplotlib.pyplot as plt

assert len(sys.argv) == 3
inputfile = open(sys.argv[1], 'r')

x_axis = []
y_axis = []
y2_axis = []



for line in inputfile:
    try:
        a,b,c = line.split(" ")
        x_axis.append(float(a))
        y_axis.append(float(b))
        y2_axis.append(float(c))

    except ValueError:
        print(line)

x_axis = np.array(x_axis)
y_axis = np.array(y_axis)
y2_axis = np.array(y2_axis)

fig, ax = plt.subplots(2, sharex=True)
ax[0].scatter(x_axis,y_axis, s=1)
ax[1].plot(x_axis, y2_axis)

ax[0].set_ylabel("Lookup time (ns)")
ax[1].set_ylabel("Load factor")

plt.xlabel("Number of entries")

ax[0].grid(b=1)
ax[1].grid(b=1)
ax[0].set_title(sys.argv[2])

ax[0].set_ylim(0,1500)


fig.savefig('figure.png')
fig.show()