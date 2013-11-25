#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Node
{
	int value;
	Node * next;
	Node * prev;
	Node(int v, Node * n = NULL, Node * p = NULL) : value(v), next(n), prev(p) {}
};

struct List
{
	Node * first;
	Node * last;
	int length;
	List(Node * f = NULL, Node * l = NULL, int len = 0) : length(len), first(f), last(l) {}
	void append(int v)
	{
		if (last == NULL)
			first = last = new Node(v);
		else
			last = last->next = new Node(v, NULL, last);
		++length;
	}
/*	void insert(Node * node)
	{
		if (last == NULL)
			first = last = node;
		else
			last = last->next = node;
		++length;
	}
*/
	void swap(Node * n, Node * m)
	{
/*
		Node * t = n;
		n->prev->next = t;
		n->next->prev = t;
		n->next = m->next;
		n->prev = m->prev;
		m->prev->next = n;
		m->next->prev = n;
		m->next = t->next;
		m->prev = t->prev;
		t->prev->next = m;
		t->next->prev = m;
*/
		int temp = n->value;
		n->value = m->value;
		m->value = temp;
	}

	void insertionSort()
	{
		Node * i = first->next, * j;
		while (i != NULL)
		{
			j = i;
			while (j != first && j->value < j->prev->value)
			{
				swap(j, j->prev);
				j = j->prev;
			}
			i = i->next;
		}
	}

	void mergeSort()
	{

	}

	void quickSort()
	{
		// For lists of length < 10, do not partition further.
		if (first == last || first == NULL || last == NULL)//length < 10)
			return;
		// Choose pivot, put it at the end
		//int pivot = last->value;
		// Partition list
		Node * left = first, * right = last->prev;
		while (left != right && left->prev != right)
		{
			while (left->value < last->value)
				left = left->next;
			while (right != first && right->value > last->value)
				right = right->prev;
			if (left != right && left->prev != right)
			{
				swap(left, right);
				left = left->next;
				right = right->prev;
			}
		}
		// Place pivot value in final position
		swap(left, last);
		List l1 = List(first, left->prev, 0);
		l1.quickSort();
		List l2 = List(left->next, last, 0);
		l2.quickSort();

	}
	friend ostream & operator<<(ostream & os, const List & list);
};

ostream & operator<<(ostream & os, const List & list)
{
	Node * node = list.first;
	while (node != NULL)
	{
		os << node->value << ' ';
		node = node->next;
	}
	return os;
}

int main(int argc, char * argv[])
{
	const int N = argc > 1 ? atoi(argv[1]) : 20;
	srand(time(NULL));
	List list;
	for (int i = 0; i < N; ++i)
		list.append(rand() % N);
	cout << list << endl;
	list.quickSort();
	cout << list << endl;

	return 0;
}
