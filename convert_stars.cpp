// Name        : starstopoints.cpp
// Author      : Shana Li, Jane Hsieh, Aidan KW
// Version     :
// Copyright   : Your copyright notice
// Description : Converts RA and Dec points to (x,y) 
//============================================================================

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

/* removes leading + */
string fix(string str){
	if (str.at(0) == '+')
		return str.erase(0,1);
	else
		return str;
}

/* Converts RA and Dec to (x,y)
 * Input: array of size 6
 * Output: line of two numbers, separated by a space, followed by a \n
 */
void convert(string (&array)[6]){
	int i = 0;
	try {
		float x0 = stof(fix (array[0]));
		float x1 = stof(fix (array[1]));
		float x2 = stof(fix (array[2]));	
		cout << x0 + x1/60 + x2/3600 << ' ';
		
		float y0 = stof(fix (array[3]));
		float y1 = stof(fix (array[4]));
		float y2 = stof(fix (array[5]));
		cout << y0 + y1/60 + y2/3600 << endl;

	} catch (const std::invalid_argument& ia) {
		std::cerr << "Invalid argument: " << ia.what() << '\n';
	}
	
}

int main(int argc, char** argv){
	string line;
	string delimiter = "|";
	ifstream myfile;
	myfile.open(argv[1]);
	
	/* Open file and read line by line  */
	if (myfile.is_open()){
		while (getline (myfile, line)){
			/* Print name of galaxy */
                        cout << line.substr(0, line.find(delimiter));
                        line = line.substr(line.find(delimiter)+ 1, line.size());
			
			/* Convert line into an array */
			string arr[6];
			int i = 0;
			stringstream ssin(line);

			while (ssin.good() && i < 6){
				ssin >> arr[i];
				i++;
			}
			convert(arr);
			//for(i = 0; i < 6; i++){
			//	cout << arr[i] << endl;
			//}		
		}
		myfile.close();
	}
	else cout << "Unable to open file";
	return 0;
}
