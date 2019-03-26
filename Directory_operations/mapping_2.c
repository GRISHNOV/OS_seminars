#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{

	int fd;
	size_t length;
	int i;

	struct A
	{
		char message[256];
	} * ptr, *tmpptr;

	fd = open("mapped.dat", O_RDWR | O_CREAT, 0666);

	if (fd == -1)
	{
		printf("File open failed!\n");
		exit(1);
	}

	length = sizeof(struct A);

	ftruncate(fd, length);

	ptr = (struct A *)mmap(NULL, length, PROT_WRITE | PROT_READ,
						   MAP_SHARED, fd, 0);

	close(fd);

	if (ptr == MAP_FAILED)
	{
		printf("Mapping failed!\n");
		exit(2);
	}

	tmpptr = ptr;

	printf("%s\n", tmpptr->message);

	munmap((void *)ptr, length);
	//free(buffer);
	return 0;
}
