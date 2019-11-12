#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int MAX = 1000;

int main(int argc, char const *argv[]){
  
	int nsets, bsize, assoc, flag_saida,dados[MAX],j=0;
	char *subs,*txt,file[8],teste; 
	FILE *entrada;
	//atribuições iniciais
	nsets = atoi (argv[1]);
	bsize = atoi (argv[2]);
	assoc = atoi (argv[3]);
	subs = argv [4];
	flag_saida = atoi (argv [5]); 
	txt = argv[6];
	//copiando nome do arquivo para uma string
	strcpy(file,txt);
	file[8] = '\0';
	entrada = fopen(file,"r");
	
	// leitura até o final do arquivo, menor que o máximo
	while((fscanf(entrada,"%d",&dados[j]) != EOF) && j<MAX){
		j++;
	}

	for (int i = 0; i < j; ++i)
	{
		printf("%d ",dados[i]);
	}
  	
  	
	return 0;
}