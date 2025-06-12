#include <stdio.h>
#include <stdbool.h>

#define MAX 5

typedef struct {
	int chave;
	// outros campos do registro
} REGISTRO;

typedef struct {
	REGISTRO elementos[MAX];
	int topo1;
	int topo2;
} PILHA;

void inicializar_pilha(PILHA *p) {
	p->topo1 = -1;
	p->topo2 = MAX;
}

int tamanho_pilha(PILHA *p, int n_pilha) {
	if (n_pilha == 1)
		return (p->topo1 + 1);
	if (n_pilha == 2)
		return (MAX - p->topo2);
	return -1;
}

bool push(PILHA *p, REGISTRO reg, int n_pilha) {
	if (p->topo1 + 1 == p->topo2) {
		return false;
	}
	
	if (n_pilha != 1 && n_pilha != 2) {
		return false;
	}
	
	if (n_pilha == 1) {
		p->topo1++;
		p->elementos[p->topo1] = reg;
	}
	
	if (n_pilha == 2) {
		p->topo2--;
		p->elementos[p->topo2] = reg;	
	}
	
	return true;
}

bool pop(PILHA *p, REGISTRO *reg, int n_pilha) {
	if (n_pilha != 1 && n_pilha != 2) {
		return false;
	}
	
	if (n_pilha == 1) {
		if (p->topo1 == -1) {
			return false;
		}
		
		*reg = p->elementos[p->topo1];
		p->topo1--;
	}
	
	if (n_pilha == 2) {
		if(p->topo2 == MAX) {
			return false;
		}
		*reg = p->elementos[p->topo2];
		p->topo2++;
	}
	
	return true;	
}

void reinicializar_pilha(PILHA *p) {
	inicializar_pilha(p);
}

void exibir_pilha(PILHA* p, int n_pilha) {

	if (n_pilha == 1) {
		printf("Pilha 1 (%d) topo: ", tamanho_pilha(p, n_pilha));
		for (int i = p->topo1; i >= 0; i--) {
			printf("%d ", p->elementos[i].chave);
		}
		printf(" base\n");
	} else if (n_pilha == 2) {
		printf("Pilha 2 (%d) topo: ", tamanho_pilha(p, n_pilha));
		for (int i = p->topo2; i < MAX; i++) {
			printf("%d ", p->elementos[i].chave);
		}
		printf(" base\n");
	} else {
		printf("Pilha invalida: %d\n", n_pilha);
	}
}


int main() {
	PILHA p;
	REGISTRO reg;
	inicializar_pilha(&p);
	exibir_pilha(&p, 1);
	exibir_pilha(&p, 2);

	reg.chave = 10;	
	push(&p, reg, 1);
	exibir_pilha(&p, 1);
	
	reg.chave = 50;	
	push(&p, reg, 1);
	exibir_pilha(&p, 1);
	
	reg.chave = 30;	
	push(&p, reg, 1);
	exibir_pilha(&p, 1);
	
		/*
	pop(&p, &reg, 1);
	printf("registro removido: %d\n", reg.chave);
	exibir_pilha(&p, 1);
	
	pop(&p, &reg, 1);
	printf("registro removido: %d\n", reg.chave);
	exibir_pilha(&p, 1);
	*/

	reg.chave = 500;	
	push(&p, reg, 2);
	exibir_pilha(&p, 2);
	
	reg.chave = 900;	
	push(&p, reg, 2);
	exibir_pilha(&p, 2);
	
	reg.chave = 3000;	
	push(&p, reg, 2);
	exibir_pilha(&p, 2);
	
		
	pop(&p, &reg, 2);
	printf("registro removido: %d\n", reg.chave);
	exibir_pilha(&p, 2);
	
	pop(&p, &reg, 2);
	printf("registro removido: %d\n", reg.chave);
	exibir_pilha(&p, 2);
	
	bool ret = pop(&p, &reg, 2);
	if (ret)
		printf("registro removido: %d\n", reg.chave);
	else
		printf("pilha vazia\n");
	exibir_pilha(&p, 2);

	return 0;
}

