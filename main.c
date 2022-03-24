#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N1 30
#define N2 35
#define N 15

void matrixsum(int m1[8][8], int m2);
void matrixmultiplication(int m1[8][8], int m2[8][8]);

int main() {
    int losowa;
    int M1[8][8], i1, j1;
    int M2[8][8], i2, j2;
    srand(time(NULL));
    for (i1 = 0; i1 < 8; i1++) {
        for (j1 = 0; j1 < 8; j1++) {
            losowa = rand() % 15;
            M1[i1][j1] = losowa;
            printf("%d ", M1[i1][j1]);
        }
        printf("\n");
    }
    printf("\n");
    for (i2 = 0; i2 < 8; i2++) {
        for (j2 = 0; j2 < 8; j2++) {
            losowa = rand() % 15;
            M2[i2][j2] = losowa;
            printf("%d ", M2[i2][j2]);
        }
        printf("\n");
    }
    printf("\n");
    matrixsum(M1, M2);
    printf("\n");
    matrixmultiplication(M1, M2);
}

void matrixmultiplication(int m1[8][8], int m2[8][8]){
    int multiplication = 0;
    int rowColumnSUM = 0;
    for (int i1 = 0; i1 < 8; i1++) {
        int i2 = 0;
        for ( int j1 = 0; j1 < 8; j1++) {
            rowColumnSUM =  rowColumnSUM + (m1[i1][j1] * m2[i2++][j1]);
        }
        printf("\n");
        multiplication = multiplication + rowColumnSUM;
    }
    printf(" wunik mnozenia wynosi %d", multiplication);
}
void matrixsum(int m1[8][8], int m2) {
    int diagsum = 0;
    int rowsum = 0;
    int columnsum = 0;
    int sum = 0;
    int i3 = 0, j3 = 0;
    for (int i=0; i < 8; i++){
        int j = 0;
        for (j = 0; j < 8; j++){
            rowsum = rowsum + m1[i][j];
            if ( i == j)
                diagsum = diagsum + m1[i][j];
            while (i == 0) {
                columnsum = m1[i3][j] + m1[i3 + 1][j] + m1[i3 + 2][j] + m1[i3 + 3][j] + m1[i3 + 4][j] + m1[i3 + 5][j] +
                            m1[i3 + 6][j] + m1[i3 + 7][j];
                printf("|suma w kolumnie %d wynosi %d\n", j + 1, columnsum);
                break;
            }

        }
        printf("-->suma w wierszu %d wynosi %d \n",i + 1, rowsum);
        sum = sum + rowsum;
    }
    printf("suma po przekatnej wynosi %d\n ", diagsum);
    printf("suma wynosi %d \n", sum);

}