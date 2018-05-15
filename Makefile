all: clustering 

clustering: clustering.cpp
	g++ -std=c++11 -o clustering clustering.cpp 
testgnu: testgnu.cpp
	g++ -std=c++11 -o testgnu testgnu.cpp -lboost_iostreams -lboost_system -lboost_filesystem

clean:
	-rm clustering testgnu
