#include "ponto.h"

#define MAX_POINTS 1000

typedef struct{
    int qtd_pontos;
    Ponto pontos[MAX_POINTS];
}Lista_Pontos;

Lista_Pontos* criarListaPontos();
int cheiaListaPontos(Lista_Pontos *);
int addPonto(Lista_Pontos *, float x, float y);
int removerPonto(Lista_Pontos *, Ponto ponto);
void desenhaPontos(Lista_Pontos *);