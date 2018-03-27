
#
# cvthms - convert seconds to hh:mm:ss
#
function cvthms ()
{
    let hh=$1/3600
    mm=$(( ($1-(hh*3600))/60 ))
    ss=$(( ($1-(hh*3600)-(mm*60)) ))

    printf "%02d:%02d:%02d\n" $hh $mm $ss
}

#
# difftime - compute the time difference between two timestamps
#
# input format:   hh:mm:ss  for both arguments
#
function difftime ()
{
    t1=$1
    t2=$2
    hr1=${t1%%:*}
    hr2=${t2%%:*}
    t1=${1#*:}
    t2=${2#*:}
    mn1=${t1%%:*}
    mn2=${t2%%:*}
    t1=${t1#*:} #change from ${1#*:} b/c $1 is the unaltered original
    t2=${t2#*:} #change from ${2#*:} b/c $2 is the unaltered original
    sc1=$t1
    sc2=$t2

    insec1=$((10#$hr1*3600+10#$mn1*60+10#$sc1)) #Bash thinks that these are octal numbers b/c of leading zero
    insec2=$((10#$hr2*3600+10#$mn2*60+10#$sc2))

    diffsec=$((insec2-insec1))
    diffsec=${diffsec#-}

    cvthms $diffsec
}

difftime $1 $2
