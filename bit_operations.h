#include <stdio.h>
#include <stdlib.h>

typedef struct a{
	FILE* f;
	char decal;
	char* mode;
	char buff;
	char l2r;
}BFILE;

BFILE* bstart(FILE* f, const char* mode);

int bstop(BFILE* fichier);

char bitread(BFILE *fichier);

int bitwrite(BFILE *fichier, char bit);

int beof(BFILE *fichier);
