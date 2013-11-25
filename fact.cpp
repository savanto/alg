#include <iostream>
#include <cstdlib>
using namespace std;

// n! = (n - 1)! * n for n > 1; 1! = 0! = 1
long factr(long n)
{
	if (n < 0 || n > 25)	// Error
		return -1;
	if (n <= 1)
		return 1;
	return n * factr(n - 1);
}

long facti(int n)
{
	if (n < 0 || n > 25)	// Error
		return -1;
	long f = 1;
	for (int i = 1; i <= n; i++)
		f *= i;
	return f;
}
		
int main(int argc, char * argv[])
{
	if (argc < 2)
	{
		long f = 1, n = 1;
		while (true)
		{
			cout << f << endl;
			n++;
			f *= n;
		}
		return 0;
	}
	while (argc > 1)
	{
		long n = atol(argv[argc-1]);
		cout << "n! (iterative): " << facti(n) << endl;
		cout << "n! (recursive): " << factr(n) << endl;
		argc--;
	}

	return 0;
}
