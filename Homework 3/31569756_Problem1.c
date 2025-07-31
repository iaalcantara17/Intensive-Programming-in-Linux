#include <stdio.h>
#include <stdlib.h>

int main ()
{
    int dim1, dim2, n;
    FILE *file1, *file2, *outFile;

    file1 = fopen("matrix1.bin", "rb");
    file2 = fopen("matrix2.bin", "rb");
    if (file1 == NULL || file2 == NULL)
    {
        printf("Error: Unable to open one or both matrix files.\n");
        if (file1) fclose(file1);
        if (file2) fclose(file2);
        return 1;
    }

    if (fread(&dim1, sizeof(int), 1, file1) != 1 ||
        fread(&dim2, sizeof(int), 1, file2) != 1)
    {
        printf("Error: Could not read matrix dimensions.\n");
        fclose(file1);
        fclose(file2);
        return 1;
    }

    if (dim1 != dim2 || dim1 > 100)
    {
        printf("Error: Matrices are not compatible or dimension exceeds 100.\n");
        fclose(file1);
        fclose(file2);
        return 1;
    }
    n = dim1;
    int totalElements = n * n * n;

    int (*matrixOne)[n][n] = malloc(totalElements * sizeof(int));
    int (*matrixTwo)[n][n] = malloc(totalElements * sizeof(int));
    long long (*resultMatrix)[n][n] = malloc(totalElements * sizeof(long long));

    if (matrixOne == NULL || matrixTwo == NULL || resultMatrix == NULL)
    {
        printf("Error: Memory allocation failed.\n");
        free(matrixOne);
        free(matrixTwo);
        free(resultMatrix);
        fclose(file1);
        fclose(file2);
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                if (fread(&matrixOne[i][j][k], sizeof(int), 1, file1) != 1)
                {
                    printf("Error reading matrix1 element.\n");
                    free(matrixOne);
                    free(matrixTwo);
                    free(resultMatrix);
                    fclose(file1);
                    fclose(file2);
                    return 1;
                }
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                if (fread(&matrixTwo[i][j][k], sizeof(int), 1, file2) != 1)
                {
                    printf("Error reading matrix2 element.\n");
                    free(matrixOne);
                    free(matrixTwo);
                    free(resultMatrix);
                    fclose(file1);
                    fclose(file2);
                    return 1;
                }
            }
        }
    }

    fclose(file1);
    fclose(file2);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                resultMatrix[i][j][k] = (long long)matrixOne[i][j][k] * (long long)matrixTwo[i][j][k];
            }
        }
    }

    outFile = fopen("result.bin", "wb");
    if (outFile == NULL)
    {
        printf("Error: Could not open result.bin for writing.\n");
        free(matrixOne);
        free(matrixTwo);
        free(resultMatrix);
        return 1;
    }

    if (fwrite(&n, sizeof(int), 1, outFile) != 1)
    {
        printf("Error writing dimension to output file.\n");
        free(matrixOne);
        free(matrixTwo);
        free(resultMatrix);
        fclose(outFile);
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                if (fwrite(&resultMatrix[i][j][k], sizeof(long long), 1, outFile) != 1)
                {
                    printf("Error writing result element.\n");
                    free(matrixOne);
                    free(matrixTwo);
                    free(resultMatrix);
                    fclose(outFile);
                    return 1;
                }
            }
        }
    }

    fclose(outFile);
    free(matrixOne);
    free(matrixTwo);
    free(resultMatrix);

    printf("Matrix multiplication completed successfully!\n");
    return 0;
}

