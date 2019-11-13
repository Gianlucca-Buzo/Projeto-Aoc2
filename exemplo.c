#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char const *argv[]){
  
	int nsets, bsize, assoc, flag_saida,dados[5];
	char *subs,*txt; 
	FILE *entrada;
	entrada = fopen(txt,"r");
	nsets = atoi (argv[1]);
	bsize = atoi (argv[2]);
	assoc = atoi (argv[3]);
	subs = argv [4];
	flag_saida = atoi (argv [5]); 
	txt = argv[6];
  	for (int i = 0; i < 4; ++i)
  	{
  		fscanf(entrada,"%d",&dados[i]);
  	}
  	for (int i = 0; i < 4; ++i)
  	{
  		printf("%d ",dados[i]);
  	}
  	
	return 0;
}