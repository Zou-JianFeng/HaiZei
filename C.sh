#!/bin/bash

NowTime=`date +"%Y-%m-%d__%H:%M:%S"`

#Used=(` top -n 1 | head -n 3 | tail -n 1 | awk '{printf("%s%%",100-$8)}' `)

Loadavg1=(` cat /proc/loadavg | awk '{print $1 }'`) 
Loadavg5=(` cat /proc/loadavg | awk '{print $2 }'`) 
Loadavg15=(` cat /proc/loadavg | awk '{print $3}'`) 

UsedAll=(` cat  /proc/stat | head -n 1 | awk -v sum=0 '{sum=$2+$3+$4+$5+$6+$7+$8+$9} ;\
 {printf("%d %d\n",sum,$5)}' `)

sleep 0.5

NowUsedAll=(` cat  /proc/stat | head -n 1 | awk -v sum=0 '{sum=$2+$3+$4+$5+$6+$7+$8+$9} ;\
 {printf("%.2f", (1-($5-"'${UsedAll[1]}'")/(sum-"'${UsedAll[0]}'"))*100 )}' `)



Temp=` cat /sys/class/thermal/thermal_zone0/temp | awk '{print ($1/1000)}'` 

State=(`	echo $Temp \
	| awk '{if($1>70) printf"warning"; else if($1>50) printf"note"; else printf"normal"}' \
	`)

echo "$NowTime ${Loadavg1} ${Loadavg5} ${Loadavg15} $NowUsedAll% $Temp°C  $State" # >>$CpuLog
