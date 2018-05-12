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
#include <tuple>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <cstdlib>
using namespace std;

class Point {
private:
	double x;
	double y;
	string name;
public:
	Point * ClustCenter; // the corresponding center for the cluster in which the point lies
	
	Point(double x, double y) {
		this->x = x;
		this->y = y;
	}

	string getName() {
		return this->name;
	}

	double getx() {
		return this->x;
	}

	double gety() {
		return this->y;
	}

	// calculate the distance between this point and dest, based on the pythagorean theorem
	double distToPoint(Point *dest) {
		double distx = (dest->x - this->x) * (dest->x - this->x);
		double disty = (dest->y - this->y) * (dest->y - this->y);
		return (sqrt(distx + disty));
	}

	void setClustCenter(Point *newCenter) { 
		this->ClustCenter = newCenter; 
	}
};

// Class for a determined cluster of points
class Cluster {
private:
	Point * center;
	vector<Point*> points;

public:
	Cluster(Point *ctr) {
		addPoint(ctr);
		this->center = ctr;
	}

	int numPoints() {
		return points.size();
	}

	// add a point to the vector of points
	void addPoint(Point *newPoint) {
		points.push_back(newPoint);
	}

	// recenters the cluster, returns old center coordinate
	tuple<double, double> recenter() {
		// average of x and y 
		double xavg, yavg = 0;
		cout << numPoints() << endl;

		// iterate and add coordinates
		for (const auto& a : points) {
			Point p = *a;
			xavg += p.getx();
			yavg += p.gety();
		}                                                         

		// divide by number of points for average value
		xavg = xavg / numPoints();
		yavg = yavg / numPoints();

		// return tuple of coordinates
		return make_tuple(xavg, yavg);
	}
};

// how to use map:
// first load in all the points with addPoint()
// then make random centers with randCenters()
// then assign all of them centers with sort()
class Map {
private:
	vector<Point*> unsorted; // vector to hold all the points that don't have an assigned center yet 

	// add a cluster with the given center
	void addCluster(Point *newcenter) {
		allCenters.push_back(newcenter);
		new Cluster(newcenter);
	}

	// for initiation - assign k random centers
	void randCenters(int k) {
		// start with all points in unsorted
		// choose k random ints out of the size of unsorted
		// after each iteration, remove the point at the selected index from unsorted and add to allCenters
		for (int i = 0; i < k; i++) {
			srand(time(0)); // initialize rng
			int r = rand() % unsorted.size(); // random int between 0 and size of unsorted (0 included)
											  // get the selected item
			Point *newcenter = unsorted.at(r);
			addCluster(newcenter); // make a new cluster
			unsorted.erase(unsorted.begin() + r); // erase the item from unsorted
		}
	}

	// for intiation - put everything left in unsorted in clusters
	void sort() {
		// loop through unsorted until it is empty
		while (!unsorted.empty()) {
			Point *p = unsorted.at(0);
			cout << "p is at " << p->getx() << "," << p->gety() << endl;
			clusterize(p);
			
			unsorted.erase(unsorted.begin() + 0);
		}
	}
public:

	int totPoints;
	vector<Point*> allCenters; // vector to hold all the centers of clusters

	Map() {
		totPoints = 0;
	}

	// add in the beginning: add all points
	void initiate(int k) {

		randCenters(k);
		sort();
	}

	// testing
	void printcenters() {
		for (const auto& c : allCenters) {
			Point *cent = c;
			cout << "A center is " << c->getx() << "," << c->gety() << endl;
		}
	}

	// add a point to the unsorted vector
	void addPoint(Point *p) {
		unsorted.push_back(p);
		totPoints++;
	}

	// returns the distance between 2 points
	double getDist(Point *a, Point *b) {
		return a->distToPoint(b);
	}

	// puts point in the cluster it belongs
	void clusterize(Point *p) {
		Point *mincent = allCenters.at(0); // center (in allCenters) that has the minimum distance to p - initialize
		// iterate through allCenters
		for (const auto& c : allCenters) {
			Point *cent = c;
			cout << "cent is at " << cent->getx() << "," << cent->gety() << "with distance " << getDist(p, cent) << endl;
			if (getDist(p, cent) < getDist(p, mincent)) {
				cout << "setting center to cent" << endl;
				mincent = cent;
			}
		}
		// put the point in the cluster and set the point's variables
		p->setClustCenter(mincent);
		mincent->ClustCenter = p;

		cout << "The point " << p->getx() << "," << p->gety() << " has the center " << p->ClustCenter->getx() << "," << p->ClustCenter->gety() << endl;
	}
};

// analysis methods
class KMeans {
private:
	int k; // specified number of clusters
	int limit; // the iteration limit of the algorithm
	vector<Point*> oldCenters; // stores the previously calculated centers for comparison
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
	
	int k = 2;

	Map *map = new Map();
	KMeans *km = new KMeans(*map, k, 5);

	Point *a = new Point(0, 0);
	Point *b = new Point(4, 4);
	Point *c = new Point(0, 4);
	Point *d = new Point(4, 0);

	map->addPoint(a);
	map->addPoint(b);
	map->addPoint(c);
	map->addPoint(d);
 
	map->initiate(k);
	map->printcenters();

	/*
	Cluster *cluster = new Cluster(a);
	cluster->addPoint(b);
	cluster->addPoint(c);
	cluster->addPoint(d);

	// coordinates of new center
	tuple<double, double> newCenter = cluster->recenter();
	cout << "new center coordinate is " << get<0>(newCenter) << "," << get<1>(newCenter) << endl;
	*/

	return 0;

	// runs the algorithm
	// uses methods from KM, loops doCluster() and reCenter()
}
