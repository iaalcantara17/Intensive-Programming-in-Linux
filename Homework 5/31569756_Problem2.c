#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int opt, numOperands, i;
    while ((opt = getopt(argc, argv, "cduf:s:")) != -1)
    {
        switch (opt)
        {
        case 'c':
            printf("option: %c\n", opt);
            break;
        case 'd':
            printf("option: %c\n", opt);
            break;
        case 'u':
            printf("option: %c\n", opt);
            break;
        case 'f':
            printf("option: %c, option argument: %s\n", opt, optarg);
            break;
        case 's':
            printf("option: %c, option argument: %s\n", opt, optarg);
            break;
        case ':':
            printf("option: %c, missing option argument\n", optopt);
            break;
        case '?':
            printf("Unknown option: %c\n", optopt);
            break;
        }
    }

    numOperands = argc - optind;
    if (numOperands >= 2)
    {
        printf("Input File: %s\n", argv[optind]);
        printf("Output File: %s\n", argv[optind + 1]);
        for (i = optind + 2; i < argc; i++)
            printf("Extra File: %s\n", argv[i]);
    }
    else if (numOperands == 1)
    {
        printf("Input File: %s\n", argv[optind]);
        printf("Missing output file\n");
    }
    else
    {
        printf("Missing input and output files\n");
    }

    return 0;
}

