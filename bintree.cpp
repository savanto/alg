#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

/* Binary Tree Node */
struct Node
{
	int value;
	Node * left;
	Node * right;
	Node(int v, Node * l = NULL, Node * r = NULL) : value(v), left(l), right(r) {}
};

/* Queue Node */
struct QNode
{
	Node * node;
	QNode * next;
	QNode * prev;
	QNode(Node * nd, QNode * nx = NULL, QNode * pr = NULL) : node(nd), next(nx), prev(pr) {}
};

/* Simple Queue */
struct Queue
{
	QNode * head;
	QNode * tail;
	Queue() : head(NULL), tail(NULL) {}
	void enqueue(Node * node)
	{
		if (empty())
			head = tail = new QNode(node);
		else
		{
			tail = new QNode(node, NULL, tail);
			tail->prev->next = tail;
		}
	}
	Node * dequeue()
	{
		QNode * qnode = head;
		if (qnode->next == NULL)
			head = tail = NULL;
		else
		{
			head = qnode->next;
			head->prev = NULL;
		}
		Node * node = qnode->node;
		delete qnode;
		return node;
	}
	bool empty()
	{
		return tail == NULL;
	}
};

/* Insert Node into Binary Search Tree, preserving BST property */
Node * insert(Node * root, int v)
{
	if (root == NULL)
		return new Node(v);
	if (v < root->value)
		root->left = insert(root->left, v);
	else
		root->right = insert(root->right, v);
	return root;
}

/* Traverse Binary Tree Inorder */
void inorder(Node * root)
{
	if (root == NULL)
		return;
	inorder(root->left);
	cout << root->value << ' ';
	inorder(root->right);
}

/* Traverse Binary Tree Reverse Inorder */
void rinorder(Node * root)
{
	if (root == NULL)
		return;
	rinorder(root->right);
	cout << root->value << ' ';
	rinorder(root->left);
}

/* Traverse Binary Tree Preorder */
void preorder(Node * root)
{
	if (root == NULL)
		return;
	cout << root->value << ' ';
	preorder(root->left);
	preorder(root->right);
}

/* Traverse Binary Tree Postorder */
void postorder(Node * root)
{
	if (root == NULL)
		return;
	postorder(root->left);
	postorder(root->right);
	cout << root->value << ' ';
}

/* Depth-first search of Binary Tree */
bool search(Node * root, int s)
{
	if (root == NULL)
		return false;
	if (root->value == s)
		return true;
	return search(root->left, s) || search(root->right, s);
}

/* Traverse Binary Tree Breadth-first */
void breadthfirst(Node * root)
{
	Queue q;
	q.enqueue(root);
	while (! q.empty())
	{
		Node * node = q.dequeue();
		if (node == NULL)
			continue;
		q.enqueue(node->left);
		q.enqueue(node->right);
		cout << node->value << ' ';
	}
}

/* Validate Binary Tree has Binary Search Tree Property */
bool check(Node * root, int low, int high)
{
	if (root == NULL)
		return true;
	if (root->value < low || root->value > high)
		return false;
	return check(root->left, low, root->value - 1) && check(root->right, root->value - 1, high);
}

/* Count levels of Binary Tree */
int height(Node * root, int h)
{
	if (root == NULL)
		return h;
	int left = height(root->left, h + 1);
	int right = height(root->right, h + 1);
	return left > right ? left : right;
}

/* Count leaves of Binary Tree */
int leaves(Node * root)
{
	if (root == NULL)
		return 0;
	if (root->left == NULL && root->right == NULL)
		return 1;
	return leaves(root->left) + leaves(root->right);
}

/* Count parent-nodes in Binary Tree */
int parents(Node * root)
{
	if (root == NULL)
		return 0;
	if (root->left == NULL && root->right == NULL)
		return 0;
	return 1 + parents(root->left) + parents(root->right);
}

/* Traverse and sum all Nodes in BST */
int sum(Node * root)
{
	if (root == NULL)
		return 0;
	return root->value + sum(root->left) + sum(root->right);
}

/* Traverse Binary Tree and print all Nodes who's grandparent Node->value % 5 == 0 */
void grandchild(Node * root, int gen)
{
	if (root == NULL)
		return;
	if (gen == 0)
	{
		cout << root->value << ' ';
		return;
	}
	grandchild(root->left, gen - 1);
	grandchild(root->right, gen - 1);
}
void grandparent(Node * root)
{
	if (root == NULL)
		return;
	if (root->value % 5 == 0)
		grandchild(root, 2);
	grandparent(root->left);
	grandparent(root->right);
}

/* Traverse Binary Tree and print all Nodes with 4 great-grandchildren */
bool greatgrandchildren(Node * root, int gen)
{
	if (root == NULL)
		return false;
	if (gen == 0)
		return true;
	return greatgrandchildren(root->left, gen - 1) && greatgrandchildren(root->right, gen - 1);
}
void greatgrandparent(Node * root)
{
	if (root == NULL)
		return;
	if (greatgrandchildren(root, 3))
		cout << root->value << ' ';
	greatgrandparent(root->left);
	greatgrandparent(root->right);
}

/* Check if value exists in Binary Search Tree */
bool searchBST(Node * root, int s)
{
	if (root == NULL)
		return false;
	if (root->value == s)
		return true;
	if (s < root->value)
		return searchBST(root->left, s);
	return searchBST(root->right, s);
}

/* Count Nodes in Binary Search Tree with values <= k */
int smallcount(Node * root, int k)
{
	if (root == NULL)
		return 0;
	if (k < root->value)
		return smallcount(root->left, k);
	return 1 + smallcount(root->left, k) + smallcount(root->right, k);
}

/* Count Nodes in Binary Search Tree with values >= k */
int largecount(Node * root, int k)
{
	if (root == NULL)
		return 0;
	if (k > root->value)
		return largecount(root->right, k);
	return 1 + largecount(root->left, k) + largecount(root->right, k);
}

/* Output all Nodes from BST in order such that low <= value <= high */
void printrange(Node * root, int low, int high)
{
	if (root == NULL)
		return;
	if (low < root->value)
		printrange(root->left, low, high);
	if (high >= root->value)
	{
		cout << root->value << ' ';
		printrange(root->right, low, high);
	}
}

int main(int argc, char * argv[])
{
	const int N = argc > 1 ? atoi(argv[1]) : 20;
	// Produce random input
	srand(time(NULL));
	Node * bst = NULL;
	cout << "Input: ";
	for (int i = 0; i < N; i++)
	{
		int r = rand() % N;
		cout << r << ' ';

		bst = insert(bst, r);
	}
	cout << endl << "-----------------------------" << endl;

	// 5.21
	cout << "BST is " << (check(bst, 0, N) ? "VALID." : "NOT VALID.") << endl;

	// 5.8
	cout << "BST is " << height(bst, 0) << " levels." << endl;

	// 5.9
	cout << "BST has " << leaves(bst) << " leaves." << endl;
	cout << "BST has " << parents(bst) << " non-leaves." << endl;

	// 5.5
	cout << "Inorder BST:   ";
	inorder(bst);
	cout << endl;
	// 5.18
	cout << "RInorder BST:  ";
	rinorder(bst);
	cout << endl;

	cout << "Preorder BST:  ";
	preorder(bst);
	cout << endl;
	cout << "Postorder BST: ";
	postorder(bst);
	cout << endl;

	// 5.7
	cout << "Breadth-first: ";
	breadthfirst(bst);
	cout << endl;

	// 5.11
	cout << "Grandchildren of Nodes divisible by 5: ";
	grandparent(bst);
	cout << endl;

	// 5.12
	cout << "Nodes with 4 great-grandchildren: ";
	greatgrandparent(bst);
	cout << endl;

	// 5.6
	int s = rand() % N;
	cout << "Value " << s << (search(bst, s) ? " found" : " NOT found") << " in tree." << endl;
	cout << "Value " << s << (searchBST(bst, s) ? " found" : "NOT found") << " in Binary Search Tree." << endl;

	// 5.10
	cout << "Sum of BST: " << sum(bst) << endl;

	// 5.19
	cout << smallcount(bst, s) << " nodes <= " << s << endl;
	cout << largecount(bst, s) << " nodes >= " << s << endl;

	// 5.20
	int low = rand() % N/2, high = rand() % N/2 + N/2;
	cout << "Nodes " << low << " <= node <= " << high << ": ";
	printrange(bst, low, high);
	cout << endl;

	return 0;
}
