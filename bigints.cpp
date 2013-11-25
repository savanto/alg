#include <iostream>
using namespace std;

struct Digit
{
	int digit;
	Digit * next;
	Digit() {}
	Digit(int d, Digit * n = NULL) : digit(d), next(n) {}
};

struct Bigint
{
	Digit * ones;
	Bigint() : ones(new Digit()) {}
	Bigint(char bigint[])
	{
		ones = new Digit();
		int i = 0;
		while (bigint[i] != 0)
		{
			if (bigint[i] >= '0' && bigint[i] <= '9')
				push(bigint[i] - '0');
			i++;
		}
	}
	void push(int digit)
	{
		ones->next = new Digit(digit, ones->next);
	}
};

ostream & operator<<(ostream & os, const Bigint & rhs)
{
	Digit * n = rhs.ones->next;
	while (n != NULL && n->digit == 0)
		n = n->next;
	if (n == NULL)
		os << 0;
	else
	{
		while (n != NULL)
		{
			os << n->digit;
			n = n->next;
		}
	}
	return os;
}

Bigint operator+(const Bigint & lhs, const Bigint & rhs)
{
	Digit * place1 = lhs.ones->next, * place2 = rhs.ones->next;
	int carry = 0;
	Bigint r;
	while (place1 != NULL && place2 != NULL)
	{
		r.push((place1->digit + place2->digit + carry) % 10);
		carry = (place1->digit + place2->digit + carry) / 10;
		place1 = place1->next;
		place2 = place2->next;
	}
	while (place2 != NULL)
	{
		r.push((place2->digit + carry) % 10);
		carry = (place2->digit + carry) / 10;
		place2 = place2->next;
	}

	while (place1 != NULL)
	{
		r.push((place1->digit + carry) % 10);
		carry = (place1->digit + carry) / 10;
		place1 = place1->next;
	}
	if (carry != 0)
		r.push(carry);

	return r;
}

int main(int argc, char * argv[])
{
	if (argc != 4)
	{
		cout << "Usage: bigint <int> [+,-,*,^] <int>" << endl;
		return 1;
	}
	Bigint n = Bigint(argv[1]);
	char op = argv[2][0];
	Bigint m = Bigint(argv[3]);

	switch (op)
	{
		case '+':
			cout << n + m << endl;
			break;
		default:
			cout << "Operation " << op << " not supported." << endl;
			break;
	}

	return 0;
}
