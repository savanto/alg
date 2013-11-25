#include <iostream>
#include <cstdlib>
using namespace std;

// 1 <= LCF(n, m) <= m
// if n % m != 0, then LCF(n, m) = LCF(m, n % m)
int lcfr(int n, int m)
{
	int mod = n % m;
	if (mod == 0)
		return m;
	return lcfr(m, mod);
}

int lcfi(int n, int m)
{
	int mod;
	do
	{
		mod = n % m;
		n = m;
		m = mod;
	} while (mod != 0);
	return n;
}

int main(int argc, char * argv[])
{
	if (argc != 3)
	{
		cout << "Usage: lcf n m" << endl;
		return 1;
	}
	int n = atoi(argv[1]), m = atoi(argv[2]);
	if (n < m)
	{
		int tmp = n;
		n = m;
		m = tmp;
	}

	cout << "LCF (iterative): " << lcfi(n, m) << endl;
	cout << "LCF (recursive): " << lcfr(n, m) << endl;

	return 0;
}
