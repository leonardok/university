package webservice;

import javax.jws.WebMethod;
import javax.jws.WebService;
import javax.jws.soap.SOAPBinding;
import javax.jws.soap.SOAPBinding.Style;

@WebService
@SOAPBinding(style = Style.RPC)
public interface Calculadora {

	@WebMethod
	public int somarInt(int a, int b);

	@WebMethod
	public int multiplicarInt(int a, int b);
}
