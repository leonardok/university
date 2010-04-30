#!/bin/bash

# this script receives two words and verifies if the second
# is inside the first

if [  ];

content="`echo $1| grep $2`"
if [ "$content" != "" ];
then
	echo -e "The second word is inside the first word.\n"
else
	echo -e "The second substring is not on the first word.\n"
fi
