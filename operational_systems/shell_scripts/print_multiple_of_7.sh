#!/bin/bash
# set -x

# this program prints all multiples of 7 that were passed on
# command line.

arg_number=$#
arg_counter=1

for arg in $*
do
	if [ `expr $arg % 7` -eq 0 ];
	then
	      echo -en "$arg \t"
	fi


	arg_counter=`expr $arg_counter + 1`
done

echo
