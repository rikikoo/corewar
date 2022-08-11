#include <stdio.h>
#include <string.h>

int main() {
    int n = -2;
    unsigned char byt[4] = { 0x01, 0x02, 0x01, 0x02 };

    memcpy(&byt, (unsigned char *)&n, 4);
    for (int i = 0; i < 4; i++) {
        printf("%02x", byt[i]);
    }
    printf("\n");
}

