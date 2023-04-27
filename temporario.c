#include <windows.h>
#include <GL/glut.h>
#define MAX_POINTS 1000
#define MAX_LINES 1000
#define MAX_POLYGONS 1000

//cria uma estrutura para definir uma cor
typedef struct{
    float red;
    float green;
    float blue;
}Cor;

Cor vermelho = { 1.0, 0.0, 0.0 };
Cor verde = { 0.0, 1.0, 0.0 };
Cor azul = { 0.0, 0.0, 1.0 };
Cor preto = { 0.0, 0.0, 0.0 };

//cria uma estrutura para definir um ponto
typedef struct{
    float x;
    float y;
    Cor cor;
}Ponto;

//cria uma estrutura para definir uma reta
typedef struct{
    Ponto inicio;
    Ponto fim;
}Reta;

//cria uma estrutura para definir um poligono
typedef struct{
    int tamanho;
    Ponto pontos[];
}Poligono;

//define vetor para armazenar pontos no programa
int quantidade_pontos = 0;
Ponto pontos[MAX_POINTS];

//define vetor para armazenar retas no programa
int quantidade_retas = 0;
Reta retas[MAX_LINES];

//define vetor para armazenar poligonos no programa
int quantidade_poligonos = 0;
Poligono poligonos[MAX_POLYGONS];

void addPonto(float x, float y, Cor cor){

    pontos[quantidade_pontos].x = x;
    pontos[quantidade_pontos].y = y;
    pontos[quantidade_pontos].cor = cor;

    quantidade_pontos++;
}

void desenhaPontos(){

    glPointSize(5.0);
    glBegin(GL_POINTS);
    for (int i = 0; i < quantidade_pontos; i++){
        glColor3f(pontos[i].cor.red, pontos[i].cor.green, pontos[i].cor.blue); //define a cor vermelho
        glVertex2f(pontos[i].x, pontos[i].y); //define localizalção do vértice
    }
    glEnd();
}

void addReta(float x1, float y1, Cor cor1, float x2, float y2, Cor cor2){

    retas[quantidade_retas].inicio.x = x1;
    retas[quantidade_retas].inicio.y = y1;
    retas[quantidade_retas].inicio.cor = cor1;

    retas[quantidade_retas].fim.x = x2;
    retas[quantidade_retas].fim.y = y2;
    retas[quantidade_retas].fim.cor = cor2;

    quantidade_retas++;
}

void desenhaRetas(){

    glLineWidth(2.0);
    glBegin(GL_LINES);
    for (int i = 0; i < quantidade_retas; i++){
        glColor3f(retas[i].inicio.cor.red, retas[i].inicio.cor.green, retas[i].inicio.cor.blue); //define a cor azul
        glVertex2f(retas[i].inicio.x, retas[i].inicio.y); //define localização do vértice A
        glColor3f(retas[i].fim.cor.red, retas[i].fim.cor.green, retas[i].fim.cor.blue);
        glVertex2f(retas[i].fim.x, retas[i].fim.y); //define localização do vértice B
    }
    glEnd();
}

void addPoligono(int tamanho, Ponto newPontos[]){

    poligonos[quantidade_poligonos].tamanho = tamanho;
    for (int i = 0; i < tamanho; i++){
        poligonos[quantidade_poligonos].pontos[i].x = newPontos[i].x;
        poligonos[quantidade_poligonos].pontos[i].y = newPontos[i].y;
        poligonos[quantidade_poligonos].pontos[i].cor = newPontos[i].cor;
    }

    quantidade_poligonos++;
}

void desenhaPoligonos(){

    glLineWidth(2.0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < quantidade_poligonos; i++){
        for (int j = 0; j < poligonos[i].tamanho; j++){
            glColor3f(poligonos[i].pontos[j].cor.red, poligonos[i].pontos[j].cor.green, poligonos[i].pontos[j].cor.blue); //define a cor azul
            glVertex2f(poligonos[i].pontos[j].x, poligonos[i].pontos[j].y); //define localização do vértice A
        }
    }
    glEnd();
}

void display(){

    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    desenhaPoligonos();
    desenhaRetas();
    desenhaPontos();

    glFlush(); //desenha os comandos não executados
}

void init(){

    glClearColor(1.0, 1.0, 1.0, 1.0); //define a cor de fundo

    glMatrixMode(GL_PROJECTION); //carrega a matriz de projeção
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); //define a projeção ortogonal 2D

    //adiciona pontos (0, 0) e o (0, 0.5)
    addPonto(0, 0, vermelho);
    addPonto(0, 0.5, azul);
    addPonto(0.5, 0.5, verde);
    addPonto(0, -0.5, verde);
    addPonto(-0.5, 0, vermelho);
    addPonto(-0.5, -0.5, azul);

    //adiciona uma reta com vértices A (-0.5, 0.3) e B (0.5, -0.1)
    addReta(-0.5, 0.3, vermelho, 0.5, -0.1, vermelho);
    addReta(-0.5, -0.7, azul, -0.1, 0.8, verde);
    addReta(0.5, -0.6, azul, 0.7, 0.5, preto);

    Ponto P1 = { -0.5, -0.5, azul }, P2 = { 0.5, -0.5, verde }, P3 = { 0.0, 0.5, vermelho };
    Ponto newPoligono[3] = { P1, P2, P3 };
    addPoligono(3, newPoligono);

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

    init();

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
