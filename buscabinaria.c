#include <stdio.h>
#include <string.h>

//Lembrando que o arquivo precisa ser o CEP ORDENADO para dar certo!


typedef struct _Endereco Endereco;

// registroCEP = struct.Struct("72s72s72s72s2s8s2s")

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

int main(int argc, char**argv)
{
	FILE *f;
	
	Endereco e;
	int qt;
	int c;
	int tb, tr;
    int meio;

    	if(argc != 2)
	{
		fprintf(stderr, "USO: %s [CEP]", argv[0]);
		return 1;
	}

	c = 0;
	printf("Tamanho da Estrutura: %ld\n\n", sizeof(Endereco));
	f = fopen("cep_ordenado.dat","rb");

    fseek(f,0,SEEK_END);
    tb = ftell(f);
    tr = tb/sizeof(Endereco);
    int inicio = 0;
    int fim = tr - 1;
 

    while(inicio <= fim){
        meio = (inicio+fim)/2;
        fseek(f,meio*sizeof(Endereco),SEEK_SET);
        fread(&e,sizeof(Endereco),1,f);  //parte que não entendi muito bem
        c++;
        if(strncmp(argv[1],e.cep,8)==0){
            printf("%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n",e.logradouro,e.bairro,e.cidade,e.uf,e.sigla,e.cep);
            printf("levou %d tentativas",c);
            fclose(f);
            return 0; 
        }
        
        if(strncmp(argv[1],e.cep,8)>0){ 
            inicio = meio+1;
        }
        if(strncmp(argv[1],e.cep,8)<0){
            fim = meio-1;
        }

    }
    printf("arquivo não encontrado!");
    fclose(f);
}

	