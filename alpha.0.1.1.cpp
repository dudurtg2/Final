#include <ctype.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CLIENTES 100
#define MAX_QUARTOS 30
#define MAX_HISTORICO 200

int tentativasLogin = 3;

typedef struct {
  char senha[3][12] = { "p9Y8B7v6Hj", "3fH8zD0L9K", "S3nh4_F0rt3" };
  int adm;
}
Adminstrador;

typedef struct {
  char nome[50];
  char endereco[100];
  char telefone[15];
  char cpf[11];
  char palavraChave[20];
  int quarto;
  int existeCliente;
  int temQuarto;
}
Cliente;

typedef struct {
  float preco;
  int numero;
  int capacidade;
  int idCliente[4];
  int quartoVago[4];
  int existeQuarto;
}
Quarto;

typedef struct {
  Cliente clientes[MAX_CLIENTES];
  Quarto quartos[MAX_QUARTOS];
  Adminstrador adm;
  int HotelIdCliente;
  int Hotelquartos;
  int idAux;
  char historico[MAX_HISTORICO]; /* <- inpementar */
}
Hotel;

/* Salva e carregar dados */
void salvarDados(Hotel hotel);
/* cadastros */
void cadastrarCliente(Hotel* hotel);
void cadastrarQuarto(Hotel* hotel);
void editarClientes(Hotel* hotel);
void editarQuartos(Hotel* hotel);
/* excluir */
void excluirClientes(Hotel* hotel);
void excluirQuartos(Hotel* hotel);
/* imformaçoes */
void exibirQuartos(Hotel hotel);
void historicoDeReservas(Hotel hotel); /* <- inpementar */
void detalharClientes(Hotel hotel);
void exibirClientes(Hotel hotel);
/* Check-in check-out */
void checkInQuarto(Hotel hotel); 
void checkOnQuarto(Hotel hotel); /* <- inpementar */
/* Verificadores */
int verificarReservas(int Id); /* <- inpementar */
int verificaCPF(char* cpfEntrada);
int buscarIdDoQuarto(int Cnumero, Hotel Hotel);
int buscarNumeroDeQuartos(int Cnumero, Hotel hotel);
int adicionarNoQuarto(int numero, int cliente, Hotel hotel);
/* menus */
void menu(Hotel* hotel);
void Clientes(Hotel hotel);
void Quartos(Hotel hotel);
void Resevas(Hotel hotel);
void Login(Hotel hotel);

/*  */
void salvarDados(Hotel hotel) {
  FILE* file = fopen("hotel.bin", "wb");

  fwrite(&hotel, sizeof(Hotel), 1, file);

  fclose(file);
}

void cadastrarCliente(Hotel* hotel) {
  fflush(stdin);

  int Ccomfirmacao;

  system("cls");

  if (hotel->clientes[hotel->idAux].existeCliente== 1) {
    if (hotel->idAux != hotel->HotelIdCliente) {
      hotel->idAux++;
      cadastrarCliente(hotel);
    }
  }

  printf("Digite o cpf: ");
  scanf("%s", hotel->clientes[hotel->idAux].cpf);

  if (!verificaCPF(hotel->clientes[hotel->idAux].cpf)) {
    printf("CPF inválido.\n");
    cadastrarCliente(hotel);
  }

  fflush(stdin);
  printf("Digite o nome do cliente: ");
  gets(hotel->clientes[hotel->idAux].nome);

  printf("Digite o endereço do cliente: ");
  gets(hotel->clientes[hotel->idAux].endereco);

  printf("Digite o telefone do cliente: ");
  scanf("%19s", hotel->clientes[hotel->idAux].telefone);

  printf("Digite oa sua palavra chave: ");
  scanf("%19s", hotel->clientes[hotel->idAux].palavraChave);

  fflush(stdin);
  printf("Deseja confirma o cadastro\n 1 - Sim \n 2 - Não; \n");
  scanf("%d", &Ccomfirmacao);

  if (Ccomfirmacao == 1) {
    system("cls");
    printf("Cadatro do cliente confirmado. \nId = %d\n", hotel->idAux);
    hotel->clientes[hotel->idAux].existeCliente= 1;
    hotel->clientes[hotel->idAux].temQuarto = 0;

    if (hotel->idAux == hotel->HotelIdCliente) {
      hotel->HotelIdCliente++;

      Clientes(*hotel);
    } else {
      Clientes(*hotel);
    }
  } else {
    system("cls");

    *hotel->clientes[hotel->idAux].nome = NULL;
    *hotel->clientes[hotel->idAux].cpf = NULL;
    *hotel->clientes[hotel->idAux].endereco = NULL;
    *hotel->clientes[hotel->idAux].telefone = NULL;
    *hotel->clientes[hotel->idAux].palavraChave = NULL;

    Clientes(*hotel);
  }
}

void cadastrarQuarto(Hotel* hotel) {
  fflush(stdin);
  system("cls");

  int Ccomfirmacao;

  if (hotel->quartos[hotel->idAux].existeQuarto == 1) {
    if (hotel->idAux != hotel->Hotelquartos) {
      hotel->idAux++;
      cadastrarQuarto(hotel);
    }
  }

  int nunAux;

  printf("Digite o número do quarto: ");
  scanf("%d", &nunAux);

  if (buscarNumeroDeQuartos(nunAux, *hotel) == 0) {
    printf("Numero de quarto cadastrado\n");
    system("pause");
    Quartos(*hotel);
  }

  hotel->quartos[hotel->idAux].numero = nunAux;

  printf("Digite a capacidade do quarto: ");
  scanf("%d", &hotel->quartos[hotel->idAux].capacidade);

  if (hotel->quartos[hotel->idAux].capacidade > 4) {
    hotel->quartos[hotel->idAux].capacidade = 4;
    printf("O maximo em um quarto é 4 pessoas.\n");
  }

  printf("Digite o preço do quarto: ");
  scanf("%f", &hotel->quartos[hotel->idAux].preco);

  printf("Deseja confirma o cadastro\n 1 - Sim \n 2 - Não; \n");
  scanf("%d", &Ccomfirmacao);

  if (Ccomfirmacao == 1) {
    system("cls");

    printf("Cadatro do quarto confirmado. \nId = %d\n", hotel->idAux);

    hotel->quartos[hotel->idAux].existeQuarto = 1;
    for (int i = 0; i < 4; i++) {
      hotel->quartos[hotel->idAux].quartoVago[i] = 1;
      hotel->quartos[hotel->idAux].idCliente[i] = 0;
    }

    if (hotel->idAux == hotel->Hotelquartos) {
      hotel->Hotelquartos++;
      Quartos(*hotel);
    } else {
      Quartos(*hotel);
    }

    Quartos(*hotel);
  } else if (Ccomfirmacao == 2) {
    system("cls");

    hotel->quartos[hotel->idAux].numero = -1;
    hotel->quartos[hotel->idAux].preco = NULL;
    hotel->quartos[hotel->idAux].capacidade = NULL;

    Quartos(*hotel);
  }
}

void excluirClientes(Hotel* hotel) {
  int Id, Ccomfirmacao;

  system("cls");

  if (hotel->HotelIdCliente != 0) {
    printf("Informe o Id do cliente\n ");
    scanf("%d", &Id);

    if (Id == 0) {
      printf("O ID 0 não pode ser excluido.\n");
      system("pause");
      Clientes(*hotel);
    }

    printf("Deseja excluir o cadastro de %s\n 1 - Sim \n 2 - Não; \n", hotel->clientes[Id].nome);
    scanf("%d", &Ccomfirmacao);

    if (Ccomfirmacao == 1) {
      system("cls");
      printf("Cadatro do cliente excluido. \nId = %d\n", hotel->idAux);
      *hotel->clientes[Id].nome = NULL;
      *hotel->clientes[Id].cpf = NULL;
      *hotel->clientes[Id].endereco = NULL;
      *hotel->clientes[Id].telefone = NULL;
      hotel->clientes[Id].existeCliente= 0;
      hotel->clientes[Id].quarto = -1;
    } else {
      system("cls");
      Clientes(*hotel);
    }
  } else {
    printf("Não a clientes registrados\n.");
    Clientes(*hotel);
  }
}

void excluirQuartos(Hotel* hotel) {
  int Id, Ccomfirmacao;

  system("cls");

  if (hotel->Hotelquartos != 0) {
    printf("Informe o numero do quarto\n ");
    scanf("%d", &Id);
    int numero = buscarIdDoQuarto(Id, *hotel);

    printf("Deseja excluir o quarto de numero: %d\n 1 - Sim \n 2 - Não; \n", hotel->quartos[numero].numero);
    scanf("%d", &Ccomfirmacao);

    if (Ccomfirmacao == 1) {
      system("cls");
      printf("Cadatro do cliente excluido. \nId = %d\n", hotel->idAux);
      hotel->quartos[Id].numero = NULL;
      hotel->quartos[Id].preco = NULL;
      hotel->quartos[Id].capacidade = NULL;
      hotel->quartos[Id].existeQuarto = 0;
    } else {
      system("cls");
      Quartos(*hotel);
    }
  } else {
    printf("Não a quartos registrados\n.");
    Quartos(*hotel);
  }
}

void editarClientes(Hotel* hotel) {
  int Id;

  system("cls");

  if (hotel->HotelIdCliente != 0) {
    printf("Informe o Id do cliente para editar seu cadastro\n ");
    scanf("%d", &Id);

    printf("Digite o novo cpf: ");
    scanf("%s", hotel->clientes[Id].cpf);

    if (!verificaCPF(hotel->clientes[Id].cpf)) {
      system("cls");
      printf("CPF inválido.\n");

      editarClientes(hotel);
    }

    fflush(stdin);

    printf("Digite o novo nome do cliente: ");
    gets(hotel->clientes[Id].nome);

    printf("Digite o novo endereço do cliente: ");
    gets(hotel->clientes[Id].endereco);

    printf("Digite o novo telefone do cliente: ");
    gets(hotel->clientes[Id].telefone);

    printf("Edição completa. o cliente do id %d, foi editado com sucesso.\n", Id);
    system("pause");

    Clientes(*hotel);
  } else {
    printf("Não a clientes registrados.\n");
  }

  system("pause");

  Clientes(*hotel);
}

void editarQuartos(Hotel* hotel) {
  int Id;

  system("cls");

  if (hotel->Hotelquartos != 0) {
    printf("Informe o Id do cliente para editar seu cadastro\n ");
    scanf("%d", &Id);

    int nunAux;

    printf("Digite o número do quarto: ");
    scanf("%d", &nunAux);

    if (buscarNumeroDeQuartos(nunAux, *hotel) == 0) {
      printf("Numero de quarto cadastrado\n");
      system("pause");
      Quartos(*hotel);
    }

    hotel->quartos[Id].numero = nunAux;

    printf("Digite a capacidade do quarto: ");
    scanf("%d", &hotel->quartos[Id].capacidade);

    if (hotel->quartos[Id].capacidade > 4) {
      hotel->quartos[Id].capacidade = 4;
      printf("O maximo em um quarto é 4 pessoas.\n");
    }

    printf("Digite o preço do quarto: ");
    scanf("%f", &hotel->quartos[Id].preco);

    printf("Edição completa. o Quarto do id %d, foi editado com sucesso.\n", Id);
    system("pause");

    Quartos(*hotel);
  } else {
    printf("Não a quartos registrados.\n");
  }

  system("pause");

  Quartos(*hotel);
}

void exibirClientes(Hotel hotel) {
  system("cls");
  if (hotel.HotelIdCliente != 1) {
    for (int i = 1; i < hotel.HotelIdCliente; i++) {
      if (hotel.clientes[i].existeCliente!= 0) {
        printf("ID: %d - Nome: %s\n", i, hotel.clientes[i].nome);
      }
    }
  } else {
    printf("Não a clientes registrados.\n");
  }
  system("pause");

  Clientes(hotel);
}

void checkInQuarto(Hotel hotel) {
  int numero, cliente;

  system("cls");

  printf("Digite o numero do quarto: ");
  scanf("%d", &numero);

  if (buscarIdDoQuarto(numero, hotel) != 0) {
    numero = buscarIdDoQuarto(numero, hotel);
  } else if (hotel.quartos[0].numero == numero) {
    numero = 0;
  } else {
    printf("Quarto não existe.\n");
    system("pause");
    Resevas(hotel);
  }

  printf("Digite o id do cliente: ");
  scanf("%d", &cliente);
  if (cliente == 0) {
    printf("Não pode acicionar o ID 0.\n");
    system("pause");
    Resevas(hotel);
  }

  if (hotel.clientes[cliente].temQuarto == 1) {
    printf("O cliente já está em um quarto.\n");
    system("pause");
    Resevas(hotel);
  }

  if (cliente <= hotel.HotelIdCliente) {
    if (adicionarNoQuarto(numero, cliente, hotel) != 0) {
      hotel.quartos[numero].idCliente[adicionarNoQuarto(numero, cliente, hotel) - 1] = cliente;
      hotel.quartos[numero].quartoVago[adicionarNoQuarto(numero, cliente, hotel) - 1] = 0;
      hotel.clientes[numero].quarto = numero;
      hotel.clientes[numero].temQuarto = 1;
      printf("Cliente adcionado\n");
      system("pause");
      Resevas(hotel);
    } else {
      printf("Limite alcançado\n");
      system("pause");
      Resevas(hotel);
    }
  } else {
    printf("Cliente não existe\n");
    system("pause");
    Resevas(hotel);
  }
}

void detalharClientes(Hotel hotel) {
  int Id;
  char palavraChave[20];

  system("cls");

  if (hotel.HotelIdCliente != 0) {
    printf("Informe o Id do cliente\n ");
    scanf("%d", &Id);

    fflush(stdin);
    printf("Informe a palavra chave do cliente\n ");
    scanf("%19s", &palavraChave);

    if (strcmp(hotel.clientes[Id].palavraChave, palavraChave) == 0) {
      system("cls");

      printf("Nome: %s\n", hotel.clientes[Id].nome);
      printf("Cpf: %s\n", hotel.clientes[Id].cpf);
      printf("Endereço: %s\n", hotel.clientes[Id].endereco);
      printf("Telefone: %s\n", hotel.clientes[Id].telefone);

      system("pause");

      Clientes(hotel);
    } else {
      printf("Palavra chave incorreta.\n");
      system("pause");

      Clientes(hotel);
    }
  } else {
    printf("Não a clientes registrados.\n");
  }
  system("pause");

  Clientes(hotel);
}

void exibirQuartos(Hotel hotel) {
  system("cls");

  if (hotel.Hotelquartos != 0) {
    for (int i = 0; i < hotel.Hotelquartos; i++) {
      if (hotel.quartos[i].existeQuarto != 0) {
        printf("===========================\n");
        printf("ID: %d - Numero: %d - Capacidade:%d - Preço:%.2f\n", i, hotel.quartos[i].numero, hotel.quartos[i].capacidade, hotel.quartos[i].preco);
        for (int j = 0; j < hotel.quartos[i].capacidade; j++) {
          printf("Clientes: %s\n", hotel.clientes[hotel.quartos[i].idCliente[j]].nome);
        }
        printf("===========================\n");
      }
    }
  } else {
    printf("Não a clientes registrados.\n");
  }
  system("pause");
}

void Clientes(Hotel hotel) {
  int opcao;

  hotel.idAux = 0;

  do {
    system("cls");

    salvarDados(hotel);

    printf("\nMenu:\n");
    printf("1. Listar clientes\n");
    printf("2. Exibir detalhe do cliente\n");
    printf("3. Cadastra clientes\n");
    if (hotel.adm.adm == 1) {
      printf("4. Editar clientes\n");
      printf("5. Excluir clientes\n\n");
    }

    printf("%d. Voltar ao menu\n", (hotel.adm.adm == 0) ? 4 : 6);
    printf("Escolha uma opção: ");

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
        if (hotel.adm.adm == 1) {
          editarClientes(&hotel);
          break;
        } else {
          system("cls");
          printf("Voltando ao menu...\n");
          menu(&hotel);
          break;
        }

      case 5:
        if (hotel.adm.adm == 1) {
          excluirClientes(&hotel);
          break;
        } else {
          printf("Opção inválida. Tente novamente.\n");
          Clientes(hotel);
          break;
        }

        break;
      case 6:
        if (hotel.adm.adm == 1) {
          system("cls");
          printf("Voltando ao menu...\n");
          menu(&hotel);
          break;
        } else {
          printf("Opção inválida. Tente novamente.\n");
          Clientes(hotel);
          break;
        }
      default:
        printf("Opção inválida. Tente novamente.\n");
    }

  } while (true);
}

void Quartos(Hotel hotel) {
  int opcao;

  hotel.idAux = 0;

  do {
    system("cls");

    salvarDados(hotel);

    printf("\nMenu:\n");
    printf("1. Exibir quartos\n");
    if (hotel.adm.adm == 1) {
      printf("2. Cadastrar quarto\n");
      printf("3. Excluir quarto\n");
      printf("4. Editar quartos\n\n");
    }

    printf("%d. Voltar ao menu\n", (hotel.adm.adm == 0) ? 2 : 5);
    printf("Escolha uma opção: ");

    scanf("%d", &opcao);
    fflush(stdin);

    switch (opcao) {
      case 1:
        if (hotel.Hotelquartos != 0) {
          exibirQuartos(hotel);
        } else {
          printf("Nenhum quarto cadastrado.\n");
          system("pause");
        }
        break;
      case 2:
        if (hotel.adm.adm == 1) {
          cadastrarQuarto(&hotel);
          break;
        } else {
          system("cls");
          printf("Voltando ao menu...\n");
          menu(&hotel);
          break;
        }
      case 3:
        if (hotel.adm.adm == 1) {
          excluirQuartos(&hotel);
          break;
        } else {
          printf("Opção inválida. Tente novamente.\n");
          Quartos(hotel);
          break;
        }

        break;
      case 4:
        if (hotel.adm.adm == 1) {
          editarQuartos(&hotel);
          break;
        } else {
          printf("Opção inválida. Tente novamente.\n");
          Quartos(hotel);
          break;
        }

        break;
      case 5:
        if (hotel.adm.adm == 1) {
          system("cls");
          printf("Voltando ao menu...\n");
          menu(&hotel);
          break;
        } else {
          printf("Opção inválida. Tente novamente.\n");
          Quartos(hotel);
          break;
        }
        break;
      default:
        printf("Opção inválida. Tente novamente.\n");
    }

  } while (true);
}

void Resevas(Hotel hotel) {
  int opcao;

  hotel.idAux = 0;

  do {
    system("cls");

    salvarDados(hotel);

    printf("\nMenu:\n");
    printf("1. reservar quartos\n");

    printf("4. Voltar ao menu\n");
    printf("Escolha uma opção: ");

    scanf("%d", &opcao);
    fflush(stdin);

    switch (opcao) {
      case 1:
        checkInQuarto(hotel);
        break;
      case 2:

        break;
      case 3:

        break;
      case 4:
        system("cls");
        printf("Voltando ao menu...\n");
        menu(&hotel);
        break;
      default:
        printf("Opção inválida. Tente novamente.\n");
    }

  } while (true);
}

void Login(Hotel hotel) {
  char senha[20];

  system("cls");
  printf("Você tem %d tentativas\n", tentativasLogin);
  printf("Digite a senha de administrador: ");
  scanf("%19s", senha);

  if (strcmp(hotel.adm.senha[0], senha) == 0 || strcmp(hotel.adm.senha[1], senha) == 0 || strcmp(hotel.adm.senha[2], senha) == 0) {
    system("cls");
    hotel.adm.adm = 1;
    printf("Login de administrador realizado com sucesso.\n");
    system("pause");
    menu(&hotel);
  } else {
    system("cls");
    printf("Senha incorreta.\n");
    if (tentativasLogin == 0) {
      tentativasLogin = 3;
      printf("Você excedeu o limite de tentativas.\n");
      system("pause");
      menu(&hotel);
    }
    tentativasLogin--;
    Login(hotel);
  }
}

void menu(Hotel* hotel) {
  int opcao;
  do {
    salvarDados(*hotel);

    printf("\nMenu:\n");
    printf("1. Clientes\n");
    printf("2. Quartos\n\n");

    printf("3. %s\n", (hotel->adm.adm == 0) ? "Login" : "Deslogar");
    if (hotel->adm.adm == 1) {
      printf("4. Reservas\n");
    }
    printf("%s. Sair\n", (hotel->adm.adm == 0) ? "4" : "5");

    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

    fflush(stdin);

    switch (opcao) {
      case 1:
        Clientes(*hotel);
        break;
      case 2:
        Quartos(*hotel);
        break;

      case 3:
        if (hotel->adm.adm == 0) {
          Login(*hotel);
          break;
        } else {
          system("cls");
          printf("Deslogando...\n");
          hotel->adm.adm = 0;
          system("pause");
          break;
        }
      case 4:
        if (hotel->adm.adm == 1) {
          Resevas(*hotel);
          break;
        } else {
          hotel->adm.adm = 0;
          salvarDados(*hotel);
          printf("Saindo...\n");
          abort();
        }
        break;
      case 5:
        if (hotel->adm.adm == 0) {
          Resevas(*hotel);
          break;
        } else {
          hotel->adm.adm = 0;
          salvarDados(*hotel);
          printf("Saindo...\n");
          abort();
        }
      default:
        printf("Opção inválida. Tente novamente.\n");
    }
  } while (true);
}

int verificaCPF(char* cpfEntrada) {
  int indice, peso, digitoVerificador1 = 0, digitoVerificador2 = 0;

  if (strcmp(cpfEntrada, "00000000000") == 0) {
    return 1;
  }

  if (strlen(cpfEntrada) != 11)
    return 0;

  for (indice = 0, peso = 10; indice < strlen(cpfEntrada) - 2; indice++, peso--) {
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

  for (indice = 0, peso = 11; indice < strlen(cpfEntrada) - 1; indice++, peso--) {
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

int buscarNumeroDeQuartos(int numero, Hotel hotel) {
  for (int i = 0; i < hotel.Hotelquartos; i++) {
    if (hotel.quartos[i].numero == numero) {
      return 0;
    }
  }
  return numero;
}

int buscarIdDoQuarto(int numero, Hotel hotel) {
  for (int i = 0; i < hotel.Hotelquartos; i++) {
    if (hotel.quartos[i].numero == numero) {
      return i;
    }
  }
  return 0;
}

int adicionarNoQuarto(int numero, int cliente, Hotel hotel) {
  for (int i = 0; i < hotel.quartos[numero].capacidade; i++) {
    if (hotel.quartos[numero].quartoVago[i] == 1) {
      return i + 1;
    }
  }
  return 0;
}

int main() {
  Hotel hotel;

  setlocale(LC_ALL, "Portuguese_Brazil");
  hotel.adm.adm = 0;
  hotel.HotelIdCliente = 0;
  hotel.Hotelquartos = 0;

  FILE* file = fopen("hotel.bin", "rb");

  if (file == NULL) {
    printf("Arquivo não encontrado.\n");
  } else {
    fread(&hotel, sizeof(Hotel), 1, file);

    fclose(file);
  }

  menu(&hotel);
  return 0;
}