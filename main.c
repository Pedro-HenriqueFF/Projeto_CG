#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "poligono.c"

Lista_Pontos *Pontos = NULL;
Lista_Retas *Retas = NULL;
Lista_Poligonos *Poligonos = NULL;

void init(void);
void createMenu(void);
void menu(int value);
void display(void);
void desenhaPlano(void);
int main(int argc, char** argv);

static int win;
static int mainmenu;
static int criar;
static int selecionar;
static int val = 0;

int tolerancia = 5;
int ponto = -1;
int reta = -1;
int poligono = -1;

float Width = 300;
float Height = 300;
float mousex, mousey;

void init(){

    glClearColor(1.0, 1.0, 1.0, 0.0); 

    glMatrixMode(GL_PROJECTION); 
    glOrtho(-Width,Width,-Height,Height,-1.0f,1.0f);

    Ponto A = { -150, 90, vermelho }, B = { 150, -30, vermelho };
    addReta(Retas, A, B);
    Ponto C = { -150, -210, vermelho }, D = { -30, 240, vermelho };
    addReta(Retas, C, D);
    Ponto E = { 150, -180, vermelho }, F = { 210, 150, vermelho };
    addReta(Retas, E, F);

    Ponto P1 = { 0, -300, azul }, P2 = { 300, -300, azul }, P3 = { 150, 0, azul };
    Ponto lista[] = { P1, P2, P3 };
    addPoligono(Poligonos, sizeof(lista)/sizeof(lista[0]), &lista);
    Ponto P4 = { -300, 0, azul }, P5 = { -60, 300, azul }, P6 = { -300, 300, azul }, P7 = { -300, 0, azul }, P8 = { 0, 0, azul }, P9 = { 0, 240, azul };
    Ponto lista2[] = { P4, P5, P6, P7, P8, P9 };
    addPoligono(Poligonos, sizeof(lista2)/sizeof(lista2[0]), &lista2);
}

void createMenu(){
    criar = glutCreateMenu(menu);
    glutAddMenuEntry("Ponto", 1);
    glutAddMenuEntry("Reta", 2);
    glutAddMenuEntry("Poligono", 3);

    selecionar = glutCreateMenu(menu);
    glutAddMenuEntry("Ponto", 4);
    glutAddMenuEntry("Reta", 5);
    glutAddMenuEntry("Poligono", 6);

    mainmenu = glutCreateMenu(menu);
    glutAddSubMenu("Criar", criar);
    glutAddSubMenu("Selecionar", selecionar);
    glutAddMenuEntry("Cancelar", 0);
    glutAddMenuEntry("Sair", -1);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void menu(int value){
    if(value == -1){
        glutDestroyWindow(win);
        exit(0);
    }else{
        val = value;
        if(val != 4)
            ponto = -1;
        if(val != 5)
            reta = -1;
        if(val != 6)
            poligono = -1;
    }

    glutPostRedisplay();
}

void display(){

    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    desenhaPlano();
    desenhaPoligonos(Poligonos);
    desenhaRetas(Retas);
    desenhaPontos(Pontos, ponto);

    glutSwapBuffers();
}

void desenhaPlano(){
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
        glVertex2i(-300, 0);
        glVertex2i(300, 0);

        glVertex2i(0, -300);
        glVertex2i(0, 300);
    glEnd();
}

void mouse(int button, int state , int x , int y) {
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && val == 1){
        mousex = x - Width;
        mousey = Height - y;
        addPonto(Pontos, mousex, mousey);
        glutPostRedisplay();
    }else if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && val == 4){
        mousex = x - Width;
        mousey = Height - y;
        ponto = selecionaPonto(Pontos, mousex, mousey, tolerancia);
        glutPostRedisplay();
    }
}

void special(int key, int x, int y){

    if(key == GLUT_KEY_F1){
        if(val == 4 && ponto != -1){
            if(removerPonto(Pontos, ponto))
                ponto = -1;
        }
    }

    glutPostRedisplay();
}

int main(int argc, char** argv){

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    win = glutCreateWindow("Projeto CG - Paint");

    createMenu();

    Pontos = criarListaPontos();
    Retas = criarListaRetas();
    Poligonos = criarListaPoligonos();

    init();

    glutMouseFunc(mouse);
    glutSpecialFunc(special);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
