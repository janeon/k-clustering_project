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
    int num_u = 4, shift = 10, num_v_each = 10;
    vector<vector<float> > x_pts(num_u);
    vector<vector<float> > y_pts(num_u);
    vector<vector<float> > z_pts(num_u);
    for(int u = 0; u < num_u; u++) {
        x_pts[u].resize(num_v_each);
        y_pts[u].resize(num_v_each);
        z_pts[u].resize(num_v_each);
        for(int v=0; v < num_v_each; v++) {
            x_pts[u][v] = u*v;
            y_pts[u][v] = u*v;
            z_pts[u][v] = 1;
        }
    }
    Gnuplot gp;
    gp << "set terminal postscript\n";
    gp << "set output \"hello.eps\"\n";
    gp << "set palette defined ( 0 \"green\", 1 \"blue\", 2 \"red\", 3 \"orange\" ) \n";
    gp << "set autoscale fix\n";
    gp << "plot '-' using 1:2:3 with points palette title 'trial"<< to_string(1) <<"' \n";
    gp.send2d(boost::make_tuple(x_pts, y_pts, z_pts));

    for(int u = 0; u < num_u; u++) {
        for(int v=0; v < num_v_each; v++) {
            x_pts[u][v] = u*v;
            y_pts[u][v] = u*v;
            z_pts[u][v] = u;
        }
    }
    gp << "plot '-' using 1:2:3 with points palette title 'trial 2"<< to_string(1) <<"' \n";
    gp.send2d(boost::make_tuple(x_pts, y_pts, z_pts));
//    gp << "plot '-' using 1:2:3 with points palette title 'trial" << to_string(2)<< "' \n";
//    gp.send2d(frame);
    gp.flush();
    /*
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
