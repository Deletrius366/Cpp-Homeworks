package operations;

import exceptions.DivisionByZeroException;
import exceptions.OverflowException;

public class IntegerOperation implements Operation<Integer> {
	private boolean checked;

	public IntegerOperation(boolean checked) {
		this.checked = checked;
	}

	private void checkAdd(Integer x, Integer y) throws OverflowException {
		if (x > 0 && Integer.MAX_VALUE - x < y) {
			throw new OverflowException();
		}
		if (x < 0 && Integer.MIN_VALUE - x > y) {
			throw new OverflowException();
		}
	}

	@Override
	public Integer add(Integer x, Integer y) throws OverflowException {
		if (checked) {
			checkAdd(x, y);
		}
		return x + y;
	}

	private void checkSub(Integer x, Integer y) throws OverflowException {
		if (y == Integer.MIN_VALUE && x >= 0) {
			throw new OverflowException();
		}
		if (x <= 0 && y > 0 && Integer.MIN_VALUE - x > -y) {
			throw new OverflowException();
		}
		if (x >= 0 && y < 0 && Integer.MAX_VALUE - x < -y) {
			throw new OverflowException();
		}
	}

	@Override
	public Integer sub(Integer x, Integer y) throws OverflowException {
		if (checked) {
			checkSub(x, y);
		}
		return x - y;
	}

	private void checkMul(Integer x, Integer y) throws OverflowException {
		if (x > 0 && y > 0 && Integer.MAX_VALUE / x < y) {
			throw new OverflowException();
		}

		if (x > 0 && y < 0 && Integer.MIN_VALUE / x > y) {
			throw new OverflowException();
		}

		if (x < 0 && y > 0 && Integer.MIN_VALUE / y > x) {
			throw new OverflowException();
		}

		if (x < 0 && y < 0 && Integer.MAX_VALUE / x > y) {
			throw new OverflowException();
		}
	}

	@Override
	public Integer mul(Integer x, Integer y) throws OverflowException {
		if (checked) {
			checkMul(x, y);
		}
		return x * y;
	}

	private void checkDiv(Integer x, Integer y) throws DivisionByZeroException, OverflowException {
		if (y == 0) {
			throw new DivisionByZeroException();
		}
		if (x == Integer.MIN_VALUE && y == -1) {
			throw new OverflowException();
		}
	}

	@Override
	public Integer div(Integer x, Integer y) throws DivisionByZeroException, OverflowException {
		if (checked) {
			checkDiv(x, y);
		}
		if (y == 0) {
			throw new DivisionByZeroException();
		}
		return x / y;
	}

	@Override
	public Integer neg(Integer x) {
		return -x;
	}

	@Override
	public Integer parseNum(String x) {
		return Integer.parseInt(x);
	}

	@Override
	public Integer abs(Integer x) {
		return Math.abs(x);
	}

	@Override
	public Integer square(Integer x) throws OverflowException {
		if (checked) {
			checkMul(x, x);
		}
		return x * x;
	}

	@Override
	public Integer mod(Integer x, Integer y) throws DivisionByZeroException {
		if (y == 0) {
			throw new DivisionByZeroException();
		}
		return x % y;
	}

}
