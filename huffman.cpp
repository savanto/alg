#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Node
{
	public:
		virtual int weight() = 0;
		virtual bool leaf() = 0;
		friend ostream & operator<<(ostream & os, Node * c);
};

class Char : public Node
{
	private:
		char ch;
		int freq;
	public:
		Char() {}
		Char(char c) : ch(c), freq(0) {}
		Char& operator++() { ++freq; return *this; };
		int weight() { return freq; }
		bool leaf() { return true; }
		char letter() const { return ch; }
};

class Fork : public Node
{
	private:
		Node * leftChild;
		Node * rightChild;
		int wgt;
	public:
		Fork(Node * l, Node * r) : leftChild(l), rightChild(r), wgt(l->weight() + r->weight()) {}
		int weight() { return wgt; }
		bool leaf() { return false; }
		Node * left() const { return leftChild; }
		Node * right() const { return rightChild; }
};

ostream& operator<<(ostream& os, Node * c)
{
	if (c->leaf())
	{
		os << '[';
		char ch = ((Char *) c)->letter();
		switch (ch)
		{
			case '\t':
				os << "tab ";
				break;
			case '\n':
				os << "nl ";
				break;
			default:
				os << ch << ' ';
				break;
		}
		os << c->weight();
		os << ']';
	}
	else
		os << '(' << c->weight() << ')';
	return os;
}

class Heap
{
	private:
		Node ** heap;
		int size;
		void siftdown(int n)
		{
			while (! leaf(n))
			{
				int l = left(n), r = right(n), b;
				if (r < size)
				{
					b = heap[l]->weight() < heap[r]->weight() ? l : r;
					if (heap[n]->weight() > heap[b]->weight())
					{
						swap(n, b);
						n = b;
					}
					else
						return;
				}
				else
				{
					if (heap[n]->weight() > heap[l]->weight())
						swap(n, l);
					return;
				}
			}
		}
		bool leaf(int n) { return n >= size / 2; }
		int left(int n) const { return n * 2 + 1; }
		int right(int n) const { return (n + 1) * 2; }
		int parent(int n) const { return (n - 1) / 2; }
		void swap(int n, int m)
		{
			Node * temp = heap[n];
			heap[n] = heap[m];
			heap[m] = temp;
		}
	public:
		Heap(Node ** h, int s) : heap(h), size(s)
		{
			for (int i = size / 2 - 1; i >= 0; --i)
				siftdown(i);
			for (int i = 0; i < size; ++i)
			{
				while (heap[i]->weight() == 0 && size > 0)
					pop();
			}
		}
		friend ostream & operator<<(ostream & os, const Heap & h);
		int length() { return size; }
		Node * pop()
		{
			if (size > 0)
			{
				swap(0, --size);
				if (size > 0)
					siftdown(0);
				return heap[size];
			}
			return NULL;
		}
		void push(Node * n)
		{
			int i = size++, p = parent(i);
			heap[i] = n;
			while (i != 0 && heap[i]->weight() < heap[p]->weight())
			{
				swap(i, p);
				i = p;
				p = parent(i);
			}
		}
};

ostream& operator<<(ostream& os, const Heap& h)
{
	for (int i = 0; i < h.size; ++i)
		os << h.heap[i];
	return os;
}

class Huffman
{
	private:
		Node * root;
		void print(ostream & os, Node * curr) const
		{
			if (curr == NULL)
				return;
			os << curr << endl;
			if (! curr->leaf())
			{
				print(os, ((Fork *) curr)->left());
				print(os, ((Fork *) curr)->right());
			}
		}
		void print(string s, Node * curr) const
		{
			if (curr == NULL)
				return;
			if (curr->leaf())
			{
				cout << curr << " : " << s << endl;
				return;
			}
			print(s + '0', ((Fork *) curr)->left());
			print(s + '1', ((Fork *) curr)->right());
		}
		int cost(int bits, Node * curr)
		{
			if (curr == NULL)
				return 0;
			if (curr->leaf())
				return bits * curr->weight();
			return cost(bits + 1, ((Fork *) curr)->left()) + cost(bits + 1, ((Fork *) curr)->right());
		}
	public:
		Huffman(Heap & h)
		{
			while (h.length() > 1)
				h.push(new Fork(h.pop(), h.pop()));
			root = h.pop();
		}
		void print() { print("", root); }
		int cost() { return (cost(0, root) + 8) / 8; }
		friend ostream & operator<<(ostream & os, const Huffman & huff);
};

ostream & operator<<(ostream & os, const Huffman & huff) { huff.print(os, huff.root); return os; }

int main(int argc, char * argv[])
{
	if (argc < 2)
	{
		cout << "Usage: huffman <filename>" << endl;
		return 1;
	}

	ifstream fin(argv[1]);
	const int N = 97, MIN = 32, MAX = 126;
	Node * chars[N];
	int i, count = 0;
	for (i = 0; i < N-2; ++i)
		chars[i] = new Char((char) (i+MIN));
	chars[N-2] = new Char('\t');
	chars[N-1] = new Char('\n');

	char ch = fin.get();
	while (! fin.fail())
	{
		switch (ch)
		{
			case '\t':
				++(*((Char *) chars[N-2]));
				++count;
				break;
			case '\n':
				++(*((Char *) chars[N-1]));
				++count;
				break;
			default:
				if (ch >= MIN && ch <= MAX)
				{
					++(*((Char *) chars[ch-MIN]));
					++count;
				}
				break;
		}
		ch = fin.get();
	}


//	for (i = 0; i < N; ++i)
//		cout << chars[i] << endl;
//	cout << "*************************" << endl;
	Heap h(chars, N);
	// Overhead:	length of code int (4 bytes)
	//				ascii char (1 byte * length)
	//				char code int (4 bytes * length)
	int overhead = 4 + h.length() * 5;
//	cout << h;
//	cout << "*************************" << endl;
	Huffman huff(h);
	huff.print();
	int cost = huff.cost();
//	cout << huff;
//	cout << "*************************" << endl;

	cout << "Filesize (ASCII encoding):   " << count << " bytes." << endl;
	cout << "Filesize (Huffman encoding): " << cost + overhead << " bytes (cost = " << cost << ", overhead = " << overhead << ")." << endl;

	return 0;
}
