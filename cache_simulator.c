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
typedef struct cache {
	int valor[100]; //vetor que representa a quantidade de palavras em cada bloco
	int tag, validade;
}cache;

int main(int argc, char const *argv[]){
  
	int nsets, bsize, assoc, flag_saida,valores[MAX],j=0,tam=0, nindice, noffset, ntag, k, l, i, indicecache,s, random, random2, cont, p;
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
	
	//faz a leitura do arquivo
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
	p = bsize/4;

	dados endereco[tam]; //cria um endereço para cada dado lido
	int valorbinario[32]; //armazena o valor binário dos dados lidos no arquivo
	cache memoria[k][l];

	//calcula quantos bits são usados para tag, indice e offset 
	noffset = log2(bsize);
	nindice = log2(nsets);
	ntag = 32 - noffset - nindice;

	//inicializa os bits de validade com 0
	for(i=0; i < k ;i++){
		for(int t=0;t < l;t++){
			memoria[i][t].validade = 0;
		}
	} 

	//inicia o laço para cada dado lido no arquivo
	for (int t = 0; t < tam ; ++t){

		//transforma para binário
		int aux;
	    for (aux = 32; aux >= 0; aux--) {
	        if (valores[t] % 2 == 0) {
	            valorbinario[aux] = 0;
	            valores[t] = valores[t] / 2;
	        }
	        else {
	            valorbinario[aux] = 1;
	            valores[t]= valores[t] / 2;
	        }
	    }

	    //separa os bits de tag, índice e offset 
		for (i=0; i< ntag; i++){
			endereco[t].tag[i] = valorbinario[i];
		}
		i++; 
		for (j=0;j< nindice; j++)
			endereco[t].indice[j] = valorbinario[j+i];
		for (int m=0;m<noffset;m++)
			endereco[t].offset[m] = valorbinario[m+j];
		
		//transforma de binário para decimal 
		s= strlen(endereco[t].tag);
		endereco[t].tagfinal = 0;
		endereco[t].indicefinal = 0;
		endereco[t].offsetfinal = 0;
		for (int i = s-1; i >=0; i--){
			if((endereco[t].tag[i]) == '1'){
				endereco[t].tagfinal += pow(2,s-1-i);
			}
		}

		s= strlen(endereco[t].indice);
		for (int i = s-1; i >=0; i--){
			if((endereco[t].indice[i]) == '1'){
				endereco[t].indicefinal += pow(2,s-1-i);
			}
		}

		s= strlen(endereco[t].offset);
		for (int i = s-1; i >=0; i--){
			if((endereco[t].offset[i]) == '1'){
				endereco[t].offsetfinal += pow(2,s-1-i);
			}
		}

		//calcula o bloco que o dado é mapeado
		indicecache = endereco[t].indicefinal % k; 

			for (i=0;i<l;i++){
					if (memoria[indicecache][i].tag == endereco[t].tagfinal){
						hit++;
						break;
					}
					else {
						if(memoria[indicecache][i].validade == 0){
							random = rand() % p;
							memoria[indicecache][i].valor[random] = valores[t]; //salva o dado em umas das palavras do bloco
							memoria[indicecache][i].validade = 1;
							missComp++; //presente em qualquer tipo de cache 
							break;
						}
						else{
							if(i <= l){
								random = rand() % p;
								random2 = rand() % l;
								memoria[indicecache][random2].valor[random] = valores[t]; //faz a substituição randômica
							if (l==1)
								missConf++; //cache com mapeamento direto só tem miss de conflito
							else {
								if  (k==1)
									missCap++; //cache totalmente associativa só tem miss de capacidade 
								else{
									missConf++;
									cont = 0;
									for (int i = 0; i < k; ++i){
										for (int m = 0; m < l; ++m){
												if(memoria[i][m].validade==0)
													cont++;
											}
										}
									} //confere se a cache está completamente cheia
									if (cont==0)
										missCap++; //soma no miss de Capacidade só se todos os bits de validade estiverem em 1
								}
							}
						}
					}
				}
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