#!/bin/sh
# set -x

# this script does what asks questions #1, #2, #3 and #4

# this function counts from $2 to $1, were $2 > $1
# if argument #1 is greater then #2, then it decreases #1

echo "Argumentos passdos: $*"

if [ $# != 2 ];
then
	echo
	echo "USAGE"
	echo -e "\tcount.sh number1 number2"
	echo
	exit
fi

arg1=$1 # 100
arg2=$2 # 0

if [ $arg1 -gt $arg2 ];
then
	echo -e "Argument #1 is greater than #2\n"
	echo Press enter to continue...
	read
	for((;$arg1 >= $arg2;)){
		echo -en "$arg1 \t"
		arg1=`expr $arg1 - 1`
	}

# else it increases arg1 and print only multiples of 5
else
	if [ $arg1 -eq $arg2 ];
	then
		echo "Argument #1 is equal to #2"
	else
		echo "Argument #1 is lesser than #2"
	fi

	echo
	echo Press enter to continue...
	read
	for((;$arg1 <= $arg2;)){
		if [ `expr $arg1 % 5` -eq 0 ];
		then
			echo -en "$arg1 \t"
		fi
		arg1=`expr $arg1 + 1`
	}
fi

echo
