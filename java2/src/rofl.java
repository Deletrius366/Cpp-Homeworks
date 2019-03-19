import expression.*;
import expression.generic.GenericTabulator;
import expression.parser.*;
import exceptions.*;

public class rofl {
	public static void main(String[] args) throws Exception {

		int a = 0;
		a++;
		int b = a;
		a += b;

		Object[][][] res = new GenericTabulator().tabulate("f", "10", 1, 1, 1, 1, 1, 1);
		System.out.println(res[0][0][0]);
	}
}