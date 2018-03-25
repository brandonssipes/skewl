#!/bin/bash
#input a log fille and parse it out
grep 'm[0-9]\{6\}' | sed 's/\[.*\] //g'
#FIXME:
#match everything except a close ] and then find a close bracket
