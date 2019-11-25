#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int MAX = 1000;
unsigned int lido;

//int convertebinario();

int main(int argc, char const *argv[]){
  
	int nsets, bsize, assoc, flag_saida,dados[MAX],j=0,tam=0;
	char *subs,*txt,file[8],teste[32]; 
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
        dados[tam] = __builtin_bswap32(lido);
        tam++;
    }
	tam--;

	itoa(dados[0],teste,2);
	printf("%d  %s",dados[0],teste);

return 0;
}
/*
int convertebinario(){
	int dec,i,q[32],r[32]; //declaração das variáveis necessárias
	i=0;                   //contador de elementos da array do loop while
	printf("Digite o numero decimal que serah passado para binario:\n");
	scanf("%d", &dec);
	printf("%d em binarios: ",dec);
		for (i = 0; i < 32 ; ++i)
		{
			r[i] = 0;
		}
	  //Algoritmo para o cálculo 
		do{     // enquanto o quociente for diferente de 1, o programa continuará calculando
	 		if((dec % 2)==0){
	 			r[i] = 0;
	 			dec = dec/2;
	 		}
	 			else{
	 				r[i] = 1;
	 				dec--;
	 				dec = dec/2;
	 			}
	 			i++;
	 	}while (dec >= 1);
	 	i = 0;
	 	int j=32;
	 	while(i<32){
	 		q[j] = r[i];
	 	}


	printf("\n");
	return(0);
}
*/