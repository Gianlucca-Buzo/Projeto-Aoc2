#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char const *argv[]){
  
	int nsets, bsize, assoc, flag_saida,dado;
	char *subs,*txt; 
	printf("Ola Mundo!\n");
	nsets = atoi (argv[1]);
	bsize = atoi (argv[2]);
	assoc = atoi (argv[3]);
	subs = argv [4];
	flag_saida = atoi (argv [5]); 
	txt = argv[6];
  	
  	printf("%d %d %d\n",nsets,bsize,assoc);
  	
	return 0;
}