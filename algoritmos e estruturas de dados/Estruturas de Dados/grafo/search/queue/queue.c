#include <malloc.h>
#include <stdio.h>
#include <stdbool.h>
#include "queue.h"



void inicializarFila(FILA *f) {
	f->inicio = NULL;
	f->fim = NULL;
}

void entrarFila(FILA *f, int i) {
	ELEMENTO *novo = malloc(sizeof(ELEMENTO));
	
	novo->value = i;
	novo->prox = NULL;
	
	if (f->fim == NULL) {
		f->inicio = novo;
	} else { 
		f->fim->prox = novo;
	}
	f->fim = novo;
		
	return;
}

int sairFila(FILA *f) {
      
	int saida = f->inicio->value;
	ELEMENTO *antigo_inicio = f->inicio;
	f->inicio = f->inicio->prox;
	free(antigo_inicio);
	
	if (f->inicio == NULL) {
		f->fim = NULL;
	}

	return saida;
}

