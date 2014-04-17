package appcalculadora;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface Calculadora extends Remote {
	public int somarInt(int val1, int val2) throws RemoteException;
	public int multiplicarInt(int val1, int val2) throws RemoteException;
}
