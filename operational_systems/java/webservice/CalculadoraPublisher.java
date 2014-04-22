package webservice;

import javax.xml.ws.Endpoint;

public class CalculadoraPublisher
{
	public static void main(String[] args)
	{
		Endpoint.publish("http://127.0.0.1:9000/webservice",new CalculadoraServer());
		
	}	
}

