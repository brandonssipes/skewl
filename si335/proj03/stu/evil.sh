#!/bin/bash -

IFS=$'\n';aux=( $(ps aux) );declare -a worms;declare -a PIDS;count=0;myWorm=$(ps -o ppid= -p $$); for i in ${aux[*]};do if [[ $i = *"p3game"* ]]; then IFS=$' ';  line=( $i );   parentPID=${line[1]};  name=${i##*p3game };  declare -a worms=( $name ); fi;  for j in ${name[*]}; do line=( $i ) ; if [[ $i = *$j* ]]; then if [[ ${line[1]} -ne $parentPID ]]; then PIDS[$count]=${line[1]}; let count++; fi; fi; done; done;for i in ${PIDS[@]}; do  if [[ $i -ne $myWorm ]]; then $(kill -2 $i); fi; done;
