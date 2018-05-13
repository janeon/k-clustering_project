//============================================================================
// Name        : star_clustering.cpp
// Author      : Shana Li, Jane Hsieh, Aidan KW
// Version     :
// Copyright   : Your copyright notice
// Description : K-Means clustering algorithm in C++
//============================================================================

#include "clustering.h"
using namespace std;

class Point {
private:
	double x;
	double y;
	string name;
public:

	bool clustered; // whether or not this point has a cluster yet
	Cluster *clust; // the corresponding cluster

	Point(double x, double y) {
		this->x = x;
		this->y = y;
		clustered = false;
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

	// calculate the distance between this point and a coordinate, based on the pythagorean theorem
	double dist(double destx, double desty) {
		double dx = (destx - this->x) * (destx - this->x);
		double dy = (desty - this->y) * (desty - this->y);
		return (sqrt(dx + dy));
	}

	// give the point a cluster
	void setClust(Cluster *clust) {
		clustered = true;
		this->clust = clust;
	}
};

// Class for a determined cluster of points
class Cluster {
public:

	// collection of all the points in the cluster
	vector<Point*> points;

	// coordinates of cluster center
	double centerx;
	double centery;

	Cluster(double centerx, double centery) {
		this->centerx = centerx;
		this->centery = centery;
	}

	// returns coordinates of center as tuple
	tuple<double, double> getCoords() {
		return make_tuple(centerx, centery);
	}

	int numPoints() {
		return points.size();
	}

	// add a point to the vector of points, set parameters of the point
	void addPoint(Point *newPoint) {
		points.push_back(newPoint);
		newPoint->setClust(this);
	}

	// remove a point
	void removePoint(Point *p) {
		// find its position in points
		cout << "asdf" << endl;
		vector<Point*>::iterator position = find(points.begin(), points.end(), p);
		
		// erase if found
		if (position != points.end()) {
			cout << "found" << endl;
			points.erase(position);
		}

	}

	// recenters the cluster, returns old center coordinate in tuple
	tuple<double, double> recenter() {
		
		// remember old center
		tuple<double, double> old = getCoords();
		
		// average of x and y 
		double xavg, yavg = 0;

		// iterate and add coordinates
		for (const auto& a : points) {
			Point p = *a;
			xavg += p.getx();
			yavg += p.gety();
		}                                                         

		// divide by number of points for average value
		xavg = xavg / numPoints();
		yavg = yavg / numPoints();

		// set center to new center
		this->centerx = xavg;
		this->centery = yavg;

		// return tuple of coordinates
		return old;
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
		allClusters.push_back(new Cluster(newcenter->getx(), newcenter->gety()));
	}

	// for initiation - assign k random centers that are 
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
			cout << "clusterizing " << p->getx() << "," << p->gety() << endl;
			clusterize(p);
			
			unsorted.erase(unsorted.begin() + 0);
		}
	}

public:

	int totPoints;
	vector<Cluster*> allClusters; // vector to hold all the centers of clusters

	Map() {
		totPoints = 0;
	}

	//testing
	void printcenters() {
		for (const auto& c : allClusters) {
			Cluster *clust = c;
			cout << "A center is at " << c->centerx << "," << c->centery << endl;
		}
	}

	// add in the beginning: add all points
	void initiate(int k) {

		randCenters(k);
		printcenters();
		sort();
	}

	// add a point to the unsorted vector
	void addPoint(Point *p) {
		unsorted.push_back(p);
		totPoints++;
	}

	// puts point in the cluster it belongs
	void clusterize(Point *p) {
		// initialize nearest cluster
		Cluster *nearest = allClusters.at(0);

		// iterate through allCenters and compare distances
		for (const auto& c : allClusters) {
			Cluster *clust = c;
			//cout << "nearest is at " << clust->centerx << "," << clust->centery << "with distance " << p->dist(clust->centerx, clust->centery) << endl;
			if (p->dist(clust->centerx, clust->centery) < p->dist(nearest->centerx, nearest->centery)) {
				nearest = clust;
			}
		}

		// change things only if p's current cluster is not the nearest or the point did not have a cluster
		if (p->clustered == false) {
			nearest->addPoint(p);
		} else if (p->clust->centerx != nearest->centerx && p->clust->centery != nearest->centery) {

			cout << "setting center to nearest" << endl;
			// remove p from p's old cluster
			p->clust->removePoint(p);
			cout << "successfully remove" << endl;
			// add p to new cluster
			nearest->addPoint(p);
		}

		cout << "The point " << p->getx() << "," << p->gety() << " has the center " << p->clust->centerx << "," << p->clust->centery << endl;
	}
};

// analysis methods
class KMeans {
private:
	int k; // specified number of clusters
	int limit; // the iteration limit of the algorithm
	vector<Point*> oldCenters; // stores the previously calculated centers for comparison
	int changed; // whether or not the centers have changed - ending condition
	Map *map; 

	void randCenters(int k) {

		// initializes the map so that random k points are set as initial clusters
	}

public:

	KMeans(Map *map, int k, int limit) {

		if (k < 1) {
			cout << "K must be a positive integer!" << endl;
			exit(1);
		}

		this->map = map;
		this->k = k;
		this->limit = limit;
		
		randCenters(k);
	}

	// add points
	void populate() {

		map->addPoint(new Point(0, 0));
		map->addPoint(new Point(4, 4));
		map->addPoint(new Point(0, 4));
		map->addPoint(new Point(4, 0));
		map->addPoint(new Point(5, 0));
		map->addPoint(new Point(7, 10));
		map->addPoint(new Point(-2, 3.5));
		map->addPoint(new Point(-5, -2));
		map->addPoint(new Point(3, -10));
	}

	// initial clustering
	void firstCluster() {
		map->initiate(k);
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
	KMeans *km = new KMeans(map, k, 5);

	km->populate();
	km->firstCluster();
	

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
