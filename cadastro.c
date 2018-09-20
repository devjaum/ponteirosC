#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct produto
{
	char nome[101];
	float valor;
} Produto;

typedef struct fornecedor{
	char nomeFantasia[101];
	char endereco[101];
} Fornecedor;

int menu();

/** voids **/
void recebeValorProd(Produto *produto, int *iCont);
void recebeValorForn(Fornecedor *fornecedor, int *contador);

/** cadastro **/
int cadastroProduto();
int cadastroFornecedor();

/** visualizacao de dados **/
int mostraProduto(Produto *produto, int *contador);
int mostraFornecedor(Fornecedor *fornecedor, int *contador);

/** auxiliares **/
char escolha(char *nome);
void flush_in();

int main()
{
	menu();
	return 0;
}

int menu()
{

	int menu;

	printf("**Menu**\n\n");
	printf(" 1-> Administrativo\n");
	printf(" 2-> Caixa\n");
	printf(" 3-> Estoque\n");
	printf("\n Escolha a opcao desejada: ");
	scanf("%d", &menu);
	flush_in();

	switch (menu)
	{
	case 1:
		printf("\n Iniciando Administrativo...\n");
		system("cls || clear");
		//cadastroProduto();
		cadastroFornecedor();
		break;
	case 2:
		printf("\n Iniciando Caixa...\n");
		break;
	case 3:
		printf("\n Iniciando Estoque...\n");
		break;
	default:
		printf("\n Opcao invalida...\n");
	}
}
	/******************* FUNCOES PARA CADASTRO DE PRODUTOS ********************/
//recebe valor dos produtos
void recebeValorProd(Produto *produto, int *iCont)
{
	printf("Digite o nome do produto: ");
	fgets(produto[*iCont].nome, sizeof(produto[*iCont].nome), stdin);
	printf("Digite o valor do produto: ");
	scanf("%f", &produto[*iCont].valor);
}

//CADASTRA OS PRODUTOS
int cadastroProduto()
{
	//v. auxiliares
	int iCont = 0, iMaximo = 100;
	char retorno;
	Produto *produto = (Produto *)malloc(iMaximo * sizeof(Produto));
	if (!produto)
	{
		printf("Erro ao alocar memoria!!!\n");
		return 1;
	}

	do
	{
		if (iCont < iMaximo)
		{
			recebeValorProd(produto, &iCont);
			retorno = escolha("produto");
			iCont++;
			flush_in();
		}
		else
		{
			int iNovoMaximo = iMaximo + 100;
			int x;
			Produto *aux = produto;
			produto = (Produto *)malloc(iNovoMaximo * sizeof(Produto));
			if (!produto && !aux)
			{
				printf("Erro na alocacao de memoria! Contate o desenvolvedor do sistema!!\n");
				return 1;
			};
			for (x = 0; x < iCont; x++)
			{
				strcpy(produto[x].nome, aux[x].nome);
				produto[x].valor = aux[x].valor;
			}
			free(aux);
			iMaximo = iNovoMaximo;
			recebeValorProd(produto, &iCont);
			retorno = escolha("produto");
			iCont++;
			flush_in();
		}
		
	} while (retorno != 'n');
	mostraProduto(produto, &iCont);
}

//MOSTRA OS PRODUTOS CADASTRADOS
int mostraProduto(Produto *produto, int *contador)
{
	int x;
	printf("\n*** MOSTRANDO PRODUTOS ***\n");
	printf("Nome \t\t Valor Unitario\n\n");
	for (x = 0; x < *contador; x++)
	{
		produto[x].nome[strcspn(produto[x].nome, "\n")] = '\0';
		printf("%s\t %.2f\n", produto[x].nome, produto[x].valor);
	}
}

/******************* FUNCOES PARA CADASTRO DE FORNECEDOR ********************/

void recebeValorForn(Fornecedor *fornecedor, int *contador){
	printf("Digite o nome do Fornecedor: ");
	fgets(fornecedor[*contador].nomeFantasia, sizeof(fornecedor[*contador].nomeFantasia), stdin);
	printf("Digite o endereco do fornecedor: ");
	fgets(fornecedor[*contador].endereco, sizeof(fornecedor[*contador].endereco), stdin);
}

int cadastroFornecedor(){
	int iContF = 0;
	int iMaximo = 2;
	int x;
	char retorno;

	//fazer variavel do tipo fornecedor
	Fornecedor *fornecedor = (Fornecedor*) malloc(iMaximo * sizeof(Fornecedor));

	do{
		//se ultrapassar o limite maximo de cadastro, ira alocar dinamico
		if(iContF < iMaximo){
			recebeValorForn(fornecedor, &iContF);
			retorno = escolha("fornecedor");
			iContF++;
			flush_in();
		}else{
			Fornecedor *aux = fornecedor;
			int iNovoMaximo = iMaximo + 100;
			fornecedor = (Fornecedor*) malloc(iNovoMaximo * sizeof(Fornecedor));
			for(x=0; x<iContF; x++){
				strcpy(fornecedor[x].nomeFantasia, aux[x].nomeFantasia);
				strcpy(fornecedor[x].endereco, aux[x].endereco);
			}
			//liberando memoria
			free(aux);
			iMaximo = iNovoMaximo;
			recebeValorForn(fornecedor, &iContF);
			retorno = escolha("fornecedor");
			iContF++;
			flush_in();
		}
	}while(retorno != 'n');
	mostraFornecedor(fornecedor, &iContF);
}

int mostraFornecedor(Fornecedor *fornecedor, int *contador){
	int x;
	printf("\n\t********** FORNECEDORES **********\n");
	for (x = 0; x < *contador; x++)
	{
		fornecedor[x].nomeFantasia[strcspn(fornecedor[x].nomeFantasia, "\n")] = '\0';
		fornecedor[x].endereco[strcspn(fornecedor[x].endereco, "\n")] = '\0';
		printf("Nome Fantasia: %s \t\t Endereco: %s\n", fornecedor[x].nomeFantasia, fornecedor[x].endereco);
	}
}

char escolha(char *nome){
	char cEscolha;
	printf("Deseja cadastrar mais um %s? (s/n)", nome);
	scanf(" %c", &cEscolha);
	printf("\n");
	return cEscolha;
}

//Limpa buffer do teclado
void flush_in(){
	int ch;
	while ((ch = fgetc(stdin)) != EOF && ch != '\n'){}
}
