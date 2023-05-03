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
        Ponto centro = { 0.0, 0.0, preto };
        PontoPoligono *aux;
        aux = (PontoPoligono*)malloc(sizeof(PontoPoligono));
        if(aux != NULL){
            aux->p = lpt[0];
            aux->prox = NULL;
            centro.x += aux->p.x;
            centro.y += aux->p.y;
        }
        lpl->poligonos[lpl->qtd_poligonos].tamanho = tamanho;
        lpl->poligonos[lpl->qtd_poligonos].inicial = aux;
        PontoPoligono *aux2;
        aux2 = aux;
        for (int i = 1; i < tamanho; i++){
            inserir(&aux2, lpt[i]);
            aux2 = aux2->prox;
            centro.x += aux2->p.x;
            centro.y += aux2->p.y;
        }
        centro.x /= tamanho;
        centro.y /= tamanho;
        lpl->poligonos[lpl->qtd_poligonos].centroide = centro;
        lpl->qtd_poligonos++;
        return 1;
    }
}

int removerPoligono(Lista_Poligonos *lpl, int p){
    if (lpl == NULL || lpl->qtd_poligonos == 0)
        return 0;
    else{
        for (int j = p; j < lpl->qtd_poligonos; j++){
            lpl->poligonos[j] = lpl->poligonos[j+1];
        }
        lpl->qtd_poligonos--;
        return 1;
    }
}

int desenhaPoligonos(Lista_Poligonos *lpl, int p, Matriz_Transformacao *escalar){
    if (lpl == NULL || lpl->qtd_poligonos == 0)
        return 0;
    else{
        PontoPoligono *aux;
        aux = (PontoPoligono*)malloc(sizeof(PontoPoligono));
        glLineWidth(2.0);
        for (int i = 0; i < lpl->qtd_poligonos; i++){
            if (lpl->poligonos[i].inicial != NULL && i != p){
                aux = lpl->poligonos[i].inicial;
                glBegin(GL_POLYGON);
                for (aux; aux != NULL; aux = aux->prox){
                    glColor3f(aux->p.cor.red, aux->p.cor.green, aux->p.cor.blue);
                    glVertex2f(aux->p.x, aux->p.y);
                }
                glEnd();
            }
        }
        if (p != -1){
            Matriz_Transformacao *composta = criarMatrizCompostaPoligono(lpl, p, escalar);
            Matriz_Ponto *mp = NULL;
            aux = lpl->poligonos[p].inicial;
            glLineWidth(2.0);
            glColor3f(preto.red, preto.green, preto.blue);
            glBegin(GL_POLYGON);
            for (aux; aux != NULL; aux = aux->prox){
                mp = criarMatrizPonto(aux->p.x, aux->p.y);
                mp = multiplicarMatrizPonto(composta, mp);
                glVertex2f(mp->matriz[0][0], mp->matriz[0][1]);
            }
            glEnd();
            aux = lpl->poligonos[p].inicial;
            glBegin(GL_POLYGON);
            for (aux; aux != NULL; aux = aux->prox){
                glColor3f(aux->p.cor.red, aux->p.cor.green, aux->p.cor.blue);
                glVertex2f(aux->p.x, aux->p.y);
            }
            glEnd();
        }
        return 1;
    }
}

int transladarPoligono(Lista_Poligonos *lpl, int p, Matriz_Transformacao *translacao){
    if (lpl == NULL || lpl->qtd_poligonos == 0)
        return 0;
    else{
        PontoPoligono *aux;
        aux = (PontoPoligono*)malloc(sizeof(PontoPoligono));
        float centro_x = 0.0, centro_y = 0.0;
        Matriz_Ponto *mp = NULL;
        aux = lpl->poligonos[p].inicial;
        for (aux; aux != NULL; aux = aux->prox){
            mp = criarMatrizPonto(aux->p.x, aux->p.y);
            mp = multiplicarMatrizPonto(translacao, mp);
            aux->p.x = mp->matriz[0][0];
            aux->p.y = mp->matriz[0][1];
            centro_x += aux->p.x;
            centro_y += aux->p.y;
        }
        centro_x /= lpl->poligonos[p].tamanho;
        centro_y /= lpl->poligonos[p].tamanho;
        lpl->poligonos[p].centroide.x = centro_x;
        lpl->poligonos[p].centroide.y = centro_y;
        return 1;
    }
}

Matriz_Transformacao* criarMatrizCompostaPoligono(Lista_Poligonos *lpl, int p, Matriz_Transformacao *mt){
    if (lpl == NULL || lpl->qtd_poligonos == 0)
        return 0;
    else{
        Matriz_Transformacao *composta = criarMatrizTransformacao();
        Matriz_Transformacao *poligonoCentro = criarMatrizTranslacao(
            0 - lpl->poligonos[p].centroide.x, 
            0 - lpl->poligonos[p].centroide.y
        );
        Matriz_Transformacao *centroPoligono = criarMatrizTranslacao(
            lpl->poligonos[p].centroide.x, 
            lpl->poligonos[p].centroide.y
        );
        composta = multiplicarMatrizesTransformacao(centroPoligono, mt);
        composta = multiplicarMatrizesTransformacao(composta, poligonoCentro);
        return composta;
    }
}

int rotacionarPoligono(Lista_Poligonos *lpl, int p, Matriz_Transformacao *rotacao){
    if (lpl == NULL || lpl->qtd_poligonos == 0)
        return 0;
    else{
        Matriz_Transformacao *composta = criarMatrizCompostaPoligono(lpl, p, rotacao);
        PontoPoligono *aux;
        aux = (PontoPoligono*)malloc(sizeof(PontoPoligono));
        Matriz_Ponto *mp = NULL;
        aux = lpl->poligonos[p].inicial;
        for (aux; aux != NULL; aux = aux->prox){
            mp = criarMatrizPonto(aux->p.x, aux->p.y);
            mp = multiplicarMatrizPonto(composta, mp);
            aux->p.x = mp->matriz[0][0];
            aux->p.y = mp->matriz[0][1];
        }
        return 1;
    }
}

int escalarPoligono(Lista_Poligonos *lpl, int p, Matriz_Transformacao *escalar){
    if (lpl == NULL || lpl->qtd_poligonos == 0)
        return 0;
    else{
        Matriz_Transformacao *composta = criarMatrizCompostaPoligono(lpl, p, escalar);
        PontoPoligono *aux;
        aux = (PontoPoligono*)malloc(sizeof(PontoPoligono));
        float centro_x = 0.0, centro_y = 0.0;
        Matriz_Ponto *mp = NULL;
        aux = lpl->poligonos[p].inicial;
        for (aux; aux != NULL; aux = aux->prox){
            mp = criarMatrizPonto(aux->p.x, aux->p.y);
            mp = multiplicarMatrizPonto(composta, mp);
            aux->p.x = mp->matriz[0][0];
            aux->p.y = mp->matriz[0][1];
        }
        return 1;
    }
}