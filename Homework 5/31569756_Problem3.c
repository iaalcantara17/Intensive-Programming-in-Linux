#include <stdio.h>
#include <string.h>

void bubbleSort(char **envp)
{
    int count = 0;
    while (envp[count] != NULL)
    {
        count++;
    }
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            char *first = envp[j];
            char *second = envp[j + 1];
            char *eq1 = strchr(first, '=');
            char *eq2 = strchr(second, '=');
            if (!eq1 || !eq2)
            {
                continue;
            }
            char temp1 = *eq1;
            char temp2 = *eq2;
            *eq1 = '\0';
            *eq2 = '\0';
            if (strcmp(first, second) > 0)
            {
                char *temp = envp[j];
                envp[j] = envp[j + 1];
                envp[j + 1] = temp;
            }
            *eq1 = temp1;
            *eq2 = temp2;
        }
    }
}

int main(int argc, char *argv[], char *envp[])
{
    bubbleSort(envp);
    int index = 0;
    while (envp[index] != NULL)
    {
        printf("%s\n", envp[index]);
        index++;
    }
    return 0;
}

