package exceptions;

//import java.text.ParseException;

public class ParseToByteException extends ParseExceptions {
	public ParseToByteException() {
		super("cant parse constant to byte");
	}
}
