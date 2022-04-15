#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void list(int size, int type, char *p){
	FILE *f = fopen(p, "rb");
	int b;
	
	for (int i = 0; i < size; i++)
	{
		if (type) {
			fread(&b, 1, 1, f);
			printf("%c", (char)b);
		}
		else {
			fread(&b, sizeof(int), 1, f);
			printf("%i\n", b);
		}
	}
		
	fclose(f);
    printf("\n");
}

void generate(int size, int type, char *p) {
	FILE *f = fopen(p, "wb");
	int b;
	
	for (int i = 0; i < size; i++)
	{
		if (type) {
			b = ((rand() - 33) % 94) + 33;
			fwrite(&b, 1, 1, f);
		}
		else {
			b = rand();
			fwrite(&b, sizeof(int), 1, f);
		}
	}
		
	fclose(f);
}

int get(FILE *f, int index, int size) {
	int a;
	fseek(f, size * index, SEEK_SET);
	fread(&a, size, 1, f);
	return a;
}

void set(FILE *f, int index, int size, int value) {
	fseek(f, size * index, SEEK_SET);
	fwrite(&value, size, 1, f);
}

void sort(int size, int type, char *p) {
	FILE *f = fopen(p, "rb+");
	int s = type ? 1 : sizeof(int);
	
	for (int i = 0; i < size; i++)
	{
		int min = get(f, i, s);
		int iv = min;
		int imin = i;
		
		for (int j = i + 1; j < size; j++) {
			int a = get(f, j, s);
			if (a >= min)
				continue;
			
			min = a;
			imin = j;
		}
		
		if (imin == i)
			continue;
		set(f, i, s, min);
		set(f, imin, s, iv);
	}
		
	fclose(f);
}

int main(int argc, char **argv){
	srand(time(NULL));
	if (argc != 5) {
		printf("SkÅ‚adnia: [nazwa pliku] [N - liczba elementÃ³w] [c/i - char/int] [g/l/s - generate/list/sort]\n");
		return 1;
	}
   
	int mode;
	switch (argv[3][0]) {
		case 'i':
			mode = 0;
			break;
		
		case 'c':
			mode = 1;
			break;
			
		default:
			printf("Niepoprawny typ danych.\n");
			return 1;
	}
	
	int size = atoi(argv[2]);
	switch (argv[4][0]) {
		case 'g':
			generate(size, mode, argv[1]);
			break;
		
		case 'l':
			list(size, mode, argv[1]);
			break;
			
		case 's':
			sort(size, mode, argv[1]);
			break;
			
		default:
			printf("Niepoprawna operacja.\n");
			return 1;
	}
}
