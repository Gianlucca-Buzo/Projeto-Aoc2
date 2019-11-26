#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

const int MAX = 10000;
unsigned int lido;

//struct que representa o endereço
typedef struct dado {
	char tag[32],indice[32],offset[32];
	int tagfinal, indicefinal, offsetfinal;
}dados;

//struct que representa a cache
typedef struct memoria {
	char valor[32][10000]; //segundo parâmetro é a quantidade de palavras que dá pra colocar no bloco 
	char tag[32], indice[32];
	int validade;
}cache;

//int convertebinario();

int main(int argc, char const *argv[]){
  
	int nsets, bsize, assoc, flag_saida,valores[MAX],j=0,tam=0, nindice, noffset, ntag, k, l, i, indicecache,s,dec=0;
	float hit=0,missConf=0,missCap=0,missComp=0;
	float txHit, txMiss, txComp, txCap, txConf;
	char *subs,file[8]; 
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

	k = nsets/assoc;
	l = assoc;

	dados endereco[tam];
	char valorbinario[32];
	//cache memoriaPrincipal[k][l];

	noffset = log2(bsize);
	nindice = log2(nsets);
	ntag = 32 - noffset - nindice;

	for (int t = 0; t < tam ; ++t){
		itoa(valores[t],valorbinario,2);
		dec=0;
		for (i=0; i< ntag; i++){
			endereco[t].tag[i] = valorbinario[i];
		}/*
		i++; 
		for (j=0;j< nindice; j++)
			endereco[t].indice[j] = valorbinario[j+i];
		for (int m=0;m<noffset;m++)
			endereco[t].offset[m] = valorbinario[m+j];
			*/
			s= strlen(endereco[t].tag);
			for (int i = s-1; i >=0; i--)
			{
				if((endereco[t].tag[i]) == '1'){
					dec += pow(2,s-1-i);
				}
			}
			printf("\nbinario: %s decimal: %d ",endereco[t].tag,dec);
		/*itoa(endereco[t].tag, endereco[t].tagfinal, 10);
		itoa(endereco[t].indice, endereco[t].indicefinal, 10);
		itoa(endereco[t].offset, endereco[t].offsetfinal, 10);
		indicecache = endereco[t].indicefinal % k;
		*/
		/*
			for (i=0;i<j;i++){
				for (int n=0; n<p;n++){
					if (matriz[indice][i][n] == dados[t]){
						hit++;
						aux++;
						break;
					}
					else {
						if(matriz[indice][i][n] == -1){
							matriz[indice][i][n] = dados[t];
							missComp++; //presente em qualquer tipo de cache 
							aux++;
							break;
						}
						else{
							if(i <= j  && n <= p ){
								random = rand() % j;
								random2 = (rand() % p)+1;
								matriz[indice][random][random2] = dados[t];
							if (j==1)
								missConf++; //cache com mapeamento direto só tem miss de conflito
							else {
								if  (k==1)
									missCap++; //cache totalmente associativa só tem miss de capacidade 
								else{
									missConf++;
									int cont = 0;
									for (int i = 0; i < k; ++i){
										for (int m = 0; m < j; ++m){
											for (int n =0; n<p;n++){
												if(matriz[i][m][n]==-1)
													cont++;
											}
										}
									} //confere se a cache está completamente cheia
									if (cont==0)
										missCap++; //soma no miss de Capacidade só se a cache estiver cheia
								}
							}
						}
					}
				}
					
				}
				if (aux==1)
					break;
			}*/
		 }

	//calcula as taxas de miss e hit
	int missTotal = missCap + missConf + missComp;
	txHit = hit/tam;
	txMiss = 1 - txHit;
	txCap = missCap/missTotal;
	txComp = missComp/missTotal;
	txConf = missConf/missTotal;

	//imprime de acordo com o flag de saída
	if (flag_saida == 0)
		printf ("Número total de acessos: %d\nTaxa de hits: %.2f\nTaxa de miss: %.2f\nTaxa de miss compulsório: %.2f\nTaxa de miss de capacidade: %.2f\nTaxa de miss de conflito: %.2f\n", tam, txHit, txMiss, txComp, txCap, txConf);
	else 
		printf ("%d, %.2f, %.2f, %.2f, %.2f, %.2f", tam, txHit, txMiss, txComp,  txCap, txConf);

	return 0;
}