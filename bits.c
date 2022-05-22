#include <stdio.h>

int	get_arg_type(unsigned char byte, int arg)
{
	if (arg < 1 || arg > 3)
		return (0);
	if (arg == 1)
		return ((byte >> 6) & 3);
	else if (arg == 2)
		return ((byte >> 4) & 3);
	else
		return ((byte >> 2) & 3);
}

int main()
{
    unsigned char c = 0b01111000;

    for (int i = 0; i < 4; i++) {
        printf("%#.2x\n", get_arg_type(c, i + 1));
    }
}
