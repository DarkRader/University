#include <stdio.h>

int main(void) {
    int sirka, vyska, i = 0, i1 = 0, s = 0, v = 0, i2 = 0;

    printf("Zadejte pocet poli:\n");
    while (i < 2) {
        if (i == 1) {
            printf("Zadejte velikost pole:\n");
            sirka = vyska;
        }
        if (scanf("%d", &vyska)!= 1){
            printf("Nespravny vstup.\n");
            return 1;
        }
        if (vyska <= 0) {
            printf("Nespravny vstup.\n");
            return 1;
        }
        i++;
    }
    i = 0;
    printf("+");
    while (i < sirka * vyska) {
        printf("-");
        i++;
    }
    printf("+\n");
    i = 0;
    while (i < sirka) {
        while (i2 < vyska) {
            printf("|");
            while (i1 < sirka) {
                s++;
                while (v < vyska) {
                    v++;
                    if (s % 2 == 0) {
                        printf("X");
                    } else {
                        printf(" ");
                    }
                }
                i1++;
                v = 0;
            }
            if (s == sirka + 1){
                s = 1;
            } else {
                s = 0;
            }
            i1 = 0;
            i2++;
            printf("|\n");
            }
        if (s == 1) {
            s = 0;
        } else {
            s = 1;
        }
        i2 = 0;
        i++;
         }
    i = 0;
    printf("+");
    while (i < sirka * vyska) {
        printf("-");
        i++;
    }
    printf("+\n");

    return 0;
}
