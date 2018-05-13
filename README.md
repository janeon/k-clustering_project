# K-Means Clustering for Astronomical Objects
Shana Li, Jane Hsieh, Aidan Kidder-Wolff

## Summary:
A program that runs the k-means clustering algorithm on a collection of points in space (currently for x-y coordinates) and puts them in k clusters, each with a specified center. The program runs the k-means algorithm until the centers have been stabilized or until the maximum number of iterations has been reached.

The k-means algorithm is as follows:
```
Inputs: integer k indicating the number of desired centers and a set of points to be clustered
Procedure: The algorithm begins by randomly assigning k coordinates as centers for the set.
For the next iteration rounds, 
    The algorithm first assigns each point to one of the k cluster centers
    For each cluster, the average coordinate of points assigned to a center is calculated, this average becomes the new center
    After calculating average centers, if coordinates of centers have not changed, then the iterations terminate, otherwise program continues to recenter its clusters   

```

While k-means clustering can be used for a multitude of purposes, our intention for this project is to determine clusters of stars and galaxies given their coordinates in the sky. Star and galaxy clustering are natural phenomena that has been investigated using numerous scientific tools and methods, but without astronomical instrumentation, means to measure any other physical quality of spacial objects, or years of knowledge in astronomy, k-means clustering is a computationally cheap, statistical way of obtaining this information to some degree of accuracy.

## How to use this program:
The program's main() method generates a KMeans object, which automatically runs the algorithm given k (the number of clusters), and the iteration limit (maximum number of times to re-determine clusters). To change these variables, edit the first two lines of the method that initialize the variables.

## Next steps:
* Support for RA and Dec coordinates. They have to do with angles, but in plotting we will just approximate them to be on a flat plane, and the calculations (distances etc.) work the same way. The main thing of concern is that the format for these are different:

For RA:
```
04h 05m 38s
```
The minute value is 1/60 of the hour, and the second value is 1/60 of the minute. I'm thinking doing this to represent them as digits so the calculations work:
```
4 + 5*1/60 + 38*1/3600
```
I think this would be the best way, unless there's a better one?

The Dec is similar, but in degrees, arcminutes, and arcseconds. I think we can do the same thing; the two don't necessarily have to be in the same units, right?

* Parse data files and load points. There are some good stars/galaxies catalogues online, for some of them you can filter out by the type of object, and then find some way to download them. In the Map/Kmeans class, make a method or something to load in the info and make Points.

* Plotting. Separate plot for each iteration (to look at the progress), with each cluster having their own color. Some library to do this?

* Post-k-means processing to determine the most concentrated areas and sort out the objects that belong in a cluster and the ones that don't. Maybe we'll get there?
