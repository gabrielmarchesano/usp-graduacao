#include <malloc.h>
#include <stdio.h>
#include <stdbool.h>
#include "search.h"
#include "/home/gabriel-marhchesano/each-si/aed2/search/queue/queue.h"
#define V 5


typedef struct e{
    struct e* prox;
    int value;
}ELEMENTO;

typedef struct {
    ELEMENTO* inicio;
    ELEMENTO* fim;
}FILA;


typedef struct s{
    struct s* prox;
    int adjc;
}NO;

typedef struct {
    NO* inicio;
    int flag;
}vertice;

void prof(vertice *g, int i) {
    g[i].flag = 1;
    NO *p = g[i].inicio;
    while(p){
        if(g[p->adjc].flag == 0){
            prof(g, p->adjc);
        }
        p = p->prox;
    }
    g[i].flag = 2; 
}

void larg(vertice *g, int i) {
    zerarflags(g)//definir
    FILA *f;
    inicializarFila(&f);
    entrarFila(&f, i);
    g[i].flag = 1;
    while(f){
        i = sairFila(&f);
        g[i].flag = 2;
        NO *p = g[i].inicio;
        while(p){
            if(g[p->adj].flag == 0) {
                g[p->adj].flag = 1;
                entrarFila(&f, p->adj);
            }
            p = p->prox;
        }    
    }
}
