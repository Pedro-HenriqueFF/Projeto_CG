typedef struct{
    float matriz[3][3];
}Matriz_Transformacao;

typedef struct{
    float matriz[3][1];
}Matriz_Ponto;

Matriz_Transformacao* criarMatrizTransformacao();
Matriz_Ponto* criarMatrizPonto(float x, float y);
Matriz_Transformacao* criarMatrizTranslacao(float tx, float ty);
Matriz_Transformacao* criarMatrizRotacao(float theta);
Matriz_Transformacao* criarMatrizEscalar(float scale);
Matriz_Transformacao* multiplicarMatrizesTransformacao(Matriz_Transformacao *, Matriz_Transformacao *);
Matriz_Ponto* multiplicarMatrizPonto(Matriz_Transformacao *, Matriz_Ponto *);