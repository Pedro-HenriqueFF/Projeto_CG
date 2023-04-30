#include <stdlib.h>
#include <GL/glut.h>
#include "ponto.c"
#include "listaReta.h"

Lista_Retas* criarListaRetas(){
    Lista_Retas *lr;
    lr = (Lista_Retas*)malloc(sizeof(Lista_Retas));
    if(lr != NULL){
        lr->qtd_retas = 0;
    }
    return lr;
}

int cheiaListaRetas(Lista_Retas *lr){
    if (lr == NULL)
        return -1;
    else if (lr->qtd_retas == MAX_LINES)
        return 1;
    else
        return 0;
}

int addReta(Lista_Retas *lr, Ponto a, Ponto b){
    if (lr == NULL)
        return 0;
    else if (cheiaListaRetas(lr))
        return 0;
    else{
        Ponto centro = { (a.x+b.x)/2, (a.y+b.y)/2, preto };
        Reta r = { a, centro, b };
        lr->retas[lr->qtd_retas] = r;
        lr->qtd_retas++;
        return 1;
    }
}

void desenhaRetas(Lista_Retas *lr){

    glLineWidth(2.0);
    glBegin(GL_LINES);
    for (int i = 0; i < lr->qtd_retas; i++){
        glColor3f(lr->retas[i].inicio.cor.red, lr->retas[i].inicio.cor.green, lr->retas[i].inicio.cor.blue); 
        glVertex2f(lr->retas[i].inicio.x, lr->retas[i].inicio.y); 
        glColor3f(lr->retas[i].fim.cor.red, lr->retas[i].fim.cor.green, lr->retas[i].fim.cor.blue);
        glVertex2f(lr->retas[i].fim.x, lr->retas[i].fim.y);
    }
    glEnd();
}