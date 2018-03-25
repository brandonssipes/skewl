#!/bin/bash

#read in a file line by line and use $(sed) to parse out the size and then echo to stdout

while read all; do
  echo $(sed -e 's/.*size=//' <<< $all | sed -e 's/,.*//')
done < size.log
