
function facto ()
{
    if (($1 <= 2)) 
    then
      echo $1
    else
      result=$1
      let rminus=$result-1 #make result a variable
      partial=$(facto $rminus) #make rminus a variable
      echo $((result * partial))
    fi
} # facto

#
# main
#
num=${1:-6}
ans=$(facto $num)
echo $ans
