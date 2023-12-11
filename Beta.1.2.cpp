#include <ctype.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
    char palavraChave[20];
    int quarto;
    int existeCliente;
    int temQuarto;
    int tempoNoQuarto;
    int reservado;
    int idReserva;
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
    int idReserva;
}
Quarto;

typedef struct {
    Cliente clientes[MAX_CLIENTES];
    Quarto quartos[MAX_QUARTOS];
    Adminstrador adm;
    tm tempo;
    int hotelIdCliente;
    int hotelQuartos;
    int Contador[5];
    int idAux;
    char historico[MAX_HISTORICO][100]; /* <- inpementar */
}
Hotel;

/* Salva e carregar dados */
void salvarDados(Hotel hotel);
/* Cadastros */
void cadastrarCliente(Hotel hotel);
void cadastrarQuarto(Hotel hotel);
void editarClientes(Hotel hotel);
void editarQuartos(Hotel hotel);
/* Excluir */
void excluirClientes(Hotel hotel);
void excluirQuartos(Hotel hotel);
/* Histórico */
void historicoDeReservas(Hotel hotel);  /* <- Terminar */
void historicoDiaria(Hotel hotel);      /* <- Terminar */
void historicoDeClientes(Hotel hotel);  /* <- Terminar */
void historicoDeQuartos(Hotel hotel);   /* <- Terminar */
void historicoDePagamento(Hotel hotel); /* <- Terminar */
/* Informações */
void exibirQuartos(Hotel hotel);
void detalharClientes(Hotel hotel);
void exibirClientes(Hotel hotel);
/* Check-in & Check-out */
void checkInQuarto(Hotel hotel);
void checkOnQuarto(Hotel hotel);
void reservaUmQuarto(Hotel Hotel);
/* Verificadores */
int verificaCPF(char *cpfEntrada);
int buscarIdDoQuarto(int numero, Hotel Hotel);
int buscarNumeroDeQuartos(int numero, Hotel hotel);
int adicionarNoQuarto(int numero, int cliente, Hotel hotel);
int procurarClienteNoQuarto(int numero, int cliente, Hotel hotel);
/* Menus */
void menu(Hotel hotel);
void historicoMenu(Hotel hotel);
void Clientes(Hotel hotel);
void Quartos(Hotel hotel);
void Resevas(Hotel hotel);
void Login(Hotel hotel);

/* Salvar dados */
void salvarDados(Hotel hotel) {
    FILE *file = fopen("hotel.bin", "wb");

    fwrite(&hotel, sizeof(Hotel), 1, file);

    fclose(file);
}

/* --------------------------------------------------------------------- */

void cadastrarCliente(Hotel hotel) {
    fflush(stdin);

    int comfirmacao;
    char nome[50];
    char telefone[20];
    char endereco[100];
    char palavrachave[20];
    char cpf[20];

    if (hotel.clientes[hotel.idAux].existeCliente == 1) {
        if (hotel.idAux != hotel.hotelIdCliente) {
            hotel.idAux++;
            cadastrarCliente(hotel);
        }
    }

    printf("Digite o cpf: ");
    scanf("%12s", cpf);

    if (!verificaCPF(hotel.clientes[hotel.idAux].cpf)) {
        system("cls");
        printf("CPF inválido.\n");
        cadastrarCliente(hotel);
    }

    fflush(stdin);
    printf("Digite o nome do cliente: ");
    gets(nome);

    printf("Digite o endere�o do cliente: ");
    gets(endereco);

    printf("Digite o telefone do cliente: ");
    scanf("%19s", telefone);

    printf("Digite oa sua palavra chave: ");
    scanf("%19s", palavrachave);

    fflush(stdin);
    printf("Deseja confirma o cadastro\n 1 - Sim \n 2 - N�o; \n");
    scanf("%d", &comfirmacao);

    if (comfirmacao == 1) {
        system("cls");
        printf("Cadatro do cliente confirmado. \nId = %d\n", hotel.idAux);

        hotel.clientes[hotel.idAux].existeCliente = 1;
        hotel.clientes[hotel.idAux].temQuarto = 0;

        strcpy(nome, hotel.clientes[hotel.idAux].nome);
        strcpy(endereco, hotel.clientes[hotel.idAux].endereco);
        strcpy(telefone, hotel.clientes[hotel.idAux].telefone);
        strcpy(palavrachave, hotel.clientes[hotel.idAux].palavraChave);
        strcpy(cpf, hotel.clientes[hotel.idAux].cpf);

        char buffer[100];
        sprintf(buffer, "ID do cliente %d / CPF %s / Nome %s / Data %d/%d/%d", hotel.idAux, hotel.clientes[hotel.idAux].cpf, hotel.clientes[hotel.idAux].nome, hotel.tempo.tm_mday, hotel.tempo.tm_mon, hotel.tempo.tm_year);
        strcpy(hotel.historico[hotel.Contador[1]], buffer);
        hotel.Contador[1]++;

        if (hotel.idAux == hotel.hotelIdCliente) {
            
            hotel.hotelIdCliente++;
            printf("ID do cliente %d / CPF %s / Nome %s / Data do cadastro %d/%d/%d", hotel.idAux, hotel.clientes[hotel.idAux].cpf, hotel.clientes[hotel.idAux].nome, hotel.tempo.tm_mday, hotel.tempo.tm_mon, hotel.tempo.tm_year);
            system("pause");
            Clientes(hotel);

        } else {
            printf("ID do cliente %d / CPF %s / Nome %s / Data do cadastro %d/%d/%d", hotel.idAux, hotel.clientes[hotel.idAux].cpf, hotel.clientes[hotel.idAux].nome, hotel.tempo.tm_mday, hotel.tempo.tm_mon, hotel.tempo.tm_year);
            system("pause");
            Clientes(hotel);

        }
    } else {
        system("cls");
        Clientes(hotel);
    }
}

void cadastrarQuarto(Hotel hotel) {
    fflush(stdin);
    system("cls");

    int comfirmacao;
    int numero;
    float preco;
    int capacidade;

    if (hotel.quartos[hotel.idAux].existeQuarto == 1) {
        if (hotel.idAux != hotel.hotelQuartos) {
            hotel.idAux++;
            cadastrarQuarto(hotel);
        }
    }


    printf("Digite o n�mero do quarto: ");
    scanf("%d", &numero);

    if (buscarNumeroDeQuartos(numero, hotel) == 0) {
        printf("Numero de quarto cadastrado\n");
        system("pause");
        Quartos(hotel);
    }

    printf("Digite a capacidade do quarto: ");
    scanf("%d", &capacidade);

    if (capacidade > 4) {
        hotel.quartos[hotel.idAux].capacidade = 4;
        printf("O maximo em um quarto � 4 pessoas.\n");
    } else if (capacidade == 0) {
        hotel.quartos[hotel.idAux].capacidade = 1;
        printf("O minimo em um quarto � 1 pessoas.\n");
    }

    printf("Digite o pre�o do quarto: ");
    scanf("%f", &preco);

    printf("Deseja confirma o cadastro\n 1 - Sim \n 2 - N�o; \n");
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
        sprintf(buffer, "Numero do quarto %d / Capacidade %d / Pre�o %.2f / Data %d/%d/%d", numero, hotel.quartos[hotel.idAux].capacidade, hotel.quartos[hotel.idAux].preco, hotel.tempo.tm_mday, hotel.tempo.tm_mon, hotel.tempo.tm_year);
        strcpy(hotel.historico[hotel.Contador[0]], buffer);
        hotel.Contador[0]++;

        if (hotel.idAux == hotel.hotelQuartos) {
            hotel.hotelQuartos++;
            Quartos(hotel);
        } else {
            Quartos(hotel);
        }

        Quartos(hotel);
    } else if (comfirmacao == 2) {
        system("cls");
        Quartos(hotel);
    }
}

void excluirClientes(Hotel hotel) {
    int cliente, comfirmacao;

    system("cls");

    if (hotel.hotelIdCliente != 0) {

        printf("Informe o Id do cliente\n ");
        scanf("%d", &cliente);

        if (cliente > hotel.hotelIdCliente) {
            printf("O cliente n�o existe.\n");
            system("pause");
            Resevas(hotel);
        }

        if (cliente == 0) {
            printf("O ID 0 n�o pode ser excluido.\n");
            system("pause");
            Clientes(hotel);
        }

        if (hotel.clientes[cliente].temQuarto == 1) {
            printf("O ID %d n�o pode ser excluido, pois est� registrado em um quarto.\n", cliente);
            system("pause");
            Clientes(hotel);
        }

        if (hotel.clientes[cliente].reservado == 1) {
            printf("O ID %d n�o pode ser excluido, pois tem uma reserva.\n", cliente);
            system("pause");
            Clientes(hotel);
        }

        if (hotel.clientes[cliente].existeCliente == 0) {
            printf("O ID %d n�o pode ser excluido. pois n�o existe mais.\n", cliente);
            system("pause");
            Clientes(hotel);
        }

        if (hotel.adm.adm == 0) {
            char senha[20];
            printf("Informe a palavra chave.\n ");
            scanf("%s", senha);

            if (strcmp(hotel.clientes[cliente].palavraChave, senha) == 1) {
                printf("Palavra chave incorreta.\n ");
                system("cls");
                Clientes(hotel);
            }
            
        }

        printf("Deseja excluir o cadastro de %s\n 1 - Sim \n 2 - N�o; \n", hotel.clientes[cliente].nome);
        scanf("%d", &comfirmacao);

        if (comfirmacao == 1) {
            system("cls");
            printf("Cadatro do cliente excluido. \nId = %d\n", hotel.idAux);
            *hotel.clientes[cliente].nome = '\0';
            *hotel.clientes[cliente].cpf = '\0';
            *hotel.clientes[cliente].endereco = '\0';
            *hotel.clientes[cliente].telefone = '\0';
            hotel.clientes[cliente].existeCliente = 0;
            hotel.clientes[cliente].quarto = '\0';
        } else {
            system("cls");
            Clientes(hotel);
        }
    } else {
        printf("N�o a clientes registrados\n.");
        Clientes(hotel);
    }
}

void excluirQuartos(Hotel hotel) {
    int numero, comfirmacao;

    system("cls");

    if (hotel.hotelQuartos != 0) {

        printf("Informe o numero do quarto\n ");
        scanf("%d", &numero);

        int numero = buscarIdDoQuarto(numero, hotel);

        if (numero > hotel.hotelQuartos) {
            printf("O quarto n�o existe.\n");
            system("pause");
            Resevas(hotel);
        }

        if (hotel.quartos[numero].temCliente == 1) {
            printf("O quarto de numero %d n�o pode ser excluido, pois a clientes registrados.\n", hotel.quartos[numero].numero);
            system("pause");
            Quartos(hotel);
        }

        if (hotel.quartos[numero].idReserva == 1) {
            printf("O quarto de numero %d n�o pode ser excluido, pois o querto est� reservado.\n", hotel.quartos[numero].numero);
            system("pause");
            Quartos(hotel);
        }

        if (hotel.quartos[numero].existeQuarto == 0) {
            printf("O quarto n�o pode ser excluido. pois n�o existe mais.\n");
            system("pause");
            Quartos(hotel);
        }

        printf("Deseja excluir o quarto de numero: %d\n 1 - Sim \n 2 - N�o; \n", hotel.quartos[numero].numero);
        scanf("%d", &comfirmacao);

        if (comfirmacao == 1) {
            system("cls");
            printf("Cadatro do cliente excluido. \nId = %d\n", hotel.idAux);
            hotel.quartos[numero].numero = '\0';
            hotel.quartos[numero].preco = '\0';
            hotel.quartos[numero].capacidade = '\0';
            hotel.quartos[numero].existeQuarto = 0;
        } else {
            system("cls");
            Quartos(hotel);
        }
    } else {
        printf("N�o a quartos registrados\n.");
        Quartos(hotel);
    }
}

void editarClientes(Hotel hotel) {
    int cliente;

    system("cls");

    if (hotel.hotelIdCliente != 0) {
        printf("Informe o Id do cliente para editar seu cadastro\n ");
        scanf("%d", &cliente);

        if (cliente > hotel.hotelIdCliente) {
            printf("O cliente n�o existe.\n");
            system("pause");
            Resevas(hotel);
        }

        if (cliente == 0) {
            printf("O ID 0 n�o pode ser editado.\n");
            system("pause");
            Clientes(hotel);
        }

        if (hotel.clientes[cliente].temQuarto == 1) {
            printf("O ID %d n�o pode ser editado, pois est� registrado em um quarto.\n", cliente);
            system("pause");
            Clientes(hotel);
        }

        if (hotel.clientes[cliente].reservado == 1) {
            printf("O ID %d n�o pode ser editado, pois tem uma reserva.\n", cliente);
            system("pause");
            Clientes(hotel);
        }

        if (hotel.clientes[cliente].existeCliente == 0) {
            printf("O ID %d n�o pode ser editado. pois n�o existe mais.\n", cliente);
            system("pause");
            Clientes(hotel);
        }
        

        char senha[30];
        printf("Digite sua senha.\n");
        scanf("%s", senha);
        if (hotel.adm.adm == 0) {
            if (strcmp(hotel.clientes[cliente].palavraChave, senha) == 1) {
                printf("Palavra chave incorreta.\n");
                system("pause");
                Clientes(hotel);
            } 
        }

        printf("Digite o novo cpf: ");
        scanf("%s", hotel.clientes[cliente].cpf);

        if (!verificaCPF(hotel.clientes[cliente].cpf)) {
            system("cls");
            printf("CPF inv�lido.\n");

            editarClientes(hotel);
        }

        fflush(stdin);

        printf("Digite o novo nome do cliente: ");
        gets(hotel.clientes[cliente].nome);

        printf("Digite o novo endere�o do cliente: ");
        gets(hotel.clientes[cliente].endereco);

        printf("Digite o novo telefone do cliente: ");
        gets(hotel.clientes[cliente].telefone);

        printf("Edi��o completa. o cliente do id %d, foi editado com sucesso.\n", cliente);
        system("pause");

        Clientes(hotel);
    } else {
        printf("N�o a clientes registrados.\n");
    }

    system("pause");
    Clientes(hotel);
}

void editarQuartos(Hotel hotel) {
    int numero;
    int aux;

    system("cls");

    if (hotel.hotelQuartos != 0) {
        printf("Informe o numero do quarto para editar\n ");
        scanf("%d", &numero);

        int Id = buscarIdDoQuarto(numero, hotel);
        
        if (numero > hotel.hotelQuartos) {
            printf("O quarto n�o existe.\n");
            system("pause");
            Resevas(hotel);
        }

        if (hotel.quartos[Id].temCliente == 1) {
            printf("O quarto de numero %d n�o pode ser editado, pois a clientes registrados.\n", numero);
            system("pause");
            Quartos(hotel);
        }
        
        if (hotel.quartos[numero].idReserva == 1) {
            printf("O quarto de numero %d n�o pode ser editado, pois o querto est� reservado.\n", numero);
            system("pause");
            Quartos(hotel);
        }

         if (hotel.quartos[numero].existeQuarto == 0) {
            printf("O quarto n�o pode ser excluido. pois n�o existe mais.\n");
            system("pause");
            Quartos(hotel);
        }

        printf("Digite o n�mero do quarto: ");
        scanf("%d", &aux);

        if (buscarNumeroDeQuartos(aux, hotel) == 0) {
            printf("Numero de quarto cadastrado\n");
            system("pause");
            Quartos(hotel);
        }

        hotel.quartos[numero].numero = aux;

        printf("Digite a capacidade do quarto: ");
        scanf("%d", &hotel.quartos[numero].capacidade);

        if (hotel.quartos[numero].capacidade > 4) {
            hotel.quartos[numero].capacidade = 4;
            printf("O maximo em um quarto � 4 pessoas.\n");
        } else if (hotel.quartos[numero].capacidade == 0) {
            hotel.quartos[numero].capacidade = 1;
            printf("O minimo em um quarto � 1 pessoas.\n");
        }
        
        printf("Digite o pre�o do quarto: ");
        scanf("%f", &hotel.quartos[numero].preco);

        printf("Edi��o completa. o Quarto do id %d, foi editado com sucesso.\n", numero);
        system("pause");

        Quartos(hotel);
    } else {
        printf("N�o a quartos registrados.\n");
        system("pause");
        Quartos(hotel);
    }

    system("pause");
    Quartos(hotel);
}

/* --------------------------------------------------------------------- */

void exibirClientes(Hotel hotel) {
    system("cls");
    if (hotel.hotelIdCliente != 1) {
        for (int i = 1; i < hotel.hotelIdCliente; i++) {
            if (hotel.clientes[i].existeCliente != 0) {
                printf("ID: %d - Nome: %s\n", i, hotel.clientes[i].nome);
            }
        }
    } else {
        printf("N�o a clientes registrados.\n");
    }
    system("pause");

    Clientes(hotel);
}

void checkInQuarto(Hotel hotel) {
    int numero;
    int cliente;

    system("cls");

    printf("Digite o numero do quarto: ");
    scanf("%d", &numero);

    if (buscarIdDoQuarto(numero, hotel) != 0) {

        numero = buscarIdDoQuarto(numero, hotel);

        if (numero > hotel.hotelQuartos) {
            printf("O quarto n�o existe.\n");
            system("pause");
            Resevas(hotel);
        }

    } else if (hotel.quartos[0].numero == numero) {
        numero = 0;
    
    } else if (hotel.quartos[numero].existeQuarto == 0) {
        printf("Quarto n�o existe.\n");
        system("pause");
        Resevas(hotel);
    } else {
        printf("Quarto n�o existe.\n");
        system("pause");
        Resevas(hotel);
    }

    printf("Digite o id do cliente: ");
    scanf("%d", &cliente);

    if (cliente > hotel.hotelIdCliente) {
        printf("O cliente n�o existe.\n");
        system("pause");
        Resevas(hotel);
    }

    if (cliente == 0) {
        printf("N�o pode acicionar o ID 0.\n");
        system("pause");
        Resevas(hotel);
    }

    if (hotel.clientes[cliente].temQuarto == 1) {
        printf("O cliente j� est� em um quarto.\n");
        system("pause");
        Resevas(hotel);
    }
    
    if (hotel.clientes[cliente].existeCliente == 0) {
        printf("O ID %d n�o pode alugar um quarto. pois n�o existe mais.\n", cliente);
        system("pause");
        Resevas(hotel);
    }

    if (hotel.quartos[numero].reservado == 1) {
        if (hotel.quartos[numero].idReserva == cliente) {
            if (adicionarNoQuarto(numero, cliente, hotel) != 0) {

                hotel.quartos[numero].idCliente[adicionarNoQuarto(numero, cliente, hotel) - 1] = cliente;
                hotel.quartos[numero].quartoVago[adicionarNoQuarto(numero, cliente, hotel) - 1] = 0;
                hotel.quartos[numero].temCliente = 1;
                hotel.clientes[cliente].quarto = numero;
                hotel.clientes[cliente].temQuarto = 1;
                hotel.clientes[cliente].tempoNoQuarto = hotel.tempo.tm_yday;

                char buffer[100];
                sprintf(buffer, "Numero do quarto %d / Nome do cliente: %s / Pre�o do quarto %.2f / Data %d/%d/%d", hotel.quartos[numero].numero, hotel.clientes[cliente].nome, hotel.quartos[numero].preco, hotel.tempo.tm_mday, hotel.tempo.tm_mon, hotel.tempo.tm_year);
                strcpy(hotel.historico[hotel.Contador[2]], buffer);
                hotel.Contador[2]++;

                printf("Cliente adcionado\n");
                system("pause");
                Resevas(hotel);
            } else {
                printf("Limite alcan�ado\n");
                system("pause");
                Resevas(hotel);
            }

        } else {

            printf("N�o � o cliente da reserva, quarto reservado para %s\n", hotel.clientes[hotel.quartos[numero].idReserva].nome);
            system("pause");
            Resevas(hotel);
        }
    }

    if (adicionarNoQuarto(numero, cliente, hotel) != 0) {

        hotel.quartos[numero].idCliente[adicionarNoQuarto(numero, cliente, hotel) - 1] = cliente;
        hotel.quartos[numero].quartoVago[adicionarNoQuarto(numero, cliente, hotel) - 1] = 0;
        hotel.quartos[numero].temCliente = 1;
        hotel.clientes[cliente].quarto = numero;
        hotel.clientes[cliente].temQuarto = 1;
        hotel.clientes[cliente].tempoNoQuarto = hotel.tempo.tm_yday;

        char buffer[100];
        sprintf(buffer, "Numero do quarto %d / Nome do cliente: %s / Pre�o do quarto %.2f / Data %d/%d/%d", hotel.quartos[numero].numero, hotel.clientes[cliente].nome, hotel.quartos[numero].preco, hotel.tempo.tm_mday, hotel.tempo.tm_mon, hotel.tempo.tm_year);
        strcpy(hotel.historico[hotel.Contador[2]], buffer);
        hotel.Contador[2]++;

        printf("Cliente adcionado\n");
        system("pause");
        Resevas(hotel);
    } else {
        printf("Limite alcan�ado\n");
        system("pause");
        Resevas(hotel);
    }
}

void checkOnQuarto(Hotel hotel) {
    int numero;
    int cliente;
    int pago;

    system("cls");

    printf("Digite o ID do cliete: ");
    scanf("%d", &cliente);

    if (cliente > hotel.hotelIdCliente) {
            printf("O cliente n�o existe.\n");
            system("pause");
            Resevas(hotel);
        }

        if (cliente == 0) {
            printf("O ID 0 n�o pode ser modificado.\n");
            system("pause");
            Clientes(hotel);
        }

        if (hotel.clientes[cliente].existeCliente == 0) {
            printf("O ID %d n�o tem quartos. pois n�o existe mais.\n", cliente);
            system("pause");
            Clientes(hotel);
        }

    if (cliente <= hotel.hotelIdCliente) {
        if (hotel.clientes[cliente].temQuarto == 1) {

            int possicao = procurarClienteNoQuarto(hotel.clientes[cliente].quarto, cliente, hotel);

            if (possicao == 5) {
                printf("cliente n�o estar em um quarto.\n");
                system("pause");
                Resevas(hotel);
            }

            int preco = ((hotel.tempo.tm_yday - hotel.clientes[cliente].tempoNoQuarto) * hotel.quartos[hotel.clientes[cliente].quarto].preco) + hotel.quartos[hotel.clientes[cliente].quarto].preco;

            int dias = (hotel.tempo.tm_yday - hotel.clientes[cliente].tempoNoQuarto) + 1;

            printf("O cliente %s, precisar pagar %d de um periodo de %d dias no quarto.\n", hotel.clientes[cliente].nome, preco, dias);
            printf("1 - Pagou | 2 n�o pagou\n");
            scanf("%d", &pago);

            if (pago == 1) {

                char buffer[200];
                sprintf(buffer, "Numero do quarto: %d / Pre�o pago: %.2f / Data %d/%d/%d / Dias hospedados: %d / Nome: %s / CPf: %s", hotel.quartos[hotel.clientes[cliente].quarto].numero, hotel.quartos[hotel.clientes[cliente].quarto].preco, hotel.tempo.tm_mday, hotel.tempo.tm_mon, hotel.tempo.tm_year, dias, hotel.clientes[cliente].nome, hotel.clientes[cliente].cpf);
                strcpy(hotel.historico[hotel.Contador[0]], buffer);
                hotel.Contador[3]++;

                hotel.clientes[cliente].temQuarto = 0;
                hotel.quartos[hotel.clientes[cliente].quarto].quartoVago[possicao] = 0;
                hotel.quartos[hotel.clientes[cliente].quarto].idCliente[possicao] = 0;

                if (hotel.clientes[cliente].reservado == 1) {
                    hotel.clientes[cliente].reservado == 0;
                    hotel.quartos[hotel.clientes[cliente].quarto].reservado = 0;
                }

                printf("O Cliente pagou %d\n", preco);
                system("pause");
                Resevas(hotel);
            }
        } else {
            printf("Cliente n�o est� em um quarto\n");
            system("pause");
            Resevas(hotel);
        }
    } else {
        printf("Cliente n�o existe\n");
        system("pause");
        Resevas(hotel);
    }
}

void reservaUmQuarto(Hotel hotel) {
    int cliente, numero;

    printf("Digite o Id do cliente para reserva um quarto.\n");
    scanf("%d", &cliente);

    if (cliente > hotel.hotelIdCliente) {
        printf("O cliente n�o existe.\n");
        system("pause");
        Resevas(hotel);
    }
    if (cliente == 0) {
        printf("O ID 0 n�o pode ser excluido.\n");
        system("pause");
        Clientes(hotel);
    }
    if (hotel.clientes[cliente].temQuarto == 1) {
        printf("Cliente j� tem o quarto.");
        system("pause");
        Clientes(hotel);
    }
    if (hotel.clientes[cliente].reservado == 1) {
        printf("Cliente j� tem uma reserva.\n");
        system("pause");
        Clientes(hotel);
    }
    if (hotel.clientes[cliente].existeCliente == 0) {
        printf("O ID %d n�o pode fazer uma reseva. pois n�o existe mais.\n", cliente);
        system("pause");
        Clientes(hotel);
    }

    printf("Digite o numero do quarto: ");
    scanf("%d", &numero);

    if (buscarIdDoQuarto(numero, hotel) != 0) {
        numero = buscarIdDoQuarto(numero, hotel);

        if (numero > hotel.hotelQuartos) {
            printf("O quarto n�o existe.\n");
            system("pause");
            Resevas(hotel);
        }

    } else if (hotel.quartos[0].numero == numero) {
        numero = 0;
    } else if (hotel.quartos[numero].existeQuarto == 0) {
        printf("Quarto n�o existe.\n");
        system("pause");
        Resevas(hotel);
    } else {
        printf("Quarto n�o existe.\n");
        system("pause");
        Resevas(hotel);
    }

    if (hotel.quartos[numero].reservado == 1) {
        printf("Quarto ja estar reservado para %s\n", hotel.clientes[hotel.quartos[numero].idReserva].nome);
        system("pause");
        Resevas(hotel);
    }

    char buffer[100];
    sprintf(buffer, "Numero do quarto %d / Nome do cliente: %s / Pre�o do quarto %.2f / Data da reserva %d/%d/%d", hotel.quartos[numero].numero, hotel.clientes[cliente].nome, hotel.quartos[numero].preco, hotel.tempo.tm_mday, hotel.tempo.tm_mon, hotel.tempo.tm_year);
    strcpy(hotel.historico[hotel.Contador[2]], buffer);
    hotel.Contador[4]++;

    hotel.clientes[cliente].reservado = 1;
    hotel.clientes[cliente].idReserva = numero;
    hotel.quartos[numero].idReserva = cliente;
    hotel.quartos[numero].reservado = 1;

    printf("Quarto reservado para %s.\n", hotel.clientes[cliente].nome);
    system("pause");
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

/* Adcionar mais coisas */
void detalharClientes(Hotel hotel) {
    int cliente;
    char palavraChave[20];

    system("cls");

    if (hotel.hotelIdCliente != 0) {
        printf("Informe o Id do cliente\n ");
        scanf("%d", &cliente);

        fflush(stdin);
        printf("Informe a palavra chave do cliente\n ");
        scanf("%19s", &palavraChave);

        if (strcmp(hotel.clientes[cliente].palavraChave, palavraChave) == 0) {
            system("cls");

            printf("Nome: %s\n", hotel.clientes[cliente].nome);
            printf("Cpf: %s\n", hotel.clientes[cliente].cpf);
            printf("Endere�o: %s\n", hotel.clientes[cliente].endereco);
            printf("Telefone: %s\n", hotel.clientes[cliente].telefone);

            system("pause");

            Clientes(hotel);
        } else {
            printf("Palavra chave incorreta.\n");
            system("pause");

            Clientes(hotel);
        }
    } else {
        printf("N�o a clientes registrados.\n");
    }
    system("pause");

    Clientes(hotel);
}
/* Adcionar mais coisas */
void exibirQuartos(Hotel hotel) {
    system("cls");

    if (hotel.hotelQuartos != 0) {
        for (int i = 0; i < hotel.hotelQuartos; i++) {
            if (hotel.quartos[i].existeQuarto != 0) {
                printf("===========================\n");
                printf("ID: %d - Numero: %d - Capacidade:%d - Pre�o:%.2f\n", i, hotel.quartos[i].numero, hotel.quartos[i].capacidade, hotel.quartos[i].preco);
                for (int j = 0; j < hotel.quartos[i].capacidade; j++) {
                    if (hotel.adm.adm == 1) {
                        printf("Clientes: %s\n", hotel.clientes[hotel.quartos[i].idCliente[j]].nome);
                    }
                }
                printf("===========================\n");
            }
        }
    } else {
        printf("N�o a clientes registrados.\n");
    }
    system("pause");
}

void Login(Hotel hotel) {
    char senha[20];

    system("cls");
    printf("Voc� tem %d tentativas\n", tentativasLogin);
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
            printf("Voc� excedeu o limite de tentativas.\n");
            system("pause");
            menu(hotel);
        }
        tentativasLogin--;
        Login(hotel);
    }
}

/* --------------------------------------------------------------------- */

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
        printf("4. Editar clientes\n");
        printf("5. Excluir clientes\n\n");

        printf("6. Voltar ao menu\n");
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
                system("cls");
                cadastrarCliente(hotel);
                break;
            case 4:
                editarClientes(hotel);
                break;
            case 5:
                excluirClientes(hotel);
                break;
            case 6:
                system("cls");
                printf("Voltando ao menu...\n");
                menu(hotel);
                break;
            default:
                printf("Op��o inv�lida. Tente novamente.\n");
        }

    } while (true);
}

void Quartos(Hotel hotel) {
    int opcao;

    hotel.idAux = 0;

    do {
        system("cls");

        salvarDados(hotel);

        printf("\nMenu de quartos:\n");
        printf("1. Exibir quartos\n");
        if (hotel.adm.adm == 1) {
            printf("2. Cadastrar quarto\n");
            printf("3. Excluir quarto\n");
            printf("4. Editar quartos\n");
        }

        printf("\n%d. Voltar ao menu\n", (hotel.adm.adm == 0) ? 2 : 5);
        printf("Escolha uma op��o: ");

        scanf("%d", &opcao);
        fflush(stdin);

        switch (opcao) {
            case 1:
                if (hotel.hotelQuartos != 0) {
                    exibirQuartos(hotel);
                } else {
                    printf("Nenhum quarto cadastrado.\n");
                    system("pause");
                }
                break;
            case 2:
                if (hotel.adm.adm == 1) {
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
                    excluirQuartos(hotel);
                    break;
                } else {
                    printf("Op��o inv�lida. Tente novamente.\n");
                    Quartos(hotel);
                    break;
                }

                break;
            case 4:
                if (hotel.adm.adm == 1) {
                    editarQuartos(hotel);
                    break;
                } else {
                    printf("Op��o inv�lida. Tente novamente.\n");
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
                    printf("Op��o inv�lida. Tente novamente.\n");
                    Quartos(hotel);
                    break;
                }
                break;
            default:
                printf("Op��o inv�lida. Tente novamente.\n");
        }

    } while (true);
}

void Resevas(Hotel hotel) {
    int opcao;

    hotel.idAux = 0;

    do {
        system("cls");

        salvarDados(hotel);

        printf("\nMenu de reservas:\n");
        printf("1. alugar quartos\n");
        printf("2. pagar quartos\n");
        printf("3. reservar quartos\n");
        printf("\n4. Voltar ao menu\n");
        printf("Escolha uma op��o: ");

        scanf("%d", &opcao);
        fflush(stdin);

        switch (opcao) {
            case 1:
                checkInQuarto(hotel);
                break;
            case 2:
                checkOnQuarto(hotel);
                break;
            case 3:
                reservaUmQuarto(hotel);
                break;
            case 4:
                system("cls");
                printf("Voltando ao menu...\n");
                menu(hotel);
                break;
            default:
                printf("Op��o inv�lida. Tente novamente.\n");
        }

    } while (true);
}

void historicoMenu(Hotel hotel) {
    int opcao;
    system("cls");
    do {
        salvarDados(hotel);

        printf("\nMenu:\n");
        printf("1. Historico de cliente\n");
        printf("2. Historico de quarto\n");
        printf("3. Historico de diaria\n");
        printf("4. Historico de pagamentos\n");
        printf("5. Historico de reserva\n");

        printf("\n6. Voltar ao menu\n");
        printf("Escolha uma op��o: ");
        scanf("%d", &opcao);

        fflush(stdin);

        switch (opcao) {
            case 1:
                system("cls");
                if (hotel.Contador[1] != 0) {
                    historicoDeClientes(hotel);
                    break;
                } else {
                    printf("N�o a clientes registrados.\n");
                    system("pause");
                    break;
                }
            case 2:
                system("cls");
                if (hotel.Contador[0] != 0) {
                    historicoDeQuartos(hotel);
                    break;
                } else {
                    printf("N�o a quartos registrados.\n");
                    system("pause");
                    break;
                }
            case 3:
                if (hotel.Contador[2] != 0) {
                    historicoDiaria(hotel);
                    break;
                } else {
                    printf("N�o a reservas registradas.\n");
                    system("pause");
                    break;
                }

            case 4:
                if (hotel.Contador[3] != 0) {
                    historicoDePagamento(hotel);
                    break;
                    break;
                } else {
                    printf("N�o a pagamento registradas.\n");
                    system("pause");
                    break;
                }

            case 5:
                if (hotel.Contador[4] != 0) {
                    historicoDeReservas(hotel);
                    break;
                    break;
                } else {
                    printf("N�o a pagamento registradas.\n");
                    system("pause");
                    break;
                }
            case 6:
                system("cls");
                printf("Voltando ao menu...\n");
                menu(hotel);
                break;
            default:
                printf("Op��o inv�lida. Tente novamente.\n");
        }
    } while (true);
}

void menu(Hotel hotel) {
    int opcao;
    do {
        salvarDados(hotel);

        printf("\nMenu:\n");
        printf("1. Clientes\n");
        printf("2. Quartos\n\n");

        printf("3. %s\n", (hotel.adm.adm == 0) ? "Login" : "Deslogar");
        if (hotel.adm.adm == 1) {
            printf("4. Reservas\n");
            printf("5. historicos\n");
        }
        printf("%s. Sair\n", (hotel.adm.adm == 0) ? "4" : "6");

        printf("Escolha uma op��o: ");
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
                    salvarDados(hotel);
                    printf("Saindo...\n");
                    abort();
                }
                break;
            case 5:
                if (hotel.adm.adm == 0) {
                    Resevas(hotel);
                    break;
                } else {
                    historicoMenu(hotel);
                    break;
                }
            case 6:
                if (hotel.adm.adm == 0) {
                    Resevas(hotel);
                    break;
                } else {
                    hotel.adm.adm = 0;
                    salvarDados(hotel);
                    printf("Saindo...\n");
                    abort();
                }

            default:
                printf("Op��o inv�lida. Tente novamente.\n");
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
    for (int i = 0; i < hotel.hotelQuartos; i++) {
        if (hotel.quartos[i].numero == numero) {
            return 0;
        }
    }
    return numero;
}

int buscarIdDoQuarto(int numero, Hotel hotel) {
    for (int i = 0; i < hotel.hotelQuartos; i++) {
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
    hotel.hotelIdCliente = 0;
    hotel.hotelQuartos = 0;
    for (int i = 0; i < 3; i++) {
        hotel.Contador[i] = 0;
    }

    FILE *file = fopen("hotel.bin", "rb");

    if (file == NULL) {
        printf("Arquivo n�o encontrado.\n");
    } else {
        fread(&hotel, sizeof(Hotel), 1, file);

        fclose(file);
    }

    menu(hotel);
    return 0;
}