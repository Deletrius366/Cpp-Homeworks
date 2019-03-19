package expression;

import exceptions.ParseExceptions;

/**
 * @author Georgiy Korneev (kgeorgiy@kgeorgiy.info)
 */
public interface TripleExpression<T> {
	T evaluate(T x, T y, T z) throws ParseExceptions;
}
