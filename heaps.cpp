#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Heap
{
	int size;
	int max;
	int * heap;
	Heap(int * h, int n, int m) : heap(h), max(m), size(n > m ? m : n) { heapify(); }
	void heapify()
	{
		for (int i = size/2 - 1; i >= 0; --i)
			sift(i);
	}

	void sift(int n)
	{
		while (! leaf(n))
		{
			int left = leftChild(n), right = rightChild(n);
			if (right < size)	// curr node has two children
			{
				int next = heap[left] > heap[right] ? left : right;
				if (heap[next] > heap[n])
				{
					swap(n, next);
					n = next;
				}
				else
					return;
			}
			else	// curr node has only one child: the left
			{
				if (heap[left] > heap[n])
					swap(n, left);
				return;	// no further children
			}
		}
	}

	void push(int v)
	{
		if (size >= max)
		{
			cout << "Cannot insert: heap is full." << endl;
			return;
		}
		int n = size++, p = parent(n);
		heap[n] = v;
		while (n != 0 && heap[n] > heap[p])
		{
			swap(n, p);
			n = p;
			p = parent(n);
		}
	}

	int pop()
	{
		if (size <= 0)
		{
			cout << "Cannot remove: heap is empty." << endl;
			return -1;
		}
		swap(0, --size);
		sift(0);
		return heap[size];
	}

	bool leaf(int n) { return n >= size / 2; }

	void swap(int n, int m)
	{
		int temp = heap[n];
		heap[n] = heap[m];
		heap[m] = temp;
	}

	int leftChild(int n) { return n * 2 + 1; }
	int rightChild(int n) { return n * 2 + 2; }
	int parent(int n) { return (n - 1) / 2; }

	void print()
	{
		for (int i = 0; i < size; ++i)
			cout << heap[i] << ' ';
		cout << endl;
	}
};

int main(int argc, char * argv[])
{
	const int N = argc > 1 ? atoi(argv[1]) : 20;
	const int M = argc > 2 ? atoi(argv[2]) : 5;
	// Random input
	srand(time(NULL));
	int h[N + M];
	cout << "Input: ";
	for (int i = 0; i < N; ++i)
	{
		h[i] = rand() % N;
		cout << h[i] << ' ';
	}
	cout << endl;

	Heap heap(h, N, N + M);

	// Output heap breadth-first
	cout << "Heapified: ";
	heap.print();

	// Insert
	cout << "Push: ";
	for (int i = 0; i < M; ++i)
	{
		int v = rand() % N;
		cout << v << ' ';
		heap.push(v);
	}
	cout << endl;
	cout << "New heap: ";
	heap.print();

	cout << "Pop " << M << " times: ";
	for (int i = 0; i < M; ++i)
		cout << heap.pop() << ' ';
	cout << endl;
	cout << "New heap: ";
	heap.print();


	return 0;
}
