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
	if((mode[0]==r)||(mode[1]==r)){
		fread(bf->buff,8,1,f);
	}
	return B;
}

int bstop(BFILE* bf){
	if(bf==NULL){
		return 0;
	}
	while(bf->decal!=8){
		bitwrite(bf,0);
	}
	fwrite(bf->buff,8,1,bf->f);
	free(bf->mode);
	free(bf);
	return 0;
}

char bitread(BFILE *bf){
	if(bf->f==NULL){
		return -1;
	}
	if(bf->decal==8){
		fwrite(bf->buff,8,1,bf->f);
		fread(bf->buff,8,1,bf->f);
		bf->decal = 0;
	}
	if(bf->buff == EOF){
		return -1;
	}
	bf->decal++;
	return ((bf->buff >> (8-bf->decal)) & 1);
}

int bitwrite(BFILE* bf, char bit){
	if(bf->f == NULL){
		return -1;
	}
	if(bf->decal==8){
		fwrite(bf->buff,8,1,bf->f);
		bf->decal=0;
	}
	if(bit){
		bf->buff |= (1<<(7-decal));
	}
	else{
		bf->buff &= ~(1<<(7-decal));
	}
	bf->decal++;
	return 0;
}

int beof(BFILE* bf){
	return(bitread(bf)==-1);
}
