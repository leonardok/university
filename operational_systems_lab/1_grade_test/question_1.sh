#!/bin/bash
while true; do
    if [ "$#" -lt 2 ]; then exit 0; fi 
    case "$1" in 
    -e)
        i=0 
        for h in $(cat $2); do
            if [ -f $h -a -x $h ]; then 
                $h &gt;/dev/null 2&gt;/dev/null 
                echo “$i:$h -&gt; $?\n”
            fi
            i=$((i+1))
        done ;; 
#   -c) cat "$h" | grep "$USER" | sort ;;
    *) echo "$0 [-e|-c] filename..."; exit -1 ;; 
    esac 
    shift 2
done