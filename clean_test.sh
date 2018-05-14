#!/bin/sh

#types of galaxies we want to work with
array=("|G  |"  "|Gic|" "|BiC|" "|GiG|" "|GiP|" "|HzG|" "|rG |" "|H2G|" "|LSB|" "|EmG|" "|SBG|" "|bCG|" "|SyG|" "|Sy1|" "|Sy2|" )

for element in ${array[@]}
do
	grep $element $1
done

//cut -f 5 -d "|" galaxies.txt gives us the numbers
