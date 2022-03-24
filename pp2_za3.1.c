#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void show_tab(int *tab, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
            printf("%d \t", tab[i * size + j]);
        printf("\n");
    }
    printf("\n");
}

int main() {
    printf("Podaj wymiar macierzy\n");
    int n;
    scanf("%d", &n);
    int s = n * n;
    int *tab = malloc(s * sizeof(int));

    for (int i = 0; i < s; i ++)
        scanf("%d", tab + i);


    show_tab(tab, n);

    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (*(tab + n * i + j) != 0) {
                printf("Nie jest trojkatna dolna\n");
                return 0;
            }

    printf("Jest trojkatna dolna\n");
    free(tab);
}
