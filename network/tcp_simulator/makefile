all: console hosts

console: 
	gcc console.c pipe.c -o console -Wall

hosts: host_a host_b

host_a:
	gcc -DDEF_HOST_A pipe.c host.c socket.c -o host_a -Wall

host_b:
	gcc -DDEF_HOST_B pipe.c host.c socket.c -o host_b -Wall
	
clean:
	rm console host_a host_b
	rm *.pipe
