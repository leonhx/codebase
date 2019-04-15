/*
ID: xerxes.1
LANG: C
TASK: ride
*/

#include <stdio.h>

int mod47(char* str) {
    int val = 1;
    while (*str != '\0' && *str != '\n') {
        val *= (*str) - 'A' + 1;
        val %= 47;
        str++;
    }
    return val;
}

_Bool is_ready(char* comet, char* group) {
    return mod47(comet) == mod47(group);
}

int main() {
    FILE *fin  = fopen("ride.in", "r");
    FILE *fout = fopen("ride.out", "w");

    int a, b;

    char comet[10];
    char group[10];

    fgets(comet, 10, fin);
    fgets(group, 10, fin);

    if (is_ready(comet, group)) {
        fprintf(fout, "GO\n");
    } else {
        fprintf(fout, "STAY\n");
    }

    return 0;
}
