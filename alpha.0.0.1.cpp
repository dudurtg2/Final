#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct {
    int codigo;
    char nome[50];
    char cpf[15];
    char telefone[15];
    char email[50];
} Cliente;

struct {
    int numero;
    int capacidade;
    float diaria;
    int disponivel;
} Quarto;

void cadastrar_cliente();
void cadastrar_quarto();
void cadastrar_reserva();
void listar_clientes();
void listar_quartos();
void listar_reservas();
void buscar_cliente();
void buscar_quarto();
void buscar_reserva();
void excluir_cliente();
void excluir_quarto();
void excluir_reserva();
void salvar_dados();
void carregar_dados();
void menu();

int main()
{
    menu();
}

void menu(){

}

