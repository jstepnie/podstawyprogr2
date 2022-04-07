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

int intToCharArray(char* a, int in) {
	int len, t = in;
	
	for (len = 0; t != 0; len++)
		t /= 10;
	
	for (int i = len - 1; i >= 0; i--) {
		a[i] = (in % 10) + 48;
		in /= 10;
	}
	
	return len;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static inline char getOneHex(char value) {
    return value + (value <= 9 ? 48 : 55);
}

char* getHexAscii(char c) {
    char* hex = malloc(2 * sizeof(char));
    hex[0] = getOneHex((c & 0xF0) >> 4);
    hex[1] = getOneHex(c & 0xF);
    return hex;
}

int intToCharArray(char* a, int in) {
    int len, t = in;

    for (len = 0; t != 0; len++)
        t /= 10;

    for (int i = len - 1; i >= 0; i--) {
        a[i] = (in % 10) + 48;
        in /= 10;
    }

    return len;
}

char** getData(int* len) {
    char** a = calloc(3, sizeof(char*));
    char *buffer = NULL;
    (*len) = 0;

    int l;

    while (1) {
        int r = getline(&buffer, &l, stdin);

        if (r == -1)
            break;

        if (*len > 2)
            a = realloc(a, (*len + 1) * sizeof(char*));

        if (buffer[r - 1] != '\n')
            r++;
        buffer[r - 1] = 0;
        a[*len] = malloc(r * sizeof(char));
        memcpy(a[*len], buffer, r * sizeof(char));

        (*len)++;
    }

    return a;
}

char* compress(char** a, int len) {
    char* f = malloc(len * LINE_SIZE * sizeof(char));
    int l = 0;

    for (int i = 0; i < len; i++) {
        int ls = 0, oc = 1;

        do {
            ls++;
            if (a[i][ls] == a[i][ls - 1]) {
                oc++;
                continue;
            }

            char c = a[i][ls - 1];
            if (oc < 5 && !(c == '(' || c == ')' || c == '%'))
                for (int j = 0; j < oc; j++)
                    f[l++] = c;
            else {
                if (c == '(' || c == ')' || c == '%') {
                    char* hex = getHexAscii(c);
                    f[l++] = '%';
                    f[l++] = hex[0];
                    f[l++] = hex[1];
                    free(hex);
                }
                else f[l++] = c;

                f[l++] = '(';
                l += intToCharArray(&f[l], oc);
                f[l++] = ')';
            }

            oc = 1;
        } while(a[i][ls] != 0);

        f[l++] = '\n';
    }

    return f;
}

int getAmount(char* a, int* i) {
    int l = 0;

    for (*i = 0; a[*i] != ')'; (*i)++) {
        l *= 10;
        l += a[*i] - 48;
    }

    return l;
}

char* decompress(char** a, int len) {
    char* f = malloc(len * LINE_SIZE * 5 * sizeof(char));
    int l = 0;

    for (int k = 0; k < len; k++) {
        if (a[k][0] != 0)
            for (int i = 1; i < LINE_SIZE; i++) {
                switch (a[k][i]) {
                    case '(':
                    {
                        int s = 0;
                        int oc = getAmount(&a[k][i + 1], &s);
                        for (int j = 0; j < oc; j++)
                            f[l++] = a[k][i - 1];

                        i += s + 1;
                    }
                        break;

                    case '%':
                    {
                        if (a[k][i - 1] != ')')
                            f[l++] = a[k][i - 1];

                        char c;
                        switch (a[k][i + 2]) {
                            case '5':
                                c = '%';
                                break;

                            case '8':
                                c = '(';
                                break;

                            case '9':
                                c = ')';
                                break;
                        }

                        int s = 0;
                        int oc = getAmount(&a[k][i + 4], &s);
                        i += s + 4;
                        for (int j = 0; j < oc; j++)
                            f[l++] = c;
                    }
                        break;

                    case 0:
                        if (a[k][i - 1] != ')')
                            f[l++] = a[k][i - 1];
                        i = LINE_SIZE;
                        break;


                    default:
                        if (a[k][i - 1] != ')')
                            f[l++] = a[k][i - 1];
                        break;
                }
            }

        f[l++] = '\n';
    }

    f = realloc(f, l * sizeof(char));
    return f;
}

void freeAll(char** a, int len) {
    if (len < 3)
        len = 3;

    for (int i = 0; i < len; i++)
        free(a[i]);
    free(a);
}


int main() {
    char c;
    scanf("%c", &c);
    getHexAscii(c);
}
