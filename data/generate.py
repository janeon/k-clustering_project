# Import the necessary packages and modules
import matplotlib.pyplot as plt
import numpy as np
from sklearn.datasets.samples_generator import make_blobs
samples = 300
centers  = 4

samples = input("Enter sample size: ")
centers = input("Enter desired number of centers: ")
filename = str(samples)
filename += "_"+str(centers)
filename += ".txt"

X, y_true = make_blobs(n_samples = int(samples),
                       centers = int(centers),
                       cluster_std = 0.60,
                       random_state = 0)

with open(filename, "w") as out_file:
    for point in X:
        point = point.tolist()
        line = str(point[0])+" "+str(point[1])
        out_file.write(line)
        out_file.write("\n")
plt.scatter(X[:, 0], X[:, 1])
plt.show()