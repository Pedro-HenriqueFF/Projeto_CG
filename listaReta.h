#include "reta.h"

#define MAX_LINES 1000

typedef struct{
    int qtd_retas;
    Reta retas[MAX_LINES];
}Lista_Retas;

Lista_Retas* criarListaRetas();
int cheiaListaRetas(Lista_Retas *);
int addReta(Lista_Retas *, Ponto a, Ponto b);
int removerReta(Lista_Retas *, int r);
void desenhaRetas(Lista_Retas *, int r);
int transladarReta(Lista_Retas *, int r, Matriz_Transformacao *);
int rotacionarReta(Lista_Retas *, int r, Matriz_Transformacao *);
