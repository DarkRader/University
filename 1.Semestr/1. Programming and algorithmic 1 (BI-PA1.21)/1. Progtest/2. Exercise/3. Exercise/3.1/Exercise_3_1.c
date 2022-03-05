#include <stdio.h>

int main(void) {
    int r, g, b;
    char zavorka;
    printf("Zadejte barvu v RGB formatu:\n");

    if ( scanf(" rgb ( %d , %d , %d %c", &r, &g, &b, &zavorka) != 4) {
        printf("Nespravny vstup.\n");
        return 1;
    }
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255) {
        printf("Nespravny vstup.\n");
        return 1;
    }
    if (zavorka != ')')
        printf("Nespravny vstup\n");
    printf("#");
    if (r < 16)
        printf("0%X", r);
    else
        printf("%X", r);
    if (g < 16)
        printf("0%X", g);
    else
        printf("%X", g);
    if (b < 16)
        printf("0%X\n", b);
    else
        printf("%X\n", b);
    return 0;
}
