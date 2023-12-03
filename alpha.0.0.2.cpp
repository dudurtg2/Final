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

void cadastrarCliente(Hotel *hotel);
void cadastrarQuarto(Hotel *hotel);
void exibirClientes(Hotel hotel);
void exibirQuartos(Hotel hotel);
int verificaCPF(char *cpf);
void menu(Hotel *hotel);

// teste de para salva variavel - não funcionou ;-;
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
  scanf("%d", &Ccomfirmacao);
  

  if (Ccomfirmacao == 1) {
    system("cls");
    
    printf("Cadatro do quarto confirmado. \nId = %d\n", hotel->numQuartos);
    hotel->quartos[hotel->numQuartos].disponivel = 1;
    hotel->numQuartos++;
    
    menu(hotel);
  } else if (Ccomfirmacao == 2){
    system("cls");

    hotel->quartos[hotel->numQuartos].numero = NULL;
    hotel->quartos[hotel->numQuartos].preco = NULL;
    hotel->quartos[hotel->numQuartos].capacidade = NULL;

    menu(hotel);
  }
}

void exibirClientes(Hotel hotel) {
  for (int i = 0; i <= hotel.numClientes - 1; i++) {
    printf("ID: %d - Nome: %s\n", hotel.numClientes, hotel.clientes[i].nome);
  }
  menu(&hotel);
}

void exibirQuartos(Hotel hotel) {
  for (int i = 0; i < hotel.numQuartos; i++) {
    printf("N*:%d %s  ", hotel.quartos[i].numero, (hotel.quartos[i].disponivel == 1) ? "+" : "-");
  }
}

void menu(Hotel *hotel) {
  int opcao;
  // Hotel meuHotel;
  do {
    // salvarDados(&meuHotel, "dados_hotel.dat");
    printf("\nMenu:\n");
    printf("1. Cadastrar cliente\n");
    printf("2. Exibir clientes\n");
    printf("3. Cadastrar quarto\n");
    printf("4. Exibir quartos\n");
    printf("5. Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    fflush(stdin);

    switch (opcao) {
    case 1:
      cadastrarCliente(hotel);
      break;
    case 2:
      exibirClientes(*hotel);
      break;
    case 3:
      cadastrarQuarto(hotel);
      break;
    case 4:
      if (hotel->numQuartos != 0) {
        exibirQuartos(*hotel);
      } else {
        printf("Nenhum quarto cadastrado.\n");
      }
      break;
    case 5:
      printf("Saindo...\n");
      break;
    default:
      printf("Opção inválida. Tente novamente.\n");
    }
  } while (true);
}

int main() {
  /* Hotel meuHotel;
  carregarDados(&meuHotel, "dados_hotel.dat"); */
  setlocale(LC_ALL, "Portuguese_Brazil");
  Hotel hotel;
  if (hotel.numClientes == NULL && hotel.numQuartos == NULL)
  {
    hotel.numClientes = 0;
    hotel.numQuartos = 0;
  }
  
  
  menu(&hotel);
  return 0;
}
