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

int addReta(Lista_Retas *lr, float mx, float my, int desenhando){
    if (lr == NULL)
        return 0;
    else if (cheiaListaRetas(lr))
        return 0;
    else{
        if(desenhando == -1){
            lr->retas[lr->qtd_retas].inicio.x = mx;
            lr->retas[lr->qtd_retas].inicio.y = my;
            lr->retas[lr->qtd_retas].inicio.cor = vermelho;
            return 1;
        }else{
            lr->retas[lr->qtd_retas].fim.x = mx;
            lr->retas[lr->qtd_retas].fim.y = my;
            lr->retas[lr->qtd_retas].fim.cor = vermelho;
            lr->retas[lr->qtd_retas].centro.x = (lr->retas[lr->qtd_retas].inicio.x + lr->retas[lr->qtd_retas].fim.x)/2;
            lr->retas[lr->qtd_retas].centro.y = (lr->retas[lr->qtd_retas].inicio.y + lr->retas[lr->qtd_retas].fim.y)/2;
            lr->retas[lr->qtd_retas].centro.cor = preto;
            lr->qtd_retas++;
            return -1;
        }
    }
}

int removerReta(Lista_Retas *lr, int r){
    if (lr == NULL || lr->qtd_retas == 0)
        return 0;
    else{
        for (int j = r; j < lr->qtd_retas; j++){
            lr->retas[j] = lr->retas[j+1];
        }
        lr->qtd_retas--;
        return 1;
    }
}

void desenhaRetas(Lista_Retas *lr, int r){
    glLineWidth(2.0);
    glBegin(GL_LINES);
    for (int i = 0; i < lr->qtd_retas; i++){
        if (i != r){
            glColor3f(lr->retas[i].inicio.cor.red, lr->retas[i].inicio.cor.green, lr->retas[i].inicio.cor.blue); 
            glVertex2f(lr->retas[i].inicio.x, lr->retas[i].inicio.y); 
            glColor3f(lr->retas[i].fim.cor.red, lr->retas[i].fim.cor.green, lr->retas[i].fim.cor.blue);
            glVertex2f(lr->retas[i].fim.x, lr->retas[i].fim.y);
        }
    }
    glEnd();
    if (r != -1){
        glLineWidth(4.0);
        glBegin(GL_LINES);
            glColor3f(preto.red, preto.green, preto.blue);
            glVertex2f(lr->retas[r].inicio.x, lr->retas[r].inicio.y);
            glVertex2f(lr->retas[r].fim.x, lr->retas[r].fim.y); 
        glEnd();
        glLineWidth(2.0);
        glBegin(GL_LINES);
            glColor3f(lr->retas[r].inicio.cor.red, lr->retas[r].inicio.cor.green, lr->retas[r].inicio.cor.blue); 
            glVertex2f(lr->retas[r].inicio.x, lr->retas[r].inicio.y); 
            glColor3f(lr->retas[r].fim.cor.red, lr->retas[r].fim.cor.green, lr->retas[r].fim.cor.blue);
            glVertex2f(lr->retas[r].fim.x, lr->retas[r].fim.y);
        glEnd();
    }
}

int transladarReta(Lista_Retas *lr, int r, Matriz_Transformacao *translacao){
    if (lr == NULL || lr->qtd_retas == 0)
        return 0;
    else{
        Matriz_Ponto *mp1 = criarMatrizPonto(lr->retas[r].inicio.x, lr->retas[r].inicio.y);
        Matriz_Ponto *mp2 = criarMatrizPonto(lr->retas[r].fim.x, lr->retas[r].fim.y);
        mp1 = multiplicarMatrizPonto(translacao, mp1);
        mp2 = multiplicarMatrizPonto(translacao, mp2);
        lr->retas[r].inicio.x = mp1->matriz[0][0];
        lr->retas[r].inicio.y = mp1->matriz[0][1];
        lr->retas[r].fim.x = mp2->matriz[0][0];
        lr->retas[r].fim.y = mp2->matriz[0][1];
        lr->retas[r].centro.x = (lr->retas[r].inicio.x + lr->retas[r].fim.x)/2;
        lr->retas[r].centro.y = (lr->retas[r].inicio.y + lr->retas[r].fim.y)/2;
        return 1;
    }
}

Matriz_Transformacao* criarMatrizCompostaReta(Lista_Retas *lr, int r, Matriz_Transformacao *mt){
    if (lr == NULL || lr->qtd_retas == 0)
        return 0;
    else{
        Matriz_Transformacao *composta = criarMatrizTransformacao();
        Matriz_Transformacao *retaCentro = criarMatrizTranslacao(
            0 - lr->retas[r].centro.x, 
            0 - lr->retas[r].centro.y
        );
        Matriz_Transformacao *centroReta = criarMatrizTranslacao(
            lr->retas[r].centro.x, 
            lr->retas[r].centro.y
        );
        composta = multiplicarMatrizesTransformacao(centroReta, mt);
        composta = multiplicarMatrizesTransformacao(composta, retaCentro);
        return composta;
    }
}

int rotacionarReta(Lista_Retas *lr, int r, Matriz_Transformacao *rotacao){
    if (lr == NULL || lr->qtd_retas == 0)
        return 0;
    else{
        Matriz_Transformacao *composta = criarMatrizCompostaReta(lr, r, rotacao);
        Matriz_Ponto *mp1 = criarMatrizPonto(lr->retas[r].inicio.x, lr->retas[r].inicio.y);
        Matriz_Ponto *mp2 = criarMatrizPonto(lr->retas[r].fim.x, lr->retas[r].fim.y);
        mp1 = multiplicarMatrizPonto(composta, mp1);
        mp2 = multiplicarMatrizPonto(composta, mp2);
        lr->retas[r].inicio.x = mp1->matriz[0][0];
        lr->retas[r].inicio.y = mp1->matriz[0][1];
        lr->retas[r].fim.x = mp2->matriz[0][0];
        lr->retas[r].fim.y = mp2->matriz[0][1];
        return 1;
    }
}

int escalarReta(Lista_Retas *lr, int r, Matriz_Transformacao *escalar){
    if (lr == NULL || lr->qtd_retas == 0)
        return 0;
    else{
        Matriz_Transformacao *composta = criarMatrizCompostaReta(lr, r, escalar);
        Matriz_Ponto *mp1 = criarMatrizPonto(lr->retas[r].inicio.x, lr->retas[r].inicio.y);
        Matriz_Ponto *mp2 = criarMatrizPonto(lr->retas[r].fim.x, lr->retas[r].fim.y);
        mp1 = multiplicarMatrizPonto(composta, mp1);
        mp2 = multiplicarMatrizPonto(composta, mp2);
        lr->retas[r].inicio.x = mp1->matriz[0][0];
        lr->retas[r].inicio.y = mp1->matriz[0][1];
        lr->retas[r].fim.x = mp2->matriz[0][0];
        lr->retas[r].fim.y = mp2->matriz[0][1];
        return 1;
    }
}