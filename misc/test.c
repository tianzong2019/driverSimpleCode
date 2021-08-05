#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv)
{
	int fd;
	int val = 1;

	fd = open("/dev/arm.mali.c71", O_RDWR);
	if (fd < 0)
		printf("can't open!\n");

	if (argc != 2) {
		printf("Usage :\n");
		printf("%s <on|off>\n", argv[0]);
		return 0;
	}

	if (strcmp(argv[1], "on") == 0)
		val  = 1;
	else
		val = 0;

	write(fd, &val, 4);

	close(fd);

	return 0;
}