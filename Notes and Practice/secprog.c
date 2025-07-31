#include <stdlib.h>
#include <stdio.h>

int main()
{
	int num, result=1;
	printf("Etner a number: ");
	scanf("%d", &num);

	for (int i=1; i<=num; i++)
	{
		result = result * i;
	}

	printf("the factorial is %d", result);
}
