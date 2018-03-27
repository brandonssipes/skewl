#!/bin/bash

# BFMI shuffle of the lines of a file:
# count the # of lines as you read it in
# generate an array of random numbers
# print the lines in that random order

# insert the new value at end of list if it's unique
function insert ()
{
    NEWVAL=$1
    found=0
    LLEN=$((SIZ-LFT))
    for ((i=0; i<LLEN; i++))
    do
	if (("${NEWLIST[$i]}" == $NEWVAL))
	then
	    found=1
	    break
	fi
    done
    if ((found == 0))
    then
	NEWLIST[$i]=$NEWVAL
	LFT=$((LFT-1))
    fi

} # insert

function readup ()
{
    lc=0
    while read aline
    do
	bufr[$lc]="$aline"
	lc=$((lc+1))
    done < $1 #better reading in from argument
    SIZ=$lc
}

function command_not_found_handle ()
{
    $0 "${@}" x.x
}

# how many lines to work with?
FN=${1:-~/input.txt} #you do not want quotes around this string b/c we want that substitution
SIZ=0
readup $FN
LFT=${SIZ}

# build the list
while ((LFT > 0))
do
    VAL=$((RANDOM % SIZ))
    insert $VAL
done

# display it
for ((i=0; i<SIZ; ++i)) #added double parens and change i++ to ++i
do
    NDX=${NEWLIST[i]}
    echo ${bufr[$NDX]}
done
