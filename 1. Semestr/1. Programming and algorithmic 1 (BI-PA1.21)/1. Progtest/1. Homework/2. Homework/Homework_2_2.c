#include <stdio.h>
#include <math.h>

int main() {
    int Poz, Soust, i, space, m, k, i1, ukazka, c;
    printf("Pozice a soustava:\n");
    while ((c = scanf("%d %d", &Poz, &Soust)) != EOF) {
    if (c != 2 || Poz < 0 || Soust < 2 || Soust > 36) {
        printf("Nespravny vstup.\n");
        return 1;
    }
    i = 0;
    space = 1;
    m = 0;
    k = 1;
    i1 = 0;
    while (i + k <= Poz) {
        if (k < space) {
            k++;
            m--;
            i = i - k;
        }
        m++;
        i = i + k;
        space = log10(m) + 1;

    }
    ukazka = Poz - i;
    printf("%d\n", m);
    while (i1 < ukazka) {
        printf(" ");
        i1++;
    }
    printf("^\n");

    }


    return 0;
}
