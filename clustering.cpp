//============================================================================
// Name        : star_clustering.cpp
// Author      : Shana Li, Jane Hsieh, Aidan KW
// Version     :
// Copyright   : Your copyright notice
// Description : K-Means clustering algorithm in C++
//============================================================================

#include <iostream>
#include <math.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

class Point {
private:
	double x;
	double y;
	Point *ClustCenter;

public: // The class for a point and their methods
	Point(double x, double y) {
		this->x = x;
		this->y = y;
	}

	// calculate the distance between this point and dest, based on the pythagorean theorem
	double distToPoint(Point dest) {
		double a = sqrt((this->x * this->x) + (this->y * this->y));
		double b = sqrt((dest.x * dest.x) + (dest.y * dest.y));
		return (sqrt(a * a + b * b));
	}

	double getx() { 
		return this->x; 
	}

	double gety() { 
		return this->y; 
	}

	// the corresponding center in which the point lies
	Point getClustCenter() { 
		return *(this->ClustCenter); 
	}

	void setClustCenter(Point newCenter) { 
		this->ClustCenter = &newCenter; 
	}
};

// Class for a determined cluster of points
class Cluster {
private:
	Point * center;
	vector<Point> points;

public:
	Cluster(Point *ctr) {
		this->center = ctr;
	}

	Point getClustCenter() {
		return *(this->center);
	}

	vector<Point> getPoints() {
		return this->points;
	}

	int getNumPoints() {
		return getPoints().size();
	}

	// add a point to the vector of points
	void addPoint(Point newPoint) {
		getPoints().push_back(newPoint);
	}

	// recenters the cluster, returns new center coordinate
};


class Map {
private:
	int totPoints;
	vector<Point> unsorted; // vector to hold all the points that don't have an assigned center yet 
	vector<Point> allCenters; // vector to hold all the centers of clusters

public:

	Map() {
		totPoints = 0;
	}

	int getTotPoints() {
		return this->totPoints;
	}

	vector<Point> getUnsorted() {
		return this->unsorted;
	}

	void addPoint(Point p) {

		// add a point to the unsorted vector
	}

	void addCenter(Point p) {

		// add a center point to the array of all centers
	}

	double getDist(Point a, Point b) {
		return a.distToPoint(b);
		// returns the distance between 2 points
	}
};

// analysis methods
class KMeans {
private:
	int k; // specified number of clusters
	int limit; // the iteration limit of the algorithm
	Point oldCenters[0]; // stores the previously calculated centers for comparison
	int changed; // whether or not the centers have changed - ending condition
	Map map; 

	void randCenters(int k) {

		// initializes the map so that random k points are set as initial clusters
	}

public:

	KMeans(Map map, int k, int limit) {

		if (k < 1) {
			cout << "K must be a positive integer!" << endl;
			exit(1);
		}

		this->map = map;
		this->k = k;
		this->limit = limit;
		
		randCenters(k);
	}

	void doCluster() {

		// iterate through all points on map, assign each point to cluster by closest distance to center
	}

	Point * reCenter() {
		return NULL;
		// calculate new centers based on average coordinates of all points in each cluster
	}

	int ifChanged() {
		return changed; // remember to update changed as recenter is done
		// return whether or not the centers have changed by comparing oldCenters[] and map->allCenters[]
	}
};



int main() {
	
	Map *map = new Map();
	KMeans *km = new KMeans(*map, 1, 5);

	Point *pt = new Point(0, 0);
	Point *pt2 = new Point(1, 1);
	cout << "The distance is " << pt->distToPoint(*pt2) << endl;
	return 0;

	// runs the algorithm
	// uses methods from KM, loops doCluster() and reCenter()
}
