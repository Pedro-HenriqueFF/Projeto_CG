typedef struct{
    int matriz[3][3];
}Matriz_Transformacao;

typedef struct{
    int matriz[3][1];
}Matriz_Ponto;

Matriz_Transformacao* criarMatrizTransformacao();
Matriz_Ponto* criarMatrizPonto(int x, int y);
Matriz_Transformacao* criarMatrizTranslacao(int x, int y);
Matriz_Transformacao* multiplicarMatrizesTransformacao(Matriz_Transformacao *, Matriz_Transformacao *);
Matriz_Ponto* multiplicarMatrizPonto(Matriz_Transformacao *, Matriz_Ponto *);