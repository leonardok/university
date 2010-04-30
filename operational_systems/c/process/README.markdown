# Exercises

This exercises are about process management.

1. Create a C program that creates a child process using fork (). The child 
presents to the screen message "I am a child!", its PID and the PPID. After the 
child finishes its execution, the father displays on the screen the message 
"I am a father!", its PID and PPID. Do not forget to perform the treatments of 
error! 

2. Make a C program that 5 creates child processes. Each child starts to 
execute a sleeping different time (hint: random value between 5 and 8) seconds.
Upon waking the child prints your order in creation, its pid and the message 
"woke up". After create all children, the father awaits each end. print "END."
Example:
        Father raising children ... 
        Father waiting for children ... 
        son # 3 (pid = 1234) woke up! 
        son # 1 (pid = 1234) woke up! 
        son # 5 (pid = 1234) woke up! 
        son # 4 (pid = 1234) woke up! 
        son # 2 (pid = 1234) woke up! 
        END!

3. Create a C program that stays in a loop reading command names from stdin 
and executing the corresponding program in a child process. Each child 
process in initiation of its execution prints its PID and program name 
that will perform. For simplicity, assume that the commands are executed in the
system PATH (Select variant of exec () appropriate. 

4. Create a C program that remains in a loop reading URLs on its standard input
(one per line) and shoot a child process to download the page from the internet 
Tip: Use the program wget or curl to make the download. 

5. Create a program in shell script that writes to a file specified as the 
parameter numbers 1 through 10 and return an error value (always). 
Next, create a C program that receives as parameter the command line
the name of file to be recorded, and shoot the script on a child 
process, passing to the script the destination filename as a parameter. The parent 
process must await the completion of the child (Script) and print a message 
indicating the success or failure of the script execution. After that the
father must turn into a text editor to edit the file created. 
Tip: To write to a file from the script use the redirection operator output
