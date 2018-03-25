#!/bin/bash

#Read input file one line at a time and use substitutions to extract 
#the value of the size parameter from each line
#echo the number to stdou

while read all; do
  FIRST=${all##*size=}
  SECOND=${FIRST%%,*}
  echo $SECOND
done < size.log

