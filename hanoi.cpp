#include <iostream>
#include <cstdlib>
using namespace std;

struct Disk
{
	int size;
	Disk * down;
	Disk * up;
	Disk(int s) : size(s) {}
};

struct Tower
{
	int height;
	Disk * top;
	Disk * bot;
	Tower() : height(0), top(NULL), bot(NULL) {}
	void push(Disk * disk)
	{
		if (height == 0)
		{
			top = disk;
			top->up = NULL;
			top->down = NULL;
			bot = top;
		}
		else
		{
			top->up = disk;
			disk->down = top;
			top = disk;
			top->up = NULL;
		}
		height++;
	}
	Disk * pop()
	{
		if (height == 0)
			return NULL;
		if (height == 1)
		{
			Disk * disk = top;
			top = NULL;
			bot = NULL;
			height = 0;
			return disk;
		}
		else
		{
			Disk * disk = top;
			top = top->down;
			top->up = NULL;
			height--;
			return disk;
		}
	}
};

void nodisk(const int DISKS)
{
	int i;
	for (i = 0; i < DISKS; i++)
		cout << ' ';
	cout << '|';
	for (i = 0; i < DISKS; i++)
		cout << ' ';
}

// Print towers a, b, c to screen
void print(const Tower towers[], const int DISKS, const int * step)
{
	int n, i, j;
	Disk * diskA, * diskB, *diskC;
	cout << "Step " << *step << endl;
	nodisk(DISKS);
	cout << ' ';
	nodisk(DISKS);
	cout << ' ';
	nodisk(DISKS);
	cout << endl;

	diskA = towers[0].top;
	diskB = towers[1].top;
	diskC = towers[2].top;

	for (n = 0; n < DISKS; n++)
	{
		// tower a
		if (towers[0].height < DISKS - n)
			nodisk(DISKS);
		else
		{ 
			if (towers[0].height > DISKS - n)
				diskA = diskA->down;
			for (i = 0; i < DISKS - diskA->size / 2; i++)
				cout << ' ';
			for (i = 0; i < diskA->size; i++)
				cout << '*';
			for (i = 0; i < DISKS - diskA->size / 2; i++)
				cout << ' ';
		}
		cout << ' ';
		// tower b
		if (towers[1].height < DISKS - n)
			nodisk(DISKS);
		else
		{
			if (towers[1].height > DISKS - n)
				diskB = diskB->down;
			for (i = 0; i < DISKS - diskB->size / 2; i++)
				cout << ' ';
			for (i = 0; i < diskB->size; i++)
				cout << '*';
			for (i = 0; i < DISKS - diskB->size / 2; i++)
				cout << ' ';
		}
		cout << ' ';
		// tower c
		if (towers[2].height < DISKS - n)
			nodisk(DISKS);
		else
		{
			if (towers[2].height > DISKS - n)
				diskC = diskC->down;
			for (i = 0; i < DISKS - diskC->size / 2; i++)
				cout << ' ';
			for (i = 0; i < diskC->size; i++)
				cout << '*';
			for (i = 0; i < DISKS - diskC->size / 2; i++)
				cout << ' ';
		}
		cout << endl;
	}
	for (int t = 0; t < 3; t++)
	{
		for (i = 0; i < DISKS * 2 + 1; i++)
			cout << '-';
		cout << ' ';
	}
	cout << endl;
}

void move(Tower towers[], const int origin, const int dest)
{
	towers[dest].push(towers[origin].pop());
}

void hanoi(Tower towers[], const int a, const int b, const int c, int disk, const int DISKS, int * step)
{
	if (disk == 0)
		return;
	hanoi(towers, a, c, b, disk - 1, DISKS, step);
	move(towers, a, c);
	(*step)++;
	print(towers, DISKS, step);
	hanoi(towers, b, a, c, disk - 1, DISKS, step);
}

int main(int argc, char * argv[])
{
	Tower towers[3];
	int n, * step;

	if (argc < 2)
		n = 6;
	else
		n = atoi(argv[1]);

	for (int i = n - 1; i >= 0; i--)
		towers[0].push(new Disk(i * 2 + 1));

	step = new int(0);
	cout << (*step) << endl;
	print(towers, n, step);
	hanoi(towers, 0, 1, 2, n, n, step);
	return 0;
}
