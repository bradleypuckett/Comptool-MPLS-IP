import sys
import numpy as np
import matplotlib.pyplot as plt

assert len(sys.argv) == 3
inputfile = open(sys.argv[1], 'r')

x_axis = []
y_axis = []

for line in inputfile:
    try:
        a,b, c = line.split(" ")
        x_axis.append(float(a))
        y_axis.append(float(b))
    except ValueError:
        print(line)

x_axis = np.array(x_axis)
y_axis = np.array(y_axis)

fig, ax = plt.subplots()
fit_line = np.polyfit(x_axis, y_axis, deg=1)

#ax.plot(x_axis, fit_line[0] * x_axis + fit_line[1], color='red')
ax.scatter(x_axis,y_axis, s=1)
#ax.set_ylim(0,10000)

plt.ylabel("Lookup time (ns)")
plt.xlabel("Number of entries")
plt.grid(b=1)
plt.title(sys.argv[2])

fig.savefig('figure.png')
fig.show()