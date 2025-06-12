#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct NO_ {
	int chave;
	struct NO_ *esq, *dir;
} NO;

typedef NO* ARVORE;

NO* criar_no(int chave) {
	NO *novo = malloc(sizeof(NO));
	novo->chave = chave;
	novo->esq = NULL;
	novo->dir = NULL;
	return novo;
}

void inicializar_arvore(ARVORE *arvore, int ch) {
	*arvore = criar_no(ch);
}

NO* busca(ARVORE raiz, int ch_busca) {
	if (raiz == NULL)
		return NULL;
	if (raiz->chave == ch_busca)
		return raiz;
	NO *achou_esquerda = busca(raiz->esq, ch_busca);
	if (achou_esquerda != NULL) {
		return achou_esquerda;
	}
	return busca(raiz->dir, ch_busca);
}

#define DIREITA 0
#define ESQUERDA 1

bool inserir(ARVORE raiz, int ch_novo, int ch_pai, int lado) {
	NO *pai = busca(raiz, ch_pai);
	if (pai == NULL) {
		return false;
	}
	NO *novo = busca(raiz, ch_novo);
	if (novo != NULL)
		return false;
	novo = criar_no(ch_novo);
	if (lado == ESQUERDA) {
		novo->esq = pai->esq;
		pai->esq = novo;
	} else if (lado == DIREITA) {
		novo->dir = pai->dir;
		pai->dir = novo;
	} else {
		free(novo);
		printf("Lado invalido: %d\n", lado);
		return false;
	}
	return true;
}

void exibir_preordem(ARVORE raiz) {
	if(raiz == NULL) return;
	printf("%d", raiz->chave);
	printf("(");
	exibir_preordem(raiz->esq);
	printf("|");
	exibir_preordem(raiz->dir);
	printf(")");
}

void free_subarvore(ARVORE raiz) {
	if (raiz == NULL) return;
	free_subarvore(raiz->esq);
	free_subarvore(raiz->dir);
	free(raiz);
}

bool excluir(ARVORE *raiz, int ch_exclusao) {
	if (*raiz == NULL)
		return false;
	if ((*raiz)->chave == ch_exclusao) {
		free_subarvore(*raiz);
		*raiz = NULL;
		return true;
	}
	bool dercerto = excluir(&(*raiz)->esq, ch_exclusao);
	if (dercerto) {
		return dercerto;
	}
	return excluir(&(*raiz)->dir, ch_exclusao);
}

int main() {
	ARVORE raiz;
	inicializar_arvore (&raiz, 1);
	exibir_preordem(raiz);
	printf("\n");
	
	bool deucerto = inserir(raiz, 2, 1, ESQUERDA);
	if (!deucerto) printf("Erro ao inserir\n");
	exibir_preordem(raiz);
	printf("\n");
	
	deucerto = inserir(raiz, 3, 1, DIREITA);
	if (!deucerto) printf("Erro ao inserir\n");
	
	deucerto = inserir(raiz, 20, 2, ESQUERDA);
	if (!deucerto) printf("Erro ao inserir\n");
	
	deucerto = inserir(raiz, 40, 2, DIREITA);
	if (!deucerto) printf("Erro ao inserir\n");
	
	deucerto = inserir(raiz, 30, 3, ESQUERDA);
	if (!deucerto) printf("Erro ao inserir\n");
	
	deucerto = inserir(raiz, 60, 3, DIREITA);
	if (!deucerto) printf("Erro ao inserir\n");
	exibir_preordem(raiz);
	printf("\n");
	
	deucerto = inserir(raiz, 100, 1, DIREITA);
	if (!deucerto) printf("Erro ao inserir\n");
	exibir_preordem(raiz);
	printf("\n");
	
	deucerto = inserir(raiz, 200, 99, DIREITA);
	if (!deucerto) printf("Erro ao inserir\n");
	
	deucerto = inserir(raiz, 100, 30, DIREITA);
	if (!deucerto) printf("Erro ao inserir\n");
	
	deucerto = excluir(&raiz, 3);
	if (!deucerto) printf("Erro ao excluir\n");
	exibir_preordem(raiz);
	printf("\n");
	
	deucerto = excluir(&raiz, 99);
	if (!deucerto) printf("Erro ao excluir\n");
	
	deucerto = excluir(&raiz, 1);
	if (!deucerto) printf("Erro ao excluir\n");
	exibir_preordem(raiz);
	printf("\n");
	
	return 0;

}

