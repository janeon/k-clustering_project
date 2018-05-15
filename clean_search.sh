#!/bin/sh
#run this with the SIM search file:


grep "|G  " $1      |  #gives us galaxies
cut -f 2,5 -d "|"   |  #gives us the names and numbers
sed '/|No Coord./d'    #removes datapoints with no coordinates
