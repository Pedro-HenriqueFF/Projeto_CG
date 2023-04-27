#include <stdlib.h>
#include <GL/glut.h>
#include "reta.c"
#include "listaPoligono.h"

Lista_Poligonos* criarListaPoligonos(){
    Lista_Poligonos *lpl;
    lpl = (Lista_Poligonos*)malloc(sizeof(Lista_Poligonos));
    if(lpl != NULL){
        lpl->qtd_poligonos = 0;
    }
    return lpl;
}

int cheiaListaPoligonos(Lista_Poligonos *lpl){
    if (lpl == NULL)
        return -1;
    else if (lpl->qtd_poligonos == MAX_POLYGONS)
        return 1;
    else
        return 0;
}

void inserir(PontoPoligono **antigo, Ponto ponto){
    PontoPoligono *novo;
    novo = (PontoPoligono*) malloc(sizeof(PontoPoligono));
    if(novo == NULL) exit(0);
    novo->p = ponto;
    novo->prox = NULL;
    PontoPoligono *aux;
    aux = *antigo;
    aux->prox = novo;
    *antigo = aux;
}

int addPoligono(Lista_Poligonos *lpl, int tamanho, Ponto *lpt){
    if (lpl == NULL)
        return 0;
    else if (cheiaListaPoligonos(lpl))
        return 0;
    else{
        PontoPoligono *aux;
        aux = (PontoPoligono*)malloc(sizeof(PontoPoligono));
        if(aux != NULL){
            aux->p = lpt[0];
            aux->prox = NULL;
        }
        lpl->poligonos[lpl->qtd_poligonos].tamanho = tamanho;
        lpl->poligonos[lpl->qtd_poligonos].inicial = aux;
        PontoPoligono *aux2;
        aux2 = aux;
        for (int i = 1; i < tamanho; i++){
            inserir(&aux2, lpt[i]);
            aux2 = aux2->prox;
        }
        lpl->qtd_poligonos++;
        return 1;
    }
}

int desenhaPoligonos(Lista_Poligonos *lpl){
    if (lpl == NULL)
        return 0;
    else if (cheiaListaPoligonos(lpl))
        return 0;
    else{
        glLineWidth(2.0);
        for (int i = 0; i < lpl->qtd_poligonos; i++){
            glBegin(GL_POLYGON);
            if (lpl->poligonos[i].inicial != NULL){
                PontoPoligono *aux = lpl->poligonos[i].inicial;
                for (aux; aux != NULL; aux = aux->prox){
                    glColor3f(aux->p.cor.red, aux->p.cor.green, aux->p.cor.blue);
                    glVertex2f(aux->p.x, aux->p.y);
                }
            }
            glEnd();
        }
        return 1;
    }
}