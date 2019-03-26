#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

int main(int argc, char *argv[], char *envp[])
{

    for (int i = 0; i < argc; i++)
    {
        printf("For argc = %i -> %s\n", i, argv[i]);
    }

    if (argc < 2)
    {
        printf("argv from user is void\n");
        argv[1] = "./";
    }

    DIR *dir_ptr = opendir(argv[1]);
    if (dir_ptr == NULL)
    {
        printf("Error from opendir()\n");
        exit(-1);
    }
    printf("open ok\n\n");

    struct dirent *dir_struct = readdir(dir_ptr);
    printf("%s\n", dir_struct->d_name);

    while ((dir_struct = readdir(dir_ptr)) != NULL)
    {
        printf("%s\n", dir_struct->d_name);
    }

    if (closedir(dir_ptr) == -1)
    {
        printf("Error from closedir()\n");
        exit(-1);
    }
    printf("\nclose ok\n");

    return 0;
}