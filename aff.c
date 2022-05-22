#include <stdio.h>

int	main()
{
    unsigned char map[4] = { 0x50, 0x66, 0x51, 0x65 };

    printf("%u\n", (int)map); 
    printf("%d\n", map);
    return 0;
}
