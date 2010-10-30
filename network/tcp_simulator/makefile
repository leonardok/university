all: console hosts

console: 
	gcc console.c pipe.c -o console

hosts: host_a host_b

host_a:
	gcc -DHOST_A pipe.c host.c -o host_a

host_b:
	gcc -DHOST_B pipe.c host.c -o host_b
	
clean:
	rm console host_a host_b
