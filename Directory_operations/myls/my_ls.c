#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

int main(int argc, char *argv[], char *envp[])
{

    /*for (int i = 0; i < argc; i++)
    {
        printf("For argc = %i -> %s\n", i, argv[i]);
    }*/

    printf("\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n\n");

    if (argc < 2)
    {
        printf("Argv from user is void. Work in that directory\n\n");
        argv[1] = "./";
    }
    else
    {
        printf("Work in directory: %s\n\n", argv[1]);
    }

    DIR *dir_ptr = opendir(argv[1]);
    if (dir_ptr == NULL)
    {
        printf("Error from opendir()\n");
        exit(-1);
    }
    printf("Open directory -> OK\n\n");

    //struct dirent *dir_struct = readdir(dir_ptr);
    struct dirent *dir_struct = NULL;
    //printf("%s\n", dir_struct->d_name);

    //struct stat stat_buf;
    struct stat stat_buf;
    struct stat *stat_buf_p = &stat_buf;

    //char cat_buf[256] = "./";
    //argv++;
    //(void)strcat(cat_buf, argv);
    //argv--;
    //printf("QWE -> %s\n", cat_buf);

    argv++;

    while ((dir_struct = readdir(dir_ptr)) != NULL)
    {
        printf("======================\n");
        printf("File name: %s\n", dir_struct->d_name);
        //printf("ARGV %s\n", *argv);
        char cat_buf[256] = "./";
        char cat_buf_add[256] = "/";
        strcat(cat_buf, *argv);
        //printf("cat_buf -> %s\n", cat_buf);
        strcat(cat_buf, cat_buf_add);
        //printf("cat_buf -> %s\n", cat_buf);
        strcat(cat_buf, dir_struct->d_name);
        //printf("cat_buf -> %s\n", cat_buf);
        if (lstat(cat_buf, stat_buf_p) < 0)
        {
            printf("error with lstat\n");
            exit(-1);
        }
        //printf("Mode: %d\n", stat_buf_p->st_mode);

        printf("Mode: ");
        for (int i = 8, j = 1; i >= 0; --i, j++)
        {
            printf("%d", stat_buf_p->st_mode & (1 << i) ? 1 : 0);
            if (j % 3 == 0)
                printf(" ");
        }
        printf(" (rwx rwx rwx) \n");
        printf("UID: %d \n", stat_buf_p->st_uid);
        printf("GID: %d \n", stat_buf_p->st_gid);
        printf("inode: %ld \n", stat_buf_p->st_ino);
        printf("last access time: %ld \n", stat_buf_p->st_atime);
        printf("last modified time: %ld \n", stat_buf_p->st_mtime);
        printf("last changes time: %ld \n", stat_buf_p->st_ctime);
        printf("Size: %ld (bytes)\n\n", stat_buf_p->st_size);

        printf("Is it directory? -> ");
        if (S_ISDIR(stat_buf_p->st_mode) > 0)
        {
            printf("Yes\n");
        }
        else
        {
            printf("No\n");
        }

        printf("Is it regular file? -> ");
        if (S_ISREG(stat_buf_p->st_mode) > 0)
        {
            printf("Yes\n");
        }
        else
        {
            printf("No\n");
        }

        printf("Is it FIFO file? -> ");
        if (S_ISFIFO(stat_buf_p->st_mode) > 0)
        {
            printf("Yes\n");
        }
        else
        {
            printf("No\n");
        }

        printf("Is it socket file? -> ");
        if (S_ISSOCK(stat_buf_p->st_mode) > 0)
        {
            printf("Yes\n");
        }
        else
        {
            printf("No\n");
        }

        printf("Is it block device? -> ");
        if (S_ISBLK(stat_buf_p->st_mode) > 0)
        {
            printf("Yes\n");
        }
        else
        {
            printf("No\n");
        }

        printf("Is it character device? -> ");
        if (S_ISCHR(stat_buf_p->st_mode) > 0)
        {
            printf("Yes\n");
        }
        else
        {
            printf("No\n");
        }

        printf("Is it link? -> ");
        if (S_ISLNK(stat_buf_p->st_mode) > 0)
        {
            printf("Yes => ");
            size_t link_size;
            //char buf_path[256];
            char *buf_path = (char *)malloc(256 * sizeof(char));
            link_size = readlink(cat_buf, buf_path, 256);
            if (link_size < 0)
            {
                printf("error on readlink()\n");
                exit(0);
            }
            else
            {
                printf("Link refer on -> %s\n", buf_path);
            }
            free(buf_path);
        }
        else
        {
            printf("No\n");
        }

        printf("======================\n\n");
    }

    if (closedir(dir_ptr) == -1)
    {
        printf("Error from closedir()\n");
        exit(-1);
    }
    printf("\nClose directory -> OK\n");
    printf("\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n\n");

    return 0;
}