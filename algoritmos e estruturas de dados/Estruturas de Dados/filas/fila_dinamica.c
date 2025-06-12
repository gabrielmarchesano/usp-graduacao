#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct {
	int chave;
	// outros campos ...
} REGISTRO;

typedef struct ELEMENTO_ {
	REGISTRO reg;
	struct ELEMENTO_* prox;
} ELEMENTO;

typedef struct {
	ELEMENTO *inicio;
	ELEMENTO *fim;
} FILA;

void inicializar_fila(FILA *f) {
	f->inicio = NULL;
	f->fim = NULL;
}

int tamanho_fila(FILA *f) {
	ELEMENTO *atual = f->inicio;
	int tamanho = 0;
	while (atual != NULL) {
		tamanho++;
		atual = atual->prox;
	}
	return tamanho;
}

void exibir_fila(FILA *f) {
	ELEMENTO *atual = f->inicio;
	printf ("Fila (%d) comeco: ", tamanho_fila(f));
	while (atual != NULL) {
		printf("%d ", atual->reg.chave);
		atual = atual->prox;
	}
	printf(" (fim)\n");
}

bool enfileirar(FILA *f, REGISTRO reg) {
	ELEMENTO *novo = malloc(sizeof(ELEMENTO));
	if (novo == NULL)
		return false;
	
	novo->reg = reg;
	novo->prox = NULL;
	
	if (f->fim == NULL) {
		f->inicio = novo;
	} else { 
		f->fim->prox = novo;
	}
	f->fim = novo;
		
	return true;
}

bool desenfileirar(FILA *f, REGISTRO *reg) {
	if (f->inicio == NULL) {
		return false;
	}
	
	*reg = f->inicio->reg;
	ELEMENTO *antigo_inicio = f->inicio;
	f->inicio = f->inicio->prox;
	free(antigo_inicio);
	
	if (f->inicio == NULL) {
		f->fim = NULL;
	}

	return true;
}

void reinicializar_fila(FILA *f) {
	ELEMENTO *atual = f->inicio;
	while (atual) {
		ELEMENTO *apagar = atual;
		atual = atual->prox;
		free(apagar);
	}
	f->inicio = NULL;
	f->fim = NULL;
}

int main() {
	FILA f;
	inicializar_fila(&f);
	
	for (int i = 0; i < 7; i++) {
		REGISTRO reg;
		reg.chave = (random() % 100);
		printf("Enfileirando reg com chave %d\n\t", reg.chave);
		bool deucerto = enfileirar(&f, reg);
		if (!deucerto) {
			printf("Fila cheia\n");
		}
		exibir_fila(&f);
	}
	
	reinicializar_fila(&f);
	exibir_fila(&f);
	
	for (int i = 0; i < 8; i++) {
		REGISTRO reg;
		bool deucerto = desenfileirar(&f, &reg);
		if (deucerto) {
			printf("Elemento desenfileirado: %d\n", reg.chave);
		} else {
			printf("Fila estava vazia\n");
		}
		
		exibir_fila(&f);
	}
	
	return 0;
}

