package expression.parser;

import expression.*;
import operations.Operation;

import java.util.EnumSet;
import java.util.Set;

import exceptions.*;

public class ExpressionParser<T> implements Parser<T> {
	private Operation<T> oper;

	public ExpressionParser(Operation<T> op) {
		oper = op;
	}

	private ExpressionSplitter<T> expr;
	private ExpressionSplitter.Token now;

	public TripleExpression<T> parse(String expression) throws ParseExceptions {
		expr = new ExpressionSplitter<T>(expression, oper);
		now = ExpressionSplitter.Token.ERROR;
		return addAndSubOp();
	}

	private TripleExpression<T> unaryOp() throws ParseExceptions {
		now = expr.nextElement();
		TripleExpression<T> ans = null;
		switch (now) {
		case NUM:
			ans = new Const<T>(expr.nowConst());
			now = expr.nextElement();
			break;
		case VAR:
			ans = new Variable<T>(expr.nowVar());
			now = expr.nextElement();
			break;
		case NOT:
			ans = new CheckedNegate<T>(unaryOp(), oper);
			break;
		case ABS:
			ans = new CheckedAbs<T>(unaryOp(), oper);
			break;
		case SQUARE:
			ans = new CheckedSquare<T>(unaryOp(), oper);
			break;
		case OPEN:
			ans = addAndSubOp();
			now = expr.nextElement();
			break;
		case CLOSE:
			now = expr.nextElement();
			break;
		default:
			throw new WrongOperationException();
		}
		return ans;
	}

	private TripleExpression<T> mulAndDivOp() throws ParseExceptions {
		TripleExpression<T> ans = unaryOp();
		do {
			switch (now) {
			case MUL:
				ans = new CheckedMultiply<T>(ans, unaryOp(), oper);
				break;
			case DIV:
				ans = new CheckedDivide<T>(ans, unaryOp(), oper);
				break;
			case MOD:
				ans = new CheckedMod<T>(ans, unaryOp(), oper);
			default:
				return ans;
			}
		} while (true);
	}

	private TripleExpression<T> addAndSubOp() throws ParseExceptions {
		TripleExpression<T> ans = mulAndDivOp();
		do {
			switch (now) {
			case ADD:
				ans = new CheckedAdd<T>(ans, mulAndDivOp(), oper);
				break;
			case SUB:
				ans = new CheckedSubtract<T>(ans, mulAndDivOp(), oper);
				break;
			default:
				return ans;
			}
		} while (true);
	}
}
