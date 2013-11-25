#include <iostream>
using namespace std;

// List of Children General Tree
struct LOC
{
	struct Child
	{
		int index;
		Child * next;
		Child(int i) : index(i), next(NULL) {}
	};
	struct Node
	{
		char value;
		int parent;
		Child * children;
		Node(char v, int p) : value(v), parent(p), children(NULL) {}
	};
	Node * nodeArray;
	LOC(Node * na) : nodeArray(na) {}
};

// Binary tree implementation of General Tree
struct GenTree
{
	struct Node
	{
		char value;
		Node * child;
		Node * sibling;
		Node(char v) : value(v), child(NULL), sibling(NULL) {}
	};
	Node * root;
	GenTree(char * serial)
	{
		if (serial[0] != 0 && serial[0] != ')')
		{
			root = new Node(serial[0]);
			int i = 1;
			insert(root, serial, i);
		}
		else
			root = NULL;
	}

	// Add new child with value v to parent
	void insert(Node * parent, char * serial, int & i)
	{
		// Finished processing
		if (serial[i] == 0)
			return;
		while (serial[i] != ')')
		{
			Node * next = parent->child;
			if (next == NULL)
			{
				parent->child = new Node(serial[i]);
				next = parent->child;
			}
			else
			{
				while (next->sibling != NULL)
					next = next->sibling;
				next->sibling = new Node(serial[i]);
				next = next->sibling;
			}
			insert(next, serial, ++i);
		}
		++i;
	}

	// Preorder traversal of tree
	void print(Node * node)
	{
		if (node == NULL)
		{
			cout << ')';
			return;
		}
		cout << node->value;
		print(node->child);
		print(node->sibling);
	}

	void print() { print(root); cout << endl; }
};

int main(int argc, char * argv[])
{
	if (argc < 2)
	{
		cout << "Usage: gentree XPC)Q)RV)M))))" << endl;
		return 1;
	}

	GenTree g(argv[1]);
	g.print();

/*
	int i = 0;
	while (argv[1][i] != 0)
	{
		cout << argv[1][i++] << endl;
	}
*/
	return 0;
}
