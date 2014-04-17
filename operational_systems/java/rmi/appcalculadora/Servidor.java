package appcalculadora;

import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;  
import java.rmi.RemoteException;

import appcalculadora.Calculadora;

public class Servidor implements Calculadora {
	public static void main(String args[])
	{

		/**
		 * The main method's first task is to create and install a
		 * security manager, which protects access to system resources
		 * from untrusted downloaded code running within the Java
		 * virtual machine
		 *
		 * A security manager determines whether
		 * downloaded code has access to the local file system or can
		 * perform any other privileged operations.
		 */

		if (System.getSecurityManager() == null) {
		    System.setSecurityManager(new SecurityManager());
		}
		try {
			String name = "Calculadora";

			/**
			 * creates an instance of ComputeEngine and exports it
			 * to the RMI runtime
			 */

			Calculadora calc = new Servidor();
			Calculadora stub = (Calculadora) UnicastRemoteObject.exportObject(calc, 0);

			/**
			 * adds the name to the RMI registry running on the server
			 */
			Registry registry = LocateRegistry.getRegistry();
			registry.rebind(name, stub);
			System.out.println("Calculadora bounded");
		}
		catch (Exception e) {
			System.err.println("ComputeEngine exception:");
			e.printStackTrace();
		}
	}

	public int somarInt(int val1, int val2) throws RemoteException
	{
		return val1 + val2;
	}

	public int multiplicarInt(int val1, int val2) throws RemoteException
	{
		return val1 * val2;
	}
}
