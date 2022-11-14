#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int abilityReach (int posl[], int N, int cislo) {
    
    for(int i = 0; i < N; i++) {
        for(int j = i + 1; j <= N; j++) {
            if(posl[i] + posl[j] == cislo) {
                return 1;
            }
        }
    }
    return 0;
}

int main(int argc, char * argv []) {
    int cislo, scan, N = -1, sizeArray = 1000;
    //int posl[SIZE];
    char znak;
    //int *posl, *posl_2;
    int* posl = (int*)malloc(sizeArray*sizeof(*posl));
    printf("Vstupni posloupnost:\n");
    if (scanf(" %d ", &cislo) != 1) {
        printf("Nespravny vstup.\n");
        free (posl);
        return 1;
    }
    N++;
    posl[N] = cislo;
    while ((scan = scanf(" %c", &znak)) != EOF) {
        if(scan != 1 || (znak != ',' && znak != '?' && znak)) {
            printf("Nespravny vstup.\n");
            free (posl);
            return 1;
        }

        if(znak == ',') {
            if (scanf(" %d ", &cislo) != 1) {
                printf("Nespravny vstup.\n");
                free (posl);
                return 1;
            } else {
                N++;
                posl[N] = cislo;
                if (N == sizeArray) {
                    sizeArray = sizeArray * 2;
                    posl = (int*)realloc(posl, sizeof(int)* sizeArray);
                }
            }
        } else if (znak == '?') {
            if (N == 0) {
                printf("Nespravny vstup.\n");
                free (posl);
                return 1;
            }
            printf("Testovane hodnoty:\n");
               while ((scan = scanf(" %d", &cislo)) != EOF) {
                   if(scan != 1) {
                       printf("Nespravny vstup.\n");
                       free (posl);
                       return 1;
                   } else if (abilityReach(posl, N, cislo) == 1) {
                       printf("> Soucet %d lze dosahnout.\n", cislo);
                       //free (posloup);
                   } else {
                       printf("> Soucet %d nelze dosahnout.\n", cislo);
                   }
           
               }
            break;
        }

    }
    
//    printf("0. Cislo: %d \n", posl[0]);
//    printf("1. Cislo: %d \n", posl[1]);
//    printf("2. Cislo: %d \n", posl[2]);
//    printf("3. Cislo: %d \n", posl[3]);
//    printf("4. Cislo: %d \n", posl[4]);
//    printf("5. Cislo: %d \n", posl[5]);
//    printf("6. Cislo: %d \n", posl[6]);
//    printf("7. Cislo: %d \n", posl[7]);
//    printf("8. Cislo: %d \n", posl[8]);
//    printf("9. Cislo: %d \n", posl[9]);
//    printf("10. Cislo: %d \n", posl[10]);

    
    free (posl);
    return 0;
}

