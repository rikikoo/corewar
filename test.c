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

	i = 2192;
	fd = open("vm_champs/42.cor", O_RDONLY);
	read(fd, &buff, 2300);
	while (i < 2300)
	{
		printf("%x\n", buff[i]);
		i++;
	}
	return (0);
}
