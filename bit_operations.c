#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bit_operations.h"

BFILE* bstart(FILE* f, const char* mode){
	if(f==NULL){
		return NULL;
	}
	BFILE* B = malloc(sizeof(BFILE));
	B->f = f;
	B->decal = 0;
	B->mode = malloc((strlen(mode)+1)*sizeof(char));
	strcpy(B.mode,mode);
	return B;
}

int bstop(BFILE* bf){
	if(bf==NULL){
		return 0;
	}
	if((bf->decal!=0)&&((bf->mode[0]=='w')||(bf->mode[1]=='w'))){
		fprintf(bf->f,"%c",bf->buff);
	}
	free(bf->mode);
	free(bf);
	return 0;
}

char bitread(BFILE *bf){
    char b = fgetc(bf->f);
    if(b == EOF)
        return -1;
    if(bf->decal < 8)
        fseek(bf->f, -1, SEEK_CUR);
    else
        bf->decal = 1;
    return (b >> 8 - bf->decal) & 1;
}

int bitwrite(BFILE* bf, char bit){
    if(bf->f == NULL)
        return -1;
    bf->buff &= (0 << 8-bf->decal);
	bf->buff |= (bit & 1) << 8-bf->decal;
    bf->decal++;
    if(bf->decal == 8){
        fputc(bf->f, bf->buff);
        bf->decal = 1;
    }
    return 0;
}

int beof(BFILE* bf){
	return(bitread(bf)==-1);
}
