#!/bin/bash

# this script will find out how many lines and words
# there is on all the files on the current directory

lines="`cat ./* | wc -l`"
words="`cat ./* | wc -w`"

echo "The number, on the current directory, of words are $words and lines are $lines."
echo
