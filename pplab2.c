
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N1 30
#define N2 35
#define N 15

void reverse(int arr[], int len) {
    len--;
    for (int i = 0; i < len / 2; i++) {
        int t = arr[len - i];
        arr[len - i] = arr[i];
        arr[i] = t;
    }
}
void dump_array(int *arr, int len) {
    for (int i = 0; i < len; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
int one_two(int *ar1, int le1, int *ar2, int le2, int *ar3) {
    int le3 = le1 + le2;
    if (le3 == 0)
        return 0;

    int i1 = 0, i2 = 0, length = 0;
    for (int i3 = 0; i1 + i2 < le3 ; i3++){
        int n = 0;
        if (ar1[i1] > ar2[i2]) {
            n = 0;
            for (int i = 0; ar3[i]; i++) {
                if (ar2[i2] == ar3[i])
                    n++;
            }
            if (n == 0)
                ar3[i3] = ar2[i2++], length++;
            else
                i2++;
                ar3[i3] = ar3[i3];
        }
        else {
            for (int i = 0; ar3[i]; i++) {
                n = 0;
                if (ar1[i1] == ar3[i])
                    n++;
            }
            if (n == 0)
                ar3[i3] = ar1[i1++], length++;
            else
                i1++;
                ar3[i3] = ar3[i3];
        }
    }
    for ( int j = 0; j < length; j++){
        printf("%d ", ar3[j]);
    }
    printf("\n%d ", length);
    return length;


}
void randomfill(int *arr, int len, int max, int r);

int main() {
    srand(time(NULL));
    int t1[30];
    int t2[35];
    int T1[5] = {2, 3, 4, 5, 6};
    int T2[7] = {1,  7, 8, 9, 10, 11, 12};
    int T3[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int T[N];
    randomfill(T, N, 20, 10);
    for (int i = 0; i < N; i++){
        printf("%d ", T[i]);
    }
//    randomfill(t1, 30, 10, 1);
//    randomfill(t2, 35, 10, 1);
//    for (int i = 0; i < 30; i++)
//        printf("%d ", t1[i]);
//    printf("\n");
//    for (int i = 0; i < 35; i++)
//        printf("%d ", t2[i]);
    printf("\n");
    one_two(T1, 5, T2, 7, T3);
}

void randomfill(int *arr, int len, int max, int r) {
    for (int i = 0; i < len; i++)
        arr[i] = (rand() % max) + 1 - r;
}
