#include <ctype.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define MAX_CLIENTES 100
#define MAX_QUARTOS 30
#define MAX_HISTORICO 1000

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
    int quartoC;
    int existeCliente;
    int temQuarto;
    int tempoNoQuarto;
    int reservadoC;
    int IdreservaC;
    char Chave[20];
}
Cliente;

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
}
Quarto;

typedef struct {
    Cliente clientes[MAX_CLIENTES];
    Quarto quartos[MAX_QUARTOS];
    Adminstrador adm;
    int HotelIdCliente;
    int Hotelquartos;
    int Contador[5];
    int idAux;
    char historico[MAX_HISTORICO][100]; /* <- inpementar */
}
Hotel;

/* Salva e carregar dados */
void salvarDados(Hotel hotel);
/* cadastros */
void cadastrarCliente(Hotel hotel);
void cadastrarQuarto(Hotel hotel);
void editarClientes(Hotel hotel);
void editarQuartos(Hotel hotel);
/* excluir */
void excluirClientes(Hotel hotel);
void excluirQuartos(Hotel hotel);
/* Historico */
void historicoDeReservas(Hotel hotel);  /* <- Terminar */
void historicoDiaria(Hotel hotel);      /* <- Terminar */
void historicoDeClientes(Hotel hotel);  /* <- Terminar */
void historicoDeQuartos(Hotel hotel);   /* <- Terminar */
void historicoDePagamento(Hotel hotel); /* <- Terminar */
/* imformaçoes */
void exibirQuartos(Hotel hotel);
void detalharClientes(Hotel hotel);
void exibirClientes(Hotel hotel);
/* Check-in check-out */
void checkInQuarto(Hotel hotel);
void checkOutQuarto(Hotel hotel);
void reservaUmQuarto(Hotel Hotel);
/* Verificadores */
int verificaCPF(char *cpfEntrada);
int buscarIdDoQuarto(int numero, Hotel Hotel);
int buscarNumeroDeQuartos(int numero, Hotel hotel);
int adicionarNoQuarto(int numero, int cliente, Hotel hotel);
int procurarClienteNoQuarto(int numero, int cliente, Hotel hotel);
/* menus */
void menu(Hotel hotel);
void historicoMenu(Hotel hotel);
void Clientes(Hotel hotel);
void Quartos(Hotel hotel);
void Resevas(Hotel hotel);
void Login(Hotel hotel);

void salvarDados(Hotel hotel) {
    FILE *file = fopen("hotel.bin", "wb");

    fwrite(&hotel, sizeof(Hotel), 1, file);

    fclose(file);
}

/* --------------------------------------------------------------------- */

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
    char nome[50];
    char telefone[20];
    char endereco[100];
    char senha[20];
    char cpf[20];

    if (hotel.clientes[hotel.idAux].existeCliente == 1) {
        if (hotel.idAux != hotel.HotelIdCliente) {
            hotel.idAux++;
            system("cls");
            cadastrarCliente(hotel);
        }
    }

    printf("Digite o cpf: ");
    scanf("%12s", cpf);

    if (!verificaCPF(cpf)) {
        system("cls");
        printf("CPF inválido.\n");
        cadastrarCliente(hotel);
    }

    fflush(stdin);
    printf("Digite o nome do cliente: ");
    gets(nome);

    printf("Digite o endereço do cliente: ");
    gets(endereco);

    printf("Digite o telefone do cliente: ");
    scanf("%19s", telefone);

    printf("Digite a palavra chave: ");
    scanf("%s", senha);

    fflush(stdin);
    printf("Deseja confirma o cadastro\n 1 - Sim / 2 - Não \n");
    scanf("%d", &comfirmacao);

    if (comfirmacao == 1) {
        system("cls");
        printf("Cadatro do cliente confirmado. ", hotel.idAux);
        system("pause");

        hotel.clientes[hotel.idAux].existeCliente = 1;
        hotel.clientes[hotel.idAux].temQuarto = 0;

        strcpy(hotel.clientes[hotel.idAux].nome, nome);
        strcpy(hotel.clientes[hotel.idAux].endereco, endereco);
        strcpy(hotel.clientes[hotel.idAux].cpf, cpf);
        strcpy(hotel.clientes[hotel.idAux].telefone, telefone);
        strcpy(hotel.clientes[hotel.idAux].Chave, senha);

        char buffer[100];
        sprintf(buffer, "ID do cliente %d / CPF %s / Nome %s / Data do cadastro %d/%d/%d\n", hotel.idAux, hotel.clientes[hotel.idAux].cpf, hotel.clientes[hotel.idAux].nome, diaDoMes, mes, ano);
        strcpy(hotel.historico[hotel.Contador[1]], buffer);
        hotel.Contador[1]++;

        if (hotel.idAux == hotel.HotelIdCliente) {
            hotel.HotelIdCliente++;
            printf("ID do cliente %d / CPF %s / Nome %s / Data do cadastro %d/%d/%d\n", hotel.idAux, hotel.clientes[hotel.idAux].cpf, hotel.clientes[hotel.idAux].nome, diaDoMes, mes, ano);
            system("pause");
            sleep(3);
            salvarDados(hotel);
            Clientes(hotel);

        } else {
            printf("ID do cliente %d / CPF %s / Nome %s / Data do cadastro %d/%d/%d\n", hotel.idAux, hotel.clientes[hotel.idAux].cpf, hotel.clientes[hotel.idAux].nome, diaDoMes, mes, ano);
            system("pause");
            sleep(3);
            salvarDados(hotel);
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

    printf("Digite o número do quarto: ");
    scanf("%d", &numero);

    if (buscarNumeroDeQuartos(numero, hotel) == 0) {
        printf("Número de quarto cadastrado: ");
        system("pause");
        Quartos(hotel);
    }

    printf("Digite a capacidade do quarto: ");
    scanf("%d", &capacidade);

    if (capacidade > 4) {
        capacidade = 4;
        printf("O maximo em um quarto é 4 pessoas.\n");
    } else if (capacidade == 0) {
        capacidade = 1;
        printf("O minimo em um quarto é 1 pessoas.\n");
    }

    printf("Digite o preço do quarto: ");
    scanf("%f", &preco);

    printf("Deseja confirma o cadastro\n 1 - Sim \n 2 - Não; \n");
    scanf("%d", &comfirmacao);

    if (comfirmacao == 1) {
        system("cls");

        printf("Cadatro do quarto confirmado. \nId = %d\n", hotel.idAux);

        hotel.quartos[hotel.idAux].numero = numero;
        hotel.quartos[hotel.idAux].preco = preco;
        hotel.quartos[hotel.idAux].capacidade = capacidade;
        hotel.quartos[hotel.idAux].existeQuarto = 1;
        hotel.quartos[hotel.idAux].temCliente = 0;

        for (int loop = 0; loop < 4; loop++) {
            hotel.quartos[hotel.idAux].quartoVago[loop] = 1;
            hotel.quartos[hotel.idAux].idCliente[loop] = 0;
        }

        char buffer[100];
        sprintf(buffer, "Numero do quarto %d / Capacidade %d / Preço %.2f / Data %d/%d/%d", numero, hotel.quartos[hotel.idAux].capacidade, hotel.quartos[hotel.idAux].preco, diaDoMes, mes, ano);
        strcpy(hotel.historico[hotel.Contador[0]], buffer);
        hotel.Contador[0]++;

        if (hotel.idAux == hotel.Hotelquartos) {
            hotel.Hotelquartos++;
            sleep(3);
            salvarDados(hotel);
            Quartos(hotel);
        } else {
            sleep(3);
            salvarDados(hotel);
            Quartos(hotel);
        }
        sleep(3);
        salvarDados(hotel);
        Quartos(hotel);
    } else if (comfirmacao == 2) {
        Quartos(hotel);
    }
}

void excluirClientes(Hotel hotel) {
    int cliente, comfirmacao;

    system("cls");

    if (hotel.HotelIdCliente != 0) {
        printf("Informe o Id do cliente: ");
        scanf("%d", &cliente);

        if (cliente > hotel.HotelIdCliente) {
            printf("O cliente não existe.\n");
            system("pause");
            Clientes(hotel);
        }

        if (cliente == 0) {
            printf("O ID 0 não pode ser excluido.\n");
            system("pause");
            Clientes(hotel);
        }

        if (hotel.clientes[cliente].temQuarto == 1) {
            printf("O ID %d não pode ser excluido, pois está registrado em um quarto.\n", cliente);
            system("pause");
            Clientes(hotel);
        }

        if (hotel.clientes[cliente].reservadoC == 1) {
            printf("O ID %d não pode ser excluido, pois tem uma reserva.\n", cliente);
            system("pause");
            Clientes(hotel);
        }

        if (hotel.clientes[cliente].existeCliente == 0) {
            printf("O ID %d não pode ser excluido. pois não existe mais.\n", cliente);
            system("pause");
            Clientes(hotel);
        }

        if (hotel.adm.adm == 0) {
            char senha[20];
            printf("Informe a palavra chave: ");
            scanf("%s", senha);

            if (strcmp(hotel.clientes[cliente].Chave, senha) == 1) {
                printf("Palavra chave incorreta.\n ");
                system("pause");
                Clientes(hotel);
            }
        }

        printf("Deseja excluir o cadastro de %s\n 1 - Sim \n 2 - Não; \n", hotel.clientes[cliente].nome);
        scanf("%d", &comfirmacao);

        if (comfirmacao == 1) {
            system("cls");
            printf("Cadatro do cliente excluido. \nId = %d\n", cliente);
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
        printf("Não a clientes registrados\n.");
        system("pause");
        Clientes(hotel);
    }
}

void excluirQuartos(Hotel hotel) {
    int quarto, comfirmacao;

    system("cls");

    if (hotel.Hotelquartos != 0) {
        printf("Informe o numero do quarto: ");
        scanf("%d", &quarto);

        int quarto = buscarIdDoQuarto(quarto, hotel);

        if (quarto > hotel.Hotelquartos) {
            printf("O quarto não existe.\n");
            system("pause");
            Quartos(hotel);
        }

        if (hotel.quartos[quarto].temCliente == 1) {
            printf("O quarto de numero %d não pode ser excluido, pois a clientes registrados.\n", hotel.quartos[quarto].numero);
            system("pause");
            Quartos(hotel);
        }

        if (hotel.quartos[quarto].Idreserva == 1) {
            printf("O quarto de numero %d não pode ser excluido, pois o querto está reservado.\n", hotel.quartos[quarto].numero);
            system("pause");
            Quartos(hotel);
        }

        if (hotel.quartos[quarto].existeQuarto == 0) {
            printf("O quarto não pode ser excluido. pois não existe mais.\n");
            system("pause");
            Quartos(hotel);
        }

        printf("Deseja excluir o quarto de numero: %d\n 1 - Sim / 2 - Não \n", hotel.quartos[quarto].numero);
        scanf("%d", &comfirmacao);

        if (comfirmacao == 1) {
            system("cls");

            printf("Cadatro do quarto excluido. \nId = %d\n status %d\n", quarto, hotel.quartos[quarto].existeQuarto);
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
        printf("Não a quartos registrados.\n.");
        system("pause");
        Quartos(hotel);
    }
}

void editarClientes(Hotel hotel) {
    int cliente;

    system("cls");

    if (hotel.HotelIdCliente != 0) {
        printf("Informe o Id do cliente para editar seu cadastro: ");
        scanf("%d", &cliente);

        if (cliente > hotel.HotelIdCliente) {
            printf("O cliente não existe.\n");
            system("pause");
            Clientes(hotel);
        }

        if (cliente == 0) {
            printf("O ID 0 não pode ser editado.\n");
            system("pause");
            Clientes(hotel);
        }

        if (hotel.clientes[cliente].temQuarto == 1) {
            printf("O ID %d não pode ser editado, pois está registrado em um quarto.\n", cliente);
            system("pause");
            Clientes(hotel);
        }

        if (hotel.clientes[cliente].reservadoC == 1) {
            printf("O ID %d não pode ser editado, pois tem uma reserva.\n", cliente);
            system("pause");
            Clientes(hotel);
        }

        if (hotel.clientes[cliente].existeCliente == 0) {
            printf("O ID %d não pode ser editado. pois não existe mais.\n", cliente);
            system("pause");
            Clientes(hotel);
        }

        if (hotel.adm.adm == 0) {
            char senha[30];
            printf("Digite sua senha.\n");
            scanf("%s", senha);
            if (strcmp(hotel.clientes[cliente].Chave, senha) == 1) {
                printf("Palavra chave incorreta.\n");
                system("pause");
                Clientes(hotel);
            }
        }

        printf("Digite o novo cpf: ");
        scanf("%s", hotel.clientes[cliente].cpf);

        if (!verificaCPF(hotel.clientes[cliente].cpf)) {
            system("cls");
            printf("CPF inválido.\n");

            editarClientes(hotel);
        }

        fflush(stdin);

        printf("Digite o novo nome do cliente: ");
        gets(hotel.clientes[cliente].nome);

        printf("Digite o novo endereço do cliente: ");
        gets(hotel.clientes[cliente].endereco);

        printf("Digite o novo telefone do cliente: ");
        gets(hotel.clientes[cliente].telefone);

        printf("Edição completa. o cliente do id %d, foi editado com sucesso.\n", cliente);
        system("pause");
        sleep(3);
        salvarDados(hotel);

        Clientes(hotel);
    } else {
        printf("Não a clientes registrados.\n");
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
            printf("O quarto não existe.\n");
            system("pause");
            Quartos(hotel);
        }

        if (hotel.quartos[numero].temCliente == 1) {
            printf("O quarto de numero %d não pode ser editado, pois a clientes registrados.\n", numero);
            system("pause");
            Quartos(hotel);
        }

        if (hotel.quartos[numero].Idreserva == 1) {
            printf("O quarto de numero %d não pode ser editado, pois o querto está reservado.\n", numero);
            system("pause");
            Quartos(hotel);
        }

        if (hotel.quartos[numero].existeQuarto == 0) {
            printf("O quarto não pode ser excluido. pois não existe mais.\n");
            system("pause");
            Quartos(hotel);
        }

        printf("Digite o número do quarto: ");
        scanf("%d", &aux);

        if (buscarNumeroDeQuartos(aux, hotel) == 0) {
            printf("Numero de quarto cadastrado.\n");
            system("pause");
            Quartos(hotel);
        }

        hotel.quartos[numero].numero = aux;

        printf("Digite a capacidade do quarto: ");
        scanf("%d", &hotel.quartos[numero].capacidade);

        if (hotel.quartos[numero].capacidade > 4) {
            hotel.quartos[numero].capacidade = 4;
            printf("O maximo em um quarto é 4 pessoas.\n");
        } else if (hotel.quartos[numero].capacidade == 0) {
            hotel.quartos[numero].capacidade = 1;
            printf("O minimo em um quarto é 1 pessoas.\n");
        }

        printf("Digite o preço do quarto: ");
        scanf("%f", &hotel.quartos[numero].preco);

        printf("Edição completa. o Quarto do id %d, foi editado com sucesso.\n", numero);
        system("pause");
        sleep(3);
        salvarDados(hotel);
        Quartos(hotel);
    } else {
        printf("Não a quartos registrados.\n");
        system("pause");
        Quartos(hotel);
    }

    system("pause");
    Quartos(hotel);
}

/* --------------------------------------------------------------------- */

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

    printf("Digite o numero do quarto: ");
    scanf("%d", &quarto);

    if (buscarIdDoQuarto(quarto, hotel) != 0) {
        quarto = buscarIdDoQuarto(quarto, hotel);

        if (quarto > hotel.Hotelquartos) {
            printf("O quarto não existe.\n");
            system("pause");
            Resevas(hotel);
        }

    } else if (hotel.quartos[0].numero == quarto) {
        quarto = 0;

    } else if (hotel.quartos[quarto].existeQuarto == 0) {
        printf("Quarto não existe.\n");
        system("pause");
        Resevas(hotel);
    } else {
        printf("Quarto não existe.\n");
        system("pause");
        Resevas(hotel);
    }

    printf("Digite o id do cliente: ");
    scanf("%d", &cliente);

    if (cliente > hotel.HotelIdCliente) {
        printf("O cliente não existe.\n");
        system("pause");
        Resevas(hotel);
    }

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

    if (hotel.clientes[cliente].existeCliente == 0) {
        printf("O ID %d não pode alugar um quarto. pois não existe mais.\n", cliente);
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

                char buffer[100];
                sprintf(buffer, "Numero do quarto %d / Nome do cliente: %s / Preço do quarto %.2f / Data %d/%d/%d", hotel.quartos[quarto].numero, hotel.clientes[cliente].nome, hotel.quartos[quarto].preco, diaDoMes, mes, ano);
                strcpy(hotel.historico[hotel.Contador[2]], buffer);
                hotel.Contador[2]++;

                printf("Cliente adcionado\n");
                system("pause");
                sleep(3);
                salvarDados(hotel);
                Resevas(hotel);
            } else {
                printf("Limite alcançado\n");
                system("pause");
                Resevas(hotel);
            }

        } else {
            printf("Não é o cliente da reserva, quarto reservado para %s\n", hotel.clientes[hotel.quartos[quarto].Idreserva].nome);
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

        char buffer[100];
        sprintf(buffer, "Numero do quarto %d / Nome do cliente: %s / Preço do quarto %.2f / Data %d/%d/%d", hotel.quartos[quarto].numero, hotel.clientes[cliente].nome, hotel.quartos[quarto].preco, diaDoMes, mes, ano);
        strcpy(hotel.historico[hotel.Contador[2]], buffer);
        hotel.Contador[2]++;

        printf("Cliente adcionado\n");
        system("pause");
        sleep(3);
        salvarDados(hotel);
        Resevas(hotel);
    } else {
        printf("Limite alcançado\n");
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
        printf("O cliente não existe.\n");
        system("pause");
        Resevas(hotel);
    }

    if (cliente == 0) {
        printf("O ID 0 não pode ser modificado.\n");
        system("pause");
        Clientes(hotel);
    }

    if (hotel.clientes[cliente].existeCliente == 0) {
        printf("O ID %d não tem quartos. pois não existe mais.\n", cliente);
        system("pause");
        Clientes(hotel);
    }

    if (cliente <= hotel.HotelIdCliente) {
        if (hotel.clientes[cliente].temQuarto == 1) {
            int possicao = procurarClienteNoQuarto(hotel.clientes[cliente].quartoC, cliente, hotel);

            if (possicao == 5) {
                printf("cliente não estar em um quarto.\n");
                system("pause");
                Resevas(hotel);
            }

            int preco = ((diaDoAno - hotel.clientes[cliente].tempoNoQuarto) * hotel.quartos[hotel.clientes[cliente].quartoC].preco) + hotel.quartos[hotel.clientes[cliente].quartoC].preco;

            int dias = (diaDoAno - hotel.clientes[cliente].tempoNoQuarto) + 1;

            printf("O cliente %s, precisar pagar %d de um periodo de %d dias no quarto.\n", hotel.clientes[cliente].nome, preco, dias);
            printf("1 - Pagou / 2 não pagou.\n");
            scanf("%d", &pago);

            if (pago == 1) {
                char buffer[200];
                sprintf(buffer, "Numero do quarto: %d / Preço pago: %.2f / Data %d/%d/%d / Dias hospedados: %d / Nome: %s / CPf: %s", hotel.quartos[hotel.clientes[cliente].quartoC].numero, hotel.quartos[hotel.clientes[cliente].quartoC].preco, diaDoMes, mes, ano, dias, hotel.clientes[cliente].nome, hotel.clientes[cliente].cpf);
                strcpy(hotel.historico[hotel.Contador[0]], buffer);
                hotel.Contador[3]++;

                hotel.clientes[cliente].temQuarto = 0;
                hotel.quartos[hotel.clientes[cliente].quartoC].quartoVago[possicao] = 0;
                hotel.quartos[hotel.clientes[cliente].quartoC].idCliente[possicao] = 0;
                hotel.clientes[cliente].reservadoC = 0;
                hotel.quartos[hotel.clientes[cliente].quartoC].reservado = 0;

                printf("O Cliente pagou R$%d. dos %s hospedado.\n", preco, (dias > 2) ? dias + " dias" : dias + " dia");
                sleep(3);
                salvarDados(hotel);
                system("pause");
                Resevas(hotel);
            }
        } else {
            printf("Cliente não está em um quarto.\n");
            system("pause");
            Resevas(hotel);
        }
    } else {
        printf("Cliente não existe.\n");
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

    int cliente, quarto;

    printf("Digite o Id do cliente para reserva um quarto: ");
    scanf("%d", &cliente);

    if (cliente > hotel.HotelIdCliente) {
        printf("O cliente não existe.\n");
        system("pause");
        Resevas(hotel);
    }
    if (cliente == 0) {
        printf("O ID 0 não pode ser excluido.\n");
        system("pause");
        Resevas(hotel);
    }
    if (hotel.clientes[cliente].temQuarto == 1) {
        printf("Cliente já tem o quarto.\n");
        system("pause");
        Resevas(hotel);
    }
    if (hotel.clientes[cliente].reservadoC == 1) {
        printf("Cliente já tem uma reserva.\n");
        system("pause");
        Resevas(hotel);
    }
    if (hotel.clientes[cliente].existeCliente == 0) {
        printf("O ID %d não pode fazer uma reseva. pois não existe mais.\n", cliente);
        system("pause");
        Resevas(hotel);
    }

    printf("Digite o numero do quarto: ");
    scanf("%d", &quarto);

    if (buscarIdDoQuarto(quarto, hotel) != 0) {
        quarto = buscarIdDoQuarto(quarto, hotel);

        if (quarto > hotel.Hotelquartos) {
            printf("O quarto não existe.\n");
            system("pause");
            Resevas(hotel);
        }

    } else if (hotel.quartos[0].numero == quarto) {
        quarto = 0;
    } else if (hotel.quartos[quarto].existeQuarto == 0) {
        printf("Quarto não existe.\n");
        system("pause");
        Resevas(hotel);
    } else {
        printf("Quarto não existe.\n");
        system("pause");
        Resevas(hotel);
    }

    if (hotel.quartos[quarto].reservado == 1) {
        printf("Quarto ja estar reservado para %s.\n", hotel.clientes[hotel.quartos[quarto].Idreserva].nome);
        system("pause");
        Resevas(hotel);
    }

    char buffer[100];
    sprintf(buffer, "Numero do quarto %d / Nome do cliente: %s / Preço do quarto %.2f / Data da reserva %d/%d/%d", hotel.quartos[quarto].numero, hotel.clientes[cliente].nome, hotel.quartos[quarto].preco, diaDoMes, mes, ano);
    strcpy(hotel.historico[hotel.Contador[2]], buffer);
    hotel.Contador[4]++;

    hotel.clientes[cliente].reservadoC = 1;
    hotel.clientes[cliente].IdreservaC = quarto;
    hotel.quartos[quarto].Idreserva = cliente;
    hotel.quartos[quarto].reservado = 1;

    printf("Quarto reservado para %s.\n", hotel.clientes[cliente].nome);
    system("pause");
    sleep(3);
    salvarDados(hotel);
    Resevas(hotel);
}

/* --------------------------------------------------------------------- */

void historicoDeQuartos(Hotel hotel) {
    system("cls");
    for (int i = 0; i < hotel.Contador[0]; i++) {
        printf("%s\n", hotel.historico[i]);
    }
    system("pause");
    historicoMenu(hotel);
}

void historicoDeClientes(Hotel hotel) {
    system("cls");
    for (int i = 0; i < hotel.Contador[1]; i++) {
        printf("%s\n", hotel.historico[i]);
    }
    system("pause");
    historicoMenu(hotel);
}

void historicoDiaria(Hotel hotel) {
    system("cls");
    for (int i = 0; i < hotel.Contador[2]; i++) {
        printf("%s\n", hotel.historico[i]);
    }
    system("pause");
    historicoMenu(hotel);
}

void historicoDeReservas(Hotel hotel) {
    system("cls");
    for (int i = 0; i < hotel.Contador[4]; i++) {
        printf("%s\n", hotel.historico[i]);
    }
    system("pause");
    historicoMenu(hotel);
}

void historicoDePagamento(Hotel hotel) {
    system("cls");
    for (int i = 0; i < hotel.Contador[3]; i++) {
        printf("%s\n", hotel.historico[i]);
    }
    system("pause");
    historicoMenu(hotel);
}

/* --------------------------------------------------------------------- */

void exibirClientes(Hotel hotel) {
    system("cls");
    if (hotel.HotelIdCliente != 0) {
        for (int i = 1; i < hotel.HotelIdCliente; i++) {
            if (hotel.clientes[i].existeCliente == 1) {
                printf("ID: %d - Nome: %s\n", i, hotel.clientes[i].nome);
            }
        }
    } else {
        printf("Não a clientes registrados.\n");
    }
    system("pause");

    Clientes(hotel);
}
/* Adcionar mais coisas */
void detalharClientes(Hotel hotel) {
    int cliente;
    char senha[20];

    system("cls");

    if (hotel.HotelIdCliente != 0) {
        printf("Informe o Id do cliente\n ");
        scanf("%d", &cliente);

        printf("Nome: %s\n", hotel.clientes[cliente].Chave);

        if (cliente > hotel.HotelIdCliente) {
            printf("O cliente não existe.\n");
            system("pause");
            Clientes(hotel);
        }
        if (hotel.clientes[cliente].existeCliente == 0) {
            printf("O ID %d não existe mais.\n", cliente);
            system("pause");
            Clientes(hotel);
        }

        if (hotel.adm.adm == 0) {
            fflush(stdin);
            printf("Informe a palavra chave do cliente\n ");
            scanf("%s", senha);
        }

        if (strcmp(hotel.clientes[cliente].Chave, senha) == 0 || hotel.adm.adm == 1) {
            system("cls");

            printf("Nome: %s\n", hotel.clientes[cliente].nome);
            printf("Cpf: %s\n", hotel.clientes[cliente].cpf);
            printf("Endereço: %s\n", hotel.clientes[cliente].endereco);
            printf("Telefone: %s\n", hotel.clientes[cliente].telefone);

            system("pause");
            sleep(3);
            salvarDados(hotel);
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
/* Adcionar mais coisas */
void exibirQuartos(Hotel hotel) {
    system("cls");

    for (int i = 0; i < hotel.Hotelquartos; i++) {
        if (hotel.quartos[i].existeQuarto == 1) {
            printf("===========================\n");
            printf("ID: %d - Numero: %d - Capacidade:%d - Preço:%.2f\n", i, hotel.quartos[i].numero, hotel.quartos[i].capacidade, hotel.quartos[i].preco);
            if (hotel.quartos[i].reservado == 0) {
                for (int j = 0; j < hotel.quartos[i].capacidade; j++) {
                    if (hotel.adm.adm == 1) {
                        printf("Clientes: %s\n", hotel.clientes[hotel.quartos[i].idCliente[j]].nome);
                    }
                }
            } else {
                printf("Quarto reservado para %s.", hotel.clientes[hotel.quartos[i].Idreserva].nome);
            }

            printf("===========================\n");
        }
    }

    system("pause");
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

/* --------------------------------------------------------------------- */

void Clientes(Hotel hotel) {
    system("cls");
    int opcao;

    hotel.idAux = 1;

    do {
        system("cls");
        printf("\nMenu:\n");
        printf("1. Listar clientes\n");
        printf("2. Exibir detalhe do cliente\n");
        printf("3. Cadastra clientes\n");
        printf("4. Editar clientes\n");
        printf("5. Excluir clientes\n\n");

        printf("6. Voltar ao menu\n");
        printf("Escolha uma opção: ");

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
                printf("Voltando ao menu...\n");
                menu(hotel);
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }

    } while (true);
}

void Quartos(Hotel hotel) {
    system("cls");
    int opcao;

    hotel.idAux = 0;

    do {
        printf("\nMenu de quartos:\n");
        printf("1. Exibir quartos\n");
        if (hotel.adm.adm == 1) {
            printf("2. Cadastrar quarto\n");
            printf("3. Excluir quarto\n");
            printf("4. Editar quartos\n");
        }

        printf("\n%d. Voltar ao menu\n", (hotel.adm.adm == 0) ? 2 : 5);
        printf("Escolha uma opção: ");

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
                    printf("Voltando ao menu...\n");
                    menu(hotel);
                    break;
                }
            case 3:
                if (hotel.adm.adm == 1) {
                    system("cls");
                    excluirQuartos(hotel);
                    break;
                } else {
                    printf("Opção inválida. Tente novamente.\n");
                    Quartos(hotel);
                    break;
                }

                break;
            case 4:
                if (hotel.adm.adm == 1) {
                    system("cls");
                    editarQuartos(hotel);
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
                    menu(hotel);
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
    system("cls");

    int opcao;

    hotel.idAux = 1;

    do {
        system("cls");

        printf("\nMenu de reservas:\n");
        printf("1. alugar quartos\n");
        printf("2. pagar quartos\n");
        printf("3. reservar quartos\n");
        printf("\n4. Voltar ao menu\n");
        printf("Escolha uma opção: ");

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
                printf("Voltando ao menu...\n");
                menu(hotel);
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }

    } while (true);
}

void historicoMenu(Hotel hotel) {
    int opcao;
    system("cls");
    do {
        system("cls");

        printf("\nMenu:\n");
        printf("1. Historico de cliente\n");
        printf("2. Historico de quarto\n");
        printf("3. Historico de diaria\n");
        printf("4. Historico de pagamentos\n");
        printf("5. Historico de reserva\n");

        printf("\n6. Voltar ao menu\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        fflush(stdin);

        switch (opcao) {
            case 1:
                system("cls");
                if (hotel.Contador[1] != 0) {
                    historicoDeClientes(hotel);
                    break;
                } else {
                    printf("Não a clientes registrados.\n");
                    system("pause");
                    break;
                }
            case 2:
                system("cls");
                if (hotel.Contador[0] != 0) {
                    historicoDeQuartos(hotel);
                    break;
                } else {
                    printf("Não a quartos registrados.\n");
                    system("pause");
                    break;
                }
            case 3:
                if (hotel.Contador[2] != 0) {
                    historicoDiaria(hotel);
                    break;
                } else {
                    printf("Não a reservas registradas.\n");
                    system("pause");
                    break;
                }
            case 4:
                if (hotel.Contador[3] != 0) {
                    historicoDePagamento(hotel);
                    break;
                    break;
                } else {
                    printf("Não a pagamento registradas.\n");
                    system("pause");
                    break;
                }
            case 5:
                if (hotel.Contador[4] != 0) {
                    historicoDeReservas(hotel);
                    break;
                    break;
                } else {
                    printf("Não a pagamento registradas.\n");
                    system("pause");
                    break;
                }
            case 6:
                system("cls");
                printf("Voltando ao menu...\n");
                menu(hotel);
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (true);
}

void menu(Hotel hotel) {
    int opcao;
    system("cls");
    do {
        system("cls");
        printf("\nMenu:\n");
        printf("1. Clientes\n");
        printf("2. Quartos\n\n");

        printf("3. %s\n", (hotel.adm.adm == 0) ? "Login" : "Deslogar");
        if (hotel.adm.adm == 1) {
            printf("4. Reservas\n");
            printf("5. historicos\n");
        }
        printf("%s. Sair\n", (hotel.adm.adm == 0) ? "4" : "6");

        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        fflush(stdin);

        switch (opcao) {
            case 1:
                Clientes(hotel);
                break;
            case 2:
                Quartos(hotel);
                break;

            case 3:
                if (hotel.adm.adm == 0) {
                    Login(hotel);
                    break;
                } else {
                    system("cls");
                    printf("Deslogando...\n");
                    hotel.adm.adm = 0;
                    system("pause");
                    break;
                }
            case 4:
                if (hotel.adm.adm == 1) {
                    Resevas(hotel);
                    break;
                } else {
                    hotel.adm.adm = 0;
                    printf("Saindo...\n");
                    abort();
                }
                break;
            case 5:
                if (hotel.adm.adm == 0) {
                    Resevas(hotel);
                    break;
                } else {
                    system("cls");
                    historicoMenu(hotel);
                    break;
                }
            case 6:
                if (hotel.adm.adm == 0) {
                    Resevas(hotel);
                    break;
                } else {
                    hotel.adm.adm = 0;
                    printf("Saindo...\n");
                    abort();
                }

            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (true);
}

/* --------------------------------------------------------------------- */

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

/* --------------------------------------------------------------------- */

int main() {
    Hotel hotel;

    setlocale(LC_ALL, "Portuguese_Brazil");
    hotel.adm.adm = 0;
    hotel.HotelIdCliente = 1;

    strcpy(hotel.clientes[0].nome, "Vago");
    strcpy(hotel.clientes[0].endereco, "Vago");
    hotel.clientes[0].existeCliente = 1;

    hotel.Hotelquartos = 0;

    hotel.Contador[0] = 0;
    hotel.Contador[1] = 0;
    hotel.Contador[2] = 0;
    hotel.Contador[3] = 0;

    FILE *file = fopen("hotel.bin", "rb");

    if (file == NULL) {
        printf("Arquivo não encontrado.\n");
    } else {
        fread(&hotel, sizeof(Hotel), 1, file);

        fclose(file);
    }

    menu(hotel);
    return 0;
}