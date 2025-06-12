#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct {
	int chave;
	// char nome[30];
	// ...
} REGISTRO;

typedef struct elemento_aux {
	struct elemento_aux *prox;
	REGISTRO reg;
} ELEMENTO;

typedef struct {
	ELEMENTO *cabeca;
} LISTA;

void inicializar_lista(LISTA* l) {
	l->cabeca = malloc(sizeof(ELEMENTO));
	l->cabeca->prox = l->cabeca;
}

int tamanho_lista(LISTA *l) {
	int tam = 0;
	ELEMENTO *atual = l->cabeca;
	
	while (atual->prox != l->cabeca) {
		tam ++;
		atual = atual->prox;
	}
	return tam;
}

void busca_aux(LISTA *l, int chave, ELEMENTO **ant, bool *achou) {
	*ant = l->cabeca;
	*achou = false;
	ELEMENTO *el_atual = l->cabeca->prox;
	
	while (el_atual != l->cabeca && el_atual->reg.chave < chave) {
		*ant = el_atual;
		el_atual = el_atual->prox;
	}
	
	if (el_atual != l->cabeca && el_atual->reg.chave == chave) {
		*achou = true;
	}	
}

// inserir
bool inserir_lista(LISTA* l, REGISTRO reg) {
	ELEMENTO *ant;
	bool achou;
	busca_aux(l, reg.chave, &ant, &achou);
	if (achou) {
		return false;
	}
	ELEMENTO *novo_el = malloc(sizeof(ELEMENTO));
	if (novo_el == NULL) {
		return false;
	}
	
	novo_el->reg = reg;
	
	novo_el->prox = ant->prox;
	ant->prox = novo_el;

	return true;
}

// excluir
bool excluir_lista(LISTA* l, int chave) {
	ELEMENTO *ant;
	bool achou;
	busca_aux(l, chave, &ant, &achou);
	if (!achou) {
		return false;
	}
	
	ELEMENTO *a_excluir = ant->prox;
	
	ant->prox = a_excluir->prox;
	
	free(a_excluir);
	
	return true;
}

// exibir
void exibir_lista(LISTA *l) {
	ELEMENTO *atual = l->cabeca->prox;
	printf("Tamanho: %d, Elementos: ", tamanho_lista(l));
	
	while (atual != l->cabeca) {
		printf("%d ", atual->reg.chave);
		atual = atual->prox;
	}
	printf("\n");
}

// busca
REGISTRO* buscar_lista_seq(LISTA *l, int chave) {
	l->cabeca->reg.chave = chave;
	ELEMENTO *el_atual = l->cabeca->prox;
	while(el_atual->reg.chave != chave) {
		el_atual = el_atual->prox; 
	}
	ELEMENTO *candidato = el_atual;
	if(candidato == l->cabeca) {
		return NULL;
	}
	return &candidato->reg;
}



REGISTRO* buscar_lista_ord(LISTA *l, int chave) {
	l->cabeca->reg.chave = chave;
	ELEMENTO *el_atual = l->cabeca->prox;
	while(el_atual->reg.chave < chave) {
		el_atual = el_atual->prox; 
	}
	ELEMENTO *candidato = el_atual;
	if(candidato->reg.chave != chave) {
		return NULL;
	}
	if(candidato == l->cabeca) {
		return NULL;
	}
	return &candidato->reg;
}

// reinicializar
void reinicializar_lista(LISTA *l) {
	ELEMENTO *ptr = l->cabeca->prox;
	while (ptr != l->cabeca) {
		ELEMENTO *prox = ptr->prox;
		free(ptr);
		ptr = prox;
	}
	l->cabeca->prox = l->cabeca;
}

int main() {
	// testes...
	LISTA l;
	inicializar_lista(&l);
	exibir_lista(&l);
	
	for (int i = 0; i < 6; i++) {
		REGISTRO r = {.chave = random()%100 };
		printf("Inserindo elemento com chave = %d\n\t", r.chave);
		inserir_lista(&l, r);
		exibir_lista(&l);
	}
	
	REGISTRO *resposta;
	int chave_busca = 15;
	resposta = buscar_lista_seq(&l, chave_busca);
	printf("Chave %d, elemento %d\n", chave_busca, resposta->chave);
	
	chave_busca = 93;
	resposta = buscar_lista_seq(&l, chave_busca);
	printf("Chave %d, elemento %d\n", chave_busca, resposta->chave);
	
	chave_busca = 83;
	resposta = buscar_lista_seq(&l, chave_busca);
	printf("Chave %d, elemento %d\n", chave_busca, resposta->chave);
	
	chave_busca = -1;
	resposta = buscar_lista_seq(&l, chave_busca);
	printf("Chave %d, elemento %p\n", chave_busca, resposta);	
	
	chave_busca = 15;
	resposta = buscar_lista_ord(&l, chave_busca);
	printf("Chave %d, elemento %d\n", chave_busca, resposta->chave);
	
	chave_busca = 93;
	resposta = buscar_lista_ord(&l, chave_busca);
	printf("Chave %d, elemento %d\n", chave_busca, resposta->chave);
	
	chave_busca = 83;
	resposta = buscar_lista_ord(&l, chave_busca);
	printf("Chave %d, elemento %d\n", chave_busca, resposta->chave);
	
	chave_busca = -1;
	resposta = buscar_lista_ord(&l, chave_busca);
	printf("Chave %d, elemento %p\n", chave_busca, resposta);
	
	
	
	excluir_lista(&l, 15);
	exibir_lista(&l);
	excluir_lista(&l, 93);
	exibir_lista(&l);
	excluir_lista(&l, 77);
	exibir_lista(&l);
	
	reinicializar_lista(&l);
	exibir_lista(&l);
	
	//printf("%ld\n", sizeof(ELEMENTO));
	
	return 0;
}

