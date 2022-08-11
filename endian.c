#include <stdio.h>

void	swap_endianness(unsigned char *bytes, int len)
{
	unsigned char	tmp;
	int				i;
    int             halfway;

	i = 0;
    halfway = len / 2;
	while (len > halfway)
	{
		len--;
		tmp = bytes[i];
		bytes[i] = bytes[len];
        bytes[len] = tmp;
		i++;
	}
}


int main(void)
{
    int bytes = 0xa1b2c3d4;
    
    unsigned char *byt = (unsigned char *)&bytes;
    for (int i = 0; i < sizeof(bytes); i++) {
        printf("%2x ", byt[i]);
    }
    swap_endianness((unsigned char *)&bytes, sizeof(bytes));
    for (int i = 0; i < sizeof(bytes); i++) {
        printf("%2x ", byt[i]);
    }
    printf("\n");
    printf("%X\n", bytes);
}
