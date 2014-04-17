package appcalculadora;

import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;  
import java.rmi.RemoteException;


public class Cliente {
	public static void main(String args[]) {
		if (System.getSecurityManager() == null) {
		    System.setSecurityManager(new SecurityManager());
		}
		try {
			String name = "Calculadora";

			Registry registry = LocateRegistry.getRegistry();
			Calculadora calc = (Calculadora) registry.lookup(name);

			int sum = calc.somarInt(1, 2);
			System.out.println(sum);

			int mult = calc.multiplicarInt(1, 2);
			System.out.println(mult);
		}
		catch (Exception e) {
			System.err.println("ComputeEngine exception:");
			e.printStackTrace();
		}
	}
}
