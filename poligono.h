typedef struct ponto{
    Ponto p;
    struct ponto *prox;
}PontoPoligono;

typedef struct{
    int tamanho;
    PontoPoligono *inicial;
}Poligono;