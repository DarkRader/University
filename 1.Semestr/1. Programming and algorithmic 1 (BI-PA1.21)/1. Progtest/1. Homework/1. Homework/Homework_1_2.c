#include <stdio.h>
#include <math.h>
#include <float.h>

int main() {
    double strana1, strana2, strana3;
    double P = 0, R = 0, P0 = 0, R0 = 0, p = 0;
    int tr = 0, obd = 0, ctv = 0, tr0 = 0, obd0 = 0, ctv0 = 0, i = 0;
    printf("Obrazec #1\n");
    while (i < 2) {
        if (i == 1) {
            printf("Obrazec #2\n");
        }
        if (scanf(" T %lf %lf %lf", &strana1, &strana2, &strana3) == 3) {
            if (fabs(strana1 + strana2 - strana3) <= DBL_EPSILON * fmax(strana1, fmax(strana2, strana3)) * 1e4 ||
            fabs(strana1 + strana3 - strana2) <= DBL_EPSILON * fmax(strana1, fmax(strana2, strana3)) * 1e4 ||
            fabs(strana2 + strana3 - strana1) <= DBL_EPSILON * fmax(strana1, fmax(strana2, strana3)) * 1e4 ||
            ((strana1 + strana2 <= strana3) || (strana1 + strana3 <= strana2) || (strana2 + strana3 <= strana1))) {
                printf("Nespravny vstup.\n");
                return 1;
            } else if (strana1 <= 0 || strana2 <= 0 || strana3 <= 0) {
                printf("Nespravny vstup.\n");
                return 1;
            } else {
                P = /*fabs(*/(strana1 + strana2 + strana3);// <= 1024 * DBL_EPSILON);
                p = /*fabs(*/((strana1 + strana2 + strana3) / 2);// <= 1024 * DBL_EPSILON);
                R = /*fabs(*/(sqrt(p * (p - strana1) * (p - strana2) * (p - strana3)));// <= 1024 * DBL_EPSILON);
                tr = 1;
                obd = 0;
                ctv = 0;
            }
        } else if (scanf(" R %lf %lf", &strana1, &strana2) == 2) {
            if (strana1 == strana2) {
                printf("Nespravny vstup.\n");
                return 1;
            } else if (strana1 <= 0 || strana2 <= 0) {
                printf("Nespravny vstup.\n");
                return 1;
            } else {
                P = /*fabs(*/(2 * (strana1 + strana2));// <= 1024 * DBL_EPSILON);
                R = /*fabs(*/(strana1 * strana2);// <= 1024 * DBL_EPSILON);
                ctv = 0;
                tr = 0;
                obd = 1;
            }
        } else if (scanf(" S %lf", &strana1) == 1) {
            if (strana1 <= 0) {
                printf("Nespravny vstup.\n");
                return 1;
            } else {
                P = /*fabs(*/(4 * strana1);// <= 1024 * DBL_EPSILON);
                R = /*fabs(*/(strana1 * strana1);// <= 1024 * DBL_EPSILON);
                obd = 0;
                tr = 0;
                ctv = 1;
            }
        } else {
            printf("Nespravny vstup.\n");
            return 1;
        }
        i++;
        if (i == 2)
            break;
        P0 = P;
        R0 = R;
        tr0 = tr;
        obd0 = obd;
        ctv0 = ctv;
    }
        // Obvod figur
        printf("Obvod: ");
        if (tr0 == 1) {
            printf("trojuhelnik #1 ");
        } else if (obd0 == 1) {
            printf("obdelnik #1 ");
        } else if (ctv0 == 1) {
            printf("ctverec #1 ");
        }
        if (fabs(P0 - P) <= DBL_EPSILON * fmax(P0, P) * 1e4) {
            printf("= ");
        } else if (P0 > P) {
            printf("> ");
        } else  if (P0 < P){
            printf("< ");
        }
        if (tr == 1) {
            printf("trojuhelnik #2\n");
        } else if (obd == 1) {
            printf("obdelnik #2\n");
        } else if (ctv == 1) {
            printf("ctverec #2\n");
        }

        // Obsah figur
         printf("Obsah: ");
         if (tr0 == 1) {
            printf("trojuhelnik #1 ");
        } else if (obd0 == 1) {
            printf("obdelnik #1 ");
        } else if (ctv0 == 1) {
            printf("ctverec #1 ");
        }
        if (fabs(R0 - R) <= DBL_EPSILON * fmax(R0, R) * 1e4) {
            printf("= ");
        } else if (R0 > R) {
            printf("> ");
        } else if (R0 < R){
            printf("< ");
        }
         if (tr == 1) {
            printf("trojuhelnik #2\n");
         } else if (obd == 1) {
            printf("obdelnik #2\n");
         } else if (ctv == 1) {
            printf("ctverec #2\n");
         }
         //printf("P = %lf\nR = %lf\n", P0, R0);
         //printf("P1 = %lf\nR1 = %lf\n", P, R);
         //printf("tr = %d\nobd = %d\nctv = %d\n", tr0, obd0, ctv0);
         //printf("tr1 = %d\nobd1 = %d\nctv1 = %d\n", tr, obd, ctv);
    return 0;
}
