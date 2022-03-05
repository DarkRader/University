#include <stdio.h>
#include <stdlib.h>
#define ID_NUMBER 130000
#define MAX_ACCESS 1000000

//This function is used to find a unique user and return its value
int uniqUsers (int access[], int from, int to)
{
    int uniq = to - from + 1;
    
    //The cycle is looking for non-unique users
    //(there is a comparison of users from the end,
    //if the user is already in the database, exits the cycle.
    //A non-unique user is subtracted from the total number of registered users)
    for(int i = from; i <= to; i++) {
        for(int j = to; j > i; j--){
            if(access[i] == access[j]){
                uniq--;
                break;
            }
             }
          }
    
    return uniq;
}

int main(int argc, char * argv [])
{
    //MaxId = user ID and how many of them can there be (I use in this array 130000,
    //because I have some problem with 1000000)
    //access = array filled with new users with the command "+"
    int MaxId[ID_NUMBER], access[MAX_ACCESS];
    int from, to, scan, id, Number_of_Access = 0;
    char znak;
    
    printf("Pozadavky:\n");
   
    //Checking the correctness of the character and type of input values at the input
    //and starting a cycle that runs until EOF
    while ((scan = scanf(" %c", &znak)) != EOF) {
        
        if (scan != 1 || (znak != '+' && znak != '?') || Number_of_Access > 1000000) {
            printf("Nespravny vstup.\n");
            return 1;
        }
        
        //The command for to write out unique users
        //and the total number of users in some interval
        if (znak == '?') {
            if (scanf(" %d %d", &from, &to) != 2 || from < 0 || from > to
                || to >= Number_of_Access) {
                printf("Nespravny vstup.\n");
                return 1;
            }
            //Using the function to write out unique users
            //and write out the number of all users on the entered interval
            printf("> %d / %d\n", uniqUsers(access, from, to), (to - from + 1));
        }
        
        //Command to add a user to the database (or to be correct to say "array")
        if (znak == '+') {
            if (scanf(" %d", &id) != 1 || id < 0 || id > 99999) {
                printf("Nespravny vstup.\n");
                return 1;
            }
            
            //Adding to the array number of access (first time or more)
            MaxId[id] += 1;
            //Adding new users to the database
            access[Number_of_Access] = id;
            
            if (MaxId[id] == 1) {
                printf("> prvni navsteva\n");
            } else
                printf("> navsteva #%d\n", MaxId[id]);
            
            //Adding the total number of access
            Number_of_Access++;
        }
        
    }
    
    return 0;
}
