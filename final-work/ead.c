#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include<conio.h>

//A Estrutura que armazena os dados das músicas
typedef struct musica {
    int id;
    char titulo[200];
    char artista[200];
    char album[200];
    int duracao; //segundos
} musica;

//A estrutura da lista duplamente encadeada de músicas
typedef struct musica_no {
    musica *musica;
    struct musica_no *ant;
    struct musica_no *prox;
} musica_no;

//A estrutura da lista circular de músicas de uma playlist
typedef struct playlist_no {
    musica *musica;
    struct playlist_no *prox;
} playlist_no;

//A estrutura da lista simplesmente encadeada de playlists
typedef struct lplaylists_no {
    int id;
    char nome[200];
    playlist_no *musicas;
    struct lplaylists_no *prox;
} lplaylists_no;

void menu () {
    printf("\n\n");
    int i;
    printf("------------Menu------------\n");
    printf("1 - Cadastrar nova musica\n");
    printf("2 - Listas todas as musicas\n");
    printf("3 - Criar Playlists\n");
    printf("4 - Imprimir playlist\n");
    for (i = 0; i < 50; i++)
    {
        printf("-");
    }
    printf("\n\n");
}

musica *cadastrarMusica () {
    musica *no = malloc(sizeof(musica));
    printf("Digite o id da musica: ");
    scanf("%d", &no->id);
    fflush(stdin);
    printf("Titulo da musica: ");
    gets(no->titulo);
    printf("Nome do artista: ");
    gets(no->artista);
    printf("Algum: ");
    gets(no->album);
    printf("Duracao: ");
    scanf("%d", &no->duracao);
    return no;
}


void inserirNaListDupla (musica_no *listaDupla, musica *pontM) {
    musica_no *novo;
    novo = malloc(sizeof(musica_no));
    novo->musica = pontM;
    novo->prox = listaDupla->prox;
    novo->ant = listaDupla;
    if (listaDupla->prox) listaDupla->prox->ant = novo;
    listaDupla->prox = novo;
}


void showDurationFormated (int *seg) {
    int h;
    int rest;
    int m;
    int s;
    h = *seg / 3600;
    rest = *seg % 3600;
    m = rest / 60;
    s = rest % 60;
    printf("Duracao: %02d:%02d:%02d\n\t", h, m, s);
}


void showListMusic(musica_no *listDupla) {
    musica_no *aux = listDupla->prox;
    putchar('\n');
    while (aux != NULL)
    {
        printf("Id musica: %d\n\n\t", aux->musica->id);
        printf("Titulo da musica: %s\n\t", aux->musica->titulo);
        printf("Nome do artista: %s\n\t", aux->musica->artista);
        printf("Nome do album: %s\n\t", aux->musica->album);
        showDurationFormated(&aux->musica->duracao);
        printf("\n\n");
        aux = aux->prox;
    }
}


playlist_no *montarPlayList(musica_no *listaDupla) {
    char playlist[200];
    musica_no *novo;
    char *parte;
    playlist_no *ini = malloc(sizeof(playlist_no));
    ini->prox = ini;
    playlist_no *fim = ini;
    fflush(stdin);
    printf("Digite os IDs das musicas para adicionar na playlist: ");
    gets(playlist);
    parte = (char*)strtok(playlist, " ");
    while(parte != NULL) {
        novo = listaDupla->prox;
        while (novo != NULL)
        {
            if (atoi(parte) == novo->musica->id) {
                playlist_no *novoNo = malloc(sizeof(playlist_no));
                novoNo->musica = novo->musica;
                novoNo->prox = ini->prox;
                ini->prox = novoNo;
                fim->prox = novoNo;
            }
            novo = novo->prox;
        }
        parte = (char*)strtok(NULL, " ");
    }
    return ini;
}

lplaylists_no cadastrarPlaylist(lplaylists_no *cabecaPlay, playlist_no *cabCircular, int id) {
    lplaylists_no *novoNo = malloc(sizeof(lplaylists_no));
    char nomePlaylist[200];
    fflush(stdin);
    printf("Digite o nome da playlist: ");
    gets(nomePlaylist);
    fflush(stdin);
    novoNo->id = id;
    strcpy(novoNo->nome, nomePlaylist);
    novoNo->musicas = cabCircular;
    novoNo->prox = cabecaPlay->prox;
    cabecaPlay->prox = novoNo;
}

void imprimirPlaylist (lplaylists_no *cabecaPlay, playlist_no *cab) {
    printf("\n");
    printf("\n");
    lplaylists_no *aux = cabecaPlay->prox;
    playlist_no *noPlay;
    noPlay = cab;
    while (aux) {
        printf("\tId da playlist: %d\n", aux->id);
        printf("\tNome da playlist: %d\n", aux->nome);
        do {
            printf("\tId da musica: %d\n", aux->musicas->prox->musica->id);
            printf("\tTitulo da musica: %s\n", aux->musicas->prox->musica->titulo);
            printf("\tNome do artista: %s\n", aux->musicas->prox->musica->artista);
            printf("\tNome do album: %s\n", aux->musicas->prox->musica->album);
            showDurationFormated(&aux->musicas->prox->musica->duracao);
            noPlay = noPlay->prox;
        } while (noPlay != cab);
        aux = aux->prox;
    }
}

int main () {
    setlocale(LC_ALL, "Portuguese");
    musica *m;
    musica_no *list = malloc(sizeof(musica_no));
    list->prox = NULL;
    list->ant = NULL;
    playlist_no *cabecaPlaylist = malloc(sizeof(playlist_no));
    cabecaPlaylist->prox = cabecaPlaylist;
    playlist_no *pontCab = cabecaPlaylist->prox;
    lplaylists_no *cab = malloc(sizeof(lplaylists_no));
    cab->prox = NULL;
    int op;
    int id = 0;
    while (op != 0) {
        menu();
        printf("\nDigite a opcao: ");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            m = cadastrarMusica();
            inserirNaListDupla(list, m);
            break;
        case 2:
            showListMusic(list);
            break;
        case 3:
            cabecaPlaylist = montarPlayList(list);
            cadastrarPlaylist(cab, cabecaPlaylist, id);
            id++;
            break;
        case 4:
            imprimirPlaylist(cab, cabecaPlaylist);
            break;
        default:
            printf("\nSaindo...\n");
            break;
        }
    }
    
    system("pause");
}