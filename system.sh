#!/bin/bash
time=`date +"%Y-%m-%d__%H:%M:%S"`
Name=`hostname`
UName=`uname`
Uname=`uname -r`
Uptime=`uptime -p | awk '{print $1"_"$2$3"_"$4$5"_"$6$7}'`
Load=`uptime | awk '{print $10,$11,$12}' | tr "," " "`
tem=`cat /sys/class/thermal/thermal_zone0/temp | awk '{print $1/1000}'`
fre=`free -m | tail -2 | head -1 | awk '{print $3/$2}'`
Df=`df -T -m | grep ^/dev | awk -v sum=0 -v Sum=0 '{{sum= sum+$3}} END {print sum}'`
DF=`df -T -m | grep ^/dev | awk -v Sum=0 '{{Sum=Sum+$4}} END {print Sum}'`
tem=`echo "$tem*1" | bc`
fre=`echo "$fre*100" | bc`
Tem=(`echo $tem| awk '{if($1 < 70) printf "normol"; else if($1 < 80) printf "note"; else printf "warning"}'`)
Fre=(`echo $fre | awk '{if($1 < 70)printf "normol"; else if($1 < 80) printf "note"; else printf "warning"}'`)
DFF=(`echo "$DF*100/$Df" | bc | awk '{if($1 < 70)print "normol"; else if($1 < 80) printf "note"; else printf "warning"}'`)
echo "$time $Name $UName $Uname $Uptime $Load $fre $Fre $tem $Tem $Df $DF $DFF"
