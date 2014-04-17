# Simple Java RMI

http://docs.oracle.com/javase/tutorial/rmi/running.html
http://docs.oracle.com/javase/tutorial/rmi/implementing.html


This is a simple example of java RMI.  What it does is create a server that
accepts the interface at Calculadora. Client then can spawn and execute remote
calls in the server code.

Explanation is in the code, as comments.

## Ho to run it
(in linux)

	# compile all java code
	javac appcalculadora/*.java

	# create an interface classes file
	jar cvf compute.jar compute/*.class

	# start the registry server
	rmiregistry

	# start the calculator server
	java -cp . -Djava.rmi.server.codebase=file://<path to classes>/classes.jar  -Djava.security.policy=java.policy appcalculadora.Servidor

	# run the client
	java -cp . -Djava.rmi.server.codebase=file://<path to classes>/classes.jar  -Djava.security.policy=java.policy appcalculadora.Cliente
