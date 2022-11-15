#ifndef __PROGTEST__
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#endif /* __PROGTEST__ */


// Bad try to do this homework. It's absolutely don't work program
//-----------------------------------------------------------------//
int sameWords ( const char * a, const char * b )
{

    int step = 0, m = 0, n = 0, q = 0;
    char * newA = (char*)malloc(sizeof(char) * strlen(a) + 1);
    char * newB = (char*)malloc(sizeof(char) * strlen(b) + 1);
    strcpy(newA, a);
    strcpy(newB, b);

    while(newA[step] != '\0') {
        if(isalpha(newA[step])==0) {
            newA[step] = ' ';
        }
        step++;
    }
    
    char *pOne = strtok(newA, " ");
    char *arrayWordsOne[step];
    
    while (pOne != NULL)
        {
            arrayWordsOne[m++] = pOne;
            pOne = strtok (NULL, " ");
        }
    
    step = 0;
    
    while(newB[step] != '\0') {
        if(isalpha(newB[step])==0) {
            newB[step] = ' ';
        }
        step++;
    }
    
    char *pTwo = strtok(newB, " ");
    char *arrayWordsTwo[step];
    
    while (pTwo != NULL)
        {
            arrayWordsTwo[n++] = pTwo;
            pTwo = strtok (NULL, " ");
        }
    
    for(int i = 0; i < m; i++) {
        
        for(int j = 0; j < m; j++) {
            if(tolower(*arrayWordsOne[i]) ==  tolower(*arrayWordsTwo[j])) {
                q++;
                break;
            }
        }
        if(q == 0) {
            free(newA);
            free(newB);
            return 0;
        } else
            q--;
    }
        
    free(newA);
    free(newB);
    return 1;
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
  assert ( sameWords ( "Hello students.", "HELLO studEnts!" ) == 1 );
  assert ( sameWords ( " He said 'hello!'", "'Hello.' he   said." ) == 1 );
  assert ( sameWords ( "He said he would do it.", "IT said: 'He would do it.'" ) == 1 );
  assert ( sameWords ( "one two three", "one two five" ) == 0 );
  return 0;
}

#endif /* __PROGTEST__ */
