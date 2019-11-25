#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int MAX = 1000;
unsigned int lido;

typedef struct dado {
	char tag[100],indice[1000],offset[50];
	bool validade;
}dados;

//int convertebinario();

int main(int argc, char const *argv[]){
  
	int nsets, bsize, assoc, flag_saida,valores[MAX],j=0,tam=0;
	dados dado[MAX];
	char *subs,file[8],teste[32]; 
	FILE *entrada;
	//atribuições iniciais
	nsets = atoi (argv[1]);
	bsize = atoi (argv[2]);
	assoc = atoi (argv[3]);
	subs = argv [4];
	flag_saida = atoi (argv [5]); 
	entrada = fopen(argv[6],"rb");
	
	if(entrada == NULL) {
        printf("Arquivo inválido. \n");
        return 1;
    }

    while (!feof(entrada)) {
        fread(&lido, sizeof(unsigned int), 1, entrada);
        valores[tam] = __builtin_bswap32(lido);
        tam++;
    }
	tam--;

	itoa(dados[0],teste,2);
	printf("%d  %s",dados[0],teste);

return 0;
}