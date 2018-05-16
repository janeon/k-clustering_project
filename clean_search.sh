#!/bin/sh
#run this with the SIM search file:

declare -a array=("|Gic|"  "|BiC|" "|GiG|" "|GiP|" "|EmG|" "|Sy1|" "|Sy2|" )

#Shell scripting doesn't like two spaces in a row
grep "|G  |" $1  | cut -f 3,5 -d "|" | sed '/|No Coord./d'

for element in "${array[@]}"
do
        grep $element $1 |
        cut -f 3,5 -d "|"|
        sed '/|No Coord./d'
done
