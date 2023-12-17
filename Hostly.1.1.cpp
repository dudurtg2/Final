#include <conio.h>
#include <ctype.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define MAX_CLIENTES 50
#define MAX_QUARTOS 30

#define RESET "\x1b[0m"
#define VERMELHO "\x1b[31m"
#define AMARELO "\x1b[33m"
#define VERDE "\x1b[32m"
#define CIANO "\x1b[36m"
#define AZUL "\x1b[34m"
#define PRETO "\x1b[30m"

int tentativasLogin = 3;

typedef struct {
    char senha[3][12] = { "p9Y8B7v6Hj", "3fH8zD0L9K", "S3nh4_F0rt3" };
    int adm;
} Adminstrador;
typedef struct {
    char nome[35];
    char endereco[50];
    char telefone[15];
    char cpf[11];
    int quartoC;
    int existeCliente;
    int temQuarto;
    int tempoNoQuarto;
    int reservadoC;
    int IdreservaC;
    char Chave[20];
} Cliente;
typedef struct {
    float preco;
    int numero;
    int capacidade;
    int idCliente[4];
    int quartoVago[4];
    int existeQuarto;
    int temCliente;
    int reservado;
    int Idreserva;
} Quarto;
typedef struct {
    Cliente clientes[MAX_CLIENTES];
    Quarto quartos[MAX_QUARTOS];
    Adminstrador adm;
    int HotelIdCliente;
    int Hotelquartos;
    int idAux;
} Hotel;

void salvarDados(Hotel hotel);

void cadastrarCliente(Hotel hotel);
void cadastrarQuarto(Hotel hotel);
void editarClientes(Hotel hotel);
void editarQuartos(Hotel hotel);
void excluirClientes(Hotel hotel);
void excluirQuartos(Hotel hotel);

void checkInQuarto(Hotel hotel);
void checkOutQuarto(Hotel hotel);
void reservaUmQuarto(Hotel Hotel);

void historicoDeReservas(Hotel hotel); 
void historicoDiaria(Hotel hotel);     
void historicoDeClientes(Hotel hotel); 
void historicoDeQuartos(Hotel hotel);  
void historicoDePagamento(Hotel hotel);

void exibirQuartos(Hotel hotel);
void detalharClientes(Hotel hotel);
void exibirClientes(Hotel hotel);

void menu(Hotel hotel);
void historicoMenu(Hotel hotel);
void Clientes(Hotel hotel);
void Quartos(Hotel hotel);
void Resevas(Hotel hotel);
void Login(Hotel hotel);

int verificaCPF(char *cpfEntrada);
int buscarIdDoQuarto(int numero, Hotel Hotel);
int buscarNumeroDeQuartos(int numero, Hotel hotel);
int adicionarNoQuarto(int numero, int cliente, Hotel hotel);
int procurarClienteNoQuarto(int numero, int cliente, Hotel hotel);

void salvarDados(Hotel hotel) {
    FILE *file = fopen("hotel.bin", "wb");

    fwrite(&hotel, sizeof(Hotel), 1, file);

    fclose(file);
}

void cadastrarCliente(Hotel hotel) {
    fflush(stdin);

    time_t tempo;
    struct tm
    *tempoReal;

    time(&tempo);
    tempoReal = localtime(&tempo);

    int diaDoMes = tempoReal->tm_mday;
    int mes = tempoReal->tm_mon + 1;
    int ano = tempoReal->tm_year + 1900;

    int comfirmacao;
    char *nome = (char*)malloc(sizeof(char));
    char *telefone = (char*)malloc(sizeof(char));;
    char *endereco = (char*)malloc(sizeof(char));;
    char *senha = (char*)malloc(sizeof(char));;
    char *cpf = (char*)malloc(sizeof(char));;

    if (hotel.clientes[hotel.idAux].existeCliente == 1) {
        if (hotel.idAux != hotel.HotelIdCliente) {
            hotel.idAux++;
            system("cls");
            cadastrarCliente(hotel);
        }
    }

    printf(CIANO "Digite o cpf: " RESET);
    scanf("%12s", cpf);

    if (!verificaCPF(cpf)) {
        system("cls");
        printf(AMARELO "CPF inválido.\n" RESET);
        cadastrarCliente(hotel);
    }

    fflush(stdin);
    printf(CIANO "Digite o nome do cliente: " RESET);
    gets(nome);

    printf(CIANO "Digite o endereço do cliente: " RESET);
    gets(endereco);

    printf(CIANO "Digite o telefone do cliente: " RESET);
    scanf("%19s", telefone);

    printf(CIANO "Digite a palavra chave: " RESET);
    scanf("%s", senha);

    fflush(stdin);
    printf(CIANO "Deseja confirma o cadastro\n"AMARELO" 1 - Sim \n 2 - Não \n" RESET);
    scanf("%d", &comfirmacao);

    if (comfirmacao == 1) {
        system("cls");
        printf(VERDE "Cadatro do cliente confirmado. \n" RESET, hotel.idAux);

        hotel.clientes[hotel.idAux].existeCliente = 1;
        hotel.clientes[hotel.idAux].temQuarto = 0;

        strcpy(hotel.clientes[hotel.idAux].nome, nome);
        strcpy(hotel.clientes[hotel.idAux].endereco, endereco);
        strcpy(hotel.clientes[hotel.idAux].cpf, cpf);
        strcpy(hotel.clientes[hotel.idAux].telefone, telefone);
        strcpy(hotel.clientes[hotel.idAux].Chave, senha);
        free(nome);
        free(endereco);
        free(cpf);
        free(telefone);
        free(senha);

        FILE *historio_cliente;
        historio_cliente = fopen("historio_cliente.txt", "a");
        fprintf(historio_cliente, "ID do cliente %d / CPF %s / Nome %s / Data do cadastro %d/%d/%d\n", hotel.idAux, hotel.clientes[hotel.idAux].cpf, hotel.clientes[hotel.idAux].nome, diaDoMes, mes, ano);
        fclose(historio_cliente);
        fflush(stdin);
        
        if (hotel.idAux == hotel.HotelIdCliente) {
            hotel.HotelIdCliente++;
            printf(AMARELO" ID do cliente %d \n CPF %s \n Nome %s \n Data do cadastro %d/%d/%d\n"RESET, hotel.idAux, hotel.clientes[hotel.idAux].cpf, hotel.clientes[hotel.idAux].nome, diaDoMes, mes, ano);
            system("pause");
            sleep(1);
            salvarDados(hotel);
            sleep(1);
            Clientes(hotel);

        } else {
            printf(AMARELO" ID do cliente %d \n CPF %s \n Nome %s \n Data do cadastro %d/%d/%d\n"RESET, hotel.idAux, hotel.clientes[hotel.idAux].cpf, hotel.clientes[hotel.idAux].nome, diaDoMes, mes, ano);
            system("pause");
            sleep(1);
            salvarDados(hotel);
            sleep(1);
            Clientes(hotel);
        }
    } else {
        system("cls");
        Clientes(hotel);
    }
}
void cadastrarQuarto(Hotel hotel) {
    fflush(stdin);

    time_t tempo;
    struct tm
    *tempoReal;

    time(&tempo);
    tempoReal = localtime(&tempo);

    int diaDoMes = tempoReal->tm_mday;
    int mes = tempoReal->tm_mon + 1;
    int ano = tempoReal->tm_year + 1900;

    int comfirmacao;
    int numero;
    float preco;
    int capacidade;

    if (hotel.quartos[hotel.idAux].existeQuarto == 1) {
        if (hotel.idAux != hotel.Hotelquartos) {
            hotel.idAux++;
            system("cls");
            cadastrarQuarto(hotel);
        }
    }

    printf(CIANO "Digite o número do quarto: " RESET);
    scanf("%d", &numero);

    if (buscarNumeroDeQuartos(numero, hotel) == 0) {
        printf(CIANO "Número de quarto cadastrado: " RESET);
        system("pause");
        Quartos(hotel);
    }

    printf(CIANO "Digite a capacidade do quarto: " RESET);
    scanf("%d", &capacidade);

    if (capacidade > 4) {
        capacidade = 4;
        printf(AMARELO "O maximo em um quarto é 4 pessoas.\n" RESET);
    } else if (capacidade == 0) {
        capacidade = 1;
        printf(AMARELO "O minimo em um quarto é 1 pessoas.\n" RESET);
    }

    printf(CIANO "Digite o preço do quarto: " RESET);
    scanf("%f", &preco);

    printf(CIANO "Deseja confirma o cadastro\n" AMARELO" 1 - Sim \n 2 - Não \n" RESET);
    scanf("%d", &comfirmacao);

    if (comfirmacao == 1) {
        system("cls");

        printf(VERDE "Cadatro do quarto confirmado. \nId = %d\n" RESET, hotel.idAux);

        hotel.quartos[hotel.idAux].numero = numero;
        hotel.quartos[hotel.idAux].preco = preco;
        hotel.quartos[hotel.idAux].capacidade = capacidade;
        hotel.quartos[hotel.idAux].existeQuarto = 1;
        hotel.quartos[hotel.idAux].temCliente = 0;

        for (int loop = 0; loop < 4; loop++) {
            hotel.quartos[hotel.idAux].quartoVago[loop] = 1;
            hotel.quartos[hotel.idAux].idCliente[loop] = 0;
        }

        FILE *historio_Quarto;
        historio_Quarto = fopen("historio_Quarto.txt", "a");
        fprintf(historio_Quarto,  "Numero do quarto %d / Capacidade %d / Preço %.2f / Data %d/%d/%d", numero, hotel.quartos[hotel.idAux].capacidade, hotel.quartos[hotel.idAux].preco, diaDoMes, mes, ano);
        fclose(historio_Quarto);
        fflush(stdin);

        if (hotel.idAux == hotel.Hotelquartos) {
            hotel.Hotelquartos++;
            sleep(1);
            salvarDados(hotel);
            sleep(1);
            Quartos(hotel);
        } else {
            sleep(1);
            salvarDados(hotel);
            sleep(1);
            Quartos(hotel);
        }
        sleep(1);
        salvarDados(hotel);
        sleep(1);
        Quartos(hotel);
    } else if (comfirmacao == 2) {
        Quartos(hotel);
    }
}
void excluirClientes(Hotel hotel) {
    int cliente;
    int comfirmacao;
    int i = 0;
    char ch;

    system("cls");

    if (hotel.HotelIdCliente != 0) {
        printf(CIANO "Informe o Id do cliente: " RESET);
        scanf("%d", &cliente);

        if (cliente > hotel.HotelIdCliente) {
            printf(VERMELHO "O cliente não existe.\n" RESET);
            system("pause");
            Clientes(hotel);
        }

        if (cliente == 0) {
            printf(VERMELHO "O ID 0 não pode ser excluido.\n" RESET);
            system("pause");
            Clientes(hotel);
        }

        if (hotel.clientes[cliente].temQuarto == 1) {
            printf(AMARELO "O ID %d não pode ser excluido, pois está registrado em um quarto.\n" RESET, cliente);
            system("pause");
            Clientes(hotel);
        }

        if (hotel.clientes[cliente].reservadoC == 1) {
            printf(AMARELO "O ID %d não pode ser excluido, pois tem uma reserva.\n" RESET, cliente);
            system("pause");
            Clientes(hotel);
        }

        if (hotel.clientes[cliente].existeCliente == 0) {
            printf(AMARELO "O ID %d não pode ser excluido. pois não existe mais.\n" RESET, cliente);
            system("pause");
            Clientes(hotel);
        }

        if (hotel.adm.adm == 0) {
            char senha[20];
            printf(CIANO "Informe a palavra chave: " RESET);
            while (1) {
                ch = getch();
                if (ch == '\r') {
                    senha[i] = '\0';
                    break;
                } else {
                    senha[i++] = ch;
                    printf("*");
                }
            }

            if (strcmp(hotel.clientes[cliente].Chave, senha) == 1) {
                printf(VERMELHO "Palavra chave incorreta.\n " RESET);
                system("pause");
                Clientes(hotel);
            }
        }

        printf(CIANO "Deseja excluir o cadastro de %s\n" AMARELO" 1 - Sim \n 2 - Não \n" RESET, hotel.clientes[cliente].nome);
        scanf("%d", &comfirmacao);

        if (comfirmacao == 1) {
            system("cls");
            printf(VERDE "Cadatro do cliente excluido. \nId = %d\n" RESET, cliente);
            *hotel.clientes[cliente].nome = '\0';
            *hotel.clientes[cliente].cpf = '\0';
            *hotel.clientes[cliente].endereco = '\0';
            *hotel.clientes[cliente].telefone = '\0';
            sleep(1);
            hotel.clientes[cliente].existeCliente = 0;
            hotel.clientes[cliente].quartoC = '\0';
            system("pause");
            sleep(2);
            salvarDados(hotel);
            Clientes(hotel);
        } else {
            Clientes(hotel);
        }
    } else {
        printf(VERMELHO "Não a clientes registrados\n." RESET);
        system("pause");
        Clientes(hotel);
    }
}
void excluirQuartos(Hotel hotel) {
    int quarto;
    int comfirmacao;
    system("cls");

    if (hotel.Hotelquartos != 0) {
        printf(CIANO "Informe o numero do quarto: " RESET);
        scanf("%d", &quarto);

        int quarto = buscarIdDoQuarto(quarto, hotel);

        if (quarto > hotel.Hotelquartos) {
            printf(AMARELO "O quarto não existe.\n" RESET);
            system("pause");
            Quartos(hotel);
        }
        if (hotel.quartos[quarto].temCliente == 1) {
            printf(AMARELO "O quarto de numero %d não pode ser excluido, pois a clientes registrados.\n" RESET, hotel.quartos[quarto].numero);
            system("pause");
            Quartos(hotel);
        }
        if (hotel.quartos[quarto].Idreserva == 1) {
            printf(AMARELO "O quarto de numero %d não pode ser excluido, pois o querto está reservado.\n" RESET, hotel.quartos[quarto].numero);
            system("pause");
            Quartos(hotel);
        }
        if (hotel.quartos[quarto].existeQuarto == 0) {
            printf(VERMELHO "O quarto não pode ser excluido. pois não existe mais.\n" RESET);
            system("pause");
            Quartos(hotel);
        }

        printf(CIANO "Deseja excluir o quarto de numero: %d" AMARELO" 1 - Sim \n 2 - Não \n" RESET, hotel.quartos[quarto].numero);
        scanf("%d", &comfirmacao);

        if (comfirmacao == 1) {
            system("cls");

            printf(VERDE "Cadatro do quarto excluido. \nId = %d\n" RESET, quarto);
            hotel.quartos[quarto].numero = '\0';
            hotel.quartos[quarto].preco = '\0';
            hotel.quartos[quarto].capacidade = '\0';
            sleep(1);
            hotel.quartos[quarto].existeQuarto = 0;
            sleep(2);
            salvarDados(hotel);
            system("pause");
            Quartos(hotel);
        } else {
            Quartos(hotel);
        }
    } else {
        printf(VERMELHO "Não a quartos registrados.\n." RESET);
        system("pause");
        Quartos(hotel);
    }
}
void editarClientes(Hotel hotel) {
    int cliente;
    int i = 0;
    char ch;
    system("cls");

    if (hotel.HotelIdCliente != 0) {
        printf(CIANO "Informe o Id do cliente para editar seu cadastro: " RESET);
        scanf("%d", &cliente);

        if (cliente > hotel.HotelIdCliente) {
            printf(VERMELHO "O cliente não existe.\n" RESET);
            system("pause");
            Clientes(hotel);
        }
        if (cliente == 0) {
            printf(VERMELHO "O ID 0 não pode ser editado.\n" RESET);
            system("pause");
            Clientes(hotel);
        }
        if (hotel.clientes[cliente].temQuarto == 1) {
            printf(AMARELO "O ID %d não pode ser editado, pois está registrado em um quarto.\n" RESET, cliente);
            system("pause");
            Clientes(hotel);
        }
        if (hotel.clientes[cliente].reservadoC == 1) {
            printf(AMARELO "O ID %d não pode ser editado, pois tem uma reserva.\n" RESET, cliente);
            system("pause");
            Clientes(hotel);
        }
        if (hotel.clientes[cliente].existeCliente == 0) {
            printf(AMARELO "O ID %d não pode ser editado. pois não existe mais.\n" RESET, cliente);
            system("pause");
            Clientes(hotel);
        }

        if (hotel.adm.adm == 0) {
            char senha[30];
            printf(CIANO "Digite sua senha: " RESET);
            while (1) {
                ch = getch();
                if (ch == '\r') {
                    senha[i] = '\0';
                    break;
                } else {
                    senha[i++] = ch;
                    printf("*");
                }
            }
            if (strcmp(hotel.clientes[cliente].Chave, senha) == 1) {
                printf(VERMELHO "Palavra chave incorreta.\n" RESET);
                system("pause");
                Clientes(hotel);
            }
        }

        printf(CIANO "Digite o novo cpf: " RESET);
        scanf("%s", hotel.clientes[cliente].cpf);

        if (!verificaCPF(hotel.clientes[cliente].cpf)) {
            system("cls");
            printf(AMARELO "CPF inválido.\n" RESET);

            editarClientes(hotel);
        }

        fflush(stdin);

        printf(CIANO "Digite o novo nome do cliente: " RESET);
        gets(hotel.clientes[cliente].nome);

        printf(CIANO "Digite o novo endereço do cliente: " RESET);
        gets(hotel.clientes[cliente].endereco);

        printf(CIANO "Digite o novo telefone do cliente: " RESET);
        gets(hotel.clientes[cliente].telefone);

        printf(VERDE "Edição completa. o cliente do id %d, foi editado com sucesso.\n" RESET, cliente);
        system("pause");
        sleep(1);
        salvarDados(hotel);

        Clientes(hotel);
    } else {
        printf(VERMELHO "Não a clientes registrados.\n" RESET);
    }
    system("pause");
    Clientes(hotel);
}
void editarQuartos(Hotel hotel) {
    int numero;
    int aux;
    system("cls");

    if (hotel.Hotelquartos != 0) {
        printf("Informe o numero do quarto para editar: ");
        scanf("%d", &numero);
        numero = buscarIdDoQuarto(numero, hotel);

        if (numero > hotel.Hotelquartos) {
            printf(VERMELHO "O quarto não existe.\n" RESET);
            system("pause");
            Quartos(hotel);
        }
        if (hotel.quartos[numero].temCliente == 1) {
            printf(AMARELO "O quarto de numero %d não pode ser editado, pois a clientes registrados.\n" RESET, numero);
            system("pause");
            Quartos(hotel);
        }
        if (hotel.quartos[numero].Idreserva == 1) {
            printf(AMARELO "O quarto de numero %d não pode ser editado, pois o querto está reservado.\n" RESET, numero);
            system("pause");
            Quartos(hotel);
        }
        if (hotel.quartos[numero].existeQuarto == 0) {
            printf(AMARELO "O quarto não pode ser excluido. pois não existe mais.\n" RESET);
            system("pause");
            Quartos(hotel);
        }

        printf(CIANO "Digite o número do quarto: " RESET);
        scanf("%d", &aux);

        if (buscarNumeroDeQuartos(aux, hotel) == 0) {
            printf(AMARELO "Numero de quarto cadastrado.\n" RESET);
            system("pause");
            Quartos(hotel);
        }

        hotel.quartos[numero].numero = aux;

        printf(CIANO "Digite a capacidade do quarto: " RESET);
        scanf("%d", &hotel.quartos[numero].capacidade);

        if (hotel.quartos[numero].capacidade > 4) {
            hotel.quartos[numero].capacidade = 4;
            printf(AMARELO "O maximo em um quarto é 4 pessoas.\n" RESET);
        } else if (hotel.quartos[numero].capacidade == 0) {
            hotel.quartos[numero].capacidade = 1;
            printf(AMARELO "O minimo em um quarto é 1 pessoas.\n" RESET);
        }

        printf(CIANO "Digite o preço do quarto: " RESET);
        scanf("%f", &hotel.quartos[numero].preco);

        printf(VERDE "Edição completa. o Quarto do id %d, foi editado com sucesso.\n" RESET, numero);
        system("pause");
        sleep(1);
        salvarDados(hotel);
        Quartos(hotel);
    } else {
        printf(VERMELHO "Não a quartos registrados.\n" RESET);
        system("pause");
        Quartos(hotel);
    }
    system("pause");
    Quartos(hotel);
}

void checkInQuarto(Hotel hotel) {
    int quarto;
    int cliente;

    time_t tempo;
    struct tm
    *tempoReal;

    time(&tempo);
    tempoReal = localtime(&tempo);

    int diaDoMes = tempoReal->tm_mday;
    int mes = tempoReal->tm_mon + 1;
    int ano = tempoReal->tm_year + 1900;
    int diaDoAno = tempoReal->tm_yday + 1;

    system("cls");

    printf(CIANO "Digite o numero do quarto: " RESET);
    scanf("%d", &quarto);

    if (buscarIdDoQuarto(quarto, hotel) != 0) {
        quarto = buscarIdDoQuarto(quarto, hotel);
        if (quarto > hotel.Hotelquartos) {
            printf(VERMELHO "O quarto não existe.\n" RESET);
            system("pause");
            Resevas(hotel);
        }
    } else if (hotel.quartos[0].numero == quarto) {
        quarto = 0;
    } else if (hotel.quartos[quarto].existeQuarto == 0) {
        printf(VERMELHO "Quarto não existe.\n" RESET);
        system("pause");
        Resevas(hotel);
    } else {
        printf(VERMELHO "Quarto não existe.\n" RESET);
        system("pause");
        Resevas(hotel);
    }

    printf(CIANO"Digite o id do cliente: "RESET);
    scanf("%d", &cliente);

    if (cliente > hotel.HotelIdCliente) {
        printf(VERMELHO "O cliente não existe.\n" RESET);
        system("pause");
        Resevas(hotel);
    }
    if (cliente == 0) {
        printf(VERMELHO "Não pode acicionar o ID 0.\n" RESET);
        system("pause");
        Resevas(hotel);
    }
    if (hotel.clientes[cliente].temQuarto == 1) {
        printf(AMARELO "O cliente já está em um quarto.\n" RESET);
        system("pause");
        Resevas(hotel);
    }
    if (hotel.clientes[cliente].existeCliente == 0) {
        printf(AMARELO "O ID %d não pode alugar um quarto. pois não existe mais.\n" RESET, cliente);
        system("pause");
        Resevas(hotel);
    }

    if (hotel.quartos[quarto].reservado == 1) {
        if (hotel.quartos[quarto].Idreserva == cliente) {
            if (adicionarNoQuarto(quarto, cliente, hotel) != 0) {
                hotel.quartos[quarto].idCliente[adicionarNoQuarto(quarto, cliente, hotel) - 1] = cliente;
                hotel.quartos[quarto].quartoVago[adicionarNoQuarto(quarto, cliente, hotel) - 1] = 0;
                hotel.quartos[quarto].temCliente = 1;
                hotel.clientes[cliente].quartoC = quarto;
                hotel.clientes[cliente].temQuarto = 1;
                hotel.clientes[cliente].tempoNoQuarto = diaDoAno;

                FILE *historico_checkIn;
                historico_checkIn = fopen("historico_checkIn.txt", "a");
                fprintf(historico_checkIn,  "Numero do quarto %d / Nome do cliente: %s / Preço do quarto %.2f / Data %d/%d/%d", hotel.quartos[quarto].numero, hotel.clientes[cliente].nome, hotel.quartos[quarto].preco, diaDoMes, mes, ano);
                fclose(historico_checkIn);
                fflush(stdin);

                printf(VERDE "Cliente adcionado\n" RESET);
                system("pause");
                sleep(1);
                salvarDados(hotel);
                sleep(1);
                Resevas(hotel);
            } else {
                printf(AMARELO "Limite alcançado\n" RESET);
                system("pause");
                Resevas(hotel);
            }
        } else {
            printf(VERMELHO "Não é o cliente da reserva, quarto reservado para %s\n" RESET, hotel.clientes[hotel.quartos[quarto].Idreserva].nome);
            system("pause");
            Resevas(hotel);
        }
    }
    if (adicionarNoQuarto(quarto, cliente, hotel) != 0) {
        hotel.quartos[quarto].idCliente[adicionarNoQuarto(quarto, cliente, hotel) - 1] = cliente;
        hotel.quartos[quarto].quartoVago[adicionarNoQuarto(quarto, cliente, hotel) - 1] = 0;
        hotel.quartos[quarto].temCliente = 1;
        hotel.clientes[cliente].quartoC = quarto;
        hotel.clientes[cliente].temQuarto = 1;
        hotel.clientes[cliente].tempoNoQuarto = diaDoAno;

        FILE *historico_checkIn;
                historico_checkIn = fopen("historico_checkIn.txt", "a");
                fprintf(historico_checkIn,  "Numero do quarto %d / Nome do cliente: %s / Preço do quarto %.2f / Data %d/%d/%d", hotel.quartos[quarto].numero, hotel.clientes[cliente].nome, hotel.quartos[quarto].preco, diaDoMes, mes, ano);
                fclose(historico_checkIn);
                fflush(stdin);

        printf(VERDE "Cliente adcionado\n" RESET);
        system("pause");
        sleep(1);
        salvarDados(hotel);
        sleep(1);
        Resevas(hotel);
    } else {
        printf(AMARELO "Limite alcançado\n" RESET);
        system("pause");
        Resevas(hotel);
    }
}
void checkOutQuarto(Hotel hotel) {
    int cliente;
    int pago;

    time_t tempo;
    struct tm
    *tempoReal;

    time(&tempo);
    tempoReal = localtime(&tempo);

    int diaDoMes = tempoReal->tm_mday;
    int mes = tempoReal->tm_mon + 1;
    int ano = tempoReal->tm_year + 1900;
    int diaDoAno = tempoReal->tm_yday + 1;

    system("cls");
    printf("Digite o ID do cliete: ");
    scanf("%d", &cliente);

    if (cliente > hotel.HotelIdCliente) {
        printf(VERMELHO "O cliente não existe.\n" RESET);
        system("pause");
        Resevas(hotel);
    }
    if (cliente == 0) {
        printf(VERMELHO "O ID 0 não pode ser modificado.\n" RESET);
        system("pause");
        Clientes(hotel);
    }
    if (hotel.clientes[cliente].existeCliente == 0) {
        printf(AMARELO "O ID %d não tem quartos. pois não existe mais.\n" RESET, cliente);
        system("pause");
        Clientes(hotel);
    }

    if (cliente <= hotel.HotelIdCliente) {
        if (hotel.clientes[cliente].temQuarto == 1) {
            int possicao = procurarClienteNoQuarto(hotel.clientes[cliente].quartoC, cliente, hotel);

            if (possicao == 5) {
                printf(AMARELO "cliente não estar em um quarto.\n" RESET);
                system("pause");
                Resevas(hotel);
            }

            int preco = ((diaDoAno - hotel.clientes[cliente].tempoNoQuarto) * hotel.quartos[hotel.clientes[cliente].quartoC].preco) + hotel.quartos[hotel.clientes[cliente].quartoC].preco;
            int dias = (diaDoAno - hotel.clientes[cliente].tempoNoQuarto) + 1;

            printf(CIANO "O cliente %s, precisar pagar %d de um periodo de %d dias no quarto.\n" RESET, hotel.clientes[cliente].nome, preco, dias);
            printf(VERDE "1 - Pagou " RESET "/" VERMELHO "2 não pagou.\n" RESET);
            scanf("%d", &pago);

            if (pago == 1) {

                FILE *historico_checkout;
                historico_checkout = fopen("historico_checkout.txt", "a");
                fprintf(historico_checkout, "Numero do quarto: %d / Preço pago: %.2f / Data %d/%d/%d / Dias hospedados: %d / Nome: %s / CPf: %s", hotel.quartos[hotel.clientes[cliente].quartoC].numero, hotel.quartos[hotel.clientes[cliente].quartoC].preco, diaDoMes, mes, ano, dias, hotel.clientes[cliente].nome, hotel.clientes[cliente].cpf);
                fclose(historico_checkout);
                fflush(stdin);
  
                hotel.clientes[cliente].temQuarto = 0;
                hotel.quartos[hotel.clientes[cliente].quartoC].quartoVago[possicao] = 0;
                hotel.quartos[hotel.clientes[cliente].quartoC].idCliente[possicao] = 0;
                hotel.clientes[cliente].reservadoC = 0;
                hotel.quartos[hotel.clientes[cliente].quartoC].reservado = 0;

                printf(VERDE "O Cliente pagou R$%d. dos %s hospedado.\n", preco, (dias > 2) ? dias + " dias" : dias + " dia" RESET);
                sleep(1);
                salvarDados(hotel);
                sleep(1);

                system("pause");
                Resevas(hotel);
            }
        } else {
            printf(VERMELHO "Cliente não está em um quarto.\n" RESET);
            system("pause");
            Resevas(hotel);
        }
    } else {
        printf(VERMELHO "Cliente não existe.\n" RESET);
        system("pause");
        Resevas(hotel);
    }
}
void reservaUmQuarto(Hotel hotel) {
    time_t tempo;
    struct tm
    *tempoReal;

    time(&tempo);
    tempoReal = localtime(&tempo);

    int diaDoMes = tempoReal->tm_mday;
    int mes = tempoReal->tm_mon + 1;
    int ano = tempoReal->tm_year + 1900;
    int cliente;
    int quarto;

    printf(CIANO "Digite o Id do cliente para reserva um quarto: " RESET);
    scanf("%d", &cliente);

    if (cliente > hotel.HotelIdCliente) {
        printf(VERMELHO "O cliente não existe.\n" RESET);
        system("pause");
        Resevas(hotel);
    }
    if (cliente == 0) {
        printf(VERMELHO "O ID 0 não pode ter uma reserva.\n" RESET);
        system("pause");
        Resevas(hotel);
    }
    if (hotel.clientes[cliente].temQuarto == 1) {
        printf(AMARELO "Cliente já tem o quarto.\n" RESET);
        system("pause");
        Resevas(hotel);
    }
    if (hotel.clientes[cliente].reservadoC == 1) {
        printf(AMARELO "Cliente já tem uma reserva.\n" RESET);
        system("pause");
        Resevas(hotel);
    }
    if (hotel.clientes[cliente].existeCliente == 0) {
        printf(AMARELO "O ID %d não pode fazer uma reseva. pois não existe mais.\n" RESET, cliente);
        system("pause");
        Resevas(hotel);
    }

    printf(CIANO "Digite o numero do quarto: " RESET);
    scanf("%d", &quarto);

    if (buscarIdDoQuarto(quarto, hotel) != 0) {
       int quarto1 = buscarIdDoQuarto(quarto, hotel);
        quarto = quarto1;
        if (quarto > hotel.Hotelquartos) {
            printf(VERMELHO "O quarto não existe.\n" RESET);
            printf(AMARELO "1\n");
            system("pause");
            Resevas(hotel);
        }
        system("pause");
    } else if (hotel.quartos[0].numero == quarto) {
        quarto = 0;
    } else if (hotel.quartos[quarto].existeQuarto == 0) {
        printf(VERMELHO "Quarto não existe.\n" RESET);
        system("pause");
        Resevas(hotel);
    } else {
        printf(VERMELHO "Quarto não existe.\n" RESET);
        system("pause");
        Resevas(hotel);
    }
    if (hotel.quartos[quarto].reservado == 1) {
        printf(AMARELO "Quarto está reservado para %s.\n" RESET, hotel.clientes[hotel.quartos[quarto].Idreserva].nome);
        system("pause");
        Resevas(hotel);
    }

    FILE *historico_reserva;
    historico_reserva = fopen("historico_reserva.txt", "a");
    fprintf(historico_reserva, "Numero do quarto %d / Nome do cliente: %s / Preço do quarto %.2f / Data da reserva %d/%d/%d", hotel.quartos[quarto].numero, hotel.clientes[cliente].nome, hotel.quartos[quarto].preco, diaDoMes, mes, ano);
    fclose(historico_reserva);     
    fflush(stdin);
    sleep(1);

    hotel.clientes[cliente].reservadoC = 1;
    hotel.clientes[cliente].IdreservaC = quarto;
    hotel.quartos[quarto].Idreserva = cliente;
    hotel.quartos[quarto].reservado = 1;
   
    printf(AMARELO "Quarto reservado para %s.\n" RESET, hotel.clientes[cliente].nome);
    system("pause");
    sleep(1);
    salvarDados(hotel);
    sleep(1);
    Resevas(hotel);
}

void historicoDeQuartos(Hotel hotel) {
    FILE *historio_Quarto;
    historio_Quarto = fopen("historio_Quarto.txt", "r");
    if (historio_Quarto == NULL) {
        printf(VERMELHO"Não a clientes registrados.\n"RESET);
        system("pause");
        return;
    }
    system("cls");
    char linha[100];
    while (fgets(linha, sizeof(linha), historio_Quarto) != NULL) {
        printf(CIANO"%s\n"RESET, linha);
    }
    fclose(historio_Quarto);
    system("pause");
    historicoMenu(hotel);
}
void historicoDeClientes(Hotel hotel) {
    FILE *historio_cliente;
    historio_cliente = fopen("historio_cliente.txt", "r");
    if (historio_cliente == NULL) {
        printf(VERMELHO"Não a clientes registrados.\n"RESET);
        system("pause");
        return;
    }
    system("cls");
    char linha[100];
    while (fgets(linha, sizeof(linha), historio_cliente) != NULL) {
        printf(CIANO"%s"RESET, linha);
    }
    fclose(historio_cliente);
    system("pause");
    historicoMenu(hotel);
}
void historicoDiaria(Hotel hotel) {
    FILE *historico_checkIn;
    historico_checkIn = fopen("historico_checkIn.txt", "r");
    if (historico_checkIn == NULL) {
        printf(VERMELHO"Não a clientes registrados.\n"RESET);
        system("pause");
        return;
    }
    system("cls");
    char linha[100];
    while (fgets(linha, sizeof(linha), historico_checkIn) != NULL) {
        printf(CIANO"%s"RESET, linha);
    }
    fclose(historico_checkIn);
    system("pause");
    historicoMenu(hotel);
}
void historicoDeReservas(Hotel hotel) {
    FILE *historico_reserva;
    historico_reserva = fopen("historico_reserva.txt", "r");
    if (historico_reserva == NULL) {
        printf(VERMELHO"Não a clientes registrados.\n"RESET);
        system("pause");
        return;
    }
    system("cls");
    char linha[100];
    while (fgets(linha, sizeof(linha), historico_reserva) != NULL) {
        printf(CIANO"%s"RESET, linha);
    }
    fclose(historico_reserva);
    system("pause");
    historicoMenu(hotel);
}
void historicoDePagamento(Hotel hotel) {
    FILE *historico_checkout;
    historico_checkout = fopen("historico_checkout.txt", "r");
    if (historico_checkout == NULL) {
        printf(VERMELHO"Não a clientes registrados.\n"RESET);
        system("pause");
        return;
    }
    system("cls");
    char linha[100];
    while (fgets(linha, sizeof(linha), historico_checkout) != NULL) {
        printf(CIANO"%s"RESET, linha);
    }
    fclose(historico_checkout);
    system("pause");
    historicoMenu(hotel);
}

void exibirClientes(Hotel hotel) {
    system("cls");
    if (hotel.HotelIdCliente != 0) {
        for (int i = 1; i < hotel.HotelIdCliente; i++) {
            if (hotel.clientes[i].existeCliente == 1) {
                printf(CIANO"ID: %d - Nome: %s\n"RESET, i, hotel.clientes[i].nome);
            }
        }
    } else {
        printf(VERMELHO"Não a clientes registrados.\n"RESET);
    }
    system("pause");
    Clientes(hotel);
}
void detalharClientes(Hotel hotel) {
    int cliente;
    char senha[20];
    int i = 0;
    char ch;
    system("cls");

    if (hotel.HotelIdCliente != 0) {
        printf(CIANO "Informe o Id do cliente: " RESET);
        scanf("%d", &cliente);

        if (cliente > hotel.HotelIdCliente) {
            printf(VERMELHO "O cliente não existe.\n" RESET);
            system("pause");
            Clientes(hotel);
        }
        if (hotel.clientes[cliente].existeCliente == 0) {
            printf(AMARELO "O ID %d não existe mais.\n" RESET, cliente);
            system("pause");
            Clientes(hotel);
        }
        if (hotel.adm.adm == 0) {
            fflush(stdin);
            printf(CIANO "Informe a palavra chave do cliente\n " RESET);/*  */
            while (1) {
                ch = getch();
                if (ch == '\r') {
                    senha[i] = '\0';
                    break;
                } else {
                    senha[i++] = ch;
                    printf("*");
                }
            }
        }
        if (strcmp(hotel.clientes[cliente].Chave, senha) == 0 || hotel.adm.adm == 1) {
            system("cls");

            printf(CIANO"Nome:"RESET" %s\n", hotel.clientes[cliente].nome);
            printf(CIANO"Cpf:"RESET" %s\n", hotel.clientes[cliente].cpf);
            printf(CIANO"Endereço:"RESET" %s\n", hotel.clientes[cliente].endereco);
            printf(CIANO"Telefone:"RESET" %s\n\n", hotel.clientes[cliente].telefone);

            system("pause");
            sleep(1);
            salvarDados(hotel);
            Clientes(hotel);
        } else {
            printf(VERMELHO "Palavra chave incorreta.\n" RESET);
            system("pause");
            Clientes(hotel);
        }
    } else {
        printf(VERMELHO"Não a clientes registrados.\n"RESET);
    }
    system("pause");
    Clientes(hotel);
}
void exibirQuartos(Hotel hotel) {
    system("cls");
    printf("=========================================================\n");
    for (int i = 0; i < hotel.Hotelquartos; i++) {
        if (hotel.quartos[i].existeQuarto == 1) {
            printf(CIANO"ID: %d - Numero: %d - Capacidade: %d - Preço: %.2f\n"RESET, i, hotel.quartos[i].numero, hotel.quartos[i].capacidade, hotel.quartos[i].preco);
            printf(CIANO"Clientes: "RESET);
            if (hotel.quartos[i].reservado == 0) {
                for (int j = 0; j < hotel.quartos[i].capacidade; j++) {
                    if (hotel.adm.adm == 1) {
                        printf(" %s ", hotel.clientes[hotel.quartos[i].idCliente[j]].nome);
                    }
                }
            } else {
                printf(AMARELO"Quarto reservado para %s.\n"RESET, hotel.clientes[hotel.quartos[i].Idreserva].nome);
            }
            printf("\n=========================================================\n");
        }
    }
    system("pause");
    system("cls");
}

void Login(Hotel hotel) {
    char senha[20];
    int i = 0;
    char ch;

    system("cls");
    printf("Você tem %d tentativas\n", tentativasLogin);
    printf("Digite a senha de administrador: ");
    while (1) {
                ch = getch();
                if (ch == '\r') {
                    senha[i] = '\0';
                    break;
                } else {
                    senha[i++] = ch;
                    printf("*");
                }
            }
    if (strcmp(hotel.adm.senha[0], senha) == 0 || strcmp(hotel.adm.senha[1], senha) == 0 || strcmp(hotel.adm.senha[2], senha) == 0) {
        system("cls");
        hotel.adm.adm = 1;
        printf("Login de administrador realizado com sucesso.\n");
        system("pause");
        system("cls");
        menu(hotel);
    } else {
        system("cls");
        printf("Senha incorreta.\n");
        if (tentativasLogin == 0) {
            tentativasLogin = 3;
            printf("Você excedeu o limite de tentativas.\n");
            system("pause");
            menu(hotel);
        }
        tentativasLogin--;
        Login(hotel);
    }
}
void Clientes(Hotel hotel) {
    int opcao;
    hotel.idAux = 1;

    fflush(stdin);
    do {
        system("cls");
        printf(AZUL"\n  MENU DE CLIENTES\n");
        printf("\n    [1] Listar clientes\n");
        printf("    [2] Exibir detalhe do cliente\n");
        printf("    [3] Cadastra clientes\n");
        printf("    [4] Editar clientes\n");
        printf("    [5] Excluir clientes\n\n");
        printf(AZUL"  [6] Voltar ao menu\n"RESET);
        printf(CIANO"\nEscolha uma opção: "RESET);
        scanf("%d", &opcao);
        fflush(stdin);

        switch (opcao) {
            case 1:
                system("cls");
                exibirClientes(hotel);
                break;
            case 2:
                system("cls");
                detalharClientes(hotel);
                break;
            case 3:
                system("cls");
                cadastrarCliente(hotel);
                break;
            case 4:
                system("cls");
                editarClientes(hotel);
                break;
            case 5:
                system("cls");
                excluirClientes(hotel);
                break;
            case 6:
                system("cls");
                printf(AMARELO"Voltando ao menu...\n"RESET);
                menu(hotel);
                break;
            default:
                printf(VERMELHO"Opção inválida. Tente novamente.\n"RESET);
        }
    } while (true);
}
void Quartos(Hotel hotel) {
    int opcao;
    hotel.idAux = 0;

    fflush(stdin);
    do {
        
        printf(AZUL"\n  MENU DE QUARTOS\n\n");
        printf("    [1] Exibir quartos\n");
        if (hotel.adm.adm == 1) {
            printf("    [2] Cadastrar quarto\n");
            printf("    [3] Excluir quarto\n");
            printf("    [4] Editar quartos\n");
        }
        printf("\n  [%d] Voltar ao menu\n"RESET, (hotel.adm.adm == 0) ? 2 : 5);
        printf(CIANO"\nEscolha uma opção: "RESET);
        scanf("%d", &opcao);
        fflush(stdin);

        switch (opcao) {
            case 1:
                system("cls");
                exibirQuartos(hotel);
                break;
            case 2:
                if (hotel.adm.adm == 1) {
                    system("cls");
                    cadastrarQuarto(hotel);
                    break;
                } else {
                    system("cls");
                    printf(AMARELO"Voltando ao menu...\n"RESET);
                    menu(hotel);
                    break;
                }
            case 3:
                if (hotel.adm.adm == 1) {
                    system("cls");
                    excluirQuartos(hotel);
                    break;
                } else {
                    printf(VERMELHO"Opção inválida. Tente novamente.\n"RESET);
                    Quartos(hotel);
                    break;
                }
            case 4:
                if (hotel.adm.adm == 1) {
                    system("cls");
                    editarQuartos(hotel);
                    break;
                } else {
                    printf(VERMELHO"Opção inválida. Tente novamente.\n"RESET);
                    Quartos(hotel);
                    break;
                }
            case 5:
                if (hotel.adm.adm == 1) {
                    system("cls");
                    printf(AMARELO"Voltando ao menu...\n"RESET);
                    menu(hotel);
                    break;
                } else {
                    printf(VERMELHO"Opção inválida. Tente novamente.\n"RESET);
                    Quartos(hotel);
                    break;
                }
                break;
            default:
                printf(VERMELHO"Opção inválida. Tente novamente.\n"RESET);
        }
    } while (true);
}
void Resevas(Hotel hotel) {
    int opcao;
    hotel.idAux = 1;

    fflush(stdin);
    do {
        system("cls");
        printf(AZUL"\n  MENU DE SERVIÇOS\n\n");
        printf("    [1] Alugar quartos\n");
        printf("    [2] Pagar quartos\n");
        printf("    [3] Reservar quartos\n");
        printf("\n  [4] Voltar ao menu\n");
        printf(CIANO"\nEscolha uma opção: "RESET);
        scanf("%d", &opcao);
        fflush(stdin);

        switch (opcao) {
            case 1:
                system("cls");
                checkInQuarto(hotel);
                break;
            case 2:
                system("cls");
                checkOutQuarto(hotel);
                break;
            case 3:
                system("cls");
                reservaUmQuarto(hotel);
                break;
            case 4:
                system("cls");
                printf(AMARELO"Voltando ao menu...\n"RESET);
                menu(hotel);
                break;
            default:
                printf(VERMELHO"Opção inválida. Tente novamente.\n"RESET);
        }

    } while (true);
}
void historicoMenu(Hotel hotel) {
    int opcao;

    fflush(stdin);
    do {
        system("cls");
        printf(AZUL"\n  MENU\n\n");
        printf("    [1] Historico de cliente\n");
        printf("    [2] Historico de quarto\n");
        printf("    [3] Historico de diaria\n");
        printf("    [4] Historico de pagamentos\n");
        printf("    [5] Historico de reserva\n");
        printf("\n  [6] Voltar ao menu\n");
        printf(CIANO"\nEscolha uma opção: "RESET);
        scanf("%d", &opcao);

        fflush(stdin);
        switch (opcao) {
            case 1:

                    historicoDeClientes(hotel);
                    break;
               
            case 2:
                
                    historicoDeQuartos(hotel);
                    break;
               
            case 3:
                
                    historicoDiaria(hotel);
                    break;
               
            case 4:
               
                    historicoDePagamento(hotel);
                    break;
              
            case 5:
                
                    historicoDeReservas(hotel);
                    break;
                
            case 6:
                system("cls");
                printf(AMARELO"Voltando ao menu...\n"RESET);
                menu(hotel);
                break;
            default:
                printf(VERMELHO"Opção inválida. Tente novamente.\n"RESET);
        }
    } while (true);
}
void menu(Hotel hotel) {
    int opcao;

    fflush(stdin);
    do {
        printf(AZUL"\n  MENU\n\n");
        printf("    [1] Clientes\n");
        printf("    [2] Quartos\n");
        printf("    [3] %s\n", (hotel.adm.adm == 0) ? "Login" : "Deslogar");
        if (hotel.adm.adm == 1) {
            printf("    [4] Reservas\n");
            printf("    [5] historicos\n");
        }
        printf("\n  [%s] Sair\n\n", (hotel.adm.adm == 0) ? "4" : "6");
        printf(CIANO"Escolha uma opção: "RESET);
        scanf("%d", &opcao);

        fflush(stdin);
        switch (opcao) {
            case 1:
            sleep(1);
                Clientes(hotel);
                break;
            case 2:
            sleep(1);
                system("cls");
                Quartos(hotel);
                break;
            case 3:
                if (hotel.adm.adm == 0) {
                    sleep(1);
                    Login(hotel);
                    break;
                } else {
                    system("cls");
                    printf(AMARELO"Deslogando...\n"RESET);
                    hotel.adm.adm = 0;
                    system("pause");
                    break;
                }
            case 4:
                if (hotel.adm.adm == 1) {
                    sleep(1);
                    Resevas(hotel);
                    break;
                } else {
                    hotel.adm.adm = 0;
                    printf(VERMELHO"Saindo...\n"RESET);
                    abort();
                }
            case 5:
                if (hotel.adm.adm == 0) {
                    sleep(1);
                    Resevas(hotel);
                    break;
                } else {
                    system("cls");
                    historicoMenu(hotel);
                    break;
                }
            case 6:
                if (hotel.adm.adm == 0) {
                    sleep(1);
                    Resevas(hotel);
                    break;
                } else {
                    hotel.adm.adm = 0;
                    printf(VERMELHO"Saindo...\n"RESET);
                    abort();
                }
            default:
                printf(AMARELO"Opção inválida. Tente novamente.\n"RESET);
        }
    } while (true);
}

int verificaCPF(char *cpfEntrada) {
    int indice, peso, digitoVerificador1 = 0, digitoVerificador2 = 0;
    if (strcmp(cpfEntrada, "00000000000") == 0) {
        return 1;
    }
    if (strlen(cpfEntrada) != 11){
        return 0;
    }
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
int procurarClienteNoQuarto(int numero, int cliente, Hotel hotel) {
    for (int i = 0; i < hotel.quartos[numero].capacidade; i++) {
        if (hotel.quartos[numero].idCliente[i] == cliente) {
            return i;
        }
    }
    return 5;
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
    setlocale(LC_ALL, "Portuguese_Brazil");

    Hotel hotel;
    hotel.adm.adm = 0;
    hotel.HotelIdCliente = 1;

    strcpy(hotel.clientes[0].nome, "Vago");
    strcpy(hotel.clientes[0].endereco, "Vago");
    hotel.clientes[0].existeCliente = 1;

    hotel.Hotelquartos = 0;


    FILE *file = fopen("hotel.bin", "rb");
        if (file == NULL) {
            printf("Arquivo não encontrado.\n");
        } else {
            fread(&hotel, sizeof(Hotel), 1, file);
            fclose(file);
        }
    menu(hotel);
}