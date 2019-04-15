/*
ID: xerxes.1
LANG: C
TASK: gift1
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t MAX_NAME_LEN = 16;

int NP;

char* names[10];
int initial_money[10], money[10];

int get_index(char* name) {
    int i;
    for (i = 0; i < NP; ++i) {
        if (!strncmp(name, names[i], MAX_NAME_LEN)) {
            return i;
        }
    }
    return -1;
}

void trim(char* str, size_t n) {
    int i;
    for (i = 0; i < n && str[i] != '\0'; ++i) {
        if (str[i] == '\n') {
            str[i] = '\0';
            return;
        }
    }
}

int main() {
    FILE *fin  = fopen("gift1.in", "r");
    FILE *fout = fopen("gift1.out", "w");

    fscanf(fin, "%d\n", &NP);

    int i;
    for (i = 0; i < NP; i++) {
        names[i] = (char*)malloc(sizeof(char) * MAX_NAME_LEN);
        fgets(names[i], MAX_NAME_LEN, fin);
    }

    for (i = 0; i < NP; i++) {
        char name[MAX_NAME_LEN];
        fgets(name, MAX_NAME_LEN, fin);

        int m, n;
        fscanf(fin, "%d %d\n", &m, &n);

        initial_money[get_index(name)] += m;
        money[get_index(name)] += m;

        if (n == 0)
            continue;

        const int share = m / n;
        money[get_index(name)] -= share * n;

        while (n --> 0) {
            char to_name[MAX_NAME_LEN];
            fgets(to_name, MAX_NAME_LEN, fin);

            money[get_index(to_name)] += share;
        }
    }

    for (i = 0; i < NP; i++) {
        trim(names[i], MAX_NAME_LEN);
        fprintf(fout, "%s %d\n", names[i], money[i] - initial_money[i]);
        free(names[i]);
    }

    return 0;
}
