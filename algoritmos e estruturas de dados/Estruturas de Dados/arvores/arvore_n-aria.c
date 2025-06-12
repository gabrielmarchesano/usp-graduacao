#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct NO_ {
	int chave;
	struct NO_ *filho;
	struct NO_ *irmao;
} NO;

typedef NO* ARVORE;

NO* criar_no(int ch) {
	NO* novo = malloc(sizeof(NO));
	novo->chave = ch;
	novo->filho = NULL;
	novo->irmao = NULL;
	return novo;
}

NO* inicializar(int ch) {
	return criar_no(ch);
}

NO* buscar(NO *no, int ch_busca) {
	if (no == NULL) {
		return NULL;
	}
	if (no->chave == ch_busca) {
		return no;
	}
	
	NO *resultado = buscar(no->filho, ch_busca);
	if (resultado != NULL) {
		return resultado;
	}
	resultado = buscar(no->irmao, ch_busca);
	return resultado;
}

bool inserir(ARVORE ar, int ch_novo, int ch_pai) {
	NO *pai = buscar(ar, ch_pai);
	if (pai == NULL) {
		return false;
	}
	NO *novo = criar_no(ch_novo);
	if (novo == NULL) {
		return false;
	}
	NO *ultimo_filho = pai->filho;
	if (ultimo_filho == NULL) {
		pai->filho = novo;
		return true;
	}
	
	while (ultimo_filho->irmao != NULL) {
		ultimo_filho = ultimo_filho->irmao;
	}
	ultimo_filho->irmao = novo;
	return true;
}

NO* encontrar_pai(ARVORE ar, int ch_filho) {
	if (ar == NULL) {
		return NULL;
	}
	
	NO *filho = ar->filho;
	while (filho) {
		if (filho->chave == ch_filho) {
			return ar;
		}
		filho = filho->irmao;
	}
	
	NO *pai_encontrado = encontrar_pai(ar->filho, ch_filho);
	if (pai_encontrado != NULL) {
		return pai_encontrado;
	}
	return encontrar_pai(ar->irmao, ch_filho);
}

bool excluir(ARVORE ar, int ch_exclusao) {
	if (ar->chave == ch_exclusao) {
		printf("Nao eh possivel excluir a raiz\n");
		return false;
	}
	NO *pai = encontrar_pai(ar, ch_exclusao);
	
	if (pai == NULL) {
		return false;
	}
	
	// removendo o no excluido da sequencia de irmaos
	NO *anterior = NULL;
	NO *atual = pai->filho;
	
	while(atual != NULL && atual->chave != ch_exclusao) {
		anterior = atual;
		atual = atual->irmao;
	}
	
	if (anterior == NULL) {
		pai->filho = atual->irmao;
	} else {
		anterior->irmao = atual->irmao;
	}
	
	// promover os filhos do no exluido como filhos do pai
	NO *no_excluido = atual;
	
	atual = pai->filho;
	if (atual == NULL) {
		pai->filho = no_excluido->filho;
	} else {
	
		while(atual->irmao != NULL) {
			atual = atual->irmao;
		}
		atual->irmao = no_excluido->filho;
	}
	
	
	free(no_excluido);
	return true;
}

void exibir(ARVORE ar) {
	if (ar == NULL) {
		return;
	}
	printf("%d", ar->chave);
	printf("(");
	exibir(ar->filho);
	printf(")");
	exibir(ar->irmao);
}

int main() {
	ARVORE arvore = inicializar(8); 
	
	inserir(arvore, 15, 8);
	inserir(arvore, 23, 8);
	inserir(arvore, 2, 8);
	
	inserir(arvore, 20, 15);
	inserir(arvore, 10, 15);
	inserir(arvore, 28, 15);
	
	inserir(arvore, 36, 2);
	inserir(arvore, 7, 2);
	
	exibir(arvore);
	printf("\n");
	excluir(arvore, 2);
	exibir(arvore);
	printf("\n");
	return 0;
}

