#include<stdio.h>
#include<stdlib.h>

typedef struct {
    int **adj;
    int n;
} Grafo;

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
    for (i = 0; i < 2; i++) {
        printf("Digite os IDs das 2 pessoas: ");
        scanf("%d %d", &u, &v);
        insere_aresta(g, u, v);
    }
}

void imprime_arestas(Grafo *g) {
    int u, v;
    for (u = 0; u < g->n; u++) {
        for (v = 0; v < g->n; v++) {
            if (g->adj[u][v]) {
                printf("{%d,%d}\n", u, v);
            }
            
        }
    }
}

int main () {
    Grafo *g;
    inicia_grafo(g, 50);
    le_grafo(g);
    imprime_arestas(g);
    putchar('\n');
    system("pause");
}
