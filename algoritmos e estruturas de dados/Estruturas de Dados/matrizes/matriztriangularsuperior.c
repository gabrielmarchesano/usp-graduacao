#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>


typedef struct {
	int* elementos;
	int n;
} MTS;

int soma_pa(int max) {
	return (max) * (max + 1) / 2;
}

void inicializar_matriz(MTS *m, int ordem) {
	m->n = ordem;
	m->elementos = malloc ( soma_pa(ordem) * sizeof(int));
}

bool acessar_matriz(MTS *m, int l, int c, int *v) {
	if (l <= 0 || l > m->n || c <= 0 || c > m->n) {
		return false;
	}
	if (l > c) {
		*v = 0;
		return true;
	}
	
	// int offset_linha = soma_pa(m->n) - soma_pa(l-1); // linha com erro !
	int offset_linha = soma_pa(m->n) - soma_pa(m->n - (l-1));
	int offset_coluna = c - l;
	int pos = offset_linha + offset_coluna;
	*v = m->elementos[pos];
	
	return true;
}

bool atribuir_matriz(MTS *m, int l, int c, int v) {
	if (l <= 0 || l > m->n || c <= 0 || c > m->n) {
		return false;
	}
	if (l > c) {
		return false;
	}
	
	// int offset_linha = soma_pa(m->n) - soma_pa(l-1); // linha com erro !
	int offset_linha = soma_pa(m->n) - soma_pa(m->n - (l-1));
	int offset_coluna = c - l;
	int pos = offset_linha + offset_coluna;
	
	m->elementos[pos] = v;
	
	return true;
}

void exibir_matriz(MTS *m) {
	int v;
	for (int i = 1; i <= m->n; i++) {
		for (int j = 1; j <= m->n; j++) {
			acessar_matriz(m, i, j, &v);
			printf("%4d ", v);	
		}
		printf("\n");
	}
}

int main () {

	MTS m;
	inicializar_matriz(&m, 4);
	
	
	for (int i = 1; i <= m.n; i++) {
		for (int j = 1; j <= m.n; j++) {
			bool deucerto = atribuir_matriz(&m, i, j, i*10 +j);//random()%100);
			if (!deucerto)
			    printf("Nao foi possivel atribuir em (%d, %d)\n", i ,j);
		}	
	}
	
	exibir_matriz(&m);
	atribuir_matriz(&m, 1, 1, 1234);
	printf("\n");
	atribuir_matriz(&m, m.n, m.n, 4321);
	exibir_matriz(&m);
	
	return 0;

}

