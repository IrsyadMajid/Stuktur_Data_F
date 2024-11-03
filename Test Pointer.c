#include <stdio.h>
#include <conio.h>

void main () {
    int x;
    int *px;

    x = 20;
    px = &x;

    printf("Nilai X diakses secara langsung : %d\n", x);
    printf("Nilai x diakses melalui pointer : %d", *px);
    getchar();
    return 0;
}