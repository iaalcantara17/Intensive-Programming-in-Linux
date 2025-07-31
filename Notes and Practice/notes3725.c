#include <stdio.h>

void radix_sort_signed(int A[], int n)
{
	int positive[SIZE], negative[SIZE];
	int pos_count = 0, neg_count=0;

	for(int i=0; i<n; i++)
	{
		if (A[i] >= 0)
		{
			positive[pos_count++] = A[i];
		}
		else
		{
			// negating to maintain the correct order.
			negative[neg_count++] = A[i];
		}
	}

	radix_sort(positive, pos_count);
	radix_sort(negative, neg_count);

	// join the buckets:
	
	for(int i=neg_count-1; i>= 0; i--)
	{
		A[neg_count-1-i] = ~negative[i]; // re-negating to maintain the original order
	}

	for(int i=0; i<pos_count; i++)
	{
		A[i+neg_count] = positive[i];
	}
}

int main()
{
	int A[] = {5,1,-3,-1,-5,8,9,7,6};
	int n = sizeof(A)/sizeof(A[0]);

	radix_sort_signed(A, n);

	for(int i=0; i<n; i++)
	{
		printf("%d, ", A[i]);
	}

}
