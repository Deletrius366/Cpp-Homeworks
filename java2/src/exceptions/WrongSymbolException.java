package exceptions;

public class WrongSymbolException extends ParseExceptions {
	public WrongSymbolException () {
		super("Unknown Symbol");
	}
}

