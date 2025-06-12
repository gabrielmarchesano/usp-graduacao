#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include <stdio.h>
typedef struct e{
    struct e* prox;
    int value;
}ELEMENTO;

typedef struct {
    ELEMENTO* inicio;
    ELEMENTO* fim;
}FILA;

void inicializarFila(FILA*);
void entrarFila(FILA*, int i);
int sairFila(FILA*);

#endif
