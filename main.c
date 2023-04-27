#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "poligono.c"

Lista_Pontos *Pontos = NULL;
Lista_Retas *Retas = NULL;
Lista_Poligonos *Poligonos = NULL;

void display(){

    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    desenhaPoligonos(Poligonos);
    desenhaRetas(Retas);
    desenhaPontos(Pontos);

    glFlush(); 
}

void init(){

    glClearColor(1.0, 1.0, 1.0, 1.0); 

    glMatrixMode(GL_PROJECTION); 
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); 

    addPonto(Pontos, 0, 0);
    addPonto(Pontos, 0, 0.5);
    addPonto(Pontos, 0.5, 0.5);
    addPonto(Pontos, 0, -0.5);
    addPonto(Pontos, -0.5, 0);
    addPonto(Pontos, -0.5, -0.5);

    Ponto A = { -0.5, 0.3, vermelho }, B = { 0.5, -0.1, vermelho };
    addReta(Retas, A, B);
    Ponto C = { -0.5, -0.7, vermelho }, D = { -0.1, 0.8, vermelho };
    addReta(Retas, C, D);
    Ponto E = {0.5, -0.6, vermelho }, F = { 0.7, 0.5, vermelho };
    addReta(Retas, E, F);

    Ponto P1 = { 0, -1, azul }, P2 = { 1, -1, azul }, P3 = { 0.5, 0, azul };
    Ponto lista[] = { P1, P2, P3 };
    addPoligono(Poligonos, sizeof(lista)/sizeof(lista[0]), &lista);
    Ponto P4 = { -1, 0, azul }, P5 = { -0.2, 1, azul }, P6 = { -1, 1, azul }, P7 = { -1, 0, azul }, P8 = { 0, 0, azul }, P9 = { 0, 0.8, azul };
    Ponto lista2[] = { P4, P5, P6, P7, P8, P9 };
    addPoligono(Poligonos, sizeof(lista2)/sizeof(lista2[0]), &lista2);
}

int main(int argc, char** argv){

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Projeto CG - Paint");

    Pontos = criarListaPontos();
    Retas = criarListaRetas();
    Poligonos = criarListaPoligonos();

    init();

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
