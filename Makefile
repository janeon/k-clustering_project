all: clustering

clustering: clustering.cpp
	g++ -o clustering clustering.cpp
