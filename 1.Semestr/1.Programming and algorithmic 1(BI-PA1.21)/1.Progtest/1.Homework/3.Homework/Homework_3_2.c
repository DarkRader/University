#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#endif /* __PROGTEST__ */

int leapYear (int y) {
    if ( y % 4 == 0
         && ( y % 100 != 0 || y % 400 == 0 ) && y % 4000 != 0)
      return 1;
  return 0;
}

int days_in_a_month (int m, int y) {
    if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12) {
        return 31;
    } else if (m == 4 || m == 6 || m == 9 || m == 11) {
        return 30;
    } else if (leapYear(y) == 1) {
        return 29;
    } else {
        return 28;
    }
}

int validOfInterval ( int y1, int m1, int d1, int h1, int i1,
                      int y2, int m2, int d2, int h2, int i2)
{
    if (y1 > y2 || (y1 == y2 && m1 > m2) ||
       (y1 == y2 && m1 == m2 && d1 > d2) ||
       (y1 == y2 && m1 == m2 && d1 == d2 && h1 > h2) ||
       (y1 == y2 && m1 == m2 && d1 == d2 && h1 == h2 && i1 > i2)) {
        return 0;
    } else {
        return 1;
    }
}

int validOfParametrs ( int y1, int m1, int d1, int h1, int i1,
                       int y2, int m2, int d2, int h2, int i2)
{
    if (y1 >= 1600 && m1 > 0 && m1 <= 12 && d1 > 0 &&
        d1 <= days_in_a_month(m1, y1) && h1 >= 0 && h1 <= 23 && i1 >= 0 && i1 <= 59 &&
        y2 >= 1600 && m2 > 0 && m2 <= 12 && d2 > 0 &&
        d2 <= days_in_a_month(m2, y2) && h2 >= 0 && h2 <= 23 && i2 >= 0 && i2 <= 59 &&
        validOfInterval(y1, m1, d1, h1, i1, y2, m2, d2, h2, i2) == 1)
        return 1;
    
    return 0;
}

int dayInYears (int y1, int y2) {
    int day = 0, days = 0;
    for (int i = (y1 + 1); i < y2; i++) {
        if (leapYear (i) == 1) {
            days = 366;
        } else {
            days = 365;
        }
        day = day + days;
    }
    return day;
}

int dayBetweenInterval (int y, int m, int d) {
    int dayInMounth[13] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int day = 0;
    for (int i = 1; i < m; i++) {
        day = day + days_in_a_month(*(dayInMounth+i), y);
    }
    return day + d;
}

int calculatingJoulesForHours(int h, int i) {
    int step[9] = {4, 5, 2, 3, 3, 1, 5, 4, 1};
    int h1 = 0, h2 = 0, i1 = 0, i2 = 0;
    for (int i = 0; i < (h / 10) ; i++) {
        h1 = h1 + 122030 + *(step+i);
    }
    for (int i = 0; i < (h % 10); i++) {
        h2 = h2 + 12200 + *(step+i);
    }
    for (int t = 0; t < (i / 10); t++) {
        i1 = i1 + 2030 + *(step+t);
    }
    for (int t = 0; t < (i % 10); t++) {
        i2 = i2 + 200 + *(step+t);
    }
    return h1 + h2 + i1 + i2;
}

long long int allCalculatingJoules (int y1, int m1, int d1, int h1, int i1,
                          int y2, int m2, int d2, int h2, int i2)
{
    int DayInYear1;
    if (leapYear (y1) == 1) {
        DayInYear1 = 366;
    } else {
        DayInYear1 = 365;
    }
    if (y1 == y2 && m1 == m2 && d1 == d2) {
        return calculatingJoulesForHours(h2, i2) - calculatingJoulesForHours(h1, i1);
    }
    if (y1 == y2 && m1 == m2) {
        return (d2 - d1 - 1) * 292886 + (292886 - calculatingJoulesForHours(h1, i1))
                + calculatingJoulesForHours(h2, i2);
    }
    if (y1 == y2) {
        return (292886 - calculatingJoulesForHours(h1, i1) + ((dayBetweenInterval(y2, m2, d2)
                - dayBetweenInterval(y1, m1, d1) - 1) * 292886)
                + calculatingJoulesForHours(h2, i2));
    }
    return (DayInYear1 - dayBetweenInterval(y1, m1, d1) - 1 + dayInYears(y1, y2) + dayBetweenInterval(y2, m2, d2));
}

long long int energyConsumption ( int y1, int m1, int d1, int h1, int i1,
                        int y2, int m2, int d2, int h2, int i2, long long int * consumption )
{
    if (validOfParametrs(y1, m1, d1, h1, i1, y2, m2, d2, h2, i2)) {
        if (y1 != y2) {
            * consumption = (292886 - calculatingJoulesForHours(h1, i1)) +
                             (allCalculatingJoules (y1, m1, d1, h1, i1, y2, m2, d2, h2, i2)
                              * 292886) + calculatingJoulesForHours(h2, i2);
        } else {
                * consumption = allCalculatingJoules (y1, m1, d1, h1, i1, y2, m2, d2, h2, i2);
            }
        return 1;
    } else {
        return 0;
    }
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
  long long int consumption;

  assert ( energyConsumption ( 2021, 10,  1, 13, 15,
                               2021, 10,  1, 18, 45, &consumption ) == 1
           && consumption == 67116LL );
  assert ( energyConsumption ( 2021, 10,  1, 13, 15,
                               2021, 10,  2, 11, 20, &consumption ) == 1
           && consumption == 269497LL );
  assert ( energyConsumption ( 2021,  1,  1, 13, 15,
                               2021, 10,  5, 11, 20, &consumption ) == 1
           && consumption == 81106033LL );
  assert ( energyConsumption ( 2024,  1,  1, 13, 15,
                               2024, 10,  5, 11, 20, &consumption ) == 1
           && consumption == 81398919LL );
  assert ( energyConsumption ( 1900,  1,  1, 13, 15,
                               1900, 10,  5, 11, 20, &consumption ) == 1
           && consumption == 81106033LL );
  assert ( energyConsumption ( 2021, 10,  1,  0,  0,
                               2021, 10,  1, 12,  0, &consumption ) == 1
           && consumption == 146443LL );
  assert ( energyConsumption ( 2021, 10,  1,  0, 15,
                               2021, 10,  1,  0, 25, &consumption ) == 1
           && consumption == 2035LL );
  assert ( energyConsumption ( 2021, 10,  1, 12,  0,
                               2021, 10,  1, 12,  0, &consumption ) == 1
           && consumption == 0LL );
  assert ( energyConsumption ( 2021, 10,  1, 12,  0,
                               2021, 10,  1, 12,  1, &consumption ) == 1
           && consumption == 204LL );
  assert ( energyConsumption ( 2021, 11,  1, 12,  0,
                               2021, 10,  1, 12,  0, &consumption ) == 0 );
  assert ( energyConsumption ( 2021, 10, 32, 12,  0,
                               2021, 11, 10, 12,  0, &consumption ) == 0 );
  assert ( energyConsumption ( 2100,  2, 29, 12,  0,
                               2100,  2, 29, 12,  0, &consumption ) == 0 );
  assert ( energyConsumption ( 2400,  2, 29, 12,  0,
                               2400,  2, 29, 12,  0, &consumption ) == 1
           && consumption == 0LL );
  assert ( energyConsumption ( 1995,  8, 30, 4,  59,
                               2005,  9, 3, 11,  21, &consumption ) == 1
           && consumption == 1071161804LL );
  assert ( energyConsumption ( 2000,  3, 1, 0,  0,
                               2025,  4, 1, 0,  0, &consumption ) == 1
           && consumption == 2683421532LL );
    assert ( energyConsumption ( 1961,  3, 27, 7,  8,
                                 2161,  4, 4, 20,  26, &consumption ) == 1
             && consumption == 21397534808LL );
    assert ( energyConsumption ( 1856,  2, 30, 0,  0,
                                 2400,  1, 1, 0,  0, &consumption ) == 0 );
    assert ( energyConsumption ( 1861,  8, 30, 4,  59,
                                 2016,  8, 4, 11,  21, &consumption ) == 1
            && consumption == 16573617784LL );
    assert ( energyConsumption ( 1864,  0, 0, 0,  0,
                                 2400,  1, 1, 0,  0, &consumption ) == 0 );
  return 0;
}
#endif /* __PROGTEST__ */
