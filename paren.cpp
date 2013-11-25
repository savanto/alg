#include <iostream>
using namespace std;

struct Node
{
	char c;
	Node * next;
	Node() {}
	Node(char ch, Node * n = NULL) : c(ch), next(n) {}
};

struct Stack
{
	Node * top;
	Stack() : top(new Node()) {}
	void push(char c)
	{
		top->next = new Node(c, top->next);
	}
	char pop()
	{
		if (empty())
			return 0;
		Node * n = top->next;
		char c = n->c;
		top->next = n->next;
		delete n;
		return c;
	}
	bool empty()
	{
		return top->next == NULL;
	}	
};

int main(int argc, char * argv[])
{
	if (argc < 2)
		return 1;
	int i = 0;
	char c = argv[1][i];
	Stack s;
	while (c != 0)
	{
		if (c == '(')
			s.push(c);
		else if (c == ')')
		{
			if (s.pop() != '(')
			{
				cout << "INVALID" << endl;
				return 0;
			}
		}
		c = argv[1][++i];
	}
	if (! s.empty())
		cout << "INVALID" << endl;
	else
		cout << "VALID" << endl;

	return 0;
}
