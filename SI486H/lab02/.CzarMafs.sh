#!/bin/bash

function romdigit () {
  Romulus=${1}
  DIGIT=$(case $Romulus in
    I)  echo 1;;
    V)  echo 5;;
    X)  echo 10;;
    L)  echo 50;;
    C)  echo 100;;
    D)  echo 500;;
    M)  echo 1000;;
    *)  echo "NAN";;
  esac)
} 

#romdigit 'P'
#echo $DIGIT

#REGEX Explained
#^M{0,4} must start with between zero and four M's
#(CD|CM| C can come before D or M or D can be alone D?C{0,3}) or three or more C's
#(XC|XL| X can come before C or L or L can be alone L?X{0,3}) or three or more X's
#(IX|IV| I can come before X or V or V can be alone V?I{0,3}) or three or more I's
#$ this has to end it
#

function isValidRom {
  if [[ ${1} =~ ^M{0,4}(CD|CM|D?C{0,3})(XC|XL|L?X{0,3})(IX|IV|V?I{0,3})$ ]]; then
    echo 0
  else
    echo 1
  fi
}
echo $(isValidRom ${1})



cvtRom2Dec () {
  if [ $(isValidRom ${1}) = 1 ]; then
    return;
  fi
  local VALUE=0
  for (( BLANK=0; BLANK < ${#1}; )); do
    romdigit ${1:$BLANK:1}
    CURR=$DIGIT
    romdigit ${1:$BLANK+1:1}
    NEXT=$DIGIT
    romdigit ${1:$BLANK+2:1}
    DNEXT=$DIGIT
    if (($CURR <  $NEXT)); then       #IX
      VALUE=$((VALUE + NEXT - CURR));
      BLANK=$((BLANK + 2));
    elif (( $CURR > $NEXT )); then        #XI
      VALUE=$((VALUE + CURR + NEXT)); 
      BLANK=$((BLANK + 2));
      romdigit ${1:$BLANK+2:1}                
      if (( $NEXT = $DIGIT )); then     #XII
        VALUE=$((VALUE + DIGIT));
        BLANK=$((BLANK + 1));
        romdigit ${1:$BLANK+3:1}
        if (( $NEXT = $DIGIT)); then   #XIII
          VALUE=$((VALUE + DIGIT));
          BLANK=$((BLANK + 1));
        fi
      fi
      VALUE=$((VALUE + CURR + NEXT));
      BLANK=$((BLANK + 2));
    else
      VALUE=$((VALUE+CURR));
      BLANK=$((BLANK + 1));
    fi
  done
  echo $VALUE
}

#echo $(cvtRom2Dec ${1})
      
    









