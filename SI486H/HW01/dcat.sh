#!/bin/bash
#Input multiple file names
#print out dashes and then the filename
#followed by the file
#repeat for all files
#
for arg in "${@}"
do 
  echo "------------------------------------------------------${arg}" 
  cat "${arg}"
done
