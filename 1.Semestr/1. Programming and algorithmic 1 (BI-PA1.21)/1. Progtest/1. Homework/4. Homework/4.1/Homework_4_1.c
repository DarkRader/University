#include <stdio.h>
#include <stdlib.h>


int main(int argc, const char * argv[]) {

    int n = 0;
    printf("Rozmery pole:\n");
    if(scanf("%d", &n) != 1) {
        printf("Nespravny vstup.\n");
        return 1;
    }
    if(n < 3 || n > 26) {
        printf("Nespravny vstup.\n");
        return 2;
    }
    
    //printf("Everytning is fine\n");
    
    char **pole = (char**)malloc(sizeof(char*)*(n + 3));
    
    for(int i = 0; i < n + 2; i++)
        pole[i] = (char*)malloc(sizeof(char) * (n + 3));
    
    for(int j = 0; j < n + 2; j++)
        pole[0][j] = 'Q';

    for(int i = 1; i < n + 1; i++) {
        pole[i][0] = 'Q';
        for(int j = 1; j < n + 1; j++)
            pole[i][j] = ' ';
        pole[i][n+1] = 'Q';
    }

    for(int j = 0; j < n + 2; j++)
        pole[n+1][j] = 'Q';

//    for(int i = 0; i < n + 2; i++) {
//        for(int j = 0; j < n + 2; j++)
//            printf("%c", pole[i][j]);
//        printf("\n");
//
//    }
    
    
    int scan;
    int x = 0, y = 0;
    char symbol, p;
    int player = 0;
    int maxLen[2];
    int count[2];
    maxLen[0] = 1;
    maxLen[1] = 1;
    count[0] = 1;
    count[1] = 1;
    
    while((scan = scanf("%c%c%d", &p, &symbol, &y)) != EOF )
    {
        x = symbol - 'a' + 1;
        if(scan != 3 || x < 1 || x > n + 1 || y < 1 || y > n + 1) {
            printf("Nespravny vstup.\n");
            return 3;
        }
        
        if(pole[x][y] != ' ') {
            printf("Nespravny vstup.\n");
            return 4;
        }
        
        pole[x][y] = player;
        
        int curLen = 0;
        
        int x2, y2;
        

        //ДИАГОНАЛЬ 1
        curLen = 1;
        x2 = x;
        y2 = y;
        while(pole[x2][y2] == pole[x2-1][y2-1])
        {
            curLen++;
            x2+=-1;
            y2+=-1;
        }
     
        x2 = x;
        y2 = y;
        while(pole[x2][y2] == pole[x2+1][y2+1])
        {
            curLen++;
            x2+=1;
            y2+=1;
        }
                
        if(maxLen[player] < curLen) {
            maxLen[player] = curLen;
            count[player] = 1;
        }
        else if (maxLen[player] == curLen && maxLen[player] != 1)
            count[player]++;
                
        //ВЕРТИКАЛЬ
        curLen = 1;
        x2 = x;
        y2 = y;
        while(pole[x2][y2] == pole[x2-1][y2])
        {
            curLen++;
            x2+=-1;
        }
     
        
        x2 = x;
        y2 = y;
        while(pole[x2][y2] == pole[x2+1][y2])
        {
            curLen++;
            x2+=1;
        }
                
        if(maxLen[player] < curLen) {
            maxLen[player] = curLen;
            count[player] = 1;
        }
        else if (maxLen[player] == curLen && maxLen[player] != 1)
            count[player]++;
        
        
        //ДИАГОНАЛЬ 2
        curLen = 1;
        x2 = x;
        y2 = y;
        while(pole[x2][y2] == pole[x2-1][y2+1])
        {
            curLen++;
            x2+=-1;
            y2+=1;
        }
     
        x2 = x;
        y2 = y;
        while(pole[x2][y2] == pole[x2+1][y2-1])
        {
            curLen++;
            x2+=1;
            y2+=-1;
        }
                
        if(maxLen[player] < curLen) {
            maxLen[player] = curLen;
            count[player] = 1;
        }
        else if (maxLen[player] == curLen && maxLen[player] != 1)
            count[player]++;
        
        
        //ГОРИЗОНТАЛЬ
        curLen = 1;
        x2 = x;
        y2 = y;
        while(pole[x2][y2] == pole[x2][y2-1])
        {
            curLen++;
            y2+=-1;
        }
     
        x2 = x;
        y2 = y;
        while(pole[x2][y2] == pole[x2][y2+1])
        {
            curLen++;
            y2+=1;
        }
                
        if(maxLen[player] < curLen) {
            maxLen[player] = curLen;
            count[player] = 1;
        }
        else if (maxLen[player] == curLen && maxLen[player] != 1)
            count[player]++;
                
 
        
        if (player == 0) {
            printf("Hrac 'X': nejdelsi %d (%d x)\n", maxLen[player], count[player]);
            player = 1;
        }
        else {
            printf("Hrac 'O': nejdelsi %d (%d x)\n", maxLen[player], count[player]);
            player = 0;
        }
    }
        
    
    
    return 0;
}
