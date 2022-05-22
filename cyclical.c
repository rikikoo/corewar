#include <stdio.h>
#define M_SIZE 128

int main()
{
    unsigned char   arena[M_SIZE];
    int             pos = M_SIZE - 4;

    for (int i = 0; i < M_SIZE; i++) {
        arena[i] = '0';
    }
    arena[0] = 'h';
    arena[1] = 'e';
    arena[2] = 'l';
    arena[3] = 'l';
    arena[4] = 'o';
    arena[5] = '!';
    while (pos != 9) {
        printf("%c at position %d\n", arena[pos], pos);
        pos = (pos + 1) % M_SIZE;
    }
}
