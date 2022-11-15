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
    char znak;
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
                   } else {
                       printf("> Soucet %d nelze dosahnout.\n", cislo);
                   }
           
               }
            break;
        }

    }
    
    free (posl);
    return 0;
}

