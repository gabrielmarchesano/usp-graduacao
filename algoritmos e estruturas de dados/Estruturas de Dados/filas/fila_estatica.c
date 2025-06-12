#include <stdio.h>
#include <stdlib.h>

typedef int bool;	
#define true 1
#define false 0

typedef struct {
	int chave;
	bool prioridade;
	// outros campos, como nome, data, etc
} REGISTRO;

#define MAX 5

typedef struct {
	REGISTRO regs[MAX];
	int inicio;
	int tamanho;
} FILA;

typedef struct {
	FILA sem_prioridade;
	FILA com_prioridade;
} FILA_PRIORIDADE;

void inicializar_fila(FILA *f) {
	f->inicio = 0;
	f->tamanho = 0;
}

int tamanho_fila(FILA *f) {
	return f->tamanho;
}

void exibir_fila(FILA *f) {
	printf("Fila (%d): [inicio] ", tamanho_fila(f));
	int pos_atual = f->inicio;
	for (int i = 0; i < tamanho_fila(f); i++) {
		printf("%d ", f->regs[pos_atual].chave);
		pos_atual = (pos_atual + 1) % MAX;
	} 
	printf (" [fim da fila]\n");
}

bool enfileirar(FILA *f, REGISTRO reg) {
	if (f->tamanho == MAX) return false;
	
	int pos_inserir = (f->inicio + f->tamanho) % MAX;
	f->regs[pos_inserir] = reg;
	f->tamanho++;

	return true;
}

bool desenfileirar(FILA *f, REGISTRO *reg) {
	if (f->tamanho == 0) return false;
	
	*reg = f->regs[f->inicio];
	
	f->inicio = (f->inicio + 1) % MAX;
	f->tamanho--;
	
	return true;
}

void reinicializar_fila(FILA *f) {
	f->tamanho = 0;
}

void inicializar_fila_p(FILA_PRIORIDADE *f) {
	inicializar_fila(&f->com_prioridade);
	inicializar_fila(&f->sem_prioridade);
}

bool enfileirar_p(FILA_PRIORIDADE *f, REGISTRO reg, bool prio) {
	if (prio) {
		return enfileirar(&f->com_prioridade, reg);
	} else {
		return enfileirar(&f->sem_prioridade, reg);
	}
	return false;
}

bool desenfileirar_p(FILA_PRIORIDADE *f, REGISTRO *reg) {
	if (tamanho_fila(&f->com_prioridade) > 0) {
		return desenfileirar(&f->com_prioridade, reg);
	} else {
		return desenfileirar(&f->sem_prioridade, reg);
	}
	return false;
}

void exibir_fila_p(FILA_PRIORIDADE *f) {
	printf("Com prioridade: ");
	exibir_fila(&f->com_prioridade);
	printf("Sem prioridade: ");
	exibir_fila(&f->sem_prioridade);
}

int main () {
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
	
	FILA_PRIORIDADE fp;
	inicializar_fila_p(&fp);
	
	for (int i = 0; i < 7; i++) {
		REGISTRO reg;
		reg.chave = (random() % 100);
		printf("Enfileirando reg chave %d (sem prio)\n", reg.chave);
		bool deucerto = enfileirar_p(&fp, reg, false);
		if (!deucerto) {
			printf("Fila cheia\n");
		}
		
		reg.chave = (random() % 100);
		printf("Enfileirando reg com chave %d (com prio)\n", reg.chave);
		deucerto = enfileirar_p(&fp, reg, true);
		exibir_fila_p(&fp);
		printf("\n");
	}
	
	for (int i = 0; i < 8; i++) {
		REGISTRO reg;
		bool deucerto = desenfileirar_p(&fp, &reg);
		if (deucerto) {
			printf("Elemento desenfileirado: %d\n", reg.chave);
		} else {
			printf("Fila estava vazia\n");
		}
		
		exibir_fila_p(&fp);
		printf("\n");
	}

	return 0;
}




