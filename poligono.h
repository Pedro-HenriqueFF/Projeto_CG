typedef struct ponto{
    Ponto p;
    struct ponto *prox;
}PontoPoligono;

typedef struct{
    int tamanho;
    Ponto centroide;
    PontoPoligono *inicial;
}Poligono;