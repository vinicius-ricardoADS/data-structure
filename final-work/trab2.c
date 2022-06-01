#include <stdio.h>
#include <stdlib.h>

typedef struct pessoa {
    int id;
    char CPF[12];
    char nome[200];
    char sobrenome[200];
} pessoa;

typedef struct NO* ArvAVL;

struct NO
{
    int id;
    pessoa *pessoas;
    int altura;
    struct NO *esq;
    struct NO *dir;
};

ArvAVL *cria_ArvAVL()
{
    ArvAVL *raiz = malloc(sizeof(ArvAVL));
    if (raiz != NULL) // verifica se a raiz tem algum tipo de valor, se tiver ela recebe NULL pelo fato de que a raiz precisa ser vazia
        *raiz = NULL;
    return raiz;
}

pessoa* ler_pessoa (int id) {
    pessoa *no = malloc(sizeof(pessoa));
    no->id = id;
    fflush(stdin);
    printf("CPF: ");
    gets(no->CPF);
    printf("Nome: ");
    gets(no->nome);
    printf("Sobrenome: ");
    gets(no->sobrenome);
    return no;
}

int maior(int x, int y)
{
    if (x > y)
        return x;
    else
        return y;
    /*
        compara entre os dois valores passados qual é o maior entre eles
    */
}

int altura_NO(struct NO *no)
{
    if (no == NULL)
        return -1; // se ele for nulo, ou seja não existe, retorna -1
    else
        return no->altura; // senão retorna o valor da altura dele
}

int fatorBalanceamento_NO(struct NO *no)
{
    return labs(altura_NO(no->esq) - altura_NO(no->dir)); // retorna a diferença da altura da esq entre a dir
}

void RotacaoLL(ArvAVL *A)
{
    struct NO *B;
    B = (*A)->esq;
    (*A)->esq = B->dir;
    B->dir = *A;
    (*A)->altura = maior(altura_NO((*A)->esq), altura_NO((*A)->dir)) + 1;
    B->altura = maior(altura_NO(B->esq), (*A)->altura) + 1;
    *A = B;
}

void RotacaoRR(ArvAVL *A)
{
    struct NO *B;
    B = (*A)->dir;
    (*A)->dir = B->esq;
    B->esq = (*A);
    (*A)->altura = maior(altura_NO((*A)->esq), altura_NO((*A)->dir)) + 1;
    B->altura = maior(altura_NO(B->dir), (*A)->altura) + 1;
    (*A) = B;
}

int insere_ArvAVL(ArvAVL *raiz, pessoa *p, int id)
{
    int res;
    if (*raiz == NULL)
    { //Árvore vazia ou nó folha
        struct NO *novo;
        novo = malloc(sizeof(struct NO));
        if (novo == NULL)
            return 0;
        novo->id = id;
        novo->pessoas = p;
        novo->altura = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
        return 1;
    }

    struct NO *atual = *raiz;
    if (p->id < atual->pessoas->id)
    {
        if ((res = insere_ArvAVL(&(atual->esq), p, id)) == 1)
        {
            if (fatorBalanceamento_NO(atual) >= 2)
            {
                if (p->id < (*raiz)->esq->pessoas->id)
                {
                    RotacaoLL(raiz);
                }
                else
                {
                    RotacaoRR(raiz);
                }
            }
        }
    }
    else
    {
        if (p->id > atual->pessoas->id)
        {
            if ((res = insere_ArvAVL(&(atual->dir), p, id)) == 1)
            {
                if (fatorBalanceamento_NO(atual) >= 2)
                {
                    if ((*raiz)->dir->pessoas->id < p->id)
                    {
                        RotacaoRR(raiz);
                    }
                    else
                    {
                        RotacaoLL(raiz);
                    }
                }
            }
        }
        else
        {
            printf("Valor duplicado!!\n");
            return 0;
        }
    }

    atual->altura = maior(altura_NO(atual->esq), altura_NO(atual->dir)) + 1;

    return res;
}

void emOrdem_ArvAVL(ArvAVL *raiz)
{
    if (raiz == NULL)
        return;
    if (*raiz != NULL)
    {
        emOrdem_ArvAVL(&((*raiz)->esq));
        printf("\n\nID da pessoa:  %d: \n", (*raiz)->pessoas->id);
        printf("CPF da pessoa: %s: \n", (*raiz)->pessoas->CPF);
        printf("NOME da pessoa:  %s: \n", (*raiz)->pessoas->nome);
        printf("SOBRENOME da pessoa: %s: \n", (*raiz)->pessoas->sobrenome);
        printf("----------------------------------------------\n");
        emOrdem_ArvAVL(&((*raiz)->dir));
    }
    /*
        Começa sempre pela subárvore da esquerda indo por todos os nós da esq para em seguida
        passar para os nós da dir e por fim ao não achar mais nenhum nó na subárvore da esq ele passa
        pra subárvore da dir começando pelo nós da esq
    */
}

int main () {
    int idPessoa= 0;
    int idArvoreAVL = 0;
    int res;
    ArvAVL* avl;
    avl = cria_ArvAVL();
    pessoa *p;
    int op;
    while (op != 0) {
        printf("\nDigite a opcao: ");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            /* p = cadastrarPessoa(idPessoa);
            idPessoa++;
            res = insere_ArvAVL(avl,p, idArvoreAVL);
            idArvoreAVL++; */
            p = ler_pessoa(idPessoa);
            idPessoa++;
            res = insere_ArvAVL(avl,p, idArvoreAVL);
            idArvoreAVL++;
            /* inserir_AVL(&avl, p, idArvoreAVL);
            idPessoa++;
            idArvoreAVL++; */
            break;
        case 2:
            emOrdem_ArvAVL(avl);
            break;
        default:
            printf("\nSaindo...\n");
            break;
        }
    }
}