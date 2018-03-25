#!/bin/bash







VAR="String Of Pearls"

#
# do some scripting so that the output looks like this:
# S t r i n g   O f   P e a r l s 
#
for ((i=0; i<${#VAR}; ++i))
do
    echo -n "${VAR:$i:1} "
done
echo
