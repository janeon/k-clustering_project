#include <vector>
#include <utility>
#include "gnuplot-iostream.h"

int main() {
    std::vector<std::pair<double,double>> data;
    data.emplace_back(-2,-0.8);
    data.emplace_back(-1,-0.4);
    data.emplace_back(0,-0);
    data.emplace_back(1,0.4);
    data.emplace_back(1,0.8);
    float xmax = 10, xmin = -10, ymax = 10, ymin = -10;
    Gnuplot gp;
    gp << "set terminal postscript\n";
    gp << "set output \"hello.eps\"\n";
    gp << "plot ["<<xmin<<":"<<xmax<<"] ["<<ymin<<":"<<ymax<<"] '-' tit 'data'\n";
    gp.send1d(data);
    return 0;
}
