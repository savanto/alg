#include <iostream>
using namespace std;

struct Node
{
	char ch;
	Node * next;
	Node() {}
	Node(char c, Node * n = NULL) : ch(c), next(n) {}
};

struct Stack
{
	Node * top;
	Stack() : top(new Node()) {}
	void push(char ch)
	{
		top->next = new Node(ch, top->next);
	}
	char pop()
	{
		if (! empty())
		{
			Node * n = top->next;
			char ch = n->ch;
			top->next = n->next;
			delete n;
			return ch;
		}
		return 0;
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
	Stack s;
	for (int i = 1; i < argc; i++)
		s.push(argv[i][0]);
	while (! s.empty())
		cout << s.pop() << ' ';
	cout << endl;

	return 0;
}
