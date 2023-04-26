#include <stdlib.h>
#include <GL/glut.h>
#include "ponto.h"

Cor preto = { 0.0, 0.0, 0.0 };

struct lista{
    int qtd_pontos;
    Ponto pontos[MAX_POINTS];
};

Lista_Pontos* criar(){
    Lista_Pontos *lp;
    lp = (Lista_Pontos*)malloc(sizeof(Lista_Pontos));
    if(lp != NULL){
        lp->qtd_pontos = 0;
    }
    return lp;
}

int cheia(Lista_Pontos *lp){
    if (lp == NULL)
        return -1;
    else if (lp->qtd_pontos == MAX_POINTS)
        return 1;
    else
        return 0;
}

int addPonto(Lista_Pontos *lp, float x, float y){
    if (lp == NULL)
        return 0;
    else if (cheia(lp))
        return 0;
    else{
        Ponto p = { x, y, preto };
        lp->pontos[lp->qtd_pontos] = p;
        lp->qtd_pontos++;
        return 1;
    }
}

void desenhaPontos(Lista_Pontos *lp){

    glPointSize(5.0);
    glBegin(GL_POINTS);
    for (int i = 0; i < lp->qtd_pontos; i++){
        glColor3f(lp->pontos[i].cor.red, lp->pontos[i].cor.green, lp->pontos[i].cor.blue);
        glVertex2f(lp->pontos[i].x, lp->pontos[i].y); 
    }
    glEnd();
}