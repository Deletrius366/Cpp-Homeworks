package expression.parser;

import java.util.*;
import exceptions.*;
import operations.Operation;

public class ExpressionSplitter<T> implements StringSplitter<T> {

	int iter;
	Token now;
	String in;
	String var;
	T cons;
	Operation<T> oper;

	ArrayList<Tok> expr = new ArrayList<>();

	private class Tok {
		Token term;
		String var;
		T cons;
	}

	ExpressionSplitter(String input, Operation<T> op) throws ParseExceptions {
		oper = op;
		expr = new ArrayList<>();
		iter = 0;
		in = input;
		int pos = 0;
		now = Token.ERROR;
		pos = nextOpt(pos);
		for (; now != Token.END; pos = nextOpt(pos)) {
			Tok opt = new Tok();
			if (now == Token.VAR) {
				opt.var = var;
			} else {
				opt.var = null;
			}
			if (now == Token.NUM) {
				opt.cons = cons;
			} else {
				opt.cons = oper.parseNum("0");
			}
			opt.term = now;
			expr.add(opt);
		}
		check();
	}

	private void check() throws ParseExceptions {
		int size = expr.size();
		int bal = 0;
		Token now;

		for (int i = 0; i < size; i++) {
			now = expr.get(i).term;
			if (now == Token.ERROR) {
				throw new WrongSymbolException();
			}
		}
		for (int i = 0; i < size; i++) {
			now = expr.get(i).term;
			if (now == Token.OPEN) {
				bal++;
			}
			if (now == Token.CLOSE) {
				bal--;
			}
			if (isUnaryOpt(now) && ((i == size - 1) || !(isLeftOpd(expr.get(i + 1).term)))) {
				throw new ArgumentsParsingException();
			}
			if (isBinaryOpt(now) && ((i == size - 1) || (i == 0) || !(isLeftOpd(expr.get(i + 1).term))
					|| !(isRightOpd(expr.get(i - 1).term)))) {
				throw new ArgumentsParsingException();
			}
			if ((now == Token.NUM || now == Token.VAR) && (i != 0 && !isLeftOpt(expr.get(i - 1).term))
					|| (i != size - 1 && !isRightOpt(expr.get(i + 1).term))) {

			}
			if ((now == Token.OPEN) && ((i == size - 1) || !(isLeftOpd(expr.get(i + 1).term)))) {
				throw new ArgumentsParsingException();
			}
			if ((now == Token.CLOSE) && ((i == 0) || !(isRightOpd(expr.get(i - 1).term)))) {
				throw new ArgumentsParsingException();
			}
			if (bal < 0) {
				throw new BracketException();
			}
		}
		if (bal != 0) {
			throw new BracketException();
		}
	}

	private int nextOpt(int ind) throws ParseExceptions {
		while (ind < in.length() && Character.isWhitespace(in.charAt(ind))) {
			ind++;
		}

		if (ind >= in.length()) {
			now = Token.END;
		} else {
			switch (in.charAt(ind)) {
			case '&':
				now = Token.AND;
				break;
			case '^':
				now = Token.XOR;
				break;
			case '|':
				now = Token.OR;
				break;
			case '~':
				now = Token.TIL;
				break;
			case '+':
				now = Token.ADD;
				break;
			case '-':
				if (now == Token.NUM || now == Token.VAR || now == Token.CLOSE) {
					now = Token.SUB;
				} else {
					if (ind + 1 >= in.length()) {
						throw new IllegalDataException();
					}
					if (Character.isDigit(in.charAt(ind + 1))) {
						ind = nextNum(true, ind + 1);
						now = Token.NUM;
					} else {
						now = Token.NOT;
					}
				}
				break;
			case '*':
				now = Token.MUL;
				break;
			case '/':
				now = Token.DIV;
				break;
			case '(':
				;
				now = Token.OPEN;
				break;
			case ')':
				now = Token.CLOSE;
				break;
			default:
				if (Character.isDigit(in.charAt(ind))) {
					ind = nextNum(false, ind);
					now = Token.NUM;
				} else {
					char ch = in.charAt(ind);
					if (ch == 'x' || ch == 'y' || ch == 'z') {
						now = Token.VAR;
						var = ch + "";
					} else {
						switch (ch) {
						case 'a':
							checkOpt(ind, "abs", "rofl");
							now = Token.ABS;
							ind += 2;
							break;
						case 'm':
							checkOpt(ind, "mod", "rofl");
							now = Token.MOD;
							ind += 2;
							break;
						case 's':
							checkOpt(ind, "square", "rofl");
							now = Token.SQUARE;
							ind += 5;
							break;
						}
					}
				}
			}
			ind++;
		}
		return ind;
	}

	private void checkOpt(int ind, String opt, String input) throws ParseExceptions {
		if (ind + opt.length() - 1 >= in.length() || in.substring(ind, ind + opt.length()).compareTo(opt) != 0
				|| (ind + opt.length() < in.length() && Character.isLetter(in.charAt(ind + opt.length())))) {
			throw new WrongOperationException();
		}
	}

	private boolean isLeftOpt(Token term) {
		if (isBinaryOpt(term) || isUnaryOpt(term) || (term == Token.OPEN)) {
			return true;
		}
		return false;
	}

	private boolean isRightOpt(Token term) {
		if (isBinaryOpt(term) || (term == Token.CLOSE)) {
			return true;
		}
		return false;
	}

	private boolean isLeftOpd(Token term) {
		if (term == Token.OPEN || term == Token.VAR || term == Token.NUM || isUnaryOpt(term)) {
			return true;
		}
		return false;
	}

	private boolean isRightOpd(Token term) {
		if (term == Token.CLOSE || term == Token.VAR || term == Token.NUM) {
			return true;
		}
		return false;
	}

	private boolean isUnaryOpt(Token term) {
		if (term == Token.NOT || term == Token.LOG2 || term == Token.POW2 || term == Token.LOW || term == Token.HIGH
				|| term == Token.ABS || term == Token.SQUARE) {
			return true;
		}
		return false;
	}

	private boolean isBinaryOpt(Token term) {
		if (term == Token.ADD || term == Token.SUB || term == Token.MUL || term == Token.DIV || term == Token.MOD) {
			return true;
		}
		return false;
	}

	@Override
	public T nowConst() throws ParseToByteException {
		if (iter - 1 >= expr.size()) {
			return oper.parseNum("0");
		} else {
			return expr.get(iter - 1).cons;
		}
	}

	@Override
	public String nowVar() {
		if (iter - 1 >= expr.size()) {
			return "";
		} else {
			return expr.get(iter - 1).var;
		}
	}

	@Override
	public Token nextElement() {
		if (iter >= expr.size()) {
			return Token.END;
		} else {
			return expr.get(iter++).term;
		}
	}

	private int nextNum(boolean neg, int ind) throws IllegalDataException {
		int l = ind;
		while (ind < in.length() && Character.isDigit(in.charAt(ind))) {
			ind++;
		}
		int r = ind;
		ind--;
		String temp = in.substring(l, r);
		if (neg)
			temp = "-" + temp;
		try {
			cons = oper.parseNum(temp);
		} catch (Exception e) {
			throw new IllegalDataException();
		}
		return ind;
	}
}
