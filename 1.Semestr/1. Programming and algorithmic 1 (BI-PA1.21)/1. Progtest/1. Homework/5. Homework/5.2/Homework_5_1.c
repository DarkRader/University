#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct product {
    char* name;
    size_t count;
} PRODUCT;

void allocateMemore(PRODUCT* list, size_t* listSize, size_t* listIndex, char* string)
{
    for(size_t i = 0; i < *listIndex; i++) {
        if(!strcmp(list[i].name, string)) {
            
            list[i].count++;
            return ;
        }
    }
    
    PRODUCT* tmp = NULL;
    if (listIndex >= listSize) {
        (*listSize)*=2;
        tmp = (PRODUCT*)malloc(sizeof(PRODUCT) * (*listSize));
        for(size_t i = 0; i < *listIndex; i++) {
            tmp[i] = list[i];
        }
        free(list);
        list = tmp;
    }
    list[*listIndex].name = (char*)malloc(sizeof(char)*(strlen(string) + 1));
    strcpy(list[*listIndex].name, string);
    list[*listIndex].count = 1;
    (*listIndex)++;
    
    return;
}

void freeLIST(PRODUCT* list, size_t listIndex) {
    for (size_t i = 0; i < listIndex; i++) {
        if (list[i].name)
            free(list[i].name);
    }
    
    free(list);
    return ;
}

int intCompare(const void *prod1, const void *prod2)
{
    const PRODUCT product1 = *(PRODUCT*)prod1;
    const PRODUCT product2 = *(PRODUCT*)prod2;
    
    
    if (product1.count > product2.count)
        return -1;
    else if (product1.count < product2.count)
        return 1;
    else
        return 0;
}


int main(int argc, const char * argv[]) {
    int n = 0, scan = 0, sort = 1;
    
    printf("Pocet sledovanych:\n");
    
    if (scanf(" %d", &n) != 1) {
        printf("Nespravny vstup.\n");
        return 1;
    }
    
    if (n < 1) {
        printf("Nespravny vstup.\n");
        return 2;
    }
    
    printf("Pozadavky:\n");
    
    char znak;
    PRODUCT *list = NULL;
    size_t listSize = 10;
    size_t listIndex = 0;
    list = (PRODUCT*)malloc(sizeof(PRODUCT) * (listSize));
    char word[110];
    
    while ((scan = scanf(" %c", &znak)) != EOF ) {
        
        if (scan == 0) {
            printf("Nespravny vstup.\n");
            return 3;
        }
        
        if (znak != '+' && znak != '?' && znak != '#') {
            printf("Nespravny vstup.\n");
            return 4;
        }
        
        int tmpN = n;
        int equalPosition = 1;
        int pretendent = 1;
        size_t tmpIndex = 0;
        int res = 0;
        size_t listTmpCount = listIndex;
        
        if (znak == '+') {
            if(scanf(" %101s", word) != 1) {
                printf("Nespravny vstup.\n");
                freeLIST(list, listIndex);
                return 5;
            }
            
            if (strlen((const char*)word) > 99) {
                printf("Nespravny vstup.\n");
                freeLIST(list, listIndex);
                return 6;
            }
            
            allocateMemore(list, &listSize, &listIndex, word);
            sort = 0;
            }
        
        if (znak == '#') {
            if (!sort) {
                qsort(list, listIndex, sizeof(PRODUCT), intCompare);
            }
            while(tmpN > 0 && listTmpCount > 0) {
                pretendent = 1;
                tmpIndex = equalPosition - 1;
                while(tmpIndex < listIndex - 1 && list[tmpIndex].count == list[tmpIndex + 1].count) {
                    pretendent++;
                    tmpIndex++;
                }
                if(pretendent == 1) {
                    printf("%d. ", equalPosition);
                    printf("%s", list[tmpIndex].name);
                    printf(", %zux\n", list[tmpIndex].count);
                    res+=list[tmpIndex].count;
                } else {
                    for(size_t i = equalPosition - 1; i < equalPosition + pretendent - 1; i++) {
                        printf("%d.-%d. ", equalPosition, equalPosition + pretendent - 1);
                        printf("%s", list[i].name);
                        printf(", %zux\n", list[i].count);
                        res+=list[i].count;
                    }
                }
                
                equalPosition+=pretendent;
                tmpN-=pretendent;
                listTmpCount-=pretendent;
                
            }
            printf("Nejprodavanejsi zbozi: prodano %d kusu\n", res);
            
            }
        
        if (znak == '?') {
            if (!sort) {
                qsort(list, listIndex, sizeof(PRODUCT), intCompare);
            }
            while(tmpN > 0 && listTmpCount > 0) {
                pretendent = 1;
                tmpIndex = equalPosition - 1;
                while(tmpIndex < listIndex - 1 && list[tmpIndex].count == list[tmpIndex + 1].count) {
                    pretendent++;
                    tmpIndex++;
                }
                if(pretendent == 1) {
                    res+=list[tmpIndex].count;
                } else {
                    for(size_t i = equalPosition - 1; i < equalPosition + pretendent - 1; i++) {
                        res+=list[i].count;
                    }
                }
                
                equalPosition+=pretendent;
                tmpN-=pretendent;
                listTmpCount-=pretendent;
                
            }
            printf("Nejprodavanejsi zbozi: prodano %d kusu\n", res);
            
            }
        }
        
    freeLIST(list, listIndex);
    return 0;

    
    return 0;
}
