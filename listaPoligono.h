#include "poligono.h"

#define MAX_POLYGONS 1000

typedef struct{
    int qtd_poligonos;
    Poligono poligonos[MAX_POLYGONS];
}Lista_Poligonos;

Lista_Poligonos* criarListaPoligonos();
int cheiaListaPoligonos(Lista_Poligonos *);
void inserir(PontoPoligono **, Ponto ponto);
int addPoligono(Lista_Poligonos *, int tamanho, Ponto *);
int removerPoligono(Lista_Poligonos *, Poligono poligono);
int desenhaPoligonos(Lista_Poligonos *, int p, Matriz_Transformacao *);
Matriz_Transformacao* criarMatrizCompostaPoligono(Lista_Poligonos *, int p, Matriz_Transformacao *);
int escalarPoligono(Lista_Poligonos *, int p, Matriz_Transformacao *);