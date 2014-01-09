#include <iostream> 
using namespace std;

const int MAXN = 110;

int MaxSum(int n, int a[MAXN], int &start, int &end) {
	int sum = 0;
	int b = 0;
	for (int i = 1; i <= n; i++) {
		if (b > 0)b += a[i];
		else {
			b = a[i];
			start = i;
			end = i;
		}
		if (b > sum) {
			sum = b;
			end = i;
		}
	}
	return sum;
}

int MaxSum2(int m, int n, int a[MAXN][MAXN], int &x1, int &y1, int &x2, int &y2) {
	int sum = 0, count = 0, start, end;
	//x1=y1=x2=y2=0;
	int *b = new int[n + 1];
	for (int i = 1; i <= m; i++) {
		for (int k = 1; k <= n; k++)
			b[k] = 0;
		for (int j = i; j <= m; j++) {
			for (int k = 1; k <= n; k++)
				b[k] += a[j][k];
			int max = MaxSum(n, b, start, end);
			if (max > sum) {
				if (count == 0) {
					x1 = j;
					y1 = start;
					count++;
				}
				sum = max;
				x2 = j;
				y2 = end;
			} else {
				count = 0;
			}
		}
	}
	return sum;
}

int main() {
	int m, n;
	while (cin >> m >> n && (m || n)) {
		int a[MAXN][MAXN];
		int x1, y1, x2, y2;

		for (int i = 1; i <= m; i++) {
			for (int j = 1; j <= n; j++) {
				cin >> a[i][j];
				a[i][j] = 1 - a[i][j];
				if (a[i][j] == 0) a[i][j] = -MAXN;
			}
		}

		int sum = MaxSum2(m, n, a, x1, y1, x2, y2);
		cout << sum << endl;
	}
	return 0;
}