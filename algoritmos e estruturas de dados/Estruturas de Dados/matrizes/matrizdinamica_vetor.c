#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>


typedef struct {
	int* elementos;
	int lin;
	int col;
} MATRIZ;

void inicializar_matriz(MATRIZ *m, int lin, int col) {
	m->lin = lin;
	m->col = col;
	m->elementos = malloc (lin * col * sizeof(int));
}

// l pode ir de 1 até m->lin
// c pode ir de 1 até m->col
int acessar_matriz(MATRIZ *m, int l, int c) {
	if (l <= 0 || l > m->lin || c <= 0 || c > m->col) {
		return 0;
	}
	int elemento;
	int offset_linha = m->col * (l-1);
	int offset_coluna = c - 1;
	int pos = offset_linha + offset_coluna;
	return m->elementos[pos];
}

bool atribuir_matriz(MATRIZ *m, int l, int c, int val) {
	if (l <= 0 || l > m->lin || c <= 0 || c > m->col) {
		return false;
	}
	m->elementos[m->col * (l - 1) + (c-1)] = val;
	return true;
}

void exibir_matriz(MATRIZ *m) {
	for (int i = 1; i <= m->lin; i++) {
		for (int j = 1; j <= m->col; j++) {
			printf("%4d ", acessar_matriz(m, i, j));	
		}
		printf("\n");
	}
}

int main() {
	MATRIZ m;
	inicializar_matriz(&m, 3, 4);
	
	
	for (int i = 1; i <= m.lin; i++) {
		for (int j = 1; j <= m.col; j++) {
			atribuir_matriz(&m, i, j, random()%100);
		}	
	}
	exibir_matriz(&m);
	atribuir_matriz(&m, 1, 1, 1234);
	printf("\n");
	atribuir_matriz(&m, 3, 4, 4321);
	exibir_matriz(&m);
	return 0;
}

