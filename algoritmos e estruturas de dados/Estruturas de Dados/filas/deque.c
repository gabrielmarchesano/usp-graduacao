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
	struct ELEMENTO_* ant;
} ELEMENTO;

typedef struct {
	ELEMENTO *cabeca;
} DEQUE;

void inicializar_deque(DEQUE *d) {
	d->cabeca = malloc(sizeof(ELEMENTO));
	d->cabeca->prox = d->cabeca;
	d->cabeca->ant = d->cabeca;
}

int tamanho_deque(DEQUE *d) {
	int tamanho = 0;
	ELEMENTO *atual = d->cabeca->ant;
	while (atual != d->cabeca) {
		tamanho++;
		atual = atual->ant;
	}
	return tamanho;
}

int tamanho_deque2(DEQUE *d) {
	int tamanho = 0;
	ELEMENTO *atual = d->cabeca->prox;
	while (atual != d->cabeca) {
		tamanho++;
		atual = atual->prox;
	}
	return tamanho;
}

void exibir_deque(DEQUE *d) {
	ELEMENTO *atual = d->cabeca->ant;
	printf("DEQUE (%d) fim: ", tamanho_deque(d));
	while (atual != d->cabeca) {
		printf("%d ", atual->reg.chave);
		atual = atual->ant;
	}
	printf(" (inicio)\n");
}

bool inserir_no_inicio(DEQUE *d, REGISTRO reg) {
	ELEMENTO *novo = malloc(sizeof(ELEMENTO));
	if (novo == NULL) {
		return false;
	}
	
	novo->reg = reg;
	novo->prox = d->cabeca->prox;
	novo->ant = d->cabeca;
	
	d->cabeca->prox->ant = novo;	// novo->prox->ant = novo;
	d->cabeca->prox = novo;		// novo->ant->prox = novo;
	
	return true;
}

bool inserir_no_fim(DEQUE *d, REGISTRO reg) {
	ELEMENTO *novo = malloc(sizeof(ELEMENTO));
	if (novo == NULL) {
		return false;
	}
	
	novo->reg = reg;
	ELEMENTO *antigo_fim = d->cabeca->ant;
	 
	novo->prox = d->cabeca;
	novo->ant = antigo_fim; // novo->ant = d->cabeca->ant;
	
	antigo_fim->prox = novo;	// novo->ant->prox = novo; 
	d->cabeca->ant = novo;		// novo->prox->ant = novo;
	
	return true;
}

bool remover_do_fim(DEQUE *d, REGISTRO *reg) {
	if (d->cabeca->ant == d->cabeca) {
		return false;
	}
	
	ELEMENTO *ultimo = d->cabeca->ant;
	*reg = ultimo->reg;
	
	ultimo->ant->prox = d->cabeca;
	d->cabeca->ant = ultimo->ant;
	
	free(ultimo);

	return true;
}

bool remover_do_inicio(DEQUE *d, REGISTRO *reg) {
	if (d->cabeca->ant == d->cabeca) {
		return false;
	}
	
	ELEMENTO *comeco = d->cabeca->prox;
	*reg = comeco->reg;
	
	comeco->prox->ant = d->cabeca;
	d->cabeca->prox = comeco->prox;
	
	free(comeco);

	return true;
}

void reinicializar_deque(DEQUE *d) {
	ELEMENTO *atual = d->cabeca->prox;
	while (atual != d->cabeca) {
		ELEMENTO *apagar = atual;
		atual = atual->prox;
		free(apagar);
	}
	d->cabeca->prox = d->cabeca;
	d->cabeca->ant = d->cabeca;
}

int main() {
	DEQUE d;
	
	inicializar_deque(&d);
	
	for (int i = 0; i < 7; i++) {
		REGISTRO reg;
		reg.chave = (random() % 100);
		printf("inserir_no_inicio reg com chave %d\n\t", reg.chave);
		bool deucerto = inserir_no_inicio(&d, reg);
		if (!deucerto) {
			printf("Deque cheia\n");
		}
		exibir_deque(&d);
	}
	
	for (int i = 0; i < 8; i++) {
		REGISTRO reg;
		bool deucerto = remover_do_fim(&d, &reg);
		if (deucerto) {
			printf("Elemento remover_do_fim: %d\n", reg.chave);
		} else {
			printf("Fila estava vazia\n");
		}
		
		exibir_deque(&d);
	}
	
	return 0;

}

