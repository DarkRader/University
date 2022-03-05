#ifndef __PROGTEST__
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#endif /* __PROGTEST__ */

//void freeing()

//void dynamic_array_free(int **ArrayWords, int Lenght)
//{
//    for (int i = 0; i < Lenght; i++) {
//        free(ArrayWords[i]);
//    }
//    free(ArrayWords);
//}
//
//char ** allocateArrayFunctions(int ** ArrayWords, int newLenght, int oldLenght) {
//    if(oldLenght > 100) {
//        newLenght = oldLenght * 2;
//    } else {
//        newLenght = oldLenght + 10;
//    }
//}

int sameWords ( const char * a, const char * b )
{
//    char * newA = (char*)malloc(sizeof(char) * strlen(a) + 1);
//    char * newB = (char*)malloc(sizeof(char) * strlen(b) + 1);
//    strcpy(newA, a);
//    strcpy(newB, b);
//
//    char *token1 = NULL;
//    const char s[2] = " ";
//    token1 = strtok(newA, s);
//
//    char ** oneArrayWords = NULL;
//    int newLenghtFirstArray = 0;
//    int oldLenghtFirstArray = 0;
    
//    char *token2 = NULL;
//    const char s2[2] = ' ';
//    token2 = strtok(newB, s);
//
//    char ** twoArrayWords = NULL;
//    int newLenghtSecondArray = 0;
//    int oldLenghtSecondArray = 0;
    
//    while( token != NULL ) {
//          token = strtok(NULL, del);
//       }
    
//    int step = 0;
    //int secondStep = 0;
    
//    while (newA[step] != '\0') {
//        if (isalpha(newA[step]==1)) {
//            while( token1 != NULL ) {
//                  token1 = strtok(NULL, s);
//               }
//        }
//    }
    
    
//    dynamic_array_free(oneArrayWords, oldLenght);
//    dynamic_array_free(twoArrayWords, oldLenght);
//    return token1 = strtok(newA, del1);
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

//        for (int i = 0; i < m; ++i)
//            printf("%s\n", arrayWordsOne[i]);
    
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

//    if (tolower(*arrayWordsOne[0]) ==  tolower(*arrayWordsTwo[0])) {
//        printf("It will be very great!\n");
//    } else
//        printf("It will be very bad!\n");

//        for (int i = 0; i < n; ++i)
//            printf("%s\n", arrayWordsTwo[i]);
    
    for(int i = 0; i < m; i++) {
        
        for(int j = 0; j < m; j++) {
            if(tolower(*arrayWordsOne[i]) ==  tolower(*arrayWordsTwo[j])) {
                q++;
                break;
            }
        }
        if(q == 0) {
//            printf("Sometnig go bad\n");
            free(newA);
            free(newB);
            return 0;
        } else
            q--;
    }
        

//    printf("Kontrola 1-iho slova\n");
    //printf("%s\n", newA);
    //printf("%s\n", newB);
    // tolower(a[i]) ==  tolower(b[i]);
    //    dynamic_array_free(oneArrayWords, oldLenght);
    //    dynamic_array_free(twoArrayWords, oldLenght);
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

//int main ( int argc, char * argv [] )
//{
//    printf("Kontrola 1-iho slova\n %s\n", sameWords( "Hello students.", "HELLO studEnts!" ));
//
//  return 0;
//}

#endif /* __PROGTEST__ */
