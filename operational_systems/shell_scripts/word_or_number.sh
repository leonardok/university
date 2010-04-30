#!/bin/sh

if [ $# -lt 1 ];
then
	echo
	echo "Usage is: word_or_number.sh word|number"
	echo
	exit
fi

case $1 in
	[0-9]*)
		echo "$1 is a number."
		;;
	[a-z|A-Z]*)
		echo "$1 is a word."
		;;
	*)
		echo "Invalid entry"
esac
echo
