#!/bin/bash

## Brandon Sipes 12wkexam BowlScore script
#  Program to take in numbers to calcuate the score
#  of a game of bowling
## April 3, 2018


#########################################
# cmdRead
#########################################
function cmdRead(){
  for i in $*; do
    scores[$rounds]="$i"
    let rounds++
  done
}

#########################################
# readline
#########################################
function readline(){
  read line;
  for i in $line; do
    scores=$i
    let rounds++
  done
}

#Read in a series of integers
declare -a scores
rounds=0
#echo ${#scores}
#for i in ${scores}; do
#  echo $i
#done

#or from command line arguments
if [[ ${11} ]]; then
  cmdRead $*
else #from either stdin
  readline
fi

declare -a scoreCum 
declare -a scoreRound
round=0
cum=0
two=0
magic=0
#calculate the scores as the rounds go by
for ((i=0; i < ${#scores[@]};)); do
  if (()); then
    ((two = ${scores[$i]} + ${scores[$i+1]}))
  fi
  if (( ${scores[$i]} == 10 )); then
    ((round=${scores[$i]} + ${scores[$i+1]} + ${scores[$i+2]}))
    let scoreRound[$magic]=$round
    let i++
  elif (( $two == 10 )); then
    ((round=${scores[$i]} + ${scores[$i+1]} + ${scores[$i+2]}))
    let scoreRound[$magic]=$round
    let i+=2
  else
    ((round=${scores[$i]} + ${scores[$i+1]}))
    let scoreRound[$magic]=$round
    let i+=2
  fi
  if (( i == 0 )); then
    ((cum=${scoreRound[$i]}))
    let scoreCum[$magic]=$cum
  else 
    ((cum=${scores[$i]} + scoreCum[$magic-1]))
    let scoreCum[$magic]=$cum
  fi
  let magic++
done
#printing out the score of each round individually
for i in ${scoreRound[*]}; do
  printf "%s " $i
done
echo
#and the cumulative score of each round
for i in ${scoreCum[*]}; do
  printf "%d " $i
done
echo 









