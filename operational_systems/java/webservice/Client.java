package webservice;

import java.net.URL;
import javax.xml.namespace.QName;
import javax.xml.ws.Service;
import java.net.MalformedURLException;

import webservice.Calculadora;

public class Client
{
	public static void main(String[] args)
	{
		URL url = null;
		try
		{
			url = new URL("http://127.0.0.1:9000/webservice");
		}
		catch (MalformedURLException e)
		{
			System.err.println("ComputeEngine exception:");
			e.printStackTrace();
		}

		QName n = new QName("http://webservice/", "CalculadoraServerService");
		Service service = Service.create(url, n);

		Calculadora calc = service.getPort(Calculadora.class);

		System.out.println("Somar int: " + calc.somarInt(4, 2));
		System.out.println("Multiplicar int: " + calc.multiplicarInt(4, 2));
	}
}
