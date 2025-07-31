#include <stdio.h>
#define MAX_SIZE 100

void radixSort( unsigned int A[], unsigned int n )
{
    unsigned int bucket[16][MAX_SIZE];
    unsigned int count[16] = {0};
    unsigned int mask;
    unsigned int d, i, j, k;
    for ( d = 0; d < 8; d++ )
    {
        mask = 0xF << (d * 4);
        for ( i = 0; i < n; i++ )
        {
            int index = (A[i] & mask) >> (d * 4);
            bucket[index][ count[index] ] = A[i];
            count[index]++;
        }
        for ( i = 0, j = 0; i < 16; i++ )
        {
            for ( k = 0; k < count[i]; k++ )
            {
                A[j++] = bucket[i][k];
            }
            count[i] = 0;
        }
    }
}

int main()
{
    unsigned int arrayAmount;
    int intArray[MAX_SIZE];
    unsigned int transArray[MAX_SIZE];
    unsigned int i;
    
    if ( scanf("%u", &arrayAmount) != 1 || arrayAmount > MAX_SIZE || arrayAmount == 0 )
    {
        return 1;
    }
    
    for ( i = 0; i < arrayAmount; i++ )
    {
        if ( scanf("%d", &intArray[i]) != 1 )
        {
            return 1;
        }
    }
    
    for ( i = 0; i < arrayAmount; i++ )
    {
        transArray[i] = intArray[i] ^ 0x80000000;
    }
    
    radixSort( transArray, arrayAmount );
    
    for ( i = 0; i < arrayAmount; i++ )
    {
        intArray[i] = transArray[i] ^ 0x80000000;
    }
    
    for ( i = 0; i < arrayAmount; i++ )
    {
        printf("%d\n", intArray[i]);
    }
    
    return 0;
}

