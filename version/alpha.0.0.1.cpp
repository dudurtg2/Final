#include <ctype.h>

#include <locale.h>

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#define MAX_CLIENTES 100
#define MAX_QUARTOS 30

typedef struct {
  char nome[50];
  char endereco[100];
  char telefone[15];
  char cpf[11];
} Cliente;

typedef struct {
  int numero;
  int capacidade;
  float preco;
  bool disponivel;
} Quarto;

typedef struct {
  Cliente clientes[MAX_CLIENTES];
  Quarto quartos[MAX_QUARTOS];
  int numClientes;
  int numQuartos;
} Hotel;

void cadastrarCliente(Hotel *hotel);
void cadastrarQuarto(Hotel *hotel);
void exibirClientes(Hotel hotel);
void exibirQuartos(Hotel hotel);
int verificaCPF(char *cpf);
void menu(Hotel *hotel);



void cadastrarCliente(Hotel *hotel) {
  fflush(stdin);
  int Ccomfirmacao;

  printf("Digite o cpf: ");
  scanf("%s", hotel->clientes[hotel->numClientes].cpf);

  if (!verificaCPF(hotel->clientes[hotel->numClientes].cpf)) {
    system("cls");
    printf("CPF inválido.\n");
    cadastrarCliente(hotel);
  }

  fflush(stdin);
  printf("Digite o nome do cliente: ");
  gets(hotel->clientes[hotel->numClientes].nome);

  printf("Digite o endereço do cliente: ");
  gets(hotel->clientes[hotel->numClientes].endereco);

  printf("Digite o telefone do cliente: ");
  gets(hotel->clientes[hotel->numClientes].telefone);

  printf("Deseja confirma o cadastro\n 1 - Sim \n 2 - Não; \n");
  scanf("%d", &Ccomfirmacao);

  if (Ccomfirmacao == 1) {
    system("cls");
    printf("Cadatro do cliente confirmado. \nId = %d\n", hotel->numClientes);

    hotel->numClientes++;

    menu(hotel);
  } else {
    system("cls");

    *hotel->clientes[hotel->numClientes].nome = NULL;
    *hotel->clientes[hotel->numClientes].cpf = NULL;
    *hotel->clientes[hotel->numClientes].endereco = NULL;
    *hotel->clientes[hotel->numClientes].telefone = NULL;

    menu(hotel);
  }
}

// Codigo para validar cpf, mudar nome de variaveis
int verificaCPF(char *cpfEntrada) {
  int indice, peso, digitoVerificador1 = 0, digitoVerificador2 = 0;

  if (strlen(cpfEntrada) != 11)
    return 0;

  for (indice = 0, peso = 10; indice < strlen(cpfEntrada) - 2; indice++, peso--)
    digitoVerificador1 += (cpfEntrada[indice] - 48) * peso;

  digitoVerificador1 %= 11;
  if (digitoVerificador1 < 2)
    digitoVerificador1 = 0;
  else
    digitoVerificador1 = 11 - digitoVerificador1;

  if (digitoVerificador1 != (cpfEntrada[9] - 48))
    return 0;

  for (indice = 0, peso = 11; indice < strlen(cpfEntrada) - 1; indice++, peso--)
    digitoVerificador2 += (cpfEntrada[indice] - 48) * peso;

  digitoVerificador2 %= 11;
  if (digitoVerificador2 < 2)
    digitoVerificador2 = 0;
  else
    digitoVerificador2 = 11 - digitoVerificador2;

  if (digitoVerificador2 != (cpfEntrada[10] - 48))
    return 0;

  return 1;
}

int buscarNumeroDeQuartos(int Cnumero, Hotel hotel) {
  for (int i = 0; i < hotel.numQuartos; i++) {
    if (hotel.quartos[i].numero == Cnumero) {
      return 0;
    }
  }
  return Cnumero;
}

void cadastrarQuarto(Hotel *hotel) {
  fflush(stdin);
  system("cls");

  int Ccomfirmacao;

  printf("Digite o número do quarto: ");
  scanf("%d", &hotel->quartos[hotel->numQuartos].numero);

  if (buscarNumeroDeQuartos(hotel->quartos[hotel->numQuartos].numero, *hotel) ==
      0) {
    printf("Numero de quarto cadastrado\n");
    menu(hotel);
  }

  printf("Digite a capacidade do quarto: ");
  scanf("%d", &hotel->quartos[hotel->numQuartos].capacidade);

  printf("Digite o preço do quarto: ");
  scanf("%f", &hotel->quartos[hotel->numQuartos].preco);

  printf("Deseja confirma o cadastro\n 1 - Sim \n 2 - Não; \n");
  scanf("%d", &hotel->quartos[hotel->numQuartos].capacidade);

  if (Ccomfirmacao == 1) {
    system("cls");

    printf("Cadatro do quarto confirmado. \nId = %d\n", hotel->numQuartos);

    hotel->numQuartos++;

    menu(hotel);
  } else {
    system("cls");

    hotel->quartos[hotel->numQuartos].numero = NULL;
    hotel->quartos[hotel->numQuartos].preco = NULL;
    hotel->quartos[hotel->numQuartos].capacidade = NULL;

    menu(hotel);
  }
}

void exibirClientes(Hotel hotel) {
  for (int i = 0; i <= hotel.numClientes - 1; i++) {
    printf("Nome: %s", hotel.clientes[i].nome);
  }
  menu(&hotel);
}

void exibirQuartos(Hotel hotel) {
  for (int i = 0; i < hotel.numQuartos; i++) {
    printf("N*:%d %s  ", hotel.quartos[i].numero,
           hotel.quartos[i].disponivel ? "+" : "-");
  }
}

void menu(Hotel *hotel) {
  int opcao = 0;
  fflush(stdin);
 
  if (hotel->numQuartos != NULL) {

    exibirQuartos(*hotel);
  }

  printf("\n");
  printf("Escolha:\n");
  scanf("%d", &opcao);

  do {
	
    if (opcao == 1) {
      system("cls");
      cadastrarCliente(hotel);
    } else if (opcao == 2) {
      exibirClientes(*hotel);
    } else if (opcao == 3) {
      cadastrarQuarto(hotel); 
	}
  } while (true);
}

int main() {
  Hotel hotel;
  hotel.numClientes = 0;
  hotel.numQuartos = 0;
  menu(&hotel);
  return 0;
}
