#include <iostream>
#include <cstdlib>
using namespace std;

// fib(n) = fib(n - 1) + fib(n - 2) for n > 2; fib(1) = fib(2) = 1
long fib(int n)
{
	if (n <= 0)	// Error
		return 0;
	if (n == 1) // fib(1) = 1
		return 1;
	if (n == 2) // fib(2) = 1
		return 1;
	return fib(n - 1) + fib(n - 2);
}

int main (int argc, char * argv[])
{
	if (argc < 2)
	{
		long a = 1, b = 1;
		cout << a << ' ' << b << ' ';
		while (true)
		{
			b += a;
			cout << b << ' ';
			a += b;
			cout << a << ' ';
		}
		return 0;
	}
	while (argc > 1)
	{
		cout << fib(atoi(argv[argc-1])) << endl;
		argc--;
	}

	return 0;
}
