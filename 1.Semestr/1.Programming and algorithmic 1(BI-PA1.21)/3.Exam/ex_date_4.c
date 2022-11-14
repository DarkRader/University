#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

typedef struct TItem
{
    struct TItem * m_Next;
    int m_Mul;
    int m_Pow;
} TITEM;

TITEM * createItem ( int mul, int pow, TITEM * next )
{
    TITEM * n = (TITEM *) malloc (sizeof ( *n ));
    n -> m_Mul = mul;
    n -> m_Pow = pow;
    n -> m_Next = next;
    return n;
}

void deleteList (TITEM * l)
{
    while (l)
    {
        TITEM * tmp = l -> m_Next;
        free (l);
        l = tmp;
    }
}
#endif /* __PROGTEST__ */

TITEM * addPoly ( TITEM * a , TITEM * b )
{
    TITEM * tmp = a;
    TITEM * tmp2 = b;

    if(tmp==NULL||tmp2==NULL)
    {
        return NULL;
    }
    int pocetA=0, pocetB=0;

    int chek = -1;
    while(tmp)
    {
        if (chek < tmp -> m_Pow)
        {
            chek = tmp -> m_Pow;
        }
        else return NULL;
        tmp = tmp -> m_Next;

        pocetA++;
    }
    chek = -1;
    while(tmp2)
    {
        if (chek < tmp2 -> m_Pow)
        {
            chek = tmp2 -> m_Pow;
        }
        else return NULL;
        tmp2 = tmp2 -> m_Next;
        pocetB++;
    }

    int max;
    if(pocetA>=pocetB) {
        max = pocetA;
    }
    else {
        max = pocetB;
    }
    int lol = 0;

    tmp = a;
    tmp2 = b;
    TITEM * res = (TITEM *)malloc(sizeof(*res));
    TITEM * resHead = res;
    for(int i =0 ; tmp&&tmp2 ; i++)
    {

        if(tmp -> m_Pow == tmp2 -> m_Pow&&tmp&&tmp2) {

            if(i!=0&&tmp->m_Mul + tmp2->m_Mul!=0) {
                res -> m_Next = (TITEM *) malloc(sizeof(*res));
                res = res -> m_Next;
                lol++;
            }
            else if(i!=0)break;

            res->m_Mul = tmp->m_Mul + tmp2->m_Mul;
            res->m_Pow = tmp->m_Pow;
            tmp = tmp -> m_Next;
            tmp2 = tmp2 -> m_Next;
        }

        else if(tmp&&tmp2&&tmp -> m_Pow > tmp2 -> m_Pow)
        {
            if(i!=0) {
                res -> m_Next = (TITEM *) malloc(sizeof(*res));
                res = res -> m_Next;
                lol++;
            }
            if(tmp2 -> m_Mul != 0) {
                res->m_Mul = tmp2->m_Mul;
                res->m_Pow = tmp2->m_Pow;
                tmp2 = tmp2->m_Next;
            }
            else
            {
                res -> m_Mul = tmp -> m_Mul;
                res -> m_Pow = tmp -> m_Pow;
                tmp = tmp -> m_Next;
            }
        }
        else if(tmp&&tmp2&&tmp2 -> m_Pow > tmp -> m_Pow)
        {
            if(i!=0) {
                res -> m_Next = (TITEM *) malloc(sizeof(*res));
                res = res -> m_Next;
                lol++;
            }
            if(tmp -> m_Mul != 0)
            {res -> m_Mul = tmp -> m_Mul;
            res -> m_Pow = tmp -> m_Pow;
            tmp = tmp -> m_Next;}
            else {
                res->m_Mul = tmp2->m_Mul;
                res->m_Pow = tmp2->m_Pow;
                tmp2 = tmp2->m_Next;
            }
        }
        else if(tmp!=NULL)
        {
            if(i!=0) {
                res -> m_Next = (TITEM *) malloc(sizeof(*res));
                res = res -> m_Next;
                lol++;
            }
            res -> m_Mul = tmp2 -> m_Mul;
            res -> m_Pow = tmp2 -> m_Pow;
            tmp2 = tmp2 -> m_Next;
        }
        else if(tmp2!=NULL)
        {
            if(i!=0) {
                res -> m_Next = (TITEM *) malloc(sizeof(*res));
                res = res -> m_Next;
                lol++;
            }
            res -> m_Mul = tmp -> m_Mul;
            res -> m_Pow = tmp -> m_Pow;
            tmp = tmp -> m_Next;
        }
        res -> m_Next = NULL;
    }
    if(res -> m_Mul == 0&&lol==0)
    {
        res -> m_Pow = 0;
        res -> m_Mul = 0;
        res -> m_Next = NULL;
    }
    return resHead;
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
    TITEM * a, * b;
    TITEM * res;

    a = createItem (2,1,NULL);
    b = createItem (0,0,NULL);
    res = addPoly(a,b);
    assert ( res -> m_Mul == 2 );
    assert ( res -> m_Pow == 1 );
    assert ( res -> m_Next == NULL );
    deleteList ( a );
    deleteList ( b );
    deleteList ( res );

    a = createItem (2,1,NULL);
    b = createItem (3,1,createItem (4,2,createItem (2,3,createItem(1,0,NULL))));
    res = addPoly(a,b);
    assert ( res == NULL );
    deleteList ( a );
    deleteList ( b );
    deleteList ( res );

    a = createItem (2,1,NULL);
    b = createItem (3,1,createItem (4,1,NULL));
    res = addPoly(a,b);
    assert ( res == NULL );
    deleteList ( a );
    deleteList ( b );
    deleteList ( res );

//    a = createItem (3,0,createItem (2,1,createItem (9,3,NULL)));
//    b = createItem (0,0,createItem (4,2,createItem (-1,3,NULL)));
//    res = addPoly(a,b);
//    assert ( res == NULL );
//    deleteList ( a );
//    deleteList ( b );
//    deleteList ( res );

    a = createItem (3,0,createItem (2,1,createItem (5,3,NULL)));
    b = createItem (-7,0,createItem (-2,1,createItem (-5,3,NULL)));
    res = addPoly(a,b);
    assert ( res -> m_Mul == -4 );
    assert ( res -> m_Pow == 0 );
    assert ( res -> m_Next == NULL );
    deleteList ( a );
    deleteList ( b );
    deleteList ( res );

    a = createItem (3,1,createItem (-2,2,createItem (4,3,NULL)));
    b = createItem (-3,1,createItem (2,2,createItem (-4,3,NULL)));
    res = addPoly(a,b);
    assert ( res -> m_Mul == 0 );
    assert ( res -> m_Pow == 0 );
    assert ( res -> m_Next == NULL );
    deleteList ( a );
    deleteList ( b );
    deleteList ( res );

    a = createItem (9,0,createItem (3,1,createItem (6,4,NULL)));
    b = createItem (2,0,createItem (-3,2,createItem (3,4,NULL)));
    res = addPoly(a,b);
    assert ( res -> m_Mul == 11 );
    assert ( res -> m_Pow == 0 );
    assert ( res -> m_Next -> m_Mul == 3 );
    assert ( res -> m_Next -> m_Pow == 1 );
    assert ( res -> m_Next -> m_Next -> m_Mul == -3 );
    assert ( res -> m_Next -> m_Next -> m_Pow == 2 );
    assert ( res -> m_Next -> m_Next -> m_Next -> m_Mul == 9 );
    assert ( res -> m_Next -> m_Next -> m_Next -> m_Pow == 4 );
    assert ( res -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
    deleteList ( a );
    deleteList ( b );
    deleteList ( res );

    a = createItem (3,0,createItem (2,1,createItem (9,3,NULL)));
    b = createItem (7,0,createItem (4,2,createItem (-1,3,NULL)));
    res = addPoly(a,b);
    assert ( res -> m_Mul == 10 );
    assert ( res -> m_Pow == 0 );
    assert ( res -> m_Next -> m_Mul == 2 );
    assert ( res -> m_Next -> m_Pow == 1 );
    assert ( res -> m_Next -> m_Next -> m_Mul == 4 );
    assert ( res -> m_Next -> m_Next -> m_Pow == 2 );
    assert ( res -> m_Next -> m_Next -> m_Next -> m_Mul == 8 );
    assert ( res -> m_Next -> m_Next -> m_Next -> m_Pow == 3 );
    assert ( res -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
    deleteList ( a );
    deleteList ( b );
    deleteList ( res );

    return 0;
}
#endif /* __PROGTEST__ */
