#include "reta.h"

#define MAX_LINES 1000

typedef struct{
    int qtd_retas;
    Reta retas[MAX_LINES];
}Lista_Retas;

Lista_Retas* criarListaRetas();
int cheiaListaRetas(Lista_Retas *);
int addReta(Lista_Retas *, float mx, float my, int desenhando);
int removerReta(Lista_Retas *, int r);
void desenhaRetas(Lista_Retas *, int r);
int selecionaReta(Lista_Retas *lr, float mx, float my, int t);
int cohenSutherlandClip(float x1, float y1, float x2, float y2, float mx, float my, int t);
int computeCode(float x, float y, float mx, float my, int t);
int transladarReta(Lista_Retas *, int r, Matriz_Transformacao *);
Matriz_Transformacao* criarMatrizCompostaReta(Lista_Retas *, int r, Matriz_Transformacao *);
int rotacionarReta(Lista_Retas *, int r, Matriz_Transformacao *);
int escalarReta(Lista_Retas *, int r, Matriz_Transformacao *);