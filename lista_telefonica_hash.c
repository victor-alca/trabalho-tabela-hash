#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TABLE_SIZE 100

typedef struct Contato {
    char nome[50];
    char telefone[15];
    struct Contato* proximo;
} Contato;

Contato* tabela[TABLE_SIZE];

unsigned int hash(char* nome) {
    unsigned int valor = 0;
    for (int i = 0; nome[i] != '\0'; i++) {
        valor += nome[i];
    }
    return valor % TABLE_SIZE;
}

void adicionarContato() {
    char nome[50], telefone[15];
    printf("Nome: ");
    scanf("%s", nome);
    printf("Telefone: ");
    scanf("%s", telefone);

    unsigned int indice = hash(nome);
    Contato* novoContato = (Contato*)malloc(sizeof(Contato));
    strcpy(novoContato->nome, nome);
    strcpy(novoContato->telefone, telefone);
    novoContato->proximo = tabela[indice];
    tabela[indice] = novoContato;

    printf("Contato adicionado com sucesso.\n");
}

void buscarContato() {
    char nome[50];
    printf("Nome: ");
    scanf("%s", nome);

    unsigned int indice = hash(nome);
    double tempoBusca = 0;
    Contato* atual = tabela[indice];
    clock_t inicio = clock();
    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            clock_t fim = clock();
            tempoBusca = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000;
            printf("Telefone de %s: %s (tempo de busca: %.2f ms)\n", nome, atual->telefone, tempoBusca);
            return;
        }
        atual = atual->proximo;
    }
    printf("Contato nao encontrado.\n");
}

void removerContato() {
    char nome[50];
    printf("Nome: ");
    scanf("%s", nome);

    unsigned int indice = hash(nome);
    Contato* atual = tabela[indice];
    Contato* anterior = NULL;

    while (atual != NULL && strcmp(atual->nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Contato nao encontrado.\n");
        return;
    }

    if (anterior == NULL) {
        tabela[indice] = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    free(atual);
    printf("Contato removido com sucesso.\n");
}

void exibirContatos() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Contato* atual = tabela[i];
        while (atual != NULL) {
            printf("Nome: %s, Telefone: %s\n", atual->nome, atual->telefone);
            atual = atual->proximo;
        }
    }
}

int main() {
    int opcao;
    memset(tabela, 0, sizeof(tabela));

    do {
        printf("\nEscolha uma opcao:\n");
        printf("1 - Adicionar contato\n");
        printf("2 - Buscar contato por nome\n");
        printf("3 - Remover contato\n");
        printf("4 - Exibir todos os contatos\n");
        printf("0 - Sair\n");
        printf("Digite uma opcao: ");
        
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarContato();
                break;
            case 2:
                buscarContato();
                break;
            case 3:
                removerContato();
                break;
            case 4:
                exibirContatos();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
