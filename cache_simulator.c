#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int MAX = 1000;
//Mais um teste
/*
nsets = numero de conjuntos
bsize = tamanho do bloco
assoc = nível de associatividade
subs  = politica de substituição
flag_ = flag de saida
*/
// teste branch

int main(int argc, char const *argv[]){
  
	int nsets, bsize, assoc, flag_saida,dados[MAX],k=0,tag,i,j;
	char *subs,file[15]; 
	FILE *entrada;
	//atribuições iniciais
	nsets = atoi (argv[1]);
	bsize = atoi (argv[2]);
	assoc = atoi (argv[3]);
	subs = argv [4];
	flag_saida = atoi (argv [5]); 
	//copiando nome do arquivo para uma string
	entrada = fopen(argv[6],"rb");
	
	// leitura até o final do arquivo, menor que o máximo

	k = fread(&dados[0],sizeof(int),MAX,entrada);
	i = nsets/assoc;
	j = assoc;

	int matriz[i][j];

	for (int t = 0; t < k ; ++t)
	{
		tag = dados[t]%i;

	}
  	
	return 0;
}
