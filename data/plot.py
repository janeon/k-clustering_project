# Import the necessary packages and modules
import matplotlib.pyplot as plt
import numpy as np
from sklearn.datasets.samples_generator import make_blobs

samples = input("Enter sample size: ")
centers = input("Enter desired number of centers: ")
filename = str(samples)
filename += "_"+str(centers)
filename += ".txt"
textfile = open(filename, 'r')

points = []
for line in textfile:
    line = line.split()
    x = float(line[0])
    y = float(line[1])
    points.append([x,y])
data = np.asarray(points)
# print(data)
plt.scatter(data[:, 0], data[:, 1], s=5);

# Show the plot
plt.show()
