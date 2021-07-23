# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

int	main(void)
{
	int fd;
	int i;
	unsigned char buff[12];

	i = 0;
	fd = open("vm_champs/42.cor", O_RDONLY);
	read(fd, &buff, 12);
	while (i < 12)
	{
		printf("%x\n", buff[i]);
		i++;
	}
	return (0);
}