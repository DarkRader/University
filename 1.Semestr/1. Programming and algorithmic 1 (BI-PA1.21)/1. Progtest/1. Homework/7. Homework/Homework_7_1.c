#include <stdio.h>
#include <stdlib.h>

int intCompare ( const void *a, const void *b ) {
    int * aa, *bb;
    
    aa = (int*) a;
    bb = (int*) b;
    
    if ( *aa > *bb ) return -1;
    if ( *bb > *aa ) return 1;
    return 0;
}

int rekurs(int * kostky, int N, int * lastKostky, int step)
{
    //End point
    if (N == 0) {
        for(int i = 0; i < step - 1; i++)
            printf("%d, ", lastKostky[i]);
        printf("%d\n", lastKostky[step - 1]);
        return 1;
    }
    //allocate memory for next recursion
    int * newKostky = (int*)malloc(sizeof(int)* step + 2);
    //copy from last to new
    for(int i = 0; i < step; i++)
        newKostky[i] = lastKostky[i];
    //add first element from kostky
    newKostky[step] = kostky[0];
    
    int variation = 0;
        
    //recursion calls for n-1 times with moving pointer
    for(int i = 0; i < N; i++) {
        kostky++;
        variation += rekurs(kostky, N - i - 1, newKostky, step + 1);
        if(newKostky[step] == *kostky)
            break;
    }
        
    free(newKostky);
    
    return variation;
}

int main ( int argc, char * argv [] )
{
    int N = 0, kostka = 0, step = 0, scan = 0;
    
    printf("Pocet kostek:\n");
    if (scanf(" %d", &N) != 1 || N <= 0) {
        printf("Nespravny vstup.\n");
        return 1;
    }
    
    int * kostky = (int *)malloc(sizeof(int) * N + 1);
        
    printf("Velikosti:\n");
    while(( scan = scanf(" %d", &kostka)) != EOF) {
        if (kostka <= 0 || scan == 0) {
            printf("Nespravny vstup.\n");
            return 1;
        }
        kostky[step] = kostka;
        step++;
    }
    
    if (step != N) {
        printf("Nespravny vstup.\n");
        return 1;
    }
    
    qsort( (void*)kostky, N, sizeof(kostky[0]), intCompare);
    
    step = 0;
    
    int variation = 0;
    
    for(int i = 0; i < N; i++) {
        
        variation += rekurs(kostky, N - i, NULL, step);
        kostky++;
    }

    printf("Celkem: %d\n", variation);
    
    free(kostky - N);
    
    return 0;
}
