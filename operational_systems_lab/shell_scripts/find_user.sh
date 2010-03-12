#!/bin/bash

# this script will see if the arg1: user_name is
# on the passwd file

user_name=$1

if [ "$#" -lt 1 ];
then
	echo -e "You must provide a user name.\n"
else
	if [ "`getent passwd | grep -i $user_name`" != "" ];
	then
		echo -e "The user is on the passwd file.\n"
		exit 0
	else
		echo -e "The user is not on the passwd file.\n"
		exit 1
	fi
fi
