# Operational System Laboratory Work

The deliverable of this work is a document with all the answers for the 
propouse exercises.

## Exercises

1. Describe the comportament of the following script

        #!/bin/bash
        while true; do
            if [ "$#" -lt 2 ]; then exit 0; fi 
            case "$1" in 
            -e)
                i=0 
                for h in $(cat $2); do
                    if [ -f $h -a -x $h ]; then 
                        $h >/dev/null 2>/dev/null 
                        echo "$i:$h -> $?\n"
                    fi
                    i=$((i+1))
                done ;; 
        #   -c) cat "$h" | grep "$USER" | sort ;;
            *) echo "$0 [-e|-c] filename..."; exit -1 ;; 
            esac 
            shift 2
        done


2. Write a C program that implement the functionality of the following script

        #!/bin/bash
        if [ $# -lt 1 ]; then
            echo -e "Parametros insuficientes. \nUse: $0 comando [comando...]"; exit -1
        fi 
        ns=0 
        nf=0 
        for cmd in $*; do
            $cmd & 
            pid=$! 
            sleep 2; 
            kill -KILL $pid 2>/dev/null 
            wait $pid 2>/dev/null 
            if test $? -eq 0 ; then ns=$((ns+1)); else nf=$((nf+1)); fi
        done 
        echo "=================================" 
        echo "Numero total de comandos executados: $((ns+nf))" 
        echo "Número de comandos executados com sucesso: $ns"
