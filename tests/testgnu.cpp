#include <vector>
#include "gnuplot-iostream.h"
using namespace std;
int main() {
    /*
    float frame[4][4][6];
    for (int n=0; n<4; n++)
    {
        for (int m=0; m<4; m++)
        {
            for (int o=0; o>-3; o--) {
                
                frame[n][m][o]=n+m+o;
            }
            
        }
    }
     
    
    frame[2][2][1]= 1;
    frame[1][1][5]= 5;
    frame[3][3][5]= 5;
    */
    float frame[3][3][3]=
    {
        {
            {11, 2, 1},
            {14, 5, 1},
            {17, 8, 1}
        },
        {
            {21, 1, 2},
            {24, 5, 2},
            {27, 8, 2}
        },
        {
            {31, 3, 3},
            {34, 3, 3},
            {37, 8, 3}
        },
    };
    Gnuplot gp;
    gp << "set terminal postscript\n";
    gp << "set output \"hello.eps\"\n";
    gp << "set palette defined ( 0 \"green\", 1 \"blue\", 2 \"red\", 3 \"orange\" ) \n";
    gp << "set autoscale fix\n";
    gp << "plot '-' using 1:2:3 with points palette title 'trial"<< to_string(1) <<"' \n";
    gp.send2d(frame);
    gp << "plot '-' using 1:2:3 with points palette title 'trial" << to_string(2)<< "' \n";
    gp.send2d(frame);
    gp.flush();
    /*
//    vector<pair<float,float>> data;
    vector<vector<pair<double, int>>> data;
    vector<pair<double,int>> element;
    element.push_back(make_pair(0.0, 0));
    data.push_back(element);
    
//    data[1][1].push_back(make_pair(1, 0));
//    data[0][1].push_back(make_pair(1, 0));
//    data[1][0].push_back(make_pair(1, 0));
    
    vector<float> myx;
    vector<float> myy;
    vector<float> myz;
    myx.push_back(-2);
    myy.push_back(-0.8);
    myz.push_back(-1);
    data.push_back(myx);
    data.push_back(myy);
    data.push_back(myz);
    
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
     
    float xmax = 5, xmin = -5, ymax = 5, ymin = -5;
    Gnuplot gp;
    gp << "set terminal postscript\n";
    gp << "set output \"hello.eps\"\n";
//    gp << "plot ["<<xmin<<":"<<xmax<<"] ["<<ymin<<":"<<ymax<<"] '-' tit 'data', '-' using 1:1:1 with points palette\n";
//    gp.send1d(data);
    gp << "set palette defined ( 0 \"green\", 1 \"blue\", 2 \"red\", 3 \"orange\" ) \n";
    gp << "plot ["<<xmin<<":"<<xmax<<"] ["<<ymin<<":"<<ymax<<"] '-' tit '2nddata', '-' using 1:1 with points palette\n";
//    gp << "plot 'test' using 1:2:2 with points palette\n"; // works when taking inputfiles with 2 columns
//    gp << " \n";
    gp.send2d(data);  // but how to get 2 colums from c++ structures?
     */
    return 0;
}
