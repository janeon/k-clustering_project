# K-Means Clustering for Astronomical Objects
Shana Li, Jane Hsieh, Aidan Kidder-Wolff

## Summary:
A program that runs the k-means clustering algorithm on a collection of points in space (currently for x-y coordinates) and puts them in k clusters, each with a specified center. The program runs the reclusters and changes centroids until the centers have been stabilized or until the maximum number of iterations has been reached. Coordinates are specific to the x-y approximation of Right Ascension and Declination of astronomical objects.

## Pseudocode of the k-means algorithm 
```
Inputs: integer k indicating the number of desired centers and a set of points to be clustered
Procedure: 
The algorithm begins by randomly assigning k points from the input as initial centeroids
While iteration count and convergence have not been reached: 
    Each point is assigned to its closest centroid
    For each cluster
        Average coordinate of all points in cluster is calculated and assigned to be the new centroid of this cluster
    If coordinates of centroids have not changed or if the iteration limit has been reached, the loop terminates
    Otherwise continue reclustering 

```

While k-means clustering can be used for a multitude of purposes, our intention for this project is to determine clusters of stars and galaxies given their coordinates in the sky. Star and galaxy clustering are natural phenomena that has been investigated using numerous scientific tools and methods, but without astronomical instrumentation, means to measure any other physical quality of spacial objects, or years of knowledge in astronomy, k-means clustering is a computationally cheap, statistical way of obtaining this information to some degree of accuracy.

## Vital Files Included:
* clean_search.sh - a shell script to filter out the relevant galaxy data from an unfiltered [SIMBAD](http://simbad.u-strasbg.fr/simbad/sim-fid) search. 
* convert.cpp - a C++ program to convert RA and Dec coordinates to x-y coordinates without scaling.
* clustering.cpp - a C++ program that runs the [elbow method](https://en.wikipedia.org/wiki/Elbow_method_(clustering)) to determine an optimal k for a data set, runs K-means with a specified k value, and plots the clustering results.
* Makefile - compiles and links convert.cpp and clustering.cpp. 
* Data (folder) - a collection of data files that we tested on.
* Logs (folder) - output logs of important clustering runs.
* Plots (folder) - images of plots of K-means clustering on different astronomical data.
* Not included: postscript plots grow too large in size for GitHub and has been instead been moved to the Google Drive folder https://drive.google.com/drive/folders/17xYjGFwqIHbaeEuE5M2Bb-FxztzD2qDG?usp=sharing 
Which is accessible by all Oberlin College accounts
## How to use this program:
### Cleaning Data
After downloading unfiltered data from the [SIMBAD catalogue](http://simbad.u-strasbg.fr/simbad/sim-fid) in ASCII format, run the shell script clean_search.sh on it and pipe it to another file to filter out only the coordinates of galaxy objects:
```
bash clean_search.sh < filename > outfile
```

### Converting Coordinates
Using the file from the previous step, make and run convert and pipe it to another file to translate the RA and Dec coordinates to x-y coordinates:
```
make
./convert filename > outfile
```
The clustering program scales RA and Dec, so this step does not scale the coordinates, only translates them to single numbers:

For RA:
```
04h 05m 38s
```
The minute value is 1/60 of the hour, and the second value is 1/60 of the minute. I'm thinking doing this to represent them as digits so the calculations work:
```
4 + 5*1/60 + 38*1/3600 hours
```
In the actual clustering, we further convert this to degrees through multiplying it by 360/24
```
(360/24) * (4 + 5*1/60 + 38*1/3600) degrees
```

The Dec is similar, but in degrees, arcminutes, and arcseconds. 60 arcmins in a degree, and 60 arcsecs in an arcmin.
```
48º 50' 2" becomes 48+50*1/60 + 2*1/3600 degrees 
```
A source for conversion: 
http://www.skyandtelescope.com/astronomy-resources/what-are-celestial-coordinates/

### Using the Elbow Method to Determine an Optimal K Value
Make and run clustering on the file with converted coordinates with the -e flag to run the Elbow method on a range of k values to determine the best one to use. 
```
./clustering -e
```
The program will ask for a file to run on, which will be the input filename.

The range of k can be changed in the Elbow class of clustering.cpp. The elbow method outputs each k value with the resulting average distance between each point and its corresponding cluster center. For a strongly clustered data set, there should be an "elbow point" where the average distance stops decreasing greatly and starts plateauing. The elbow point is the optimal k value to use. For more evenly distributed data, the average distance will decrease exponentially, and a more intuitive k should be used after looking at the coordinate plots first.

### Running K-means Clustering and Plotting Results
After determining a suitable k value, run clustering normally without any flags:
```
./clustering
```
The program will prompt for an input filename, and then the value of k to use. The populate() method in the KMeans class takes in the coordinates from the text file, and the x coordinate is multiplied by 360/24 to scale it - if this is not desired, remove the multiplier to use coordinates directly from the file.

Each coordinate in the input file is assigned to a Point object. In the beginning, the coordinates of k random Points are assigned as the initial centers around which to cluster. The program's main() method generates a KMeans object, which automatically runs the algorithm given k (the number of clusters), and the iteration limit (maximum number of times to re-determine clusters). To change the iteration limit, edit the first two lines of main() that initialize the variables. K-means will always converge with a k^n limit.

To plot, run the command 
``` 
./cluster_plotting
```
And input the same filename and k value as in the prompt of clustering. Plotting uses the gnuplot and gnuplot-iostream add-ons, which outputs final vector images in Postscript format. With astronomical data sets, this takes very long, and the time increases exponentially with n, this is why only the final frame is plotted. Keep this in mind as larger data sets are used. 
