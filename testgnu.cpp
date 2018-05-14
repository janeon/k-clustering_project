// Demo of vector plot.
// Compile it with:
//   g++ -o example-vector example-vector.cc -lboost_iostreams -lboost_system -lboost_filesystem

#include <vector>
#include <cmath>
#include "gnuplot-iostream.h"

int main() {
	Gnuplot gp;
	// Create a script which can be manually fed into gnuplot later:
	//    Gnuplot gp(">script.gp");
	// Create script and also feed to gnuplot:
	//    Gnuplot gp("tee plot.gp | gnuplot -persist");
	// Or choose any of those options at runtime by setting the GNUPLOT_IOSTREAM_CMD
	// environment variable.

	// Gnuplot vectors (i.e. arrows) require four columns: (x,y,dx,dy)
	// Don't forget to put "\n" at the end of each line!
	gp << "set terminal postscript\n";
	gp << "set output \"hello.eps\"\n";
	gp << "plot cos(x)\n";
#ifdef _WIN32
	// For Windows, prompt for a keystroke before the Gnuplot object goes out of scope so that
	// the gnuplot window doesn't get closed.
	std::cout << "Press enter to exit." << std::endl;
	std::cin.get();
#endif
}
