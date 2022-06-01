#include "arvore_binaria.h"
#include <stdio.h>
#include <stdlib.h>


No *criar_arvore(int x, No *esq, No *dir) {
    No *r;
    r = malloc(sizeof(No));
    r->dado = x;
    r->esq = esq;
    r->dir = dir;
    return r;
}

// Procurar o no com valor x na árvore e retornar seu endereço
No *procurar_no(No *arvore, int x) {
    No *esq;
    if (arvore == NULL || arvore->dado == x)
        return arvore;
    esq = procurar_no(arvore->esq, x);
    if (esq != NULL)
        return esq;
    return procurar_no(arvore->dir, x);
}

int numero_nos(No *arvore) {
    if (arvore == NULL)
        return 0;
    return (numero_nos(arvore->esq) + numero_nos(arvore->dir) + 1);
}

int altura(No *arvore) {
    int h_esq = 0;
    int h_dir = 0;
    if (arvore == NULL)
        return 0;
    h_esq = altura(arvore->esq);
    h_dir = altura(arvore->dir);
    if (h_esq > h_dir) {
        return 1 + h_esq;
    } else {
        return 1 + h_dir;
    }
}

NoPilha * criaPilha() {
    NoPilha * nova;
    nova = malloc(sizeof(NoPilha));
    nova->prox = NULL;
    return nova;
}

void push (NoPilha *pilha, No *no_arv) {
    if (no_arv) {
        NoPilha *novo = malloc(sizeof(NoPilha));
        novo->no_arv = no_arv;
        novo->prox = pilha->prox;
        pilha->prox = novo;
    }
}

No * pop(NoPilha *pilha) {
    if (pilha->prox) {
        NoPilha *apagar = pilha->prox;
        No * retornar = apagar->no_arv;
        pilha->prox = apagar->prox;
        free(apagar);
        return retornar;
    }
    else {
        return NULL;
    }
}

NoPilhaInt * criaPilhaInt() {
    NoPilhaInt * nova;
    nova = malloc(sizeof(NoPilhaInt));
    nova->prox = NULL;
    return nova;
}

void pushInt (NoPilhaInt *pilha, int dado) {
    NoPilhaInt *novo = malloc(sizeof(NoPilha));
    novo->dado = dado;
    novo->prox = pilha->prox;
    pilha->prox = novo;
}


int popInt(NoPilhaInt *pilha) {
    if (pilha->prox) {
        NoPilhaInt *apagar = pilha->prox;
        int retornar = apagar->dado;
        pilha->prox = pilha->prox->prox;
        free(apagar);
        return retornar;
    }
    else {
        return 0;
    }
}

int numero_nos_nrec(No *arvore) {
    NoPilha *pilha = criaPilha();
    No *atual = arvore;
    int count = 0;
    while (atual != NULL) {
        count++;
        push(pilha, atual->esq);
        push(pilha, atual->dir);
        atual = pop(pilha);
    }
    free(pilha);
    return count;
}

int altura_nrec(No *arvore) {
    NoPilha *pilha = criaPilha();
    NoPilhaInt *pilhaInt = criaPilhaInt();
    No *atual = arvore;
    int alturaAtual = 1;
    int alturaMax = 0;
    while (atual != NULL) {
        if (atual->esq != NULL) {
            push(pilha, atual->esq);
            pushInt(pilhaInt, alturaAtual+1);
        }
        if (atual->dir != NULL) {
            push(pilha, atual->dir);
            pushInt(pilhaInt, alturaAtual+1);
        }
        atual = pop(pilha);
        alturaAtual = popInt(pilhaInt);
        if (alturaAtual > alturaMax) alturaMax = alturaAtual; 
    }
    free(pilha);
    free(pilhaInt);
    return alturaMax;
}



int main() {
    No *no1;
    no1 = criar_arvore(1, criar_arvore(0, NULL, NULL), NULL);
    No *no3;
    no3 = criar_arvore(3, NULL, NULL);
    No *no2 = criar_arvore(2, no1, no3);
    No *no6 = criar_arvore(6,
    criar_arvore(5, NULL, NULL),
    criar_arvore(7, NULL, NULL));
    No *raiz = criar_arvore(4, no2, no6);
    No *busca;

    busca = procurar_no(raiz, 5);
    if (busca) {
        printf("Encontrei o no %d no endereço %p\n", busca->dado, busca);
    }

    printf("O numero de nos da arvore eh %d\n", numero_nos(raiz));
    printf("NREC - O numero de nos da arvore eh %d\n", numero_nos_nrec(raiz));


    printf("A altura da arvore eh: %d\n", altura(raiz));
    printf("NREC - A altura da arvore eh: %d\n", altura_nrec(raiz));

    system("pause");

}