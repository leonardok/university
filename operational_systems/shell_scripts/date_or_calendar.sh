#!/bin/sh

echo "Chose:"
echo "1. show calendar"
echo "2. show simple date"
echo -n "your option: "
read opt
echo

case "$opt" in
	1)
		cal
		;;
	2)
		date
        	;;
esac
