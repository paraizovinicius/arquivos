#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 8

typedef struct _Endereco Endereco;

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2]; // Ao Espaço no final da linha + quebra de linha
};

int compara(const void *e1, const void *e2)
{
	return strncmp(((Endereco*)e1)->cep,((Endereco*)e2)->cep,8);
}

int main(int argc, char**argv)
{
	FILE *f, *saida;
	Endereco *e;
	long posicao, qtd, metades, contador, aindaFalta, tamanhoBloco;
  char nomeArquivo[20];
  
	f = fopen("cep.dat","rb");
	fseek(f,0,SEEK_END);
	posicao = ftell(f);
	qtd = posicao/sizeof(Endereco); //qtd = quantos filhotes tem
  metades = qtd/N; // qtd = 24 // metades = 3 //
  aindaFalta = qtd%N;
  // 1º contador = 1
  // 2º contador = 2 .. 8
  contador = 0;
  
  
  rewind(f);
  while(contador<N){
  //
    tamanhoBloco = metades;
    if(aindaFalta != 0)
    {
      tamanhoBloco++;
      aindaFalta--;
    }
  	e = (Endereco*) malloc(tamanhoBloco*sizeof(Endereco));      
    fread(e,sizeof(Endereco),tamanhoBloco,f);
    qsort(e,tamanhoBloco,sizeof(Endereco),compara); //ORDENADO
    sprintf(nomeArquivo,"cep_%d.dat", contador);  
  	saida = fopen(nomeArquivo,"wb");
  	fwrite(e,sizeof(Endereco),tamanhoBloco,saida);
  	fclose(saida);
  	free(e);
    contador++;
  }

	fclose(f);
}