#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#define MAX_PATH 1000

int countTxtLines(const char *path)
{
    DIR *dp = opendir(path);
    if (dp == NULL)
    {
        const char *ext = strrchr(path, '.');
        if (ext == NULL || strcmp(ext, ".txt") != 0)
            return 0;
        FILE *fp = fopen(path, "r");
        if (fp == NULL)
        {
            printf("Cannot open file: %s\n", path);
            return 0;
        }
        int lines = 0;
        char ch;
        while ((ch = fgetc(fp)) != EOF)
        {
            if (ch == '\n')
                lines++;
        }
        fclose(fp);
        return lines;
    }
    else
    {
        int total = 0;
        struct dirent *entry;
        char fullPath[MAX_PATH];
        while ((entry = readdir(dp)) != NULL)
        {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            snprintf(fullPath, sizeof(fullPath), "%s/%s", path, entry->d_name);
            total += countTxtLines(fullPath);
        }
        closedir(dp);
        return total;
    }
}

int main()
{
    char directory[MAX_PATH];
    printf("Enter directory path: ");
    scanf("%s", directory);
    int lineCount = countTxtLines(directory);
    printf("Total lines in .txt files: %d\n", lineCount);
    return 0;
}

