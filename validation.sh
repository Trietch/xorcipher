#!/bin/sh
if [ $1 -eq 1 ]
then
	bash test_script.sh
	bash test_crack.sh
else
	i=0
	sum=0
	while [ $i -ne $1 ]
	do
		start=`date +%s%N | cut -b1-13`
		bash test_crack_stfu.sh
		end=`date +%s%N | cut -b1-13`
		timer=`expr $end - $start`
		i=`expr $i + 1`
		sum=`expr $sum + $timer`
	done
	echo
	moy=`expr $sum / $1`
	echo Moyenne : $moy ms.
	fi
exit 0
