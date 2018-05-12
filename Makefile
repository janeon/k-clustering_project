all: clustering

clustering: clustering.cpp
	g++  -std=c++11 -o clustering clustering.cpp
