package webservice;

import javax.jws.WebService;
import webservice.Calculadora;

@WebService(endpointInterface="webservice.Calculadora")
public class CalculadoraServer implements Calculadora
{
	@Override
	public int somarInt(int a, int b)
	{
		return a + b;
	}

	@Override
	public int multiplicarInt(int a, int b)
	{
		return a * b;
	}

}
