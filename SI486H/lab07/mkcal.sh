#!/bin/bash

#Brandon Sipes lab07  Making an HTML calendar with BASH

# ====================================
# pagehead
# ====================================
#simple function to generate the head of the page
function pagehead () {
  cat<<EOF
<html>
  <head>
    <title>
      CalciferTheCalendar
    </title>
    <link rel="stylesheet" href="./calstyle.css">
  </head>
  <body>
    <table>
EOF
}

# ====================================
# monthHead
# ====================================
#function to generate the basic outline of each month
function monthHead () {
  cat<<EOF
  <table class="caltable" cellpadding="0" cellspacing="0" border="2" width = "95%">
    <tr align="center" valign="middle">
      <th colspan="7" align="center" valign = "middle">
        <font size="+3"> $1 </font>
      </th>
      <tr>
    <th>Sunday</th>
    <th>Monday</th>
    <th>Tuesday</th>
    <th>Wednesday</th>
    <th>Thursday</th>
    <th>Friday</th>
    <th>Saturday</th>
    </tr>
    <tr class="reg">
EOF
}

# ====================================
# pageend
# ====================================
#function to end each page
function pageend () {
  cat<<EOF
    </table>
  </body>
</html>
EOF
}


# ++++++++++++++++++++++++++++++++++++
# day
# ++++++++++++++++++++++++++++++++++++
#switch statment to determine the day
function day () {
  case $0 in
    0) echo Sunday;;
    1) echo Monday;;
    2) echo Tuesday;;
    3) echo Wednesday;;
    4) echo Thursday;;
    5) echo Friday;;
    6) echo Saturday;;
  esac
}

# +++++++++++++++++++++++++++++++++++
# isColour
# ++++++++++++++++++++++++++++++++++++
#Tell if there is a color or a link to be made
function isColour () {
  case $1 in
    red) ;&
    green) ;&
    black) ;&
    tan) option="True";;
    link) option="link";;
    *) option="Error";;
  esac
}

# ====================================
# mkmonth
# ====================================
#The meat of this code that makes each individual month
function mkmonth () {
  #read in as: # Month, newlines, day, color, text, additional args
  count=-1 #match month and count newlines
  while read line; do #A first while loop for generating the beginnings
    if (( count == -1 )); then
      mon=$line
      let count++
      monthHead $mon
      continue
    fi
    
    if [ "$line" == "" ]; then
      cat <<EOF
      <td>
        &nbsp;
      </td>
EOF
    let count++
    elif [[ $line == \#* ]]; then
      continue
    else #we hit the first non blank line. Use it then break out
      cat <<END
      <td>
        <div class="calheader">$line</div>
END
    IFS=" "
    declare -a options=( $rest )
    for ((i=0; i<${#options[@]}; ++i)); do
      isColour ${options[$i]}
      if [ $option == "True" ]; then
        cat<<END
          <font color="${options[$i]}">${options[$i+1]//_/ }</font><br>
END
        let i++
      elif [ $option == "link" ]; then
        cat<<END
          <a href="http://${options[$i+2]}">${options[$i+1]//_/ }</a><br>
END
        let i=i+2
      fi
    done

    cat <<END
      </td>
END
      let count++
      break #break out of this while loop 
    fi
  done

  #loop through all the actual lines
  while read line rest; do #all of this could have been done in the first but this seems cleaner to me
    if [[ $line == \#* ]]; then #look more into how the comments are layed out and if this works
      continue
    fi
    if (( count == 7 )); then #create a new row
      let count=count%7
      cat<<END
      </tr>
      <tr class="reg">
END
    fi
    
    cat<<EOF
      <td align="center">
        <div class="calheader">$line</div><br><br>
EOF

    IFS=" "
    declare -a options=( $rest ) #create array of all the arguments
    for ((i=0; i<${#options[@]}; ++i)); do #then loop through it
      isColour ${options[$i]}
      if [ $option == "True" ]; then
        cat<<END
          <font color="${options[$i]}">${options[$i+1]//_/ }</font><br>
END
        let i++
      elif [ $option == "link" ]; then
        cat<<END
          <a href="http://${options[$i+2]}">${options[$i+1]//_/ }</a><br>
END
        let i=i+2
      fi
    done


    cat<<EOF
      </td>
EOF
    let count++
  done
  for ((;count < 7; ++count)); do #fill out the rest of the calendar
    cat <<EOF
      <td>
        &nbsp;
      </td>
EOF
  done

}


# ====================================
# main
# ====================================
pagehead > Calendar.html

for fn #loop through each file for a different month
do
  mkmonth < $fn
  echo '<p class="pad">' '&nbsp;' '</p>' #space between months
done >> Calendar.html
pageend >> Calendar.html
