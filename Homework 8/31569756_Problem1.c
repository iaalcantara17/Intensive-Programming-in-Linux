#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size;
    char filename[256];
    unsigned int *data = NULL;
    int numInts;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
        scanf("%s", filename);
    MPI_Bcast(filename, 256, MPI_CHAR, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        FILE *fp = fopen(filename, "rb");
        if (!fp) exit(1);
        fseek(fp, 0, SEEK_END);
        long fileSize = ftell(fp);
        numInts = fileSize / sizeof(unsigned int);
        rewind(fp);
        data = malloc(numInts * sizeof(unsigned int));
        fread(data, sizeof(unsigned int), numInts, fp);
        fclose(fp);
    }

    MPI_Bcast(&numInts, 1, MPI_INT, 0, MPI_COMM_WORLD);
    int chunkSize = numInts / size;
    unsigned int *localData = malloc(chunkSize * sizeof(unsigned int));

    MPI_Scatter(data, chunkSize, MPI_UNSIGNED,
                localData, chunkSize, MPI_UNSIGNED,
                0, MPI_COMM_WORLD);
    if (rank == 0)
        free(data);

    int localCounts[1000];
    int globalCounts[1000];
    memset(localCounts, 0, sizeof(localCounts));

    for (int i = 0; i < chunkSize; i++)
        localCounts[localData[i]]++;

    MPI_Reduce(localCounts, globalCounts, 1000, MPI_INT,
               MPI_SUM, 0, MPI_COMM_WORLD);
    free(localData);

    if (rank == 0) {
        unsigned int *sortedData = malloc(numInts * sizeof(unsigned int));
        int idx = 0;
        for (int v = 0; v < 1000; v++)
            for (int c = 0; c < globalCounts[v]; c++)
                sortedData[idx++] = v;

        FILE *fp = fopen(filename, "r+b");
        fwrite(sortedData, sizeof(unsigned int), numInts, fp);
        fclose(fp);
        free(sortedData);
    }

    MPI_Finalize();
    return 0;
}

