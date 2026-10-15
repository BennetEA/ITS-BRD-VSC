#include <stdio.h>
#include <limits.h>

static int plus (int val1, int val2) {
    if(val2 > 0 && val1 > INT_MAX - val2) {
        return -1;
    }
     if(val2 < 0 && val1 < INT_MIN - val2) {
        return -1;
    }
    return val1 + val2;
}
static int minus (int val1, int val2) {
    if(val2 > 0 && val1 < INT_MIN + val2) {
        return -1;
    }
     if(val2 < 0 && val1 > INT_MAX + val2) {
        return -1;
    }
    return val1 - val2;
}
static int mal (int val1, int val2) {
    int erg = val1 * val2;
    return erg;
}
static int geteilt (int val1, int val2) {
    if(val2 == 0) {
        printf("ERROR: Division durch 0 ist nicht möglich");
    }
    int erg = val1 / val2;
    return erg;
}