package tabulator;

import exceptions.ParseExceptions;
import expression.*;
import expression.parser.ExpressionParser;
import expression.parser.Parser;
import operations.*;
import operations.Operation;

public class GenericTabulator implements Tabulator {

	@Override
	public Object[][][] tabulate(String mode, String expr, int x1, int x2, int y1, int y2, int z1, int z2) {
		return makeTable(getOperation(mode), expr, x1, x2, y1, y2, z1, z2);
	}

	private <T> Object[][][] makeTable(Operation<T> oper, String expr, int x1, int x2, int y1, int y2, int z1, int z2) {
		Object[][][] res = new Object[x2 - x1 + 1][y2 - y1 + 1][z2 - z1 + 1];
		Parser<T> parser = new ExpressionParser<>(oper);
		TripleExpression<T> exp;
		try {
			exp = parser.parse(expr);
		} catch (ParseExceptions e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return res;
		}
		for (int i = x1; i <= x2; i++) {
			for (int j = y1; j <= y2; j++) {
				for (int k = z1; i <= z2; k++) {
					try {
						res[i - x1][j - y1][k - z1] = exp.evaluate(oper.parseNum(Integer.toString(i)),
								oper.parseNum(Integer.toString(i)), oper.parseNum(Integer.toString(i)));
					} catch (ParseExceptions e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
			}
		}
		return res;
	}

	private Operation<?> getOperation(String mode) {
		Operation<?> oper = new IntegerOperation();
		switch (mode.charAt(0)) {
		case 'i':
			oper = new IntegerOperation();
		case 'd':
			oper = new DoubleOperation();
		case 'b':
			oper = new BigIntegerOperation();
		}
		return oper;
	}

}
