# Signal Exercises

1. Develop, in C, a program that treats the receipt of the signal SIGUSR2. When
this signal is received, the program should print its PID and the PID of the 
parent on the screen.

2. Develop a program that treats both the signals of your choice, except 
SIGUSR1, SIGUSR2, SIGQUIT, SIGINT or SIGCHLD. Generate the signals on the 
command line and test the program.

3. Modify the program so that the chosen signals will be ignored.

4. Develop a C program that stays in a loop reading values from the keyboard 
and accumulating the sum of the values read. Upon receiving Ctrl + C, the 
program must print the sum and then terminate the application.

5. Modify the previous program so that the occurrence of SIGQUIT, the value 
currently cumulative sum to zero. In addition, the program must maintain the 
previous behavior, ie read values and sum them until it receives Ctrl + C.

6. Develop, in C, a program a program that reads from the keyboard a PID and a 
time (in seconds). After reading, the program must wait the specified amount of 
seconds and then send a SIGINT signal to the specified process.  
Use alarm () to control timing. 

7. Develop, in C, a program that awaits the arrival of a signal. When receiving 
it, the program successive starts counting from 1, sleeping 1 second between 
each increment. To SIGUSR2 get the program to close the count. The program 
should be immune to Ctrl + C. 

8. Develop a program that receives as parameter a maximum execution time and a 
command name to run. The program should create a child process to run the 
command and control the execution time. If the processing performed by the son 
exceed the fixed time, the program should be terminated with a signal that 
guarantees their termination. 

9. Modify the previous program so that the parent process, tell in the end of 
its execution if the child terminated naturally or was terminated abnormally.

