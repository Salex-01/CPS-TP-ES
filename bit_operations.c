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
	B->decal = 8;
	B->mode = malloc((strlen(mode)+1)*sizeof(char));
	strcpy(B.mode,mode);
	return B;
}

int bstop(BFILE* bf){
	if(bf==NULL){
		return 0;
	}
	if((bf->decal!=8)&&((bf->mode[0]=='w')||(bf->mode[1]=='w'))){
		while(bf->decal<8){
			bitwrite(bf,0);
		}
	}
	free(bf->mode);
	free(bf);
	return 0;
}

char bitread(BFILE *bf){
	char b = fgetc(bf->f);
	if(b == EOF){
		return -1;
	}
	if(bf->decal < 7){
		fseek(bf->f, -1, SEEK_CUR);
	}
	else{
		bf->decal = 0;
	}
	return (b >> 7 - bf->decal) & 1;
}

int bitwrite(BFILE* bf, char bit){
    if(bf->f == NULL)
        return -1;
    bf->buff &= (0 << 7-bf->decal);
	bf->buff |= (bit & 1) << 7-bf->decal;
    bf->decal++;
    if(bf->decal == 7){
        fputc(bf->f, bf->buff);
        bf->decal = 0;
    }
    return 0;
}

int beof(BFILE* bf){
	return(bitread(bf)==-1);
}
