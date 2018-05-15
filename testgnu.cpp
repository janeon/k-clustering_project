#include <vector>
#include <utility>
#include "gnuplot-iostream.h"
using namespace std;
int main() {
//    vector<pair<float,float>> data;
    vector<vector<float> > data;
    vector<float> myRow;
    myRow.push_back(-2);
    myRow.push_back(-0.8);
    myRow.push_back(-1);
    data.push_back(myRow);
    /*
    myRow.push_back(-1);
    myRow.push_back(-0.4);
    myRow.push_back(-1);
    data.push_back(myRow);
    myRow.push_back(0);
    myRow.push_back(0);
    myRow.push_back(-1);
    data.push_back(myRow);
    myRow.push_back(1);
    myRow.push_back(0.8);
    myRow.push_back(-1);
    data.push_back(myRow);
    
    
    vector<float> myRow2(0,-0);
    data.push_back(myRow2);
    vector<float> myRow3(1,0.4);
    data.push_back(myRow3);
    vector<float> myRow4(1,0.8);
    data.push_back(myRow4);
//     */
    float xmax = 5, xmin = -5, ymax = 5, ymin = -5;
    Gnuplot gp;
    gp << "set terminal postscript\n";
    gp << "set output \"hello.eps\"\n";
//    gp << "plot ["<<xmin<<":"<<xmax<<"] ["<<ymin<<":"<<ymax<<"] '-' tit 'data', '-' using 1:1:1 with points palette\n";
//    gp.send1d(data);
    gp << "set palette defined ( 0 \"green\", 1 \"blue\", 2 \"red\", 3 \"orange\" ) \n";
//    gp << "plot ["<<xmin<<":"<<xmax<<"] ["<<ymin<<":"<<ymax<<"] '-' tit '2nddata', '-' using 1:1:1 with points palette\n";
    gp << "plot 'test' using 1:2:2 with points palette\n"; // works when taking inputfiles with 2 columns
//    gp << " \n";
//    gp.send2d(data);  // but how to get 2 colums from c++ structures?
    return 0;
}
