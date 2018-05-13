//============================================================================
// Name        : star_clustering.cpp
// Author      : Shana Li, Jane Hsieh, Aidan KW
// Version     :
// Copyright   : Your copyright notice
// Description : K-Means clustering algorithm in C++
//============================================================================

#include "clustering.h"
#include <tuple>
#include <string>
#include <cmath>
#include <iostream>
#include  <fstream>
using namespace std;

class Point {
private:
	double x;
	double y;
	string name;
public:
	bool clustered; // whether or not this point has a cluster yet
	Cluster *clust; // the cluster this point belongs in

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

	// calculate the distance between this point and another coordinate, based on the pythagorean theorem
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
		vector<Point*>::iterator position = find(points.begin(), points.end(), p);
		
		// erase if found
		if (position != points.end()) {
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


class Map {
    // how to use map:
    // first load in all the points with addPoint()
    // then make random centers with randCenters()
    // then assign all of them centers with sort()
private:
	vector<Point*> allPoints; // vector of all points on map

	// add a cluster with the given center
	void addCluster(Point *newcenter) {
		allClusters.push_back(new Cluster(newcenter->getx(), newcenter->gety()));
	}

	// puts point in the cluster it belongs
	void clusterize(Point *p) {
		// initialize nearest cluster arbitrary at the first cluster center in the list
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
		}
		else if (p->clust->centerx != nearest->centerx && p->clust->centery != nearest->centery) {
			// remove p from p's old cluster
			p->clust->removePoint(p);
			cout << "successfully remove" << endl;
			// add p to new cluster
			nearest->addPoint(p);
		}

		cout << "The point " << p->getx() << "," << p->gety() << " has the center " << p->clust->centerx << "," << p->clust->centery << endl;
	}

	// sort all points into clusters
	void sort() {
		for (const auto& point : allPoints) {
			Point *p = point;
			//cout << "clusterizing " << p->getx() << "," << p->gety() << endl;
			clusterize(p);
		}
	}

	// for initiation - assign k random centers that are 
	void randCenters(int k) {
		vector<Point*> centers; // store points that have already been selected
		for (int i = 0; i < k; i++) {
			srand(time(0)); // seed based on time for different randomness
			int r = rand() % allPoints.size(); // random int between 0 and size of all (0 included)
			Point *newcenter = allPoints.at(r); // get the selected item
			// check if it is already a center
			if (!centers.empty() && find(centers.begin(), centers.end(), newcenter) != centers.end()) { // if found
				i--; // generate again
			}
			else {
				// add point to centers
				centers.push_back(newcenter);
				addCluster(newcenter); // make a new cluster with the center coordinates
			}
		}
		// deallocate vector
		centers.clear();
		vector<Point*>().swap(centers);
	}                           

public:

	vector<Cluster*> allClusters; // vector to hold all the centers of clusters

	Map() {
		// add in all the points? add a method for this?
	}

	//testing
	void printcenters() {
		for (const auto& c : allClusters) {
			Cluster *clust = c;
            cout << "A center located at coordinate: " << c->centerx << "," << c->centery << endl;
		}
	}

	// add in the beginning: add all points
	void initiate(int k) {
		randCenters(k);
		printcenters();
		sort();
	}

	// add a point
	void addPoint(Point *p) {
		allPoints.push_back(p);
	}

	// reclusters based on new averaged centers of clusters, return whether the center has changed
	bool recluster() {

		bool changed = false; // initialize to unchanged centers

		// loop through all the centers
		for (const auto& c : allClusters) {
			Cluster *clust = c;
            // tuples store x, y coordinates of centers
			tuple<double, double> oldcenter = clust->recenter();
			tuple<double, double> newcenter = make_tuple(clust->centerx, clust->centery);
			cout << "old center: " << get<0>(oldcenter) << "," << get<1>(oldcenter) << "; new center: " << get<0>(newcenter) << "," << get<1>(newcenter) << endl;

			// if the coordinates are different, set changed to true
			if (get<0>(oldcenter) != get<0>(newcenter) || get<1>(oldcenter) != get<1>(newcenter)) {
				changed = true;
				cout << "center has changed." << endl;
			}
		}

		// reseort if changed
		if (changed == true) {
			cout << "centers have changed, re-sort." << endl;
			sort();
		}

		return changed;
	}
};

class KMeans {
    // analysis methods
private:
	int k; // specified number of clusters
	int limit; // the iteration limit of the algorithm
	vector<Point*> oldCenters; // stores the previously calculated centers for comparison
	bool changed; // whether or not the centers have changed - ending condition
	Map *map; 

	// add points
	void populate(string file) {
        ifstream infile (file);
        int a, b;
        while (infile >> a >> b)  {
            cout << "A data point: " << a << " " << b << endl;
            map->addPoint(new Point(a,b));
        }
        /*
        map->addPoint(new Point(0, 0));
		map->addPoint(new Point(4, 4));
		map->addPoint(new Point(0, 4));
		map->addPoint(new Point(4, 0));
		map->addPoint(new Point(5, 0));
		map->addPoint(new Point(7, 10));
		map->addPoint(new Point(-2, 3.5));
		map->addPoint(new Point(-5, -2));
		map->addPoint(new Point(3, -10));
        
        map->addPoint(new Point(-2,4));
        map->addPoint(new Point(-2,-4));
        map->addPoint(new Point(-8,-9));
        */
	}

	// initial clustering
	void firstCluster() {
		map->initiate(k);
	}

	// calculate new centers based on average coordinates of all points in each cluster, resort points
	bool recluster() {
		cout << "reclustering" << endl;
		return map->recluster();
	}

public:
	KMeans(Map *map, int k, int limit, string file) {

		if (k < 1) {
			cout << "K must be a positive integer!" << endl;
			exit(1);
		}
        
		this->map = map;
		this->k = k;
		this->limit = limit;
		changed = true;

		cout << "K = " << k << ", Iteration limit = " << limit << endl;
		
		populate(file); // add all the points
		firstCluster(); // set random clusters and sort
		doClustering(); // do the algorithm
        printClusters(); // outputs the final clustering to an output file named: _______
	}

	// loop the algorithm until centers don't change or the limit is hit
	void doClustering() {
		int i = 0; // counter for limit
		while (i < limit && changed == true) {
			cout << "Iteration " << i+1 << endl;
			changed = recluster();
			cout << "Changed:" << changed << endl;
			i++;
		}
        if (!changed) cout << "Clustering limit not reached but k-means converged" << endl;
        else cout << "K-means has not converged but clustering limit has been reached" << endl;
	}
    
    void printClusters() {
        ofstream file ("new_clusters.txt"); // name original file will need to be inserted
        if (file.is_open())  {
            for (const auto& c : map->allClusters) { // The center of each cluster starts with character c, and the coordinates  of the cluster
                    Cluster *clust = c;
                file << "C:" << c->centerx << " " << c->centery << endl;
            for (const auto&  point: c -> points) {
                file << point->getx() << " " << point->gety() <<  endl;
            }
        }
            file.close();
            // for () // The points follow the line with the cluster center, with no prefixes
    }
        else cout << "The file was not opened" << endl;
    }
};


int main() {
	
	int k = 4; // the number of clusters
    int limit = pow(4.0,9.0); // the iteration limit
    // So k-means is supposed to converge in a finite number of steps
    // (at most k^n) but as a sanity check that our program doesn't loop infinitely we set the iteration limit to k^n

	Map *map = new Map();
	KMeans *km = new KMeans(map, k, limit, "test");

    
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
