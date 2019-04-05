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
	strcpy(B->mode,mode);
	B->l2r = 42;
	if((mode[0] == 'r') || (mode[1] == 'r')){
		fread(&B->buff,1,1,f);
		if(B->buff==(char)(0xFF)){
			fread(&B->buff,1,1,f);
			if(B->buff!=(char)(0xFF)){
				if(B->buff==0){
					return NULL;
				}
				B->l2r = B->buff;
				fread(&B->buff,1,1,f);
			}
		}
	}
	return B;
}

int bstop(BFILE* bf){
	if(bf==NULL){
		return 0;
	}
	char echap = (char)(0xFF);
	char d = bf->decal;
	fwrite(&echap,1,1,bf->f);
	fwrite(&d,1,1,bf->f);
	if(bf->mode[0]=='w'){
		while(bf->decal!=0){
			bitwrite(bf,0);
		}
	}
	free(bf->mode);
	free(bf);
	return 0;
}

char bitread(BFILE *bf){
	if(bf->f==NULL){
		return -1;
	}
	if(bf->decal==8){
		fread(&bf->buff,1,1,bf->f);
		if(bf->buff==(char)(0xFF)){
			fread(&bf->buff,1,1,bf->f);
			if(bf->buff!=(char)(0xFF)){
				if(bf->buff==0){
					return -1;
				}
				bf->l2r = bf->buff;
				fread(&bf->buff,1,1,bf->f);
			}
		}
		bf->decal = 0;
	}
	bf->decal++;
	if(bf->l2r!=42){
		if(bf->decal<=bf->l2r){
			return ((bf->buff >> (8-bf->decal)) & 1);
		}
		else{
			return -1;
		}
	}
	return ((bf->buff >> (8-bf->decal)) & 1);
}

int bitwrite(BFILE* bf, char bit){
	if(bf->f == NULL){
		return -1;
	}
	if(bit){
		bf->buff |= (1<<(7-bf->decal));
	}
	else{
		bf->buff &= ~(1<<(7-bf->decal));
	}
	bf->decal++;
	if(bf->decal==8){
		if(bf->buff==(char)(0xFF)){
			fwrite(&bf->buff,1,1,bf->f);
		}
		fwrite(&bf->buff,1,1,bf->f);
		bf->decal=0;
	}
	return 0;
}

int beof(BFILE* bf){
	return(bitread(bf)==-1);
}
