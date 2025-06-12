#include <stdlib.h>
#include <stdio.h>

typedef struct {
	char chave;
	// outras coisas
} REGISTRO;

typedef struct NO_ {
	REGISTRO reg;
	struct NO_ *esq;
	struct NO_ *dir;
} NO;

typedef NO ARVORE;

void minha_funcao (REGISTRO *reg) {
	printf("%c ", reg->chave);
}

void troca_letra(REGISTRO *reg) {
	reg->chave ++;
}

void pre_ordem(ARVORE *arvore, void (*func)(REGISTRO*)) {
	if (arvore == NULL) return;
	func(&arvore->reg);
	pre_ordem(arvore->esq, func);
	pre_ordem(arvore->dir, func);
}

void em_ordem(ARVORE *arvore, void (*func)(REGISTRO*)) {
	if (arvore == NULL) return;
	em_ordem(arvore->esq, func);
	func(&arvore->reg);
	em_ordem(arvore->dir, func);
}

void pos_ordem(ARVORE *arvore, void (*func)(REGISTRO*)) {
	if (arvore == NULL) return;
	pos_ordem(arvore->esq, func);
	pos_ordem(arvore->dir, func);
	func(&arvore->reg);
}


int main () {
	ARVORE a;
	NO *no;
	
	a.reg.chave = 'A';
	
	no = malloc(sizeof(NO));
	no->reg.chave = 'B';
	no->esq = NULL;
	no->dir = NULL;
	a.esq = no;
	
	no = malloc(sizeof(NO));
	no->reg.chave = 'C';
	no->esq = NULL;
	no->dir = NULL;
	a.dir = no;
	
	pre_ordem(&a, troca_letra);
	
	pre_ordem(&a, &minha_funcao);
	printf("\n");
	em_ordem(&a, &minha_funcao);
	printf("\n");
	pos_ordem(&a, &minha_funcao);
	printf("\n");
	return 0;
}


