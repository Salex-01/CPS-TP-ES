#include "bit_operations.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	BFILE *bfichier;
	char bit;
	if(argc!=1){
		FILE* f = fopen(argv[1],"r");
		bfichier = bstart(f,"r");
	}
	else{
		bfichier = bstart(stdin,"r");
	}
	if (bfichier == NULL){
		fprintf(stderr,"Erreur d'ouverture d'acces binaire en lecture\n");
		exit(3);
	}
	bit = bitread(bfichier);
	while (bit!=-1){
		switch (bit){
		case 0:
			printf("0");
			break;
		case 1:
			printf("1");
			break;
		default:
			printf("?");
		}
		bit = bitread(bfichier);
	}
	printf("\n");
	bstop(bfichier);
	return 0;
}
