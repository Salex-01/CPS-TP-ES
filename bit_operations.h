typedef struct a{
	FILE* f;
	int decal;
}BFILE, BFILE*;

BFILE* bstart(FILE* f, const char* mode);

int bstop(BFILE* fichier);

char bitread(BFILE *fichier);

int bitwrite(BFILE *fichier, char bit);

int beof(BFILE *fichier);