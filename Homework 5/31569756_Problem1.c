#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    unsigned char *ptr;
    int i;
    ptr = (unsigned char*)&argv;
    printf("argv    | ");
    for (i = 7; i >= 0; i--)
    {
        printf("%02hhx ", *(ptr + i));
    }
    printf("| %p\n\n", (void*)&argv);
    for (i = 0; i < argc; i++)
    {
        ptr = (unsigned char*)&argv[i];
        printf("argv[%d] | ", i);
        for (int j = 7; j >= 0; j--)
        {
            printf("%02hhx ", *(ptr + j));
        }
        printf("| %p\n", (void*)&argv[i]);
    }
    printf("\n");
    ptr = (unsigned char*)argv[0];
    while ((unsigned long)ptr % 8 != 0)
    {
        ptr--;
    }
    unsigned char *end = (unsigned char*)argv[argc - 1] + strlen(argv[argc - 1]) + 1;
    while ((unsigned long)end % 8 != 0)
    {
        end++;
    }
    while (ptr < end)
    {
        unsigned char hexbuf[8];
        unsigned char ascii[8];
        for (int j = 0; j < 8; j++)
        {
            hexbuf[j] = ptr[j];
            if (isprint(ptr[j]))
            {
                ascii[j] = ptr[j];
            }
            else
            {
                ascii[j] = '.';
            }
        }
        for (int j = 0; j < 8; j++)
        {
            printf("%02hhx ", hexbuf[j]);
        }
        printf("| %p | ", (void*)ptr);
        for (int j = 0; j < 8; j++)
        {
            printf("%c", ascii[j]);
        }
        printf("\n");
        ptr += 8;
    }
    return 0;
}

