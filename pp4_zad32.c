#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>

int get(FILE *f, int index) {
	fseek(f, 0, SEEK_SET);
	int a;
	for (int i = 0; i <= index; i++)
		fscanf(f, "%i", &a);
	return a;
}

void getStr(FILE *f, int index, char *o) {
	fseek(f, 0, SEEK_SET);
	int a;
	for (int i = 0; i <= index; i++)
		fscanf(f, "%s", o);
}

int main(int argc, char **argv){
	if (argc != 3) {
		printf("Skladnia: [plik listy] [numer]\n");
		return 1;
	}
	
	int n = atoi(argv[2]);
	FILE *f = fopen(argv[1], "r");
	char *b = malloc(30 * sizeof(char));
   
	getStr(f, n * 6 + 3, b);
	int size1 = atoi(b);
	
	getStr(f, n * 6 + 4, b);
	int size2 = atoi(b);
	
	getStr(f, n * 6 + 5, b);
	int size3 = atoi(b);
	
	getStr(f, n * 6, b);
	FILE *a1 = fopen(b, "r");
	
	getStr(f, n * 6 + 1, b);
	FILE *a2 = fopen(b, "r");
	
	getStr(f, n * 6 + 2, b);
	FILE *a3 = fopen(b, "w+");
	
	free(b);
	fclose(f);
	int flock(a3, LOCK_EX);
	
	for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size3; j++) {
			int s = 0;
            for (int k = 0; k < size2; k++)
                s += get(a1, i * size2 + k) * get(a2, j + size3 * k);
			
			fprintf(a3, "%i\t", s);
		}
		
		fprintf(a3, "\n");
	}
	
	int flock(a3, LOCK_UN);
	fclose(a1);
	fclose(a2);
	fclose(a3);
}
