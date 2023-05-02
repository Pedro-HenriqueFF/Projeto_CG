#include <stdlib.h>
#include <GL/glut.h>
#include "matriz.h"

Matriz_Transformacao* criarMatrizTransformacao(){
    Matriz_Transformacao *mt;
    mt = (Matriz_Transformacao*)malloc(sizeof(Matriz_Transformacao));
    if(mt != NULL){
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                if(i == j) mt->matriz[i][j] = 1;
                else mt->matriz[i][j] = 0;
            }
        }
    }
    return mt;
}

Matriz_Ponto* criarMatrizPonto(float x, float y){
    Matriz_Ponto *mp;
    mp = (Matriz_Ponto*)malloc(sizeof(Matriz_Ponto));
    if(mp != NULL){
        mp->matriz[0][0] = x;
        mp->matriz[1][0] = y;
        mp->matriz[2][0] = 1.0;
    }
    return mp;
}

Matriz_Transformacao* criarMatrizTranslacao(float tx, float ty){
    Matriz_Transformacao *mt = criarMatrizTransformacao();
    mt->matriz[0][2] = tx;
    mt->matriz[1][2] = ty;
    return mt;
}

Matriz_Transformacao* criarMatrizRotacao(float theta){
    Matriz_Transformacao *mr = criarMatrizTransformacao();
    mr->matriz[0][0] = cosf(theta);
    mr->matriz[0][1] = -sinf(theta);
    mr->matriz[1][0] = sinf(theta);
    mr->matriz[1][1] = cosf(theta);
    return mr;
}

Matriz_Transformacao* multiplicarMatrizesTransformacao(Matriz_Transformacao *mt1, Matriz_Transformacao *mt2){
    if (mt1 == NULL || mt2 == NULL)
        return 0;
    else{
        Matriz_Transformacao *composta = criarMatrizTransformacao();
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                composta->matriz[i][j] = mt1->matriz[i][0]*mt2->matriz[0][j] + mt1->matriz[i][1]*mt2->matriz[1][j] + mt1->matriz[i][2]*mt2->matriz[2][j];
            }
        }
        return composta;
    }
}

Matriz_Ponto* multiplicarMatrizPonto(Matriz_Transformacao *mt, Matriz_Ponto *mp){
    if (mt == NULL || mp == NULL)
        return 0;
    else{
        Matriz_Ponto *composta = criarMatrizPonto(0, 0);
        for (int i = 0; i < 3; i++){
            composta->matriz[i][0] = mt->matriz[i][0]*mp->matriz[0][0] + mt->matriz[i][1]*mp->matriz[1][0] + mt->matriz[i][2]*mp->matriz[2][0];
        }
        return composta;
    }
}