#!/bin/bash -

IFS=$'\n';aux=( $(ps aux) );ps=( $(ps -o pid,ppid) );declare -a worms;declare -a PIDS;count=0;for i in ${aux[*]};do   if [[ $i -ne *"p3game"* ]]; then    if [[ $i = *"evil"* ]]; then   IFS=$' ';   line=( $i );       myPID=${line[1]};    myWorm=$(ps -o ppid= -p $myPID);    fi;   fi ;  if [[ $i = *"p3game"* ]]; then     IFS=$' ';  line=( $i );   parentPID=${line[1]};  name=${i##*p3game };  declare -a worms=( $name ); fi;  for j in ${name[*]}; do line=( $i ) ; if [[ $i = *$j* ]]; then if [[ ${line[1]} -ne $parentPID ]]; then PIDS[$count]=${line[1]}; let count++; fi; fi; done; done;for i in ${PIDS[@]}; do if [[ $i -ne $myPID ]]; then  $(kill -2 $i); fi; done


