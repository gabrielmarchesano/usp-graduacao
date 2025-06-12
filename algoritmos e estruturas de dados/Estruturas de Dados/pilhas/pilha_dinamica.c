#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
	int chave;
	int data;
} REGISTRO;

typedef struct _ELEMENTO {
	struct _ELEMENTO* prox;
	REGISTRO reg;
} ELEMENTO;

typedef struct {
	ELEMENTO *topo;
} PILHA;

void inicializar_pilha(PILHA *p) {
	p->topo = NULL;
}

int tamanho_pilha(PILHA *p) {
	ELEMENTO *atual = p->topo;
	int t = 0;
	while (atual) {
		t++;
		atual = atual->prox;
	}
	return t;
}

int tamanho2_pilha(PILHA p) {
	ELEMENTO *atual = p.topo;
	int t = 0;
	while (atual) {
		t = t+1;
		atual = atual->prox;
	}
	return t;
}

void exibir_pilha(PILHA *p) {
	printf("Pilha (%d == %d) topo: ", tamanho_pilha(p),
					  tamanho2_pilha(*p)  );
	ELEMENTO *atual = p->topo;
	while (atual != NULL) {
		printf("%d ", atual->reg.chave);
		atual = atual->prox;
	}
	printf(" base\n");
}

bool push(PILHA *p, REGISTRO reg) {
	ELEMENTO *novo = malloc(sizeof(ELEMENTO));
	if (novo == NULL) return false;
	
	novo->reg = reg;
	novo->prox = p->topo; 
	p->topo = novo;
	
	return true;
}

bool pilha_esta_vazia(PILHA *p) {
	return p->topo == NULL;
	// return tamanho_pilha(p) == 0;
}

bool pop(PILHA *p, REGISTRO *reg) {
	if(reg == NULL) return false;
	if (pilha_esta_vazia(p)) {
		return false;
	}
	ELEMENTO *apagar = p->topo;
	
	*reg = p->topo->reg;
	p->topo = p->topo->prox;
	free(apagar);

	return true;
}

REGISTRO* peek(PILHA* p) {
	if (p->topo == NULL) return NULL;
	else return &(p->topo->reg);
}

void reinicializar_pilha(PILHA* p) {
	ELEMENTO *atual = p->topo;
	
	while (atual != NULL) {
		ELEMENTO* apagar = atual;
		atual = atual->prox;
		free(apagar);
	}
	p->topo = NULL;
}

void reverter_pilha (PILHA* p) {
	// o desafio e' resolver usando apenas as operacoes push, pop e peek da pilha
	// pode usar um numero constante de pilha(s) auxiliares
	
	// prototipo de codigo que NAO resolve o problema:
	PILHA p_aux;
	inicializar_pilha(&p_aux);
	
	// coloca todos os elementos de p em p_aux
	while (!pilha_esta_vazia(p)) {
		REGISTRO temp_reg;
		pop(p, &temp_reg);
		push(&p_aux, temp_reg);
	}
	
	// devolve os elementos de p_aux para p
	while (!pilha_esta_vazia(&p_aux)) {
		REGISTRO temp_reg;
		pop(&p_aux, &temp_reg);
		push(p, temp_reg);
	}
	
	// oops p voltou ao estado original :(
}

void ordenar_pilha (PILHA* p) {
	// o desafio e' resolver usando apenas as operacoes push, pop e peek da pilha
	// pode usar um numero constante de pilha(s) auxiliares
	
	// a pilha deve ficar ordenada na ordem crescente
	// (menor elemento no topo, maior elemento na base)
	
	PILHA p_aux;
	inicializar_pilha(&p_aux);
	int tamanho = tamanho_pilha(p);
	
	if (tamanho < 2) return;
	

}


int main() {
	PILHA* p = malloc(sizeof(PILHA));
	if (p == NULL) return -1;
	
	inicializar_pilha(p);
	for (int i = 0; i < 10; i++) {
		int novachave = random() % 100;
		REGISTRO reg = {.chave = novachave, .data = 3008 };
		
		// REGISTRO reg;
		// reg.chave = novachave;
		// reg.data = 3008;
		
		printf("push %d\n", reg.chave);
		push (p, reg);
		exibir_pilha(p);
		printf("peek: %d\n", peek(p)->chave);
		printf("\n");
	}
	
	printf("Teste reverter:\n");
	reverter_pilha(p);
	exibir_pilha(p);
	printf("\n");
	
	printf("Teste ordenar:\n");
	ordenar_pilha(p);
	exibir_pilha(p);
	printf("\n");
	
	for (int i = 0; i < 3; i++) {
		REGISTRO reg_do_topo;
		pop(p, &reg_do_topo);
		printf("chave removida: %d\n", reg_do_topo.chave);
		exibir_pilha(p);
	}
	
	reinicializar_pilha(p);
	exibir_pilha(p);
	printf("etsa vazia %d\n", pilha_esta_vazia(p));
	
	REGISTRO reg = {.chave = 99};
	push (p, reg);
	exibir_pilha(p);
	printf(" pop 1 %d\n", pop(p, &reg));
	printf(" pop 2 %d\n", pop(p, &reg));
	
	reinicializar_pilha(p);
	free(p);
	
	return 0;
}
