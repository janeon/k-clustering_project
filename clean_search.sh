#!/bin/sh
#run this with the SIM search file:

touch temp_galaxies.txt
touch temp_search.txt
grep "|G  " $1 > temp_galaxies.txt #gives us galaxies
cut -f 2,5 -d "|" temp_galaxies.txt > temp_search.txt #gives us the names and numbers
sed '/|No Coord./d' temp_search.txt #removes datapoints with no coordinates

rm temp_galaxies.txt
rm temp_search.txt
