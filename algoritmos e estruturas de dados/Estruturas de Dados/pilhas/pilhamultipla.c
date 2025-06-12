#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
	int chave;
} REGISTRO;

#define MAX 20
#define NP 4

typedef struct {
	REGISTRO regs[MAX];
	int base[NP+1];
	int topo[NP];
} PILHA_MULTIPLA;

void inicializar_pm(PILHA_MULTIPLA *pm) {
	for (int i = 0; i < NP; i++) {
		pm->base[i] = i * (MAX/NP);
		pm->topo[i] = pm->base[i] - 1;
	}
	pm->base[NP] = MAX;
	// pm->topo[NP] = ;
}

bool pilha_cheia(PILHA_MULTIPLA *pm, int k) {
	if (k < 0 || k >= NP) return true;
	
	return (pm->topo[k] + 1 == pm->base[k+1]);
}

bool pilha_vazia(PILHA_MULTIPLA *pm, int k) {
	if (k < 0 || k >= NP) return false;
	
	return (pm->topo[k] + 1 == pm->base[k]);
}

int tamanho_pilha_k(PILHA_MULTIPLA *pm, int k) {
	if (k < 0 || k >= NP) return 0;
	return pm->topo[k] - pm->base[k] + 1;
}

void exibir_pm(PILHA_MULTIPLA *pm) {
	for (int i = 0; i < NP; i++) {
		printf("\tPilha k = %d (tam = %d) (base) ", i,
			 tamanho_pilha_k(pm, i));
		for (int j = pm->base[i]; j <= pm->topo[i]; j++) {
			printf("%d ", pm->regs[j].chave);
		}
		printf("(topo)\n");
	}
}

void exibir_vetor(PILHA_MULTIPLA *pm) {
	int k = 0;
	bool preg = false;
	
	printf("Vetor da pilha multipla: \n i:");
	
	for (int i = 0; i < MAX; i++) {
		printf("%3d", i);
	}
	printf("\n   ");
	for (int i = 0; i < MAX; i++) {
		while (pm->base[k] == pm->base[k+1]) {
			k++;
		}
		if (i == pm->base[k] && !pilha_vazia(pm, k)) {
			preg = true;
		}
		if (preg) {
			printf("%3d", pm->regs[i].chave);
		} else {
			printf(" --");		
		}
		if (i == pm->topo[k] || pilha_vazia(pm, k)) {
			k = (k+1) % NP;
			preg=false;
		}
	}
	
	printf("\n");
	
	int niveis = 1;
	for (int nivel = 0; nivel < niveis; nivel++) {
		bool aumentou_nivel = false;
		for (int i = -1; i <= MAX; i++) {
			bool imprimiu = false;
			int ocorrencia = 0;
			for (int k = 0; k < NP; k++) {		
				if (i == pm->base[k]) {
					if (ocorrencia == nivel) {
						printf(" b%d", k);
						imprimiu = true;
					} else if (ocorrencia >= nivel && !aumentou_nivel) {
						niveis++;
						aumentou_nivel = true;
					}
					ocorrencia ++;
				}
				if (i == pm->topo[k]) {
					if (ocorrencia == nivel) {
						printf(" t%d", k);
						imprimiu = true;
					} else if (ocorrencia >= nivel && !aumentou_nivel) {
						niveis++;
						aumentou_nivel = true;
					}
					ocorrencia ++;
				}
			}
			if (!imprimiu) {
				printf("   ");
			}
		}
		printf("\n");
	}
}

bool pop (PILHA_MULTIPLA *pm, int k, REGISTRO *reg) {
	if (k < 0 || k >= NP) return false;
	
	if (pilha_vazia(pm, k)) return false;
	
	int topo = pm->topo[k];
	*reg = pm->regs[ topo ];
	pm->topo[k]--;
	return true;
}

bool deslocar_para_direita(PILHA_MULTIPLA *pm, int k) {
	if (k < 0 || k >= NP) return false;
	
	if (pilha_cheia(pm, k)) return false;
	
	for (int i = pm->topo[k]; i >= pm->base[k]; i--) {
		pm->regs[i+1] = pm->regs[i];
	}
	pm->base[k]++;
	pm->topo[k]++;
	return true;
}

bool deslocar_para_esquerda(PILHA_MULTIPLA *pm, int k) {
	if (k < 1 || k >= NP) return false;
	
	if (pilha_cheia(pm, k-1)) return false;
	
	for (int i = pm->base[k]; i <= pm->topo[k]; i++) {
		pm->regs[i-1] = pm->regs[i]; 
	}
	pm->base[k]--;
	pm->topo[k]--;
	return true;
}

bool push (PILHA_MULTIPLA *pm, int k, REGISTRO reg) {
	if (k < 0 || k >= NP) return false;
	
	if (pilha_cheia(pm, k)) {
		for (int i = k + 1; i < NP; i ++)
			deslocar_para_direita(pm, i);
		if (pilha_cheia(pm, k)) {
			for (int i = 1; i <= k; i ++)
				deslocar_para_esquerda(pm, i);
			if (pilha_cheia(pm, k)) {
				return false;
			}
		}
	}
	
	pm->topo[k] ++;
	int pos = pm->topo[k];
	pm->regs[ pos ] = reg;	
	return true;
}

int main() {
	PILHA_MULTIPLA pm;
	inicializar_pm(&pm);
	exibir_vetor(&pm);
	printf("\n");
	
	srandom(2024); // muda a semente do random()
	
	for (int i = 0; i < MAX * 2; i++) {
		REGISTRO reg = {.chave = -1};
		bool sucesso;
		int k = random()%NP;
		int push_or_pop = random()%4;
		if (push_or_pop != 0) { // faz push com 75% de chance
			while (k == 1) k = random()%NP; // nunca insere da pilha 1
			reg.chave = random() % 100;
			printf("Inserindo %d na pilha %d... ", reg.chave, k);
			sucesso = push(&pm, k, reg);
		} else { // faz pop com 25% de chance
			printf("Removendo da pilha %d... ", k);
			sucesso = pop(&pm, k, &reg);
			printf(" removido elemento %d ", reg.chave);
		}
		
		if (sucesso) printf("Sucesso!\n");
		else printf("Falhou :(\n");
		
		exibir_pm(&pm);
		exibir_vetor(&pm);
		printf("\n");
	}
	
	
	return 0;
}

