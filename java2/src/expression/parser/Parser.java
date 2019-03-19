package expression.parser;

import exceptions.ParseExceptions;
import expression.CommonExpression;
import expression.TripleExpression;

public interface Parser<T> {
	TripleExpression<T> parse(String expression) throws ParseExceptions;
}
