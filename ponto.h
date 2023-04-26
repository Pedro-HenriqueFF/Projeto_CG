#include "cor.h"

#define MAX_POINTS 1000

typedef struct{
    float x;
    float y;
    Cor cor;
}Ponto;

typedef struct lista Lista_Pontos;

Lista_Pontos* criar();
int cheia(Lista_Pontos *);
int addPonto(Lista_Pontos *, float x, float y);
int removerPonto(Lista_Pontos *, Ponto ponto);
void desenhaPontos(Lista_Pontos *);