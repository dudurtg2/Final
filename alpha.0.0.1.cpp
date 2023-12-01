#include <ctype.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CLIENTES 100
#define MAX_QUARTOS 100

typedef struct {
  char nome[50];
  char endereco[100];
  char telefone[15];
} Cliente;

typedef struct {
  int numero;
  int capacidade;
  float preco;
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
void menu(Hotel *hotel);

void cadastrarCliente(Hotel *hotel) {
  fflush(stdin);
  system("cls");
  printf("Digite o nome do cliente: ");
  fgets(hotel->clientes[hotel->numClientes].nome, sizeof(hotel->clientes[hotel->numClientes].nome), stdin);
  printf("Digite o endereço do cliente: ");
  fgets(hotel->clientes[hotel->numClientes].endereco, sizeof(hotel->clientes[hotel->numClientes].endereco), stdin);
  printf("Digite o telefone do cliente: ");
  fgets(hotel->clientes[hotel->numClientes].telefone, sizeof(hotel->clientes[hotel->numClientes].telefone), stdin);
  hotel->numClientes++;
  menu(hotel);
}

void cadastrarQuarto(Hotel *hotel) {
  fflush(stdin);
  system("cls");
  printf("Digite o número do quarto: ");
  scanf("%d", &hotel->quartos[hotel->numQuartos].numero);
  printf("Digite a capacidade do quarto: ");
  scanf("%d", &hotel->quartos[hotel->numQuartos].capacidade);
  printf("Digite o preço do quarto: ");
  scanf("%f", &hotel->quartos[hotel->numQuartos].preco);
  hotel->numQuartos++;
  menu(hotel);
}

void exibirClientes(Hotel hotel) {
  for (int i = 0; i < hotel.numClientes; i++)
  {
    printf("Nome: %s", hotel.clientes[i].nome);
  }
  menu(&hotel);
}

int main() {
  Hotel hotel;
  hotel.numClientes = 0;
  hotel.numQuartos = 0;
  menu(&hotel);
  return 0;
}

void menu(Hotel *hotel) {
  int opcao = 0;
  printf("Escolha:\n");
  scanf("%d", &opcao);

  do {
    if (opcao == 1) {
      cadastrarCliente(hotel);
    } else if (opcao == 2) {
      exibirClientes(*hotel);
    } else if (opcao == 3) {
      cadastrarQuarto(hotel);
    }

  } while (true);
}
