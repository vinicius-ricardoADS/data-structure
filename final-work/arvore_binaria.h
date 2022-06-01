#ifndef ARVORE_BINARIA_H
#define ARVORE_BINARIA_H

typedef struct no {
    int dado;
    struct no *esq, *dir;
} No;

typedef struct nopilha {
    No *no_arv;
    struct nopilha *prox;
} NoPilha;

typedef struct nopilhaint {
    int dado;
    struct nopilhaint *prox;
} NoPilhaInt;

// Criar um novo nó passando um valor e dois nós
No *criar_arvore(int x, No *esq, No *dir);

// Procurar o no com valor x na árvore e retornar seu endereço
No *procurar_no(No *arvore, int x);

int numero_nos(No *arvore);

int altura(No *arvore);

NoPilha * criaPilha();

void push (NoPilha *pilha, No *no_arv);

No * pop(NoPilha *pilha);


NoPilhaInt * criaPilhaInt();

void pushInt (NoPilhaInt *pilha, int dado);

int popInt(NoPilhaInt *pilha);

int numero_nos_nrec(No *arvore);

int altura_nrec(No *arvore);

#endif