//============================================================================
// Name        : star_clustering.cpp
// Author      : Shana Li, Jane Hsieh, Aidan KW
// Version     :
// Copyright   : Your copyright notice
// Description : K-Means clustering algorithm in C++
//============================================================================

#include <iostream>
#include <math.h>
using namespace std;

class Point {
private:
	double x;
	double y;
	string name;
	Point *ClustCenter;

public: // The class for a point and their methods
	Point(double x, double y, string name) {
		this->x = x;
		this->y = y;
		this->name = name;
	}

	// calculate the distance between this point and dest, based on the pythagorean theorem
	double distToPoint(Point dest) {
		double a = sqrt((this->x * this->x) + (this->y * this->y));
		double b = sqrt((dest.x * dest.x) + (dest.y * dest.y));
		return (sqrt(a*a + b * b));
	}
	double getx() { return this->x; }
	double gety() { return this->y; }
	Point getClustCenter() { return *(this->ClustCenter); }
	void setClustCenter(Point newCenter) { this->ClustCenter = &newCenter; }
};

// Class for a determined cluster of points
class Cluster {
private:
	Point * center;
	int numPoints;
public:
	Cluster(Point *ctr) {
		this->center = ctr;
	}

	Point getClustCenter() {
		return *(this->center);
	}

	int getNumPoints() {
		return this->numPoints;
	}
};


class Map {
private:
	int totPoints;
	Point *allPoints[0];
	int allCenters[];

public:

	Map() {
		totPoints = 0;
	}

	int getTotPoints() {
		return this->totPoints;
	}

	Point * getAllPoints() {
		return *(this->allPoints);
	}

	int * getAllCenters() {

		return this->allCenters;
	}

	void addPoint(Point p) {

		// add a point to the array of all points
	}

	void addCenter(Point p) {

		// add a center point to the array of all centers
	}

	double getDist(Point a, Point b) {
		return a.distToPoint(b);
		// returns the distance between 2 points
	}
};


class KM {
private:
	int k; // specified number of clusters
	int limit; // the iteration limit of the algorithm
	Point oldCenters[0]; // stores the previously calculated centers for comparison
	int changed;
	void randCenters(int k) {

		// initializes the map so that random k points are set as initial clusters
	}

public:

	KM(int k, int limit) {

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
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	Point *origin = new Point(1, 2, "origin");
	Point *pt = new Point(1, 2, "first point");
	cout << "The point's x-coord is" << pt->getx() << endl;
	return 0;

	// runs the algorithm
	// uses methods from KM, loops doCluster() and reCenter()
}
