#!/bin/bash

#
#
#Removes everything except for the lastname




for NAME in "Dr. Albing" "Ms. Johnson" "Mrs. Smith" "Mr. Jones"
do
  LASTNAME=${NAME##* }    # fill this in to extract the last name
  echo $LASTNAME
done
# output should be:
# Albing
# Johnson
# Smith
# Jones
