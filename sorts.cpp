#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void swap(int array[], int n, int m)
{
	if (array[n] != array[m])
	{
		int temp = array[n];
		array[n] = array[m];
		array[m] = temp;
	}
}

struct O
{
	int swaps;
	int iters;
	O(int s = 0, int i = 0) : swaps(s), iters(i) {}
	O & operator+=(const O & rhs) {	swaps += rhs.swaps;	iters += rhs.iters;	return *this; }
	O & operator++() { ++swaps; ++iters; return *this; }
};

ostream & operator<<(ostream & os, const O & o) { os << o.swaps << " swaps, " << o.iters << " iterations."; return os; }

// Insertion Sort
// Traverse list swapping adjacent elements until values are inserted into correct positions.
// Best case: array already sorted, no swaps, O(n)
// Average case: O(1/4 * n^2)
// Worst case: O(1/2 * n^2)
O InsertionSort(int array[], const int N)
{
	O o;
	for (int i = 1; i < N; ++i)
		for (int j = i; j > 0; --j)
		{
			++o.iters;
			if (array[j] > array[j-1])
				break;
			swap(array, j, j-1);
			++o.swaps;
		}
	return o;
}

// Bubble Sort
// Traverse list swapping adjacent elements until values "bubble" up into correct positions.
// Best/average/worst cases: O(1/2 n^2)
O BubbleSort(int array[], const int N)
{
	O o;
	for (int i = 0; i < N; ++i)
		for (int j = N-1; j > i; --j)
		{
			if (array[j] < array[j-1])
			{
				swap(array, j, j-1);
				++o.swaps;
			}
			++o.iters;
		}
	return o;
}

// Selection Sort
// Traverse list, selecting smallest value and placing it at the top. Repeat until all elements are in the correct positions.
// Swaps: O(n) - O(1/2 n)
// Iters: O(1/2 n^2)
O SelectionSort(int array[], const int N)
{
	O o;
	for (int i = 0; i < N-1; ++i)
	{
		int min = i;
		for (int j = N-1; j > i; --j)
		{
			if (array[j] < array[min])
				min = j;
			++o.iters;
		}
		if (min != i)
		{
			swap(array, i, min);
			++o.swaps;
		}
	}
	return o;
}

// Shell Sort
// Optimized Insertion sort: traverse the list using various increments, partially sorting each time,
// finishing with a standard Insertion sort. Takes advantage of Insertion sort best case low O(n).
// Swaps: O(n log n) - O(2n log n)
// Iters: O(3n log n) - O(4n log n)
O ShellSort(int array[], const int N)
{
	O o;
	if (N < 2)
		return o;

	const int INCS[] = { 701, 301, 132, 57, 23, 10, 4, 1 }, NINCS = 8;
	int n = 0;
	for (; n < NINCS && INCS[n] >= N; ++n) {}

	for (; n < NINCS; ++n)
	{
		int inc = INCS[n];
		for (int sub = 0; sub < inc; ++sub)
		{
			for (int i = inc+sub; i < N; i+=inc)
			{
				for (int j = i; j >= inc; j-=inc)
				{
					++o.iters;
					if (array[j] > array[j-inc])
						break;
					swap(array, j, j-inc);
					++o.swaps;
				}
			}
		}
	}

	return o;
}

// Merge Sort
// Divide and conquer: break list of length n in half recursively until there are n lists of length 1.
// Merge the lists back together element by element, until the resulting list is sorted.
// Can be optimized by splitting down to a certain threshhold, ~7-9 elements, and using insertion sort on those,
// then merging the results.
// Requires additional space O(n)
// Best/avg/worst cases: O(n log n)
O MergeSort(int array[], int temp[], int left, int right)
{
	// Only 1 element: done splitting
	if (left == right)
		return O(1);
	// Split subarrays in half recursively
	int mid = (right + left) / 2, i;
	O o;
	o += MergeSort(array, temp, left, mid);
	o += MergeSort(array, temp, mid+1, right);
	// Make temp copy
	for (i = left; i <= right; ++i)
	{
		temp[i] = array[i];
		++o.iters;
	}
	// Merge arrays together
	int i1 = left, i2 = mid + 1;
	for (i = left; i <= right; ++i)
	{
		if (i1 == mid + 1)	// Left sublist empty
			array[i] = temp[i2++];
		else if (i2 > right)// Right sublist empty
			array[i] = temp[i1++];
		else if (temp[i1] < temp[i2])
			array[i] = temp[i1++];
		else
			array[i] = temp[i2++];
		++o.iters;
	}
	return o;
}

// Quick Sort
// Choose pivot and partition array such that all values less than pivot are on one side, greather than on the other.
// Recursively partition the subpartitions until partitions are length <= 1.
// Can be optimized by dividing down to a certain threshhold, ~9 elements, and leaving them alone.
// After finished, array is "nearly" sorted, so a single call to insertion sort can complete the job.
// Running time O(n log n)
O QuickSort(int array[], int left, int right)
{
	O o;
	if (left < right)	// more than 1 element
	{
		// Choose pivot to be some central element
		int pivot = (left + right) / 2;
		// Place pivot at the end, so it won't be touched
		swap(array, pivot, right);
		++o.swaps;
		int l = left, r = right - 1;
		// Traverse partition from both ends
		while (l <= r)
		{
			// Move rightward if left cursor is smaller than pivot
			while (array[l] < array[right])
			{
				++l;
				++o.iters;
			}
			// Move leftward if right cursor is greater than pivot
			while (array[r] > array[right])
			{
				--r;
				++o.iters;
			}
			// If cursors have still not overlapped
			if (l <= r)
			{
				// Swap the elements at the two cursors
				swap(array, l, r);
				++o.swaps;
				// Advance the cursors forward
				++l;
				--r;
			}
		}
		// Place pivot back to where it belongs: end of left partition
		swap(array, l, right);
		++o.swaps;
		// Recursively quicksort left and right partitions on either side of pivot
		o += QuickSort(array, left, l-1);
		o += QuickSort(array, l+1, right);
	}
	return o;
}

// Heap Sort
// Convert array into a max-heap (running time O(n) since all values are available at the start).
// Use standard heapify/siftdown algorithm.
// To produce sorted array, repeatedly remove max value and reheapify (time O(log n)).
// Since "removal" of max value actually places it at the end of the array, once heap
// is "empty", array is sorted in ascending order.
// Total running time in best/worst/avg cases is O(n log n)
O HeapSort(int array[], const int N)
{
	O o;
	int n = N;
	// Heapify array
	for (int i = n / 2 - 1; i >= 0; --i)
	{
		// Sift down smaller values until a leaf is reached
		int j = i;
		while (j < n / 2)
		{
			// If right child exists
			int left = j * 2 + 1, right = j * 2 + 2;
			if (right < n)
			{
				int biggerChild = array[left] > array[right] ? left : right;
				if (array[biggerChild] > array[j])
				{
					swap(array, j, biggerChild);
					++o.swaps;
					j = biggerChild;
				}
				else
					break;
			}
			else	// No right child, only the left
			{
				if (array[left] > array[j])
				{
					swap(array, j, left);
					++o.swaps;
				}
				break;	// no further children
			}
			++o.iters;
		}
	}
	// Remove max value from heap until it is "empty"
	while (n > 0)
	{
		// Remove max value by placing it at the end
		swap(array, 0, --n);
		++o.swaps;
		// Sift down swapped value to maintain heap
		int j = 0;
		while (j < n / 2)	// while not a leaf node
		{
			// If right child exists
			int left = j * 2 + 1, right = j * 2 + 2;
			if (right < n)
			{
				int biggerChild = array[left] > array[right] ? left : right;
				if (array[biggerChild] > array[j])
				{
					swap(array, j, biggerChild);
					++o.swaps;
					j = biggerChild;
				}
				else
					break;	// done sifting
			}
			else	// only left child
			{
				if (array[left] > array[j])
				{
					swap(array, j, left);
					++o.swaps;
				}
				break;	// done sifting
			}
			++o.iters;
		}
	}
	return o;
}

O RadixSort(int array[], const int N)
{
	O o;
	// Number of bins
	const int R = 10;
	// Determine number of digits k
	int k = 1, i, r, j;
	for (i = R; (N-1) / i > 0; i *= R, ++k)
		++o.iters;

	// For k digits
	for (i = 0, r = 1; i < k; ++i, r *= R)
	{
		// Initialize counts array
		int counts[R] = { 0 };
		o.iters += R;

		// Count number of records for each bin
		for (j = 0; j < N; ++j)
		{
			++(counts[(array[j]/r)%R]);
			++o.iters;
		}

		// Index bins: count[j] will be the index for the last slot of bin j
		for (j = 1; j < R; ++j)
		{
			counts[j] += counts[j-1];
			++o.iters;
		}

		// Put records into bins, work from bottom of each bin
		// Since bins fill from bottom, j counts downward
		int bins[N];
		for (j = N - 1; j >= 0; --j)
		{
			bins[--(counts[(array[j]/r)%R])] = array[j];
			++o.iters;
		}

		// Copy bins back to array
		for (j = 0; j < N; ++j)
		{
			array[j] = bins[j];
			++o.iters;
		}
	}
	return o;
}

void print(const char title[], const int array[], const int N);

int main(int argc, char * argv[])
{
	const int N = argc > 1 ? atol(argv[1]) : 20;
	const bool SHOW = N <= 50;
	const bool SLOW = N <= 1000;
	int i, n;

	int inputs[N];
	// Insertion sort
	int sortedInsertion[N], reverseInsertion[N], randomInsertion[N];
	// Bubble sort
	int sortedBubble[N], reverseBubble[N], randomBubble[N];
	// Selection sort
	int sortedSelection[N], reverseSelection[N], randomSelection[N];
	// Shell sort
	int sortedShell[N], reverseShell[N], randomShell[N];
	// Merge sort
	int sortedMerge[N], reverseMerge[N], randomMerge[N];
	// Quick sort
	int sortedQuick[N], reverseQuick[N], randomQuick[N];
	// Heap sort
	int sortedHeap[N], reverseHeap[N], randomHeap[N];
	// Radix sort
	int sortedRadix[N], reverseRadix[N], randomRadix[N];

	srand(time(NULL));
	for (i = 0; i < N; ++i)
	{
		n = rand() % N;

		inputs[i] = n;

		if (SLOW)
		{
			// Insertion sort
			sortedInsertion[i] = i;
			reverseInsertion[i] = N-i;
			randomInsertion[i] = n;
			// Bubble sort
			sortedBubble[i] = i;
			reverseBubble[i] = N-i;
			randomBubble[i] = n;
			// Selection sort
			sortedSelection[i] = i;
			reverseSelection[i] = N-i;
			randomSelection[i] = n;
			// Shell sort
			sortedShell[i] = i;
			reverseShell[i] = N-i;
			randomShell[i] = n;
		}
		// Merge sort
		sortedMerge[i] = i;
		reverseMerge[i] = N-i;
		randomMerge[i] = n;
		// Quick sort
		sortedQuick[i] = i;
		reverseQuick[i] = N-i;
		randomQuick[i] = n;
		// Heap sort
		sortedHeap[i] = i;
		reverseHeap[i] = N-i;
		randomHeap[i] = n;
		// Radix sort
		sortedRadix[i] = i;
		reverseRadix[i] = N-i;
		randomRadix[i] = n;
	}

	if (SLOW)
	{
		// Insertion sort
		cout << "*** Insertion Sort ***" << endl;
		cout << "----------------------------------------------------------------------------" << endl;
		cout << "Sorted array:  " << InsertionSort(sortedInsertion, N)  << endl;
		cout << "Reverse array: " << InsertionSort(reverseInsertion, N) << endl;
		cout << "Random array:  " << InsertionSort(randomInsertion, N)  << endl;
		cout << "****************************************************************************" << endl;
		// Bubble sort
		cout << "*** Bubble Sort ***" << endl;
		cout << "----------------------------------------------------------------------------" << endl;
		cout << "Sorted array:  " << BubbleSort(sortedBubble, N)  << endl;
		cout << "Reverse array: " << BubbleSort(reverseBubble, N) << endl;
		cout << "Random array:  " << BubbleSort(randomBubble, N)  << endl;
		cout << "****************************************************************************" << endl;
		// Selection sort
		cout << "*** Selection Sort ***" << endl;
		cout << "----------------------------------------------------------------------------" << endl;
		cout << "Sorted array:  " << SelectionSort(sortedSelection, N)  << endl;
		cout << "Reverse array: " << SelectionSort(reverseSelection, N) << endl;
		cout << "Random array:  " << SelectionSort(randomSelection, N)  << endl;
		cout << "****************************************************************************" << endl;
		// Shell sort
		cout << "*** Shell Sort ***" << endl;
		cout << "----------------------------------------------------------------------------" << endl;
		cout << "Sorted array:  " << ShellSort(sortedShell, N)  << endl;
		cout << "Reverse array: " << ShellSort(reverseShell, N) << endl;
		cout << "Random array:  " << ShellSort(randomShell, N)  << endl;
		cout << "****************************************************************************" << endl;
	}
	// Merge sort
	int temp[N];
	cout << "*** Merge Sort ***" << endl;
	cout << "----------------------------------------------------------------------------" << endl;
	cout << "Sorted array:  " << MergeSort(sortedMerge, temp, 0, N-1)  << endl;
	cout << "Reverse array: " << MergeSort(reverseMerge, temp, 0, N-1) << endl;
	cout << "Random array:  " << MergeSort(randomMerge, temp, 0, N-1)  << endl;
	cout << "****************************************************************************" << endl;
	// Quick sort
	cout << "*** Quick Sort ***" << endl;
	cout << "----------------------------------------------------------------------------" << endl;
	cout << "Sorted array:  " << QuickSort(sortedQuick, 0, N-1)  << endl;
	cout << "Reverse array: " << QuickSort(reverseQuick, 0, N-1) << endl;
	cout << "Random array:  " << QuickSort(randomQuick, 0, N-1)  << endl;
	cout << "****************************************************************************" << endl;
	// Heap sort
	cout << "*** Heap Sort ***" << endl;
	cout << "----------------------------------------------------------------------------" << endl;
	cout << "Sorted array:  " << HeapSort(sortedHeap, N)  << endl;
	cout << "Reverse array: " << HeapSort(reverseHeap, N) << endl;
	cout << "Random array:  " << HeapSort(randomHeap, N)  << endl;
	cout << "****************************************************************************" << endl;
	// Radix sort
	cout << "*** Radix Sort ***" << endl;
	cout << "----------------------------------------------------------------------------" << endl;
	cout << "Sorted array:  " << RadixSort(sortedRadix, N)  << endl;
	cout << "Reverse array: " << RadixSort(reverseRadix, N) << endl;
	cout << "Random array:  " << RadixSort(randomRadix, N)  << endl;
	cout << "****************************************************************************" << endl;

	
	if (SHOW)
	{
		cout << "****************************************************************************" << endl;
		cout << endl;
		print("Inputs :        ", inputs, N);
		cout << "----------------------------------------------------------------------------" << endl;
		print("Insertion Sort: ", randomInsertion, N);
		print("Bubble Sort:    ", randomBubble, N);
		print("Selection Sort: ", randomSelection, N);
		print("Shell Sort:     ", randomShell, N);
		print("Merge Sort:     ", randomMerge, N);
		print("Quick Sort:     ", randomQuick, N);
		print("Heap Sort:      ", randomHeap, N);
		print("Radix Sort:     ", randomRadix, N);
	}

	return 0;
}

void print(const char title[], const int array[], const int N)
{
	cout << title;
	for (int i = 0; i < N; ++i)
		cout << array[i] << ' ';
	cout << endl;
}
