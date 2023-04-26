#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "ponto.h"

Lista_Pontos *Pontos = NULL;

void display(){

    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    desenhaPontos(Pontos);

    glFlush(); //desenha os comandos não executados
}

void init(){

    glClearColor(1.0, 1.0, 1.0, 1.0); //define a cor de fundo

    glMatrixMode(GL_PROJECTION); //carrega a matriz de projeção
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); //define a projeção ortogonal 2D

    //adiciona pontos (0, 0) e o (0, 0.5)
    addPonto(Pontos, 0, 0);
    addPonto(Pontos, 0, 0.5);
    addPonto(Pontos, 0.5, 0.5);
    addPonto(Pontos, 0, -0.5);
    addPonto(Pontos, -0.5, 0);
    addPonto(Pontos, -0.5, -0.5);

    /*as funções de adicionar ficarão dentro das funções de evento (por exemplo, clique do mouse)
      que irão realizar o adicionar objetos geométricos (pontos, linhas e polígonos)
     */
}

int main(int argc, char** argv){

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Pontos e Retas com OpenGL");

    Pontos = criar();

    init();

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
