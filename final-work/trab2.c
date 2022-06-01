#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int **adj;
    int n;
} Grafo;

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
        printf("\n\nID da pessoa:  %d \n", (*raiz)->pessoas->id);
        printf("CPF da pessoa: %s \n", (*raiz)->pessoas->CPF);
        printf("NOME da pessoa:  %s \n", (*raiz)->pessoas->nome);
        printf("SOBRENOME da pessoa %s \n", (*raiz)->pessoas->sobrenome);
        printf("----------------------------------------------\n");
        emOrdem_ArvAVL(&((*raiz)->dir));
    }
    /*
        Começa sempre pela subárvore da esquerda indo por todos os nós da esq para em seguida
        passar para os nós da dir e por fim ao não achar mais nenhum nó na subárvore da esq ele passa
        pra subárvore da dir começando pelo nós da esq
    */
}

void verificarIdPessoa(ArvAVL *raiz, int id)
{
    if (raiz == NULL)
        return;
    if (*raiz != NULL)
    {
        verificarIdPessoa(&((*raiz)->esq), id);
        if ((*raiz)->pessoas->id == id) {
            printf("NOME da pessoa:  %s \n", (*raiz)->pessoas->nome);
        }
        verificarIdPessoa(&((*raiz)->dir), id);
        
    }
}

void inicia_grafo(Grafo *g, int n) {
    int i, j;
    g->n = n;
    g->adj = malloc(n * sizeof(int *));
    for (i = 0; i < n; i++)
        g->adj[i] = malloc(n * sizeof(int));
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            g->adj[i][j] = 0;
}

void insere_aresta (Grafo *g, int u, int v) {
    g->adj[u][v] = 1;
    g->adj[v][u] = 1;
}

void le_grafo(Grafo *g) {
    int m, i, u, v;
    printf("Digite quantas amizades quer relacionar: ");
    scanf("%d", &m);
    for (i = 0; i < m; i++) {
        printf("Digite os IDs de 2 pessoas: ");
        scanf("%d %d", &u, &v);
        insere_aresta(g, u, v);
    }
}

void imprime_amigos(Grafo *g, ArvAVL *raiz, int id) {
    int u, v;
    for (v = 0; v < g->n; v++) {
        if (v != id) {
            if (g->adj[id][v]) {
                verificarIdPessoa(raiz,v);
            }   
        }
    }
}

void imprime_amigosDosAMigos(Grafo *g, ArvAVL *raiz) {
    int u, v, id;
    printf("Digite o id de quem deseja ver os amigos dos amigos dessa pessoa: ");
    scanf("%d", &id);
    for (v = 0; v < g->n; v++) {
        if (g->adj[id][v]) {
            imprime_amigos(g,raiz, v);
        }
    }
}

int tem_aresta(Grafo g, int u, int v) {
    return g.adj[u][v];
}

void menu() {
    int i;
    for (i = 0; i < 50; i++)
    {
        putchar('-');
    }
    printf("\n\t Menu de opcoes \n\t");
    printf("1 - Cadastrar pessoa\n");
    printf("\t2 - Imprimir pessoas\n");
    printf("\t3 - Cadastrar uma amizade entre 2 pessoas\n");
    printf("\t4 - Exibir amizades de uma pessoa\n");
    printf("\t5 - Exibir amizades das amizades de uma pessoa\n");
    for (i = 0; i < 50; i++)
    {
        putchar('-');
    }
    
}

int main () {
    Grafo *g = malloc(sizeof(Grafo));
    inicia_grafo(g, 50);
    int idPessoa= 1;
    int idArvoreAVL = 1;
    int res;
    int idVerAMigos;
    ArvAVL* avl;
    avl = cria_ArvAVL();
    pessoa *p;
    int op;
    while (op != 0) {
        menu();
        printf("\nDigite a opcao: ");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            p = ler_pessoa(idPessoa);
            idPessoa++;
            res = insere_ArvAVL(avl,p, idArvoreAVL);
            idArvoreAVL++;
            break;
        case 2:
            emOrdem_ArvAVL(avl);
            break;
        case 3:
            
            le_grafo(g);
            break;
        case 4:
            printf("Digite o id de quem deseja ver as amizades: ");
            scanf("%d", &idVerAMigos);
            imprime_amigos(g, avl, idVerAMigos);
            break;
        case 5:
            imprime_amigosDosAMigos(g, avl);
            break;
        default:
            printf("\nSaindo...\n");
            break;
        }
    }
}