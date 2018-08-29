#!/bin/bash

NowTime=`date +"%Y-%m-%d__%H:%M:%S"`

# df -h | awk '{if($1 ~ /\/dev\//) {printf("%s %s\n",$2,$3)}}'
Alldisk=(` df -m | awk -v sum=0 '{if($1 ~ /\/dev\//) {sum=sum+$2}} END {print sum}' `)

AllAva=(` df -m | awk -v sum=0 '{if($1 ~ /\/dev\//) {sum=sum+$4}} END {print sum}' `)

Used=$[100 - $AllAva *100 /$Alldisk ]

echo "$NowTime 0 disk $Alldisk $AllAva ${Used}%"  #>> $DiskLog

df -m | awk -v d=${NowTime} '{if($1 ~ /\/dev\//){print "'$NowTime'","1",$6,$2,$4,$5}}'  #>>$DiskLog
