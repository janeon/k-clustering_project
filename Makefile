all: clustering convert

convert: convert.cpp
	g++ -std=c++11 -o convert convert.cpp
clustering: clustering.cpp
	g++ -std=c++11 -o clustering clustering.cpp -lboost_iostreams -lboost_system -lboost_filesystem

clean:
	-rm clustering convert
