#include <stdio.h>
#include <string.h>

typedef struct {
    char nome[50];
    char endereco[100];
    char telefone[15];
} Cliente;

void cadastrarCliente(Cliente *cliente) {
    printf("Digite o nome do cliente: ");
    fgets(cliente->nome, sizeof(cliente->nome), stdin);
    printf("Digite o endereço do cliente: ");
    fgets(cliente->endereco, sizeof(cliente->endereco), stdin);
    printf("Digite o telefone do cliente: ");
    fgets(cliente->telefone, sizeof(cliente->telefone), stdin);
}

void exibirCliente(Cliente cliente) {
    printf("Nome: %s", cliente.nome);
    printf("Endereço: %s", cliente.endereco);
    printf("Telefone: %s", cliente.telefone);
}

int main() {
    Cliente cliente;
    cadastrarCliente(&cliente);
    exibirCliente(cliente);
    return 0;
}
