#include "poligono.h"

#define MAX_POLYGONS 1000

typedef struct{
    int qtd_poligonos;
    Poligono poligonos[MAX_POLYGONS];
}Lista_Poligonos;

Lista_Poligonos* criarListaPoligonos();
int cheiaListaPoligonos(Lista_Poligonos *);
int finalizaPoligono(Lista_Poligonos *, int desenhando);
int addPoligono(Lista_Poligonos *, float mx, float my, int desenhando);
void inserir(PontoPoligono **, float x, float y);
int removerPoligono(Lista_Poligonos *, int p);
int desenhaPoligonos(Lista_Poligonos *, int p, Matriz_Transformacao *);
int transladarPoligono(Lista_Poligonos *, int p, Matriz_Transformacao *);
Matriz_Transformacao* criarMatrizCompostaPoligono(Lista_Poligonos *, int p, Matriz_Transformacao *);
int rotacionarPoligono(Lista_Poligonos *, int p, Matriz_Transformacao *);
int escalarPoligono(Lista_Poligonos *, int p, Matriz_Transformacao *);