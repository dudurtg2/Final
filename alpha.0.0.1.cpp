#include <ctype.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CLIENTES 100

typedef struct {
  char nome[50];
  char endereco[100];
  char telefone[15];
} Cliente;

typedef struct {
  Cliente clientes[MAX_CLIENTES];
  int numero;
} ListaClientes;

void cadastrarCliente(ListaClientes *lista);
void exibirClientes(ListaClientes lista);
void menu(ListaClientes *lista);

void cadastrarCliente(ListaClientes *lista) {
  fflush(stdin);
  system("cls");
  printf("Digite o nome do cliente: ");
  fgets(lista->clientes[lista->numero].nome, sizeof(lista->clientes[lista->numero].nome), stdin);
  printf("Digite o endereço do cliente: ");
  fgets(lista->clientes[lista->numero].endereco, sizeof(lista->clientes[lista->numero].endereco), stdin);
  printf("Digite o telefone do cliente: ");
  fgets(lista->clientes[lista->numero].telefone, sizeof(lista->clientes[lista->numero].telefone), stdin);
  lista->numero++;
  menu(lista);
}

void exibirClientes(ListaClientes lista) {
  for (int i = 0; i < lista.numero; i++)
  {
    printf("Nome: %s", lista.clientes[i].nome);
  }
  menu(&lista);
}

int main() {
  ListaClientes lista;
  lista.numero = 0;
  menu(&lista);
  return 0;
}

void menu(ListaClientes *lista) {
  int opcao = 0;
  printf("Escolha:\n");
  scanf("%d", &opcao);

  do {
    if (opcao == 1) {
      cadastrarCliente(lista);
    } else if (opcao == 2) {
      exibirClientes(*lista);
    }

  } while (true);
}
