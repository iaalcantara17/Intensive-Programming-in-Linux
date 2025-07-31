#include <stdio.h>
#define MAX_SIZE 100

void radixSort( unsigned int A[], unsigned int n )
{
    unsigned int bucket0[100], bucket1[100];
    unsigned int mask, count0, count1;
    int d, i;
    for ( d = 0; d < 32; d++ )
    {
        mask = 1 << d;
        count0 = 0;
        count1 = 0;
        for ( i = 0; i < n; i++ )
        {
            if ((A[i] & mask) == 0)
            {
                bucket0[count0++] = A[i];
            }
            else
            {
                bucket1[count1++] = A[i];
            }
        }
        for ( i = 0; i < count0; i++ )
        {
            A[i] = bucket0[i];
        }
        for ( i = 0; i < count1; i++ )
        {
            A[count0 + i] = bucket1[i];
        }
    }
}

void realRadixSort( float A[], unsigned int n )
{
    unsigned int positive[100], negative[100];
    unsigned int pCount = 0, nCount = 0;
    unsigned int i;
    for ( i = 0; i < n; i++ )
    {
        unsigned int *p = (unsigned int *)&A[i];
        if ( A[i] >= 0 )
        {
            positive[pCount++] = *p;
        }
        else
        {
            unsigned int neg = *p ^ 0xFFFFFFFF;
            negative[nCount++] = neg;
        }
    }
    radixSort( positive, pCount );
    radixSort( negative, nCount );
    for ( i = 0; i < nCount; i++ )
    {
        unsigned int neg = negative[i] ^ 0xFFFFFFFF;
        float *f = (float *)&neg;
        A[i] = *f;
    }
    for ( i = 0; i < pCount; i++ )
    {
        float *f = (float *)&positive[i];
        A[nCount + i] = *f;
    }
}

int main()
{
    unsigned int arrayAmount, i = 0;
    scanf("%u", &arrayAmount);
    if ( arrayAmount > 100 || arrayAmount == 0 )
    {
        return 1;
    }
    float arr[MAX_SIZE];
    for ( i = 0; i < arrayAmount; i++ )
    {
        if ( scanf("%f", &arr[i]) != 1 )
        {
            return 1;
        }
    }
    realRadixSort( arr, arrayAmount );
    for ( i = 0; i < arrayAmount; i++ )
    {
        printf("%f\n", arr[i]);
    }
    return 0;
}

