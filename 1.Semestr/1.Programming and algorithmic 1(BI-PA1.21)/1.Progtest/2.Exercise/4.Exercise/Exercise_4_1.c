#include <stdio.h>
#include <math.h>

int main() {
    double x, y, sum;
    printf ( "Zadejte vzorec:\n");
    char znak, rovno;
    if (scanf("%lf %c %lf %c", &x, &znak, &y, &rovno) == 4) {
        //printf("Nespravny vstup.\n");
        //return 1;
        if (znak == '+') {
            sum = x + y;
            if (rovno != '=') {
                printf("Nespravny vstup.\n");
                return 0;
            } else {
                printf("%g\n", sum);
            }
        } else if (znak == '-') {
            sum = x - y;
            if (rovno != '=') {
                printf("Nespravny vstup.\n");
                return 0;
            } else {
                printf("%g\n", sum);
            }
        } else if (znak == '*') {
            sum = x * y;
            if (rovno != '=') {
                printf("Nespravny vstup.\n");
                return 0;
            } else {
                printf("%g\n", sum);
            }
        } else if (znak == '/') {
            sum = x / y;
            if (y == 0) {
                printf("Nespravny vstup.\n");
                return 0;
            }
            else if (rovno != '=') {
                printf("Nespravny vstup.\n");
                return 0;
            } else {
                printf("%g\n", (double)trunc(sum));
            }
        } else {
            printf("Nespravny vstup.\n");
            return 0;
        }
    } else {
        printf("Nespravny vstup.\n");
        return 0;
    }
   // if (rovno != '=') {
     //   printf("Nespravny vstup.\n");
       // return 0;
    //}


    return 0;
}

