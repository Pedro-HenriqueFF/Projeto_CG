#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include "poligono.c"

Lista_Pontos *Pontos = NULL;
Lista_Retas *Retas = NULL;
Lista_Poligonos *Poligonos = NULL;

Matriz_Transformacao *rotacao_pos = NULL;
Matriz_Transformacao *rotacao_neg = NULL;
Matriz_Transformacao *aumentar = NULL;
Matriz_Transformacao *diminuir = NULL;
Matriz_Transformacao *borda = NULL;

void init(void);
void createMenu(void);
void menu(int value);
void display(void);
void desenhaPlano(void);
void mouse(int button, int state , int x , int y);
void special(int key, int x, int y);
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

int estado = 0;
int desenhandoReta = -1;
int desenhandoPoligono = -1;

float theta = 0.05;
float scale = 1.05;
float border = 1.03;

float Width = 300;
float Height = 300;
float mousex, mousey;

void init(){

    glClearColor(1.0, 1.0, 1.0, 0.0); 

    glMatrixMode(GL_PROJECTION); 
    glOrtho(-Width,Width,-Height,Height,-1.0f,1.0f);
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
        ponto = -1;
        reta = -1;
        poligono = -1;
        estado = 0;
        desenhandoReta = -1;
        desenhandoPoligono = -1;
    }
    glutPostRedisplay();
}

void display(){

    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    desenhaPlano();
    desenhaPoligonos(Poligonos, poligono, borda);
    desenhaRetas(Retas, reta);
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
    mousex = x - Width;
    mousey = Height - y;
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && val == 1){
        addPonto(Pontos, mousex, mousey);
    }else if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && val == 2){
        desenhandoReta = addReta(Retas, mousex, mousey, desenhandoReta);
    }else if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && val == 3){
        desenhandoPoligono = addPoligono(Poligonos, mousex, mousey, desenhandoPoligono);
    }else if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && val == 4){
        if (estado == 0)
            ponto = selecionaPonto(Pontos, mousex, mousey, tolerancia);
        else if (estado == 1){
            Matriz_Transformacao *translacao = criarMatrizTranslacao(
                mousex - Pontos->pontos[ponto].x, 
                mousey - Pontos->pontos[ponto].y
            );
            transladarPonto(Pontos, ponto, translacao);
        }
    }else if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && val == 5){
        if (estado == 0)
            reta = selecionaReta(Retas, mousex, mousey, tolerancia);
        else if (estado == 1){
            Matriz_Transformacao *translacao = criarMatrizTranslacao(
                mousex - Retas->retas[reta].centro.x, 
                mousey - Retas->retas[reta].centro.y
            );
            transladarReta(Retas, reta, translacao);
        }
    }else if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && val == 6){
        if (estado == 0)
            poligono = selecionaPoligono(Poligonos, mousex, mousey);
        else if (estado == 1){
            Matriz_Transformacao *translacao = criarMatrizTranslacao(
                mousex - Poligonos->poligonos[poligono].centroide.x, 
                mousey - Poligonos->poligonos[poligono].centroide.y
            );
            transladarPoligono(Poligonos, poligono, translacao);
        }
    }
    glutPostRedisplay();
}

void special(int key, int x, int y){

    if(key == GLUT_KEY_F1){
        if(val == 3) {
            finalizaPoligono(Poligonos, desenhandoPoligono);
            desenhandoPoligono = -1;
        }
    }else if(key == GLUT_KEY_F2){
        if(val == 4 && ponto != -1){
            if(removerPonto(Pontos, ponto)){
                if (estado != 0) estado = 0;
                ponto = -1;
            }
        }else if(val == 5 && reta != -1){
            if(removerReta(Retas, reta)){
                if (estado != 0) estado = 0;
                reta = -1;
            }
        }else if(val == 6 && poligono != -1){
            if(removerPoligono(Poligonos, poligono)){
                if (estado != 0) estado = 0;
                poligono = -1;
            }
        }
    }else if(key == GLUT_KEY_F3){
        if(val == 4 && ponto != -1){
            if (estado == 1) estado = 0;
            else estado = 1;
        }else if(val == 5 && reta != -1){
            if (estado == 1) estado = 0;
            else estado = 1;
        }else if(val == 6 && poligono != -1){
            if (estado == 1) estado = 0;
            else estado = 1;
        }
    }else if(key == GLUT_KEY_F4){
        if(val == 4 && ponto != -1){
            if (estado == 2) estado = 0;
            else estado = 2;
        }else if(val == 5 && reta != -1){
            if (estado == 2) estado = 0;
            else estado = 2;
        }else if(val == 6 && poligono != -1){
            if (estado == 2) estado = 0;
            else estado = 2;
        }
    }else if(key == GLUT_KEY_F5){
        if(val == 5 && reta != -1){
            if (estado == 3) estado = 0;
            else estado = 3;
        }else if(val == 6 && poligono != -1){
            if (estado == 3) estado = 0;
            else estado = 3;
        }
    }else if(key == GLUT_KEY_LEFT){
        if(val == 4 && ponto != -1 && estado == 2){
            rotacionarPonto(Pontos, ponto, rotacao_pos);
        }else if(val == 5 && reta != -1 && estado == 2){
            rotacionarReta(Retas, reta, rotacao_pos);
        }else if(val == 6 && poligono != -1 && estado == 2){
            rotacionarPoligono(Poligonos, poligono, rotacao_pos);
        }
    }else if(key == GLUT_KEY_RIGHT){
        if(val == 4 && ponto != -1 && estado == 2){
            rotacionarPonto(Pontos, ponto, rotacao_neg);
        }else if(val == 5 && reta != -1 && estado == 2){
            rotacionarReta(Retas, reta, rotacao_neg);
        }else if(val == 6 && poligono != -1 && estado == 2){
            rotacionarPoligono(Poligonos, poligono, rotacao_neg);
        }
    }else if(key == GLUT_KEY_UP){
        if(val == 5 && reta != -1 && estado == 3){
            escalarReta(Retas, reta, aumentar);
        }else if(val == 6 && poligono != -1 && estado == 3){
            escalarPoligono(Poligonos, poligono, aumentar);
        }
    }else if(key == GLUT_KEY_DOWN){
        if(val == 5 && reta != -1 && estado == 3){
            escalarReta(Retas, reta, diminuir);
        }else if(val == 6 && poligono != -1 && estado == 3){
            escalarPoligono(Poligonos, poligono, diminuir);
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

    rotacao_pos = criarMatrizRotacao(theta);
    rotacao_neg = criarMatrizRotacao(-theta);

    aumentar = criarMatrizEscalar(scale);
    diminuir = criarMatrizEscalar(1/scale);
    
    borda = criarMatrizEscalar(border);

    init();

    glutMouseFunc(mouse);
    glutSpecialFunc(special);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
