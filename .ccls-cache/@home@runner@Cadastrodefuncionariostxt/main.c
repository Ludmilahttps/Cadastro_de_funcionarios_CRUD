/**
 * @author Ludmila Silveira (ludmila.ss@grad.ufsc.br)
 * @brief lista encadeada com manipulação de arquivos
 * Trabalho 2 de Linguagem de Programação 1
 * Engenharia de Computação - UFSC
 *
 * @date 2022-08-01
 *
 * @copyright Copyright (c) 2022
 */

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#define N 100
#define TRUE			1
#define FALSE 		0

typedef unsigned char boolean;
typedef char string[50];

struct Aniversario //estrutura de data de nascimento
{
  int dia;
  int mes;
  int ano;
};

typedef struct Funcionario //estrutura ficha de funcionario
{
  string nome;
  string cidade;
  float salario;
  struct Aniversario aniversario; //aninhamento de estrutura
  struct Funcionario *prox;
} funcionario;

int matricula=0; // variavel de controle do numero de funcionarios cadastrados
float salariomin = 1212.00; // variavel com o valor do salario minino

//declaração das funções que seram utilizadas no codigo
int menu();
funcionario* adicionar();
void insere_item_pelo_fim(funcionario **lista, funcionario *item);
void atualizar(funcionario* lista);
void relatorio(funcionario* lista);
void consultar(funcionario* lista);
void comparar(funcionario* lista);
void relacionar(funcionario* lista);
//void cidade(funcionario* lista);
void deletar(struct Funcionario funcionario[N]);
void apaga_todos_os_dados(funcionario **lista);
/*void exporta_dados_arquivo_txt(struct Funcionario funcionario[N]);
void importa_dados_arquivo_txt(struct Funcionario funcionario[N]);
void salva_dados_arquivo_bin(struct Funcionario funcionario[N]);
void recupera_dados_arquivo_bin(struct Funcionario funcionario[N]);*/
void remove_enter(char s[N]);
boolean lista_esta_vazia(funcionario *lista);

int main(){

  funcionario *lista = NULL, *novo;
  
  int varwhile = 1; //loop para sempre voltar pro menu
  int opc; // variavel de escolha do menu

  //importa dados salvos anteriormente
  //recupera_dados_arquivo_bin(funcionario);
  
  while(varwhile){
    //system(“cls”);
    
    opc = menu();
    switch(opc){
      case 1:
        printf("\n adicionar ficha de funcionario:  \n");
        novo = adicionar();
        insere_item_pelo_fim(&lista, novo);
        break;
      case 2:
        printf("\n atualizar ficha de funcionario: \n");
        atualizar(lista);
        break;
      case 3:
        printf("\n relatorio de funcionarios: \n");
        relatorio(lista);
        break;
      case 4:
        printf("\n consultar funcionario: \n");
        consultar(lista);
        break;
      case 5:
        printf("\n comparar salarios dos funcionarios com um valor escolhido: \n");
        comparar(lista);
        break;
      case 6:
        printf("\n relacionar o salario dos funcionarios com o salario minimo: \n");
        relacionar(lista);
        break;
      /*case 7:
        printf("\n relatorio do numero de funcionarios por cidade: \n");
        cidade(lista);
        break;
      case 8:
        printf("\n deletar um funcionario: \n");
        deletar(funcionario);
        break;
      case 9:
        printf("\n importar dados de um arquivo txt \n");
        importa_dados_arquivo_txt(funcionario);
        break;
      case 10:
        printf("\n exportar dados para um arquivo txt \n");
        exporta_dados_arquivo_txt(funcionario);
        break;*/
      case 11:
        printf("\n apaga todos os dados cadastrados \n");
        apaga_todos_os_dados(&lista);
        break;
      case 12:
        printf("\n encerrando programa... \n");
        //salva dados em um arquivo binario
        //salva_dados_arquivo_bin(funcionario);
        varwhile = 0; //quebra o loop
        break;
      default:
        printf("opção inválida. ");
        break;
      }
  }
  return 0;
}

int menu()
{
    int opc;
  
    printf("\n ---------------- menu ------------------");
    printf("\n 1. adicionar ficha de funcionario");
    printf("\n 2. atualizar ficha de funcionario");
    printf("\n 3. relatorio de funcionarios");
    printf("\n 4. consultar funcionario");
    printf("\n 5. comparar salarios dos funcionarios");
    printf("\n 6. relacionar o salario dos funcionarios com o salario minimo");
    printf("\n 7. relatorio do numero de funcionarios por cidade");
    printf("\n 8. deletar um funcionario");
    printf("\n 9. importar dados para um arquivo txt");
    printf("\n 10. exportar dados para um arquivo txt");
    printf("\n 11. apaga todos os dados cadastrados");
    printf("\n 12. fechar programa"); //quebra o loop
    printf("\n------------------------------------------ \n\n opcao: ");
    scanf("%i", &opc);

  return opc;
}

funcionario* adicionar()
{
  funcionario *no = (funcionario*)malloc(sizeof(funcionario));
  
  if(matricula==N) 
    // impede o usuario de cadastrar mais funcionarios após atingir o limite
  {
    printf("\ndesculpe, jah temos o limite de funcionarios cadastrados!\n");
  }
  else
  {
    matricula++; 
    //adiciona mais um numero na matricula para contar mais um funcionario no sistema.
      getchar();
      printf("\n nome do funcionario: ");
        fgets(no->nome, 50, stdin);
        remove_enter(no->nome);
      printf(" cidade do funcionario: ");
        fgets(no->cidade, 50, stdin);
        remove_enter(no->cidade);
      printf(" dia de nascimento do funcionario: ");
        scanf("%d", &no->aniversario.dia);
      printf(" mes de nascimento do funcionario: ");
        scanf("%d", &no->aniversario.mes);
      printf(" ano de nascimento do funcionario: ");
        scanf("%d", &no->aniversario.ano);
      printf(" salario do funcionario: ");
        scanf("%f", &no->salario);
      printf("\n A matricula de %s eh: %i \n", no->nome, matricula);

      no->prox = NULL;
  }
  return no;
}

void insere_item_pelo_fim(funcionario **lista, funcionario *item)
{
  funcionario *aux;
	if (lista_esta_vazia(*lista) == TRUE) {
		*lista = item;
	}
	else {
		aux = *lista;
		while (aux->prox != NULL) aux = aux->prox;
		aux->prox = item;
	}
}

void atualizar(funcionario* lista)
{
  funcionario* aux = lista;
  string alterar;//ficha a ser alterada
  int varencontrada=0; //variavel que diz se a ficha a ser alterada foi encontrada

  if(aux==NULL)
  {
    printf("\nnao existe nenhum funcionario cadastrado no sistema. \n");
  }
  else
  {
    printf("\n Digite o nome do funcionario que deseja alterar a ficha: ");
    scanf("%s", alterar);

      while(aux!=NULL)
      {
        if(strcmp(alterar, aux->nome)==0)
        {
          varencontrada++; //valida para dizer se o funcionario foi encontrado

          getchar();
          printf("\n nome do funcionario: ");
            fgets(aux->nome, 50, stdin);
            remove_enter(aux->nome);
          printf(" cidade do funcionario: ");
            fgets(aux->cidade, 50, stdin);
            remove_enter(aux->cidade);
          printf(" dia de nascimento do funcionario: ");
            scanf("%d", &aux->aniversario.dia);
          printf(" mes de nascimento do funcionario: ");
            scanf("%d", &aux->aniversario.mes);
          printf(" ano de nascimento 3do funcionario: ");
            scanf("%d", &aux->aniversario.ano);
          printf(" salario do funcionario: ");
            scanf("%f", &aux->salario);
          printf("\n ficha do funcionario %s, atualizada!\n", aux->nome);
          return;
        }
        aux=aux->prox;
      }
      if(varencontrada==0)
      {
        printf("\nfuncionario nao encontrado. ");
      }
  }
  return;
}

void relatorio(funcionario *lista)
{
  funcionario *aux = lista;
  
  //verifica se a lista está vazia
  if(aux==NULL)
  {
    printf("\nnao existe nenhum funcionario cadastrado no sistema. \n");
  }
  else
  {
    while(aux!=NULL)
    {
      //estrutura que extrai a data do sistema
      time_t mytime;
      mytime = time(NULL);
      struct tm tm = *localtime(&mytime);
      int idade = 365*(tm.tm_year + 1900) + 30*(tm.tm_mon + 1) + (tm.tm_mday) - 365*(aux->aniversario.ano) - 30*(aux->aniversario.mes - aux->aniversario.dia);
      
      // imprime a ficha de funcionario por funcionario
      printf("Nome: %s - ", aux->nome);
      printf("Cidade: %s - ", aux->cidade);
  	  printf("Nascimento: %d/%d/%d - ", aux->aniversario.dia, aux->aniversario.mes, aux->aniversario.ano);
      printf("idade: %d anos - ", idade/365);
  	  printf("Salario: %.2f ", aux->salario);
  	  printf("\n");
  	  
  		aux = aux->prox;
    }
  }
}

void consultar(funcionario *lista)
{
  funcionario *aux = lista;
  string buscafunc; //variavel para procurar um funcionario
  int varbusca=0; //variavel de controle de busca encontrada ou não

  if(aux==NULL)
  {
    printf("\nnao existe nenhum funcionario cadastrado no sistema. \n");
  }
  else
  {
    printf("\n por qual funcionario voce procura: ");
    scanf(" %s", buscafunc);

    while(aux!=NULL)
    {
      if(strcmp(aux->nome, buscafunc)==0)
      {
        //estrutura que extrai a data do sistema
        time_t mytime;
        mytime = time(NULL);
        struct tm tm = *localtime(&mytime);
        int idade = 365*(tm.tm_year + 1900) + 30*(tm.tm_mon + 1) + (tm.tm_mday) - 365*(aux->aniversario.ano) - 30*(aux->aniversario.mes - aux->aniversario.dia);
        
        varbusca++; //variavel auxiliar que informa se o funcionario buscado foi encontrado
        printf("\n Funcionario: %s encontrado, segue ficha ", aux->nome);
        printf("\n Cidade: %s  ", aux->cidade);
        printf("\n Nascimento: %i/%i/%i ", aux->aniversario.dia, aux->aniversario.mes, aux->aniversario.ano);
        printf("\n Idade: %d anos - ", idade/365);
        printf("\n Salario: %.2f reais", aux->salario);
      }
      aux=aux->prox;
    }
      if(varbusca==0)
      {
      printf("\nesse funcionario nao consta nos funcionarios cadastrados.");
      }
  }

  return;
}

void comparar(funcionario* lista)
{
  funcionario *aux = lista;
  float scompara; //salario de comparação
  int menor=0; //variaveis contadoras

  if(aux==NULL)
  {
    printf("\nnao existe nenhum funcionario cadastrado no sistema. \n");
  }
  else
  {
    printf("\n Digite um valor para buscar salarios maiores ou iguais: \n::");
    scanf("%f", &scompara);

    while(aux!=NULL)
    {
      if(aux->salario >= scompara)
      {
        printf("\n %s recebe %f", aux->nome, aux->salario);
      }
      else
      {
        menor++;
      }
      aux=aux->prox;
    }
    if(menor==matricula)
    {
      printf("\n nenhum funcionario registrado atualmente tem o salario maior ou igual ao digitado.");
    }
  }
  return;
}

void relacionar(funcionario* lista)
{
  funcionario *aux = lista;
  int sinicial=0, smedio=0, salto=0; //variaveis de contagem dos grupos

  if(matricula==0)
  {
    printf("\nnao existe nenhum funcionario cadastrado no sistema. \n");
  }
  else
  {
     while(aux!=NULL)
    {
      if(aux->salario < salariomin)
      {
        sinicial++;
      }
      if(aux->salario > salariomin && aux->salario < (3 * salariomin))
      {
        smedio++;
      }
      if(aux->salario > (3 * salariomin))
      {
        salto++;
      }
      aux=aux->prox;
    }
    printf("\n %i funcionarios recebem menos de um salario minimo.", sinicial);
    printf("\n %i funcionarios recebem de um salario minimo a tres.", smedio);
    printf("\n %i funcionarios recebem mais de 3 salarios minimos.", salto);
  }

  return;
}

/*void cidade(funcionario* lista)
{
  funcionario *aux = lista;
  int i, j; //variaveis contadoras
  int variguais=0, varanterior=0; //variaveis de controle

  if(matricula==0)
  {
    printf("\nnao existe nenhum funcionario cadastrado no sistema. \n");
  }
  else
  {
    for(i=1;i<=matricula;i++) // fixa um funcionario e compara com os outros
    {
      varanterior = 0; variguais = 0;
      for(j=i;j>0;j--) // ve se esta cidade já foi contada anteriormente
      {
        if(strcmp(funcionario[i].cidade, funcionario[j].cidade)==0)
        {
          varanterior++;
        }
      }
      if(varanterior<=1)
      {
        for(j=i;j<=matricula;j++) //procura quantas vezes essa cidade foi citada
        {
          if(strcmp(funcionario[i].cidade, funcionario[j].cidade)==0)
          {
            variguais++;
          }
        }
        printf("\n %s com %d funcionarios\n", funcionario[i].cidade, variguais);
      }
    }
  }
  return;
}
*/
void deletar(struct Funcionario funcionario[N])
{
  int i, deletar=0; //variavel contadora e variavel que armazena qual funcionario deletar
  int varencontrada=0; //variavel que indica se o funcionario a ser deletado esta cadastrado

  if(matricula==0)
  {
    printf("\nnao existe nenhum funcionario cadastrado no sistema. \n");
  }
  else
  {
    printf("\n (para deletar a ficha de um funcionario, eh necessario seu numero de matricula, caso nao saiba o numero de");
    printf("\n matricula desejado, digite 400 para voltar ao menu e retirar o relatorio dos funcionarios cadastrados.)\n");
    printf("\n digite a matricula do funcionario que deseja deletar a ficha: ");
    scanf("%i", &deletar);

    if(deletar==400)
    {
      return; //retorna para o menu
    }
    else
    {
      for(i=1;i<=matricula;i++)
      {
        if(deletar==i)
        {
          varencontrada++; //indica se o funcionario esta atualmente cadastrado
          matricula--; //diminui um da matricula já que foi excluido um funcionario. A: E SE SÓ TIVER 1 FUNCIONARIO CADASTRADO? O ALGORITMO N VAI DEIXAR DELETAR...
          for(deletar=0;deletar<=matricula;deletar++)
          {
            strcpy(funcionario[deletar].nome, funcionario[deletar+1].nome);
            strcpy(funcionario[deletar].cidade, funcionario[deletar+1].cidade);
            funcionario[deletar].aniversario.dia = funcionario[deletar+1].aniversario.dia;
            funcionario[deletar].aniversario.mes = funcionario[deletar+1].aniversario.mes;
            funcionario[deletar].aniversario.ano = funcionario[deletar+1].aniversario.ano;
            funcionario[deletar].salario = funcionario[deletar+1].salario;
          }
          printf("\n ficha do funcionario deletada!\n");
        }
      }
      if(varencontrada==0)
      {
        printf("\n funcionario nao encontrado. ");
      }
    }
  }
  return;
}

void apaga_todos_os_dados(funcionario **lista)
{
	funcionario *aux;
	
	while (*lista != NULL) 
  {
		aux = *lista;
		*lista = (*lista)->prox;
		printf("Apagando o item %s\n", aux->nome);		
		free(aux);
	}	
}

/*void exporta_dados_arquivo_txt(struct Funcionario funcionario[N])
{
	FILE* arq_funcionarios;
  //abre arquivo texto
  arq_funcionarios = fopen("registro_funcionarios.txt", "w");
  
  if(arq_funcionarios == NULL)
  {
    printf("não foi possivel abrir o arquivo.\n");
    exit(0);
  }
	int i;
		
	for (i = 1; i <= matricula; i++) {
		fprintf(arq_funcionarios, "%s\n", funcionario[i].nome);
		fprintf(arq_funcionarios, "%s\n", funcionario[i].cidade);
		fprintf(arq_funcionarios, "%d\n", funcionario[i].aniversario.dia);
    fprintf(arq_funcionarios, "%d\n", funcionario[i].aniversario.mes);
    fprintf(arq_funcionarios, "%d\n", funcionario[i].aniversario.ano);
		fprintf(arq_funcionarios, "%.2f\n\n", funcionario[i].salario);
	}
	fclose(arq_funcionarios);
}

void importa_dados_arquivo_txt(struct Funcionario funcionario[N])
{
  if(matricula!=0)
  {
    printf("\nvocê não pode importar um arquivo texto porque já existem arquivos cadastrados na base de dados.");
  }
    
  else
  {
      FILE* arq_funcionarios;
    //abre arquivo texto
    arq_funcionarios = fopen("registro_funcionarios.txt", "a+");
    
    if(arq_funcionarios == NULL)
    {
      printf("não foi possivel abrir o arquivo.\n");
      exit(0);
    }
  	int i=1;

    //passa os dados do arquivo para o programa
  	while(!feof(arq_funcionarios))
    {
      fscanf(arq_funcionarios, "%s\n", funcionario[i].nome);
  		fscanf(arq_funcionarios, "%s\n", funcionario[i].cidade);
  		fscanf(arq_funcionarios, "%d\n", &funcionario[i].aniversario.dia);
      fscanf(arq_funcionarios, "%d\n", &funcionario[i].aniversario.mes);
      fscanf(arq_funcionarios, "%d\n", &funcionario[i].aniversario.ano);
  		fscanf(arq_funcionarios, "%f\n\n", &funcionario[i].salario);
      i++;
      matricula++;
  	}
  	fclose(arq_funcionarios);
  }
  
   return;
}

void salva_dados_arquivo_bin(struct Funcionario funcionario[N])
{
  	FILE* arq_funcionarios;
  //abre arquivo binario
  arq_funcionarios = fopen("base_de_dados", "wb");
  
  if(arq_funcionarios == NULL)
  {
    printf("ERROR.\n");
    exit(0);
  }
  
  for (int i = 1; i <= matricula; i++) {
  		fwrite(funcionario[i].nome, sizeof(char), N, arq_funcionarios);
  		fwrite(funcionario[i].cidade, sizeof(char), N, arq_funcionarios);
  		fwrite(&funcionario[i].aniversario.dia, sizeof(int), N,arq_funcionarios);
      fwrite(&funcionario[i].aniversario.mes, sizeof(int), N, arq_funcionarios);
      fwrite(&funcionario[i].aniversario.ano, sizeof(int), N, arq_funcionarios);
  		fwrite(&funcionario[i].salario, sizeof(float), N, arq_funcionarios);
        
  	}
  	fclose(arq_funcionarios); 
}

void recupera_dados_arquivo_bin(struct Funcionario funcionario[N])
{
   FILE* arq_funcionarios;
    //abre arquivo texto
    arq_funcionarios = fopen("base_de_dados", "ab+");
    
    if(arq_funcionarios == NULL)
    {
      printf("ERROR\n");
      exit(0);
    }
  	int i=1;

    //passa os dados do arquivo para o programa
  	while(!feof(arq_funcionarios))
    {
      fread(funcionario[i].nome, sizeof(char), N, arq_funcionarios);
  		fread(funcionario[i].cidade, sizeof(char), N, arq_funcionarios);
  		fread(&funcionario[i].aniversario.dia, sizeof(int), N,arq_funcionarios);
      fread(&funcionario[i].aniversario.mes, sizeof(int), N, arq_funcionarios);
      fread(&funcionario[i].aniversario.ano, sizeof(int), N, arq_funcionarios);
  		fread(&funcionario[i].salario, sizeof(float), N, arq_funcionarios);
      i++;
      matricula++;
  	}
  matricula--;
  	fclose(arq_funcionarios);
}
*/
void remove_enter(char s[N])
{
	int tamanho = strlen(s);
	s[tamanho-1] = '\0';
}

boolean lista_esta_vazia(funcionario *lista)
{
	if (lista == NULL) return TRUE;
	return FALSE;
}