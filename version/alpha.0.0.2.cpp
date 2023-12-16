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
  int disponivel;
} Quarto;

typedef struct {
  Cliente clientes[MAX_CLIENTES];
  Quarto quartos[MAX_QUARTOS];
  int numClientes;
  int numQuartos;
} Hotel;

/* cadastros */
void cadastrarCliente(Hotel *hotel);
void cadastrarQuarto(Hotel *hotel);
void editarClientes(Hotel *hotel);
/* imforma�oes */
void exibirQuartos(Hotel hotel);
void detalharClientes(Hotel hotel);
void exibirClientes(Hotel hotel);
/* Buscadores */
int verificaCPF(char *cpfEntrada);
int buscarNumeroDeQuartos(int Cnumero, Hotel hotel);
/* menus */
void menu(Hotel *hotel);
void Clientes(Hotel hotel);

// teste de para salva variavel - n�o funcionou ;-;
/* void salvarDados(Hotel* hotel, const char* nomeArquivo) {
  FILE* arquivo = fopen(nomeArquivo, "wb");
  if (arquivo == NULL) {
    perror("Erro ao abrir o arquivo");
    return;
  }
  fwrite(hotel->clientes, sizeof(Cliente), hotel->numClientes, arquivo);
  fwrite(hotel->quartos, sizeof(Quarto), hotel->numQuartos, arquivo);
  fclose(arquivo);
}

void carregarDados(Hotel* hotel, const char* nomeArquivo) {
  FILE* arquivo = fopen(nomeArquivo, "rb");
  if (arquivo == NULL) {
    perror("Erro ao abrir o arquivo");
    return;
  }
  fread(hotel->clientes, sizeof(Cliente), MAX_CLIENTES, arquivo);
  fread(hotel->quartos, sizeof(Quarto), MAX_QUARTOS, arquivo);
  fseek(arquivo, 0, SEEK_END);
  long tamanhoArquivo = ftell(arquivo);
  hotel->numClientes = tamanhoArquivo / (sizeof(Cliente));
  hotel->numQuartos = tamanhoArquivo / (sizeof(Quarto));
  fclose(arquivo);
}
 */

void cadastrarCliente(Hotel *hotel) {
  fflush(stdin);
  int Ccomfirmacao;

  printf("Digite o cpf: ");
  scanf("%s", hotel->clientes[hotel->numClientes].cpf);

  if (!verificaCPF(hotel->clientes[hotel->numClientes].cpf)) {
    system("cls");
    printf("CPF inv�lido.\n");
    cadastrarCliente(hotel);
  }

  fflush(stdin);
  printf("Digite o nome do cliente: ");
  gets(hotel->clientes[hotel->numClientes].nome);

  printf("Digite o endere�o do cliente: ");
  gets(hotel->clientes[hotel->numClientes].endereco);

  printf("Digite o telefone do cliente: ");
  gets(hotel->clientes[hotel->numClientes].telefone);

  printf("Deseja confirma o cadastro\n 1 - Sim \n 2 - N�o; \n");
  scanf("%d", &Ccomfirmacao);

  if (Ccomfirmacao == 1) {
    system("cls");
    printf("Cadatro do cliente confirmado. \nId = %d\n", hotel->numClientes);

    hotel->numClientes++;

    Cliente(hotel);
  } else {
    system("cls");

    *hotel->clientes[hotel->numClientes].nome = NULL;
    *hotel->clientes[hotel->numClientes].cpf = NULL;
    *hotel->clientes[hotel->numClientes].endereco = NULL;
    *hotel->clientes[hotel->numClientes].telefone = NULL;

    Cliente(hotel);
  }
}

void cadastrarQuarto(Hotel *hotel) {
  fflush(stdin);
  system("cls");

  int Ccomfirmacao;

  printf("Digite o n�mero do quarto: ");
  scanf("%d", &hotel->quartos[hotel->numQuartos].numero);

  if (buscarNumeroDeQuartos(hotel->quartos[hotel->numQuartos].numero, *hotel) ==
      0) {
    printf("Numero de quarto cadastrado\n");
    menu(hotel);
  }

  printf("Digite a capacidade do quarto: ");
  scanf("%d", &hotel->quartos[hotel->numQuartos].capacidade);
  if (hotel->quartos[hotel->numQuartos].capacidade > 4) {
    hotel->quartos[hotel->numQuartos].capacidade = 4;
    printf("O maximo em um quarto � 4 pessoas.\n");
  }

  printf("Digite o pre�o do quarto: ");
  scanf("%f", &hotel->quartos[hotel->numQuartos].preco);

  printf("Deseja confirma o cadastro\n 1 - Sim \n 2 - N�o; \n");
  scanf("%d", &Ccomfirmacao);

  if (Ccomfirmacao == 1) {
    system("cls");

    printf("Cadatro do quarto confirmado. \nId = %d\n", hotel->numQuartos);
    hotel->quartos[hotel->numQuartos].disponivel = 1;
    hotel->numQuartos++;

    menu(hotel);
  } else if (Ccomfirmacao == 2) {
    system("cls");

    hotel->quartos[hotel->numQuartos].numero = NULL;
    hotel->quartos[hotel->numQuartos].preco = NULL;
    hotel->quartos[hotel->numQuartos].capacidade = NULL;

    menu(hotel);
  }
}

void editarClientes(Hotel *hotel) {
  int Id;

  system("cls");

  if (hotel->numClientes != 0) {
    printf("Informe o Id do cliente\n ");
    scanf("%d", &Id);

    printf("Digite o cpf: ");
    scanf("%s", hotel->clientes[Id].cpf);

    if (!verificaCPF(hotel->clientes[Id].cpf)) {
      system("cls");
      printf("CPF inv�lido.\n");

      cadastrarCliente(hotel);
    }

    fflush(stdin);

    printf("Digite o nome do cliente: ");
    gets(hotel->clientes[Id].nome);

    printf("Digite o endere�o do cliente: ");
    gets(hotel->clientes[Id].endereco);

    printf("Digite o telefone do cliente: ");
    gets(hotel->clientes[Id].telefone);
    
    printf("Edi��o completa. o cliente do id %d, foi editado com sucesso.\n", Id);
    system("pause");

    Clientes(*hotel);

  } else {
    printf("N�o a clientes registrados.\n");
  }

  system("pause");

  Clientes(*hotel);
}

void exibirClientes(Hotel hotel) {
  system("cls");

  if (hotel.numClientes != 0) {
    for (int i = 0; i < hotel.numClientes; i++) {
      printf("ID: %d - Nome: %s\n", i, hotel.clientes[i].nome);
    }
  } else {
    printf("N�o a clientes registrados.\n");
  }
  system("pause");

  Clientes(hotel);
}

void detalharClientes(Hotel hotel) {
  int Id;

  system("cls");

  if (hotel.numClientes != 0) {

    printf("Informe o Id do cliente\n ");
    scanf("%d", &Id);

    system("cls");

    printf("Nome: %s\n", hotel.clientes[Id].nome);
    printf("Cpf: %s\n", hotel.clientes[Id].cpf);
    printf("Endere�o: %s\n", hotel.clientes[Id].endereco);
    printf("Telefone: %s\n", hotel.clientes[Id].telefone);

    system("pause");

    Clientes(hotel);
  } else {
    printf("N�o a clientes registrados.\n");
  }
  system("pause");

  Clientes(hotel);
}

void exibirQuartos(Hotel hotel) {
  system("cls");

  for (int i = 0; i < hotel.numQuartos; i++) {
    printf("N*:%d %s  ", hotel.quartos[i].numero, (hotel.quartos[i].disponivel == 1) ? "+" : "-");
  }
}

void Clientes(Hotel hotel) {
  int opcao;

  do {
    system("cls");

    printf("\nMenu:\n");
    printf("1. Listar clientes\n");
    printf("2. Exibir detalhe do cliente\n");
    printf("3. cadastra clientes\n");
    printf("4. editar clientes\n");
    printf("3. Voltar ao menu\n");
    printf("Escolha uma op��o: ");

    scanf("%d", &opcao);
    fflush(stdin);

    switch (opcao) {
    case 1:
      exibirClientes(hotel);
      break;
    case 2:
      detalharClientes(hotel);
      break;
    case 3:
      cadastrarCliente(&hotel);
      break;
    case 4:
      editarClientes(&hotel);
      break;
    case 5:
      system("cls");
      printf("Voltando ao menu...\n");
      menu(&hotel);
      break;
    default:
      printf("Op��o inv�lida. Tente novamente.\n");
    }

  } while (true);
}

void menu(Hotel *hotel) {
  int opcao;
  // Hotel meuHotel;
  do {
    // salvarDados(&meuHotel, "dados_hotel.dat");
    printf("\nMenu:\n");
    printf("1. Clientes\n");
    printf("2. Cadastrar quarto\n");
    printf("3. Exibir quartos\n");
    printf("4. Sair\n");
    printf("Escolha uma op��o: ");
    scanf("%d", &opcao);
    fflush(stdin);

    switch (opcao) {

    case 1:
      Clientes(*hotel);
      break;
    case 2:
      cadastrarQuarto(hotel);
      break;
    case 3:
      if (hotel->numQuartos != 0) {
        exibirQuartos(*hotel);
      } else {
        printf("Nenhum quarto cadastrado.\n");
      }
      break;
    case 4:
      printf("Saindo...\n");
      abort();
      break;
    default:
      printf("Op��o inv�lida. Tente novamente.\n");
    }
  } while (true);
}

int verificaCPF(char *cpfEntrada) {
  int indice, peso, digitoVerificador1 = 0, digitoVerificador2 = 0;

  if (strcmp(cpfEntrada, "00000000000") == 0) {
    return 1;
  }

  if (strlen(cpfEntrada) != 11)
    return 0;

  for (indice = 0, peso = 10; indice < strlen(cpfEntrada) - 2;
       indice++, peso--) {
    digitoVerificador1 += (cpfEntrada[indice] - 48) * peso;
  }

  digitoVerificador1 %= 11;

  if (digitoVerificador1 < 2) {
    digitoVerificador1 = 0;
  } else {
    digitoVerificador1 = 11 - digitoVerificador1;
  }

  if (digitoVerificador1 != (cpfEntrada[9] - 48)) {
    return 0;
  }

  for (indice = 0, peso = 11; indice < strlen(cpfEntrada) - 1;
       indice++, peso--) {
    digitoVerificador2 += (cpfEntrada[indice] - 48) * peso;
  }

  digitoVerificador2 %= 11;

  if (digitoVerificador2 < 2) {
    digitoVerificador2 = 0;
  } else {
    digitoVerificador2 = 11 - digitoVerificador2;
  }

  if (digitoVerificador2 != (cpfEntrada[10] - 48)) {
    return 0;
  }

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

int main() {
  /* Hotel meuHotel;
  carregarDados(&meuHotel, "dados_hotel.dat"); */
  setlocale(LC_ALL, "Portuguese_Brazil");
  Hotel hotel;

  hotel.numClientes = 0;
  hotel.numQuartos = 0;

  menu(&hotel);
  return 0;
}