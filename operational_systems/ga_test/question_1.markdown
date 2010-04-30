# Describe the comportament of the following script
The script will receive files as argument containing executables and execute 
these files in background. These files must be with '-e' argument as in the 
example:
        script -e arq.txt -e arq.txt

The conditions for it to exit is:
Having less then 2 arguments, exit status 0

Hhaving 2 arguments and the option is wrong it will execute the default case
   insite the case statement ('*)'). Exit status is '-1'. Exammple:
        $ script -f arq.txt
   In this case the output will be:
        $ script [-e|-c] filename...

Case we give to the script 3 arguments it will do the first loop ($# is 3) then
in the second ($# is 1) it will exit as in number 1.

While inside the loop, it will enter when the option '-e' and a file name is 
given, it will test if the file exist ('-f') and ('-a') if the file is 
executable ('-x'), at this point the file name will be stored inside $h. If the 
test is not true it will continue the loop. If the test result is true, then it 
will get all the content in the file passed and try to execute each line, 
redirecting both stdout and stderr to /dev/null. After the execution it will 
print the command number, command name and exit status. Command number is stored 
in variable $i, that is incremented at each executed command.
