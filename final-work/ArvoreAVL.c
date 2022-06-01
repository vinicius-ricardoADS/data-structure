#include <stdio.h>
#include <stdlib.h>
#include "ArvoreAVL.h" //inclui os Protótipos

struct NO
{
    int info;
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

void libera_NO(struct NO *no)
{
    if (no == NULL) // se o no atual for nulo, ele não existe
        return;
    libera_NO(no->esq); // confere o filho da esquerda e se ele não for nulo irá liberar ele primeiro
    libera_NO(no->dir); // confere o filho da direita e se ele não for nulo irá liberar ele
    free(no);
    no = NULL;
    /*
    Por fim, após conferir os filhos da esquerda e da direita ele libera o no passado
    */
}

void libera_ArvAVL(ArvAVL *raiz)
{
    if (raiz == NULL) // se raiz for nula, não existem nós nela
        return;
    libera_NO(*raiz); // libera cada nó
    free(raiz);       // libera a raiz
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

int estaVazia_ArvAVL(ArvAVL *raiz)
{
    if (raiz == NULL) // verifica se o endereço está nulo
        return 1;
    if (*raiz == NULL) // verifica se o valor em si do endereço apontado está vazio
        return 1;
    return 0;
}

int totalNO_ArvAVL(ArvAVL *raiz)
{
    if (raiz == NULL) // verifica se o endereço está nulo
        return 0;
    if (*raiz == NULL) // verifica se o valor em si do endereço apontado está vazio
        return 0;
    int alt_esq = totalNO_ArvAVL(&((*raiz)->esq)); // busca no enereço apontado pela raiz o filho da esquerda e se não for nulo vai somando
    int alt_dir = totalNO_ArvAVL(&((*raiz)->dir)); // busca no enereço apontado pela raiz o filho da direita e se não for nulo vai somando
    return (alt_esq + alt_dir + 1);
    /*
        retorna a quantidade de nós presentes na arvore
    */
}

int altura_ArvAVL(ArvAVL *raiz)
{
    if (raiz == NULL) // verifica se o endereço está nulo
        return 0;
    if (*raiz == NULL) // verifica se o valor em si do endereço apontado está vazio
        return 0;
    int alt_esq = altura_ArvAVL(&((*raiz)->esq)); // busca no enereço apontado pela raiz o filho da esquerda e se não for nulo vai somando
    int alt_dir = altura_ArvAVL(&((*raiz)->dir)); // busca no enereço apontado pela raiz o filho da direita e se não for nulo vai somando
    if (alt_esq > alt_dir)
        return (alt_esq + 1);
    else
        return (alt_dir + 1);
    /*
        retorna a subarvore com a altura maior
    */
}

void preOrdem_ArvAVL(ArvAVL *raiz)
{
    if (raiz == NULL)
        return;
    if (*raiz != NULL)
    {
        // printf("%d\n",(*raiz)->info);
        // printf("No %d: %d\n",(*raiz)->info,fatorBalanceamento_NO(*raiz));
        printf("No %d: %d\n", (*raiz)->info, altura_NO(*raiz)); // mostra o conteúdo e a altura da raiz da arvore
        preOrdem_ArvAVL(&((*raiz)->esq));// irá mostrar pra cada nó da esq seu contéudo e altura
        preOrdem_ArvAVL(&((*raiz)->dir));// irá mostrar pra cada nó da dir seu contéudo e altura
    }
}

void emOrdem_ArvAVL(ArvAVL *raiz)
{
    if (raiz == NULL)
        return;
    if (*raiz != NULL)
    {
        emOrdem_ArvAVL(&((*raiz)->esq));
        // printf("%d\n",(*raiz)->info);
        printf("No %d: H(%d) fb(%d)\n", (*raiz)->info, altura_NO(*raiz), fatorBalanceamento_NO(*raiz));
        emOrdem_ArvAVL(&((*raiz)->dir));
    }
    /*
        Começa sempre pela subárvore da esquerda indo por todos os nós da esq para em seguida
        passar para os nós da dir e por fim ao não achar mais nenhum nó na subárvore da esq ele passa
        pra subárvore da dir começando pelo nós da esq
    */
}

void posOrdem_ArvAVL(ArvAVL *raiz)
{
    if (raiz == NULL)
        return;
    if (*raiz != NULL)
    {
        posOrdem_ArvAVL(&((*raiz)->esq));
        posOrdem_ArvAVL(&((*raiz)->dir));
        printf("%d\n", (*raiz)->info);
    }
    /*
        Primeiro irá visitar a subárvore da esq e processa-la
        Depois a subárvore da direita e por último visita a raiz
    */
}

int consulta_ArvAVL(ArvAVL *raiz, int valor)
{
    if (raiz == NULL)
        return 0;
    struct NO *atual = *raiz; // serve como uma variável auxiliar que aponta para a raiz da arvore;
    while (atual != NULL)
    {
        if (valor == atual->info)
        { // achou o valor inserido na arvore
            return 1;
        }
        if (valor > atual->info)
            atual = atual->dir;
            /*
                se o valor inserido for maior que o conteúdo do nó atual ele direciona a raiz para o nó
                da direita porque apenas do lado direito os valores são maiores que o pai
            */
        else
            atual = atual->esq;
            /*
                se o valor inserido for menor que o conteúdo do nó atual ele direciona a raiz para o nó
                da esquerda porque apenas do lado esquerdo os valores são menores que o pai
            */
    }
    return 0;
}

//=================================
void RotacaoLL(ArvAVL *A)
{ // LL
    printf("RotacaoLL\n");
    struct NO *B;
    B = (*A)->esq;
    (*A)->esq = B->dir;
    B->dir = *A;
    (*A)->altura = maior(altura_NO((*A)->esq), altura_NO((*A)->dir)) + 1;
    B->altura = maior(altura_NO(B->esq), (*A)->altura) + 1;
    *A = B;
}

void RotacaoRR(ArvAVL *A)
{ // RR
    printf("RotacaoRR\n");
    struct NO *B;
    B = (*A)->dir;
    (*A)->dir = B->esq;
    B->esq = (*A);
    (*A)->altura = maior(altura_NO((*A)->esq), altura_NO((*A)->dir)) + 1;
    B->altura = maior(altura_NO(B->dir), (*A)->altura) + 1;
    (*A) = B;
}

void RotacaoLR(ArvAVL *A)
{ // LR
    RotacaoRR(&(*A)->esq);
    RotacaoLL(A);
}

void RotacaoRL(ArvAVL *A)
{ // RL
    RotacaoLL(&(*A)->dir);
    RotacaoRR(A);
}

int insere_ArvAVL(ArvAVL *raiz, int valor)
{
    int res;
    if (*raiz == NULL)
    { //Árvore vazia ou nó folha
        struct NO *novo;
        novo = malloc(sizeof(struct NO));
        if (novo == NULL)
            return 0;
        novo->info = valor;
        novo->altura = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
        return 1;
    }

    struct NO *atual = *raiz;
    if (valor < atual->info)
    {
        if ((res = insere_ArvAVL(&(atual->esq), valor)) == 1)
        {
            if (fatorBalanceamento_NO(atual) >= 2)
            {
                if (valor < (*raiz)->esq->info)
                {
                    RotacaoLL(raiz);
                }
                else
                {
                    RotacaoLR(raiz);
                }
            }
        }
    }
    else
    {
        if (valor > atual->info)
        {
            if ((res = insere_ArvAVL(&(atual->dir), valor)) == 1)
            {
                if (fatorBalanceamento_NO(atual) >= 2)
                {
                    if ((*raiz)->dir->info < valor)
                    {
                        RotacaoRR(raiz);
                    }
                    else
                    {
                        RotacaoRL(raiz);
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

struct NO *procuraMenor(struct NO *atual)
{
    struct NO *no1 = atual;
    struct NO *no2 = atual->esq;
    while (no2 != NULL)
    {
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}

int remove_ArvAVL(ArvAVL *raiz, int valor)
{
    if (*raiz == NULL)
    { // valor não existe
        printf("valor n�o existe!!\n");
        return 0;
    }

    int res;
    if (valor < (*raiz)->info)
    {
        if ((res = remove_ArvAVL(&(*raiz)->esq, valor)) == 1)
        {
            if (fatorBalanceamento_NO(*raiz) >= 2)
            {
                if (altura_NO((*raiz)->dir->esq) <= altura_NO((*raiz)->dir->dir))
                    RotacaoRR(raiz);
                else
                    RotacaoRL(raiz);
            }
        }
    }

    if ((*raiz)->info < valor)
    {
        if ((res = remove_ArvAVL(&(*raiz)->dir, valor)) == 1)
        {
            if (fatorBalanceamento_NO(*raiz) >= 2)
            {
                if (altura_NO((*raiz)->esq->dir) <= altura_NO((*raiz)->esq->esq))
                    RotacaoLL(raiz);
                else
                    RotacaoLR(raiz);
            }
        }
    }

    if ((*raiz)->info == valor)
    {
        if (((*raiz)->esq == NULL || (*raiz)->dir == NULL))
        { // nó tem 1 filho ou nenhum
            struct NO *oldNode = (*raiz);
            if ((*raiz)->esq != NULL)
                *raiz = (*raiz)->esq;
            else
                *raiz = (*raiz)->dir;
            free(oldNode);
        }
        else
        { // nó tem 2 filhos
            struct NO *temp = procuraMenor((*raiz)->dir);
            (*raiz)->info = temp->info;
            remove_ArvAVL(&(*raiz)->dir, (*raiz)->info);
            if (fatorBalanceamento_NO(*raiz) >= 2)
            {
                if (altura_NO((*raiz)->esq->dir) <= altura_NO((*raiz)->esq->esq))
                    RotacaoLL(raiz);
                else
                    RotacaoLR(raiz);
            }
        }
        if (*raiz != NULL)
            (*raiz)->altura = maior(altura_NO((*raiz)->esq), altura_NO((*raiz)->dir)) + 1;
        return 1;
    }

    (*raiz)->altura = maior(altura_NO((*raiz)->esq), altura_NO((*raiz)->dir)) + 1;

    return res;
}
