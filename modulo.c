#include <stdio.h>

int main(void) {
    short n = -5;
    int mod = 10;
    printf("n = %hd\n", n);
    short nb = n % mod;
    printf("n mod %d = %hd\n", mod, nb);
    return 0;
}
