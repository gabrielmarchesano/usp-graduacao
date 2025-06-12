#include <stdio.h>
#include <stdbool.h>

#define MAX 50

typedef struct {
	int chave;
	// outros campos do registro
} REGISTRO;

typedef struct {
	REGISTRO elementos[MAX];
	int topo;
} PILHA;

void inicializar_pilha(PILHA *p) {
	p->topo = -1;
}

int tamanho_pilha(PILHA *p) {
	return p->topo + 1;
}

bool push(PILHA *p, REGISTRO reg) {
	if (p->topo == MAX - 1) {
		return false;
	}
	
	p->topo++;
	p->elementos[p->topo] = reg;
	
	return true;
}

bool pop(PILHA *p, REGISTRO *reg) {
	if (p->topo == -1) {
		return false;
	}
	
	*reg = p->elementos[p->topo];
	p->topo--;
	
	return true;	
}

void reinicializar_pilha(PILHA *p) {
	p->topo = -1;
}

void exibir_pilha(PILHA* p) {
	printf("Pilha (%d) topo: ", tamanho_pilha(p));
	for (int i = p->topo; i >= 0; i--) {
		printf("%d ", p->elementos[i].chave);
	}
	printf(" base\n");
}


int main() {
	PILHA p;
	REGISTRO reg;
	inicializar_pilha(&p);
	exibir_pilha(&p);

	reg.chave = 10;	
	push(&p, reg);
	exibir_pilha(&p);
	
	reg.chave = 50;	
	push(&p, reg);
	exibir_pilha(&p);
	
	reg.chave = 30;	
	push(&p, reg);
	exibir_pilha(&p);
	
		
	pop(&p, &reg);
	printf("registro removido: %d\n", reg.chave);
	exibir_pilha(&p);
	
	pop(&p, &reg);
	printf("registro removido: %d\n", reg.chave);
	exibir_pilha(&p);

	return 0;
}
