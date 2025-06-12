#ifndef CORE_H_INCLUDED
#define CORE_H_INCLUDED
#include <stdbool.h>


typedef struct s{
    struct s* prox;
    int adjc;
    int peso;
    int nmsg;
    int cia;
}NO;

typedef struct {
    NO* inicio;
    int flag;
    int via;
    int local;
}vertice;





void inicializar(vertice *g);
NO* arestaExiste(vertice *g, int i, int j, NO **ant);
int grauSaida(vertice *g, int k);
int grauEntrada(vertice *g, int k);
bool inserirAresta(vertice *g, int i, int j);
bool excluirAresta(vertice *g, int i, int j);
vertice* copiarGrafo(vertice *g);
// vertice* grafoTransposto(vertice *g);

#endif
