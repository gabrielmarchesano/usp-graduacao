#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct NO_ {
	int valor;
	struct NO_* esq;
	struct NO_* dir;
} NO;


NO* criar_no(int v) {
	NO* novo = malloc(sizeof(NO));
	novo->valor = v;
	novo->esq = NULL;
	novo->dir = NULL;
	return novo;
}

NO* inicializar_arvore() {
	return NULL;
}

void inicializar_arvore2(NO **arvore) {
	*arvore = NULL;
}

NO* inserir(NO* arv, int novo_valor) {
	if (arv == NULL) {
		return criar_no(novo_valor);
	}
	
	if (novo_valor > arv->valor) {
		arv->dir = inserir(arv->dir, novo_valor);
	}
	
	if (novo_valor < arv->valor) {
		arv->esq = inserir(arv->esq, novo_valor);
	}
	
	return arv;
}

int tamanho(NO* arv) {
	if (arv == NULL) {
		return 0;
	}
	
	return 1 + tamanho(arv->esq) + tamanho(arv->dir);
}

void exibir_preordem(NO* arv) {
	if (arv == NULL) return;
	
	printf("%d (", arv->valor);
	exibir_preordem(arv->esq);
	exibir_preordem(arv->dir);
	printf(")");
}

void exibir_emordem(NO* arv) {
	if (arv == NULL) return;
	
	exibir_emordem(arv->esq);
	printf("%d ", arv->valor);
	exibir_emordem(arv->dir);
}

NO* buscar_abb(NO* arv, int valor_buscado) {
	if (arv == NULL) {
		return NULL;
	}
	
	if (arv->valor == valor_buscado) {
		return arv;
	}
	
	if (valor_buscado > arv->valor) {
		return buscar_abb(arv->dir, valor_buscado);
	} else {
		return buscar_abb(arv->esq, valor_buscado);
	}
	
}

NO* buscar_iterativo(NO* arv, int valor_buscado) {

	while (arv != NULL) {
		if (arv->valor == valor_buscado) {
			return arv;
		}
		
		if (valor_buscado > arv->valor) {
			arv = arv->dir;
		}
		
		if (valor_buscado < arv->valor) {
			arv = arv->esq;
		}
	}
	
	return NULL;
}

bool validar(NO* arvore) {
	// completar!
	return false;
}

int main() {
	NO* minha_arvore = inicializar_arvore();
	inicializar_arvore2(&minha_arvore);
	
	minha_arvore = inserir(minha_arvore, 50);
	minha_arvore = inserir(minha_arvore, 25);
	minha_arvore = inserir(minha_arvore, 75);
	minha_arvore = inserir(minha_arvore, 25);
	printf("tamanho %d\n", tamanho(minha_arvore));
	exibir_preordem(minha_arvore);
	printf("\n");
	exibir_emordem(minha_arvore);
	printf("\n");
	
	
	minha_arvore = inserir(minha_arvore, 12);
	minha_arvore = inserir(minha_arvore, 36);
	minha_arvore = inserir(minha_arvore, 63);
	minha_arvore = inserir(minha_arvore, 87);
	minha_arvore = inserir(minha_arvore, 25);
	printf("tamanho %d\n", tamanho(minha_arvore));
	exibir_preordem(minha_arvore);
	printf("\n");
	exibir_emordem(minha_arvore);
	printf("\n");
	
	NO* no_busca = buscar_iterativo(minha_arvore, minha_arvore->valor);
	if (no_busca) printf("achou: %d\n", no_busca->valor);
	else printf("Nao achou\n");
	
	no_busca = buscar_iterativo(minha_arvore, minha_arvore->dir->valor);
	if (no_busca) printf("achou: %d\n", no_busca->valor);
	else printf("Nao achou\n");
	
	no_busca = buscar_iterativo(minha_arvore, minha_arvore->dir->esq->valor);
	if (no_busca) printf("achou: %d\n", no_busca->valor);
	else printf("Nao achou\n");
	
	no_busca = buscar_iterativo(minha_arvore, -1);
	if (no_busca) printf("achou: %d\n", no_busca->valor);
	else printf("Nao achou\n");
	
	exibir_preordem(minha_arvore);
	printf("\n");
	printf("Validar(minha_arvore) %d\n", validar(minha_arvore));
		
	NO* arvore_binaria_comum = criar_no(10);
	arvore_binaria_comum->esq = criar_no(1);
	arvore_binaria_comum->dir = criar_no(20);
	
	arvore_binaria_comum->esq->esq = criar_no(0);
	arvore_binaria_comum->esq->dir = criar_no(8);
	
	arvore_binaria_comum->dir->esq = criar_no(5);
	arvore_binaria_comum->dir->dir = criar_no(30);
	printf("Validar(arvore_binaria_comum) %d\n", validar(arvore_binaria_comum));
	
	return 0;
}

