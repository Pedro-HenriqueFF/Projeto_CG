#include <stdlib.h>
#include <GL/glut.h>
#include "listaPonto.h"

Lista_Pontos* criarListaPontos(){
    Lista_Pontos *lp;
    lp = (Lista_Pontos*)malloc(sizeof(Lista_Pontos));
    if(lp != NULL){
        lp->qtd_pontos = 0;
    }
    return lp;
}

int cheiaListaPontos(Lista_Pontos *lp){
    if (lp == NULL)
        return -1;
    else if (lp->qtd_pontos == MAX_POINTS)
        return 1;
    else
        return 0;
}

int addPonto(Lista_Pontos *lp, float mx, float my){
    if (lp == NULL)
        return 0;
    else if (cheiaListaPontos(lp))
        return 0;
    else{
        Ponto p = { mx, my, verde };
        lp->pontos[lp->qtd_pontos] = p;
        lp->qtd_pontos++;
        return 1;
    }
}

int removerPonto(Lista_Pontos *lp, int p){
    if (lp == NULL)
        return 0;
    else{
        int i = 0;
        while(i != p){
            i++;
        }
        for (int j = i; j < lp->qtd_pontos; j++){
            lp->pontos[j] = lp->pontos[j+1];
        }
        lp->qtd_pontos--;
        return 1;
    }
}

void desenhaPontos(Lista_Pontos *lp, int p){

    glPointSize(5.0);
    glBegin(GL_POINTS);
    for (int i = 0; i < lp->qtd_pontos; i++){
        if (i != p){
            glColor3f(lp->pontos[i].cor.red, lp->pontos[i].cor.green, lp->pontos[i].cor.blue);
            glVertex2f(lp->pontos[i].x, lp->pontos[i].y); 
        }
    }
    glEnd();
    if (p != -1){
        glPointSize(7.0);
        glBegin(GL_POINTS);
            glColor3f(preto.red, preto.green, preto.blue);
            glVertex2f(lp->pontos[p].x, lp->pontos[p].y); 
        glEnd();
        glPointSize(5.0);
        glBegin(GL_POINTS);
            glColor3f(lp->pontos[p].cor.red, lp->pontos[p].cor.green, lp->pontos[p].cor.blue);
            glVertex2f(lp->pontos[p].x, lp->pontos[p].y); 
        glEnd();
    }
}

int selecionaPonto(Lista_Pontos *lp, float mx, float my, int t){
    if (lp == NULL)
        return 0;
    else{
        for (int i = 0; i < lp->qtd_pontos; i++){
            if (pickPonto(lp->pontos[i].x, lp->pontos[i].y, mx, my, t)){
                return i;
            }
        }
        return -1;
    }
};

int pickPonto(float px, float py, float mx, float my, int t){
    if (mx <= px + t && mx >= px - t){
        if (my <= py + t && my >= py - t){
            return 1;
        }
    }
    return 0;
};

int transladarPonto(Lista_Pontos *lp, int p, Matriz_Transformacao *translacao){
    if (lp == NULL)
        return 0;
    else{
        Matriz_Ponto *mp = criarMatrizPonto(lp->pontos[p].x, lp->pontos[p].y);
        mp = multiplicarMatrizPonto(translacao, mp);
        lp->pontos[p].x = mp->matriz[0][0];
        lp->pontos[p].y = mp->matriz[0][1];
        return 1;
    }
}

int rotacionarPonto(Lista_Pontos *lp, int p, Matriz_Transformacao *rotacao){
    if (lp == NULL)
        return 0;
    else{
        Matriz_Ponto *mp = criarMatrizPonto(lp->pontos[p].x, lp->pontos[p].y);
        mp = multiplicarMatrizPonto(rotacao, mp);
        lp->pontos[p].x = mp->matriz[0][0];
        lp->pontos[p].y = mp->matriz[0][1];
        return 1;
    }
}