import java.io.BufferedInputStream;
import java.math.BigInteger;
import java.util.Arrays;
import java.util.Scanner;

public class UVa_10069_Distinct_Subsequences {
	static Scanner cin = new Scanner(new BufferedInputStream(System.in));
	static BigInteger dp[][] = new BigInteger[101][10001];
	static int nCase;
	static String X, Z;

	private static BigInteger DP(int x, int y) {
		if (!dp[x][y].equals(BigInteger.valueOf(-1)))
			return dp[x][y];
		if (x == Z.length() && y <= X.length()) {
			dp[x][y] = BigInteger.valueOf(1);
			return dp[x][y];
		}
		if (y >= X.length() || X.length() - y < Z.length() - x) {
			dp[x][y] = BigInteger.valueOf(0);
			return dp[x][y];
		}

		dp[x][y] = BigInteger.valueOf(0);
		for (int i = y; i < X.length(); i++) {
			if (X.charAt(i) == Z.charAt(x)) {
				dp[x][y] = dp[x][y].add(DP(x + 1, i + 1));
			}
		}
		return dp[x][y];
	}

	private static void init() {
		for (int i = 0; i <= Z.length(); i++) {
			Arrays.fill(dp[i], BigInteger.valueOf(-1));
		}
	}

	private static void input() {
		X = cin.next();
		Z = cin.next();
	}

	private static void work() {
		// System.out.println(DP(0, 0));

		for (int i = 0; i <= Z.length(); i++) {
			Arrays.fill(dp[i], BigInteger.valueOf(0));
		}
		for (int i = 0; i <= X.length(); i++) {
			dp[0][i] = BigInteger.valueOf(1);
		}

		for (int i = 1; i <= Z.length(); i++) {
			for (int j = 1; j <= X.length(); j++) {
				if (X.charAt(j - 1) == Z.charAt(i - 1)) {
					dp[i][j] = dp[i][j - 1].add(dp[i - 1][j - 1]);
				} else {
					dp[i][j] = dp[i][j - 1];
				}
			}
		}

		System.out.println(dp[Z.length()][X.length()]);
	}

	public static void main(String[] args) {
		nCase = cin.nextInt();
		while (nCase-- > 0) {
			input();
			init();
			work();
		}
	}

}

