#!/bin/bash -

IFS=$'\n'
aux=( $(ps aux) )
ps=( $(ps -o pid,ppid) )


declare -a worms
declare -a PIDS
count=0
for i in ${aux[*]};do
  if [[ $i = *"/bin/bash - ./evil.sh"* ]]; then
    echo $i
    IFS=$' '
    line=( $i )
    myPID=${line[1]}
    myWorm=$(ps -o ppid= -p $myPID)
    #echo $myWorm
  fi
  if [[ $i = *"p3game"* ]]; then
    IFS=$' '
    line=( $i )
    parentPID=${line[1]}
    name=${i##*p3game }
    declare -a worms=( $name )
  fi
  for j in ${name[*]}; do
    line=( $i )
    if [[ $i = *$j* ]]; then
      if [[ ${line[1]} -ne $parentPID ]]; then
        PIDS[$count]=${line[1]}
        let count++
      fi
    fi
  done
done

echo $myPID
#for i in ${PIDS[@]}; do
#  $(kill -2 $i)
#done


