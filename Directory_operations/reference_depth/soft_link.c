#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

#define DEPTH 50

//#define LINK_NAME "ref"

int main(int argc, char *argv[], char *envp[])
{

    FILE *fd = fopen("test_file.txt", "w");
    if (fd == NULL)
    {
        printf("ERROR CREAT FILE FOR TEST\n");
        exit(0);
    }
    fclose(fd);

    char buffer[20000];
    char link_name[20000] = "ref";

    for (int i = 1; i <= DEPTH; i++)
    {

        printf("iteration %i\n", i);
        char *link_name = (char *)malloc(20000 * sizeof(char));
        char *link_name_old = (char *)malloc(20000 * sizeof(char));

        link_name[0] = 'r';
        link_name[1] = 'e';
        link_name[2] = 'f';
        link_name[3] = '\0';

        link_name_old[0] = 'r';
        link_name_old[1] = 'e';
        link_name_old[2] = 'f';
        link_name_old[3] = '\0';

        sprintf(buffer, "%d", i);
        strcat(link_name, buffer);
        printf("NOW LINK NAME %s\n", link_name);

        if (i == 1)
        {
            if (symlink("test_file.txt", link_name) < 0)
            {
                printf("ERROR CREAT SOFT LINK\n");
                exit(0);
            }
        }

        if (i > 1)
        {
            sprintf(buffer, "%d", i - 1);
            strcat(link_name_old, buffer);

            printf("OLD NAME FOR REFERENCE %s\n", link_name_old);
            if (symlink(link_name_old, link_name) < 0)
            {
                printf("ERROR CREAT SOFT LINK\n");
                exit(0);
            }

            FILE *fd = fopen(link_name, "w");
            if (fd == NULL)
            {
                printf("\n!!! STOP ON %i !!! => MAX DEPTH = %i \n\n", i, i - 1);
                free(link_name_old);
                exit(0);
            }
            fclose(fd);
        }

        if (i % 10 == 0)
        {
            sleep(1);
        }
        free(link_name);
    }
    return 0;
}
