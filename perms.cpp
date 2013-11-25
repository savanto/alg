#include <iostream>
#include <cstdlib>
using namespace std;

void perms(int p[], int n, int q[], int o)
{
	if (n == 1)
	{
		for (int i = 0; i < o; i++)
			cout << q[i] << ' ';
		cout << p[0] << endl;
		return;
	}
	for (int i = 0; i < n; i++)
	{
		int r[n-1], s[o+1], j;
		for (j = 0; j < i; j++)
			r[j] = p[j];
		for (j = i + 1; j < n; j++)
			r[j-1] = p[j];
		for (j = 0; j < o; j++)
			s[j] = q[j];
		s[o] = p[i];
		perms(r, n - 1, s, o + 1);
	}
}

int main(int argc, char * argv[])
{
	if (argc < 2)
	{
		cout << "Usage: perms <a[, b[, c[, ...[, z]]]]>" << endl;
		return 1;
	}
	int n = argc - 1, p[n], o = 0, q[o];
	for (int i = 0; i < n; i++)
		p[i] = atoi(argv[i+1]);

	perms(p, n, q, o);

	return 0;
}
