#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#define N 100

struct Aniversario //estrutura de data de nascimento
{
  int dia;
  int mes;
  int ano;
};

struct Funcionario //estrutura ficha de funcionario
{
  char nome[100];
  char cidade[100];
  float salario;
  struct Aniversario aniversario; //aninhamento de estrutura
};

int matricula=0; // variavel de controle do numero de funcionarios cadastrados
float salariomin = 1212.00; // variavel com o valor do salario minino

//declaração das funções que seram utilizadas no codigo
void adicionar(struct Funcionario funcionario[N]);
void atualizar(struct Funcionario funcionario[N]);
void relatorio(struct Funcionario funcionario[N]);
void consultar(struct Funcionario funcionario[N]);
void comparar(struct Funcionario funcionario[N]);
void relacionar(struct Funcionario funcionario[N]);
void cidade(struct Funcionario funcionario[N]);
void deletar(struct Funcionario funcionario[N]);
void dataatual(struct Funcionario funcionario[N], int i);
void exporta_dados_arquivo_txt(struct Funcionario funcionario[N]);
void importa_dados_arquivo_txt(struct Funcionario funcionario[N]);
void exporta_dados_arquivo_bin(struct Funcionario funcionario[N]);
void importa_dados_arquivo_bin(struct Funcionario funcionario[N]);
void remove_enter(char s[N]);

int main(){
  struct Funcionario funcionario[N];
  
  int varwhile = 1; //loop para sempre voltar pro menu
  int opc; // variavel de escolha do menu

  while(varwhile){
    //system(“cls”);
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
    printf("\n 11. fechar programa"); //quebra o loop
    printf("\n------------------------------------------ \n\n opcao: ");
    scanf("%i", &opc);

    switch(opc){
      case 1:
        printf("\n adicionar ficha de funcionario:  \n");
        adicionar(funcionario);
        break;
      case 2:
        printf("\n atualizar ficha de funcionario: \n");
        atualizar(funcionario);
        break;
      case 3:
        printf("\n relatorio de funcionarios: \n");
        relatorio(funcionario);
        break;
      case 4:
        printf("\n consultar funcionario: \n");
        consultar(funcionario);
        break;
      case 5:
        printf("\n comparar salarios dos funcionarios com um valor escolhido: \n");
        comparar(funcionario);
        break;
      case 6:
        printf("\n relacionar o salario dos funcionarios com o salario minimo: \n");
        relacionar(funcionario);
        break;
      case 7:
        printf("\n relatorio do numero de funcionarios por cidade: \n");
        cidade(funcionario);
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
        break;
      case 11:
        printf("\n encerrando programa... \n");
        varwhile = 0; //quebra o loop
        break;
      default:
        printf("opção inválida. ");
        break;
      }
  }
  return 0;
}

void dataatual(struct Funcionario funcionario[N], int i)
{
  int idade;
  time_t mytime;
  mytime = time(NULL);
  struct tm tm = *localtime(&mytime); //estrutura que extrai a data do sistema

  //dia atual: tm.tm_mday . mes atual: tm.tm_mon + 1 . ano atual: tm.tm_year + 1900

  idade = 365*(tm.tm_year + 1900) + 30*(tm.tm_mon + 1) + (tm.tm_mday) - 365*(funcionario[i].aniversario.ano) - 30*(funcionario[i].aniversario.mes - funcionario[i].aniversario.dia);
  printf("- idade: %d anos ", idade/365);

  return;
}

void adicionar(struct Funcionario funcionario[N])
{
  if(matricula==N) // impede o usuario de cadastrar mais funcionarios após atingir o limite
  {
    printf("\ndesculpe, jah temos o limite de funcionarios cadastrados!\n");
  }
  else
  {
    matricula++; //adiciona mais um numero na matricula para contar mais um funcionario no sistema.
      printf("\n nome do funcionario: ");
        scanf(" %s", funcionario[matricula].nome);
      printf(" cidade do funcionario: ");
        scanf(" %s", funcionario[matricula].cidade);
      printf(" dia de nascimento do funcionario: ");
        scanf("%d", &funcionario[matricula].aniversario.dia);
      printf(" mes de nascimento do funcionario: ");
        scanf("%d", &funcionario[matricula].aniversario.mes);
      printf(" ano de nascimento do funcionario: ");
        scanf("%d", &funcionario[matricula].aniversario.ano);
      printf(" salario do funcionario: ");
        scanf("%f", &funcionario[matricula].salario);
      printf("\n A matricula de %s eh: %i \n", funcionario[matricula].nome, matricula);
  }
  return;
}

void atualizar(struct Funcionario funcionario[N])
{
  int alterar, i; //ficha a ser alterada, varivel contadora
  int varencontrada=0; //variavel que diz se a ficha a ser alterada foi encontrada

  if(matricula==0)
  {
    printf("\nnao existe nenhum funcionario cadastrado no sistema. \n");
  }
  else
  {
    printf("\n (para atualizar a ficha de um funcionario, eh necessario seu numero de matricula, caso nao saiba o numero de");
    printf("\n matricula desejado, digite 400 para voltar ao menu e retirar o relatorio dos funcionarios cadastrados.)\n");
    printf("\n digite a matricula do funcionario que deseja alterar a ficha: ");
    scanf("%i", &alterar);

    if(alterar==400)
    {
      return; //retorna para o menu
    }
    else
    {
      for(i=1;i<=matricula;i++)
      {
        if(alterar==i)
        {
          varencontrada++; //valida para dizer se o funcionario foi encontrado
          printf("\n nome do funcionario: ");
            scanf(" %s", funcionario[i].nome);
          printf(" cidade do funcionario: ");
            scanf(" %s", funcionario[i].cidade);
          printf(" dia de nascimento do funcionario: ");
            scanf("%d", &funcionario[i].aniversario.dia);
          printf(" mes de nascimento do funcionario: ");
            scanf("%d", &funcionario[i].aniversario.mes);
          printf(" ano de nascimento do funcionario: ");
            scanf("%d", &funcionario[i].aniversario.ano);
          printf(" salario do funcionario: ");
            scanf("%f", &funcionario[i].salario);
          printf("\n ficha do funcionario %s, matricula: %i atualizada!\n", funcionario[i].nome, i);
        }
      }
      if(varencontrada==0)
      {
        printf("\nfuncionario nao encontrado. ");
      }
    }
  }
  return;
}

void relatorio(struct Funcionario funcionario[N])
{
  int i; //variavel contadora
  if(matricula==0)
  {
    printf("\nnao existe nenhum funcionario cadastrado no sistema. \n");
  }
  else
  {
    for(i=1;i<=matricula;i++)
    {
      // imprime a ficha de funcionario por funcionario
      printf("\n matricula: %i ", i);
      printf("- nome: %s ", funcionario[i].nome);
      printf("- nascimento: %i/%i/%i ", funcionario[i].aniversario.dia, funcionario[i].aniversario.mes, funcionario[i].aniversario.ano);
      dataatual(funcionario, i); //funçao que contabiliza a idade a partir da data atual e da estrutura aniversario
      printf("- salario: %.2f", funcionario[i].salario);
    }
    printf("\n");
  }
  return;
}

void consultar(struct Funcionario funcionario[N])
{
  char buscafunc[100]; //variavel para procurar um funcionario
  int i, varbusca=0; //variavel contadora e variavel de controle de busca encontrada ou não

  if(matricula==0)
  {
    printf("\nnao existe nenhum funcionario cadastrado no sistema. \n");
  }
  else
  {
    printf("\n por qual funcionario voce procura: ");
    scanf(" %s", buscafunc);

    for(i=0;i<=matricula;i++)
    {
      if(strcmp(funcionario[i].nome, buscafunc)==0)
      {
        varbusca++; //variavel auxiliar que informa se o funcionario buscado foi encontrado
        printf("\n funcionario: %s encontrado, segue ficha: ", funcionario[i].nome);
        printf("\n matricula: %i ", i);
        printf("\n nascimento: %i/%i/%i ", funcionario[i].aniversario.dia, funcionario[i].aniversario.mes, funcionario[i].aniversario.ano);
        dataatual(funcionario, i); //funçao que contabiliza a idade a partir da data atual e da estrutura aniversario
        printf("\n salario: %f", funcionario[i].salario);
      }
    }
      if(varbusca==0)
      {
      printf("\nesse funcionario nao consta nos funcionarios cadastrados.");
      }
  }

  return;
}

void comparar(struct Funcionario funcionario[N])
{
  float scompara; //salario de comparação
  int i, menor=0; //variaveis contadoras
  int vmaior[N], vmenor[N]; //vetor maior que o salario sugerido, vetor menor que o salario sugerido

  if(matricula==0)
  {
    printf("\nnao existe nenhum funcionario cadastrado no sistema. \n");
  }
  else
  {
    printf("\n digite um valor para comparar com o salario dos funcionarios: ");
    scanf("%f", &scompara);

    for(i=1;i<=matricula;i++) //compara todos os funcionarios
    {
      if(funcionario[i].salario >= scompara)
      {
        printf("\n %s recebe %f", funcionario[i].nome, funcionario[i].salario);
      }
      else
      {
        menor++;
      }
    }
    if(menor==matricula)
    {
      printf("\n nenhum funcionario registrado atualmente tem o salario maior ou igual ao digitado.");
    }
  }
  return;
}

void relacionar(struct Funcionario funcionario[N])
{
  int i; //variavel contadora
  int sinicial=0, smedio=0, salto=0; //variaveis de contagem dos grupos

  if(matricula==0)
  {
    printf("\nnao existe nenhum funcionario cadastrado no sistema. \n");
  }
  else
  {
    for(i=1;i<=matricula;i++)
    {
      if(funcionario[i].salario < salariomin)
      {
        sinicial++;
      }
      if(funcionario[i].salario > salariomin && funcionario[i].salario < (3 * salariomin))
      {
        smedio++;
      }
      if(funcionario[i].salario > (3 * salariomin))
      {
        salto++;
      }
    }
    printf("\n %i funcionarios recebem menos de um salario minimo.", sinicial);
    printf("\n %i funcionarios recebem de um salario minimo a tres.", smedio);
    printf("\n %i funcionarios recebem mais de 3 salarios minimos.", salto);
  }

  return;
}

void cidade(struct Funcionario funcionario[N])
{
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

void exporta_dados_arquivo_txt(struct Funcionario funcionario[N])
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

void exporta_dados_arquivo_bin(struct Funcionario funcionario[N])
{
  
}

void importa_dados_arquivo_bin(struct Funcionario funcionario[N])
{
  
}

void remove_enter(char s[N])
{
	int tamanho = strlen(s);
	s[tamanho-1] = '\0';
}