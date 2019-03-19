package expression.parser;

public interface StringSplitter<T> {
	T nowConst() throws Exception;
	String nowVar();
	
	enum Token {
		SQUARE, ABS, MOD, NUM, VAR, ADD, SUB, MUL, DIV, LOG2, POW2, LOW, HIGH, OPEN, CLOSE, END, NOT, AND, XOR, OR, TIL, COUNT, SHR, SHL, BEGIN, ERROR
	}
	Token nextElement();
}
