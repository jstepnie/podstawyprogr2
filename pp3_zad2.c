#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* getHexAscii(char c) {
        int t;
        char stringc[5];
        t = (int)c;
        sprintf(stringc, "%X", t);

        printf("%s",stringc);
        return stringc;
}

 char** getData(void) {
    char** tablica = calloc(3, sizeof(char*));
    char *buffer = NULL;
    int* len = 0;
    int l;
    while (1) {
        int r = getline(&buffer, &l, stdin);

        if (r == -1)
            break;

        if (*len > 2)
            tablica = realloc(tablica, (*len + 1) * sizeof(char*));

        if (buffer[r - 1] != '\n')
            r++;
        buffer[r - 1] = 0;
        tablica[*len] = malloc(r * sizeof(char));
        memcpy(tablica[*len], buffer, r * sizeof(char));

        (*len)++;
    }

    return tablica;
}




int main() {
    char c;
    scanf("%c", &c);
    getHexAscii(c);
}
