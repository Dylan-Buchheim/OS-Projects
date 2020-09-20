#!/bin/bash

temph=`date | cut -c12-13`
dat=`date +"%A %d in %B of %Y (%r)"`

if [ $temph -lt 12 ]
then
    msg="Good Morning $LOGNAME, Have nice day!"
fi

if [ $temph -ge 12 -a $temph -le 16 ]
then
    msg="Good Afternoon $LOGNAME"
fi

if [ $temph -gt 16 -a $temph -le 20 ]
then
    msg="Good Evening $LOGNAME"
fi

if [ $temph -gt 20 ]
then
	msg="Hello $LOGNAME!"
fi

logwrite="$msg\nThis is $dat"

if [ -f greetingmsg ]
then
	rm -rf greetingmsg
	echo -e "$logwrite" > greetingmsg
else
	echo -e "$logwrite" > greetingmsg
fi


