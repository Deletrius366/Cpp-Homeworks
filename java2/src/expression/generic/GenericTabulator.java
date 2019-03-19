package expression.generic;

import java.util.HashMap;

import exceptions.*;
import expression.*;
import expression.parser.ExpressionParser;
import expression.parser.Parser;
import operations.*;

public class GenericTabulator implements Tabulator {

	@Override
	public Object[][][] tabulate(String mode, String expr, int x1, int x2, int y1, int y2, int z1, int z2)
			throws ParseExceptions {
		return makeTable(getOperation(mode), expr, x1, x2, y1, y2, z1, z2);
	}

	private <T> Object[][][] makeTable(Operation<T> oper, String expr, int x1, int x2, int y1, int y2, int z1, int z2)
			throws ParseExceptions {
		Object[][][] res = new Object[x2 - x1 + 1][y2 - y1 + 1][z2 - z1 + 1];
		Parser<T> parser = new ExpressionParser<>(oper);
		TripleExpression<T> exp;
		try {
			exp = parser.parse(expr);
		} catch (ParseExceptions e) {
			return res;
		}
		for (int i = x1; i <= x2; i++) {
			for (int j = y1; j <= y2; j++) {
				for (int k = z1; k <= z2; k++) {
					try {
						res[i - x1][j - y1][k - z1] = exp.evaluate(oper.parseNum(Integer.toString(i)),
								oper.parseNum(Integer.toString(j)), oper.parseNum(Integer.toString(k)));
					} catch (ParseExceptions e) {
					}
				}
			}
		}
		return res;
	}
	
	private static HashMap<String, Operation<?>> TYPES = new HashMap<>();
	
	static {
		TYPES.put("i", new IntegerOperation(true));
		TYPES.put("u", new IntegerOperation(false));
		TYPES.put("bi", new BigIntegerOperation());
		TYPES.put("b", new ByteOperation());
		TYPES.put("d", new DoubleOperation());
		TYPES.put("f", new FloatOperation());
}
	
	private Operation<?> getOperation(String mode) {
		Operation<?> res = TYPES.get(mode);
		return res;
	}

}
