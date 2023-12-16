#include <ctype.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 10
#define MAX_PRO 100

#define COLOR_RESET "\x1b[0m"
#define COLOR_RED "\x1b[31m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_BLUE "\x1b[34m"

typedef struct {
    char nome[50];
    int cpf[11];
    int telefone[11];
    int cep[8];
}
CLIENTE;

typedef struct {
    char produto[100];
    int quantidade;
    float preco;
    int ID;
}
PRODUTO;

typedef struct {
    char nome[50];
    char usuario[20];
    char senha[50];
    char email[50];
    char cpf[11];
    int ID;
}
Usuario;

typedef struct {
    CLIENTE cliente[MAX_USERS];
    PRODUTO produto[MAX_PRO];
    Usuario usuario[MAX_USERS];
    int contador[3];
    int Logado;
}
WOODSTOCK;


void salvarDados(WOODSTOCK WS);
int verificaCPF(char *cpfEntrada);
void cadastrarUsuario(WOODSTOCK WS);
void cadastro_cliente(WOODSTOCK WS);
void cadastro_Produto(WOODSTOCK WS);
void listarProduto(WOODSTOCK WS);
void mainMenu(WOODSTOCK WS);
void realizarLogin(WOODSTOCK WS);
void exibirUsuarios(WOODSTOCK WS);
void menu(WOODSTOCK WS);

void salvarDados(WOODSTOCK WS) {
    FILE *file = fopen("WOODSTOCK.bin", "wb");

    fwrite(&WS, sizeof(WOODSTOCK), 1, file);

    fclose(file);
}

int verificaCPF(char *cpfEntrada) {
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

void cadastrarUsuario(WOODSTOCK WS) {
    char nome[50];
    char email[50];
    char usuario[30];
    char senha[30];
    char cpf[12];
    int Cconfirmacao;

    printf("Digite seu CPF: ");
    scanf("%s", cpf);
    if (!verificaCPF(cpf)) {
        system("cls");
        printf("CPF invalido.\n");

        cadastrarUsuario(WS);
    }
    fflush(stdin);
    printf("Digite seu nome: ");
    gets(nome);

    printf("Digite seu Email: ");
    scanf("%s", email);

    printf("Digite seu usuario: ");
    scanf("%s", usuario);

    printf("Digite sua senha: ");
    scanf("%s", senha);

    printf("Deseja confirma o cadastro\n 1 - Sim \n 2 - Não; \n");
    scanf("%d", &Cconfirmacao);

    if (Cconfirmacao == 1) {
        strcpy(WS.usuario[WS.contador[0]].nome, nome);
        strcpy(WS.usuario[WS.contador[0]].cpf, cpf);
        strcpy(WS.usuario[WS.contador[0]].email, email);
        strcpy(WS.usuario[WS.contador[0]].senha, senha);
        strcpy(WS.usuario[WS.contador[0]].usuario, usuario);

        system("cls");
        printf("Cadatro do cliente confirmado. \nId = %d\n", WS.contador[0]);
        WS.contador[0]++;

        menu(WS);
    } else {
        system("cls");
        menu(WS);
    }
}

void cadastro_cliente(WOODSTOCK WS) {
    printf("Digite o nome do cliente: ");
    gets(WS.cliente[WS.contador[1]].nome);

    fflush(stdin);
    printf("Digite o CPF do cliente: ");
    scanf("%d", &WS.cliente[WS.contador[1]].cpf);

    printf("Digite o Telefone do cliente: ");
    scanf("%d", &WS.cliente[WS.contador[1]].telefone);

    printf("Digite o CEP do cliente: ");
    scanf("%d", &WS.cliente[WS.contador[1]].cep);

    WS.contador[1]++;

    printf("Cliente cadastrado.\n");
}

void cadastro_Produto(WOODSTOCK WS) {
    fflush(stdin);
    printf("Digite o nome do produto: ");
    gets(WS.produto[WS.contador[2]].produto);
    
    fflush(stdin);
    printf("Digite o preco do produto: ");
    scanf("%f", &WS.produto[WS.contador[2]].preco);

    fflush(stdin);
    printf("Digite a quantidade de produtos: ");
    scanf("%d", &WS.produto[WS.contador[2]].quantidade);
    
    WS.produto[WS.contador[2]].ID = WS.contador[2];

    WS.contador[2]++;
}

void listarProduto(WOODSTOCK WS){
    printf(COLOR_YELLOW "=====================================\n" COLOR_RESET);
    for (int i = 0; i < WS.contador[2]; i++) {
        printf("Produtos cadastrados:\n");
        printf("Nome do Produto: %s |", WS.produto[i].produto);
        printf("Quantidade: %d |", WS.produto[i].quantidade);
        printf("Preco: %.2f |\n", WS.produto[i].preco);
    }
    printf(COLOR_YELLOW "=====================================\n" COLOR_RESET);
}

void mainMenu(WOODSTOCK WS) {
    salvarDados(WS);

    int escolha;
    printf(COLOR_BLUE "======================================\n");
    printf("|      ====== WOOD STOCK ======      |\n");
    printf("| [1] - Realizar venda.              |\n");
    printf("| [2] - Cadastrar produto.           |\n");
    printf("| [3] - Ver itens em estoque.        |\n");
    printf("| [4] - Cadastrar cliente.           |\n");
    printf("| [5] - Ver clientes cadastrados.    |\n");
    printf("|" COLOR_RED " [6] - Sair. " COLOR_BLUE "                       |\n");
    printf("======================================\n" COLOR_RESET);
    scanf("%d", &escolha);

    switch (escolha) {
        case 1:
            system("cls");
            system("pause");
            system("cls");
            mainMenu(WS);
            break;
        case 2:

            system("cls");
            cadastro_Produto(WS);
            system("pause");
            system("cls");
            mainMenu(WS);
            break;
        case 3:
            system("cls");
            listarProduto(WS);
            system("pause");
            system("cls");
            mainMenu(WS);
            break;
        case 4:
            system("cls");
            cadastro_cliente(WS);
            system("pause");
            system("cls");
            mainMenu(WS);
            break;
        case 5:
            system("cls");

            system("pause");
            system("cls");
            mainMenu(WS);
            break;
        case 6:

            break;
    }
}

void realizarLogin(WOODSTOCK WS) {
    char nome[50];
    char senha[20];

    printf("Usuario: ");
    scanf("%s", nome);

    printf("Senha: ");
    scanf("%s", senha);

    for (int i = 0; i < WS.contador[0]; i++) {
        if (strcmp(WS.usuario[i].usuario, nome) == 0 && strcmp(WS.usuario[i].senha, senha) == 0) {
            printf("Login realizado.\n");
            WS.Logado = 1;
            system("pause");
            system("cls");
            mainMenu(WS);
        }
    }
    printf("Senha ou usuario errada.\n");
    system("pause");
    menu(WS);
}

void exibirUsuarios(WOODSTOCK WS) {
    for (int i = 1; i < WS.contador[0]; i++) {
        printf("Nome completo: " "%s\n", WS.usuario[i].nome);
        printf("CPF: " "%s\n", WS.usuario[i].cpf);
        printf("E-mail: " "%s\n", WS.usuario[i].email);
        printf("Nome de Usuário: " "%s\n", WS.usuario[i].usuario);
        printf(COLOR_YELLOW "=====================================\n" COLOR_RESET);
    }
}

void menu(WOODSTOCK WS) {
    int opcao;

    do {
        salvarDados(WS);

        printf(COLOR_BLUE "======================================\n");
        printf("|      ====== WOOD STOCK ======      |\n");
        printf("|                                    |\n");
        printf("| [1] Cadastrar usuario              |\n");
        printf("| [2] Realizar login                 |\n");
        printf("| [3] Exibir usuarios cadastrados    |\n");
        printf("|" COLOR_RED " [4] Sair " COLOR_BLUE "                          |\n");
        printf("|                                    |\n");
        printf("| Escolha uma opcao:                 |\n");
        printf("======================================\n" COLOR_RESET);
        scanf("%d", &opcao);
        system("cls");

        switch (opcao) {
            case 1:
                cadastrarUsuario(WS);
                break;
            case 2:
                realizarLogin(WS);
                break;
            case 3:
                exibirUsuarios(WS);
                system("pause");
                system("cls");
                break;
            case 4:
                printf("Saindo do programa...\n");
                abort();
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }

    } while (true);
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    WOODSTOCK WS;
    WS.Logado = 0;
    WS.contador[0] = 1;
    WS.contador[1] = 1;
    WS.contador[2] = 0;

    FILE *file = fopen("WOODSTOCK.bin", "rb");

    if (file == NULL) {
        printf("Arquivo não encontrado.\n");
    } else {
        fread(&WS, sizeof(WOODSTOCK), 1, file);

        fclose(file);
    }
    menu(WS);
}