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
    lc=0 #added line count variable
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

# how many to work with?
FN=${1:-/dev/stdin} #if arg1 is not there then us stdin
SIZ=0
readup $FN
LFT=${SIZ}

# build the list
while ((LFT > 0))
do
    VAL=$((RANDOM % SIZ)) #removed $ signs b/c they're not needed in double parens
    insert $VAL
done

# display it
for ((i=0; i<SIZ; ++i)) #changed single parens to double parens (also changed i++ to ++i, it's faster)
do
    NDX=${NEWLIST[i]}
    echo ${bufr[$NDX]}
done
