#include <stdio.h>

int main() {
    int h, h1, min, min1, sec, sec1, ms, ms1, hresult, minresult, secundresult, msresult;
    int cassum, cassum1, casmin;
    printf("Zadejte cas t1:\n");
    if (scanf("%d : %d : %d , %d", &h, &min, &sec, &ms) != 4) {
        printf("Nespravny vstup.\n");
        return 1;
    }
    if (h > 23 || min > 59 || sec > 59 || ms > 999 || h < 0 || min < 0 || sec < 0 || ms < 0) {
        printf("Nespravny vstup.\n");
        return 1;
    }
    printf("Zadejte cas t2:\n");
    if (scanf("%d : %d : %d , %d", &h1, &min1, &sec1, &ms1) != 4) {
        printf("Nespravny vstup.\n");
        return 1;
    }
    if (h1 > 23 || min1 > 59 || sec1 > 59 || ms1 > 999 || h1 < 0 || min1 < 0 || sec1 < 0 || ms1 < 0) {
        printf("Nespravny vstup.\n");
        return 1;
    }
    if (h > h1 || (h == h1 && min > min1) || (h == h1 && min == min1 && sec > sec1) ||
        (h == h1 && min == min1 && sec == sec1
         && ms > ms1)) {
        printf("Nespravny vstup.\n");
        return 1;
    }
    cassum = (h * 3600000) + (min * 60000) + (sec * 1000) + ms;
    cassum1 = (h1 * 3600000) + (min1 * 60000) + (sec1 * 1000) + ms1;
    casmin = cassum1 - cassum;
    hresult = casmin / 3600000;
    minresult = casmin / 60000 % 60;
    secundresult = casmin / 1000 % 60;
    msresult = casmin % 1000;
    printf("Doba: ");
    if (hresult < 10)
        printf(" %d:", hresult);
    else
        printf("%d:", hresult);
    if (minresult < 10)
        printf("0%d:", minresult);
    else
        printf("%d:", minresult);
    if (secundresult < 10)
        printf("0%d,", secundresult);
    else
        printf("%d,", secundresult);
    if (msresult < 10)
        printf("00%d\n", msresult);
    else if (msresult < 100)
        printf("0%d\n", msresult);
    else
        printf("%d\n", msresult);
    return 0;

}
