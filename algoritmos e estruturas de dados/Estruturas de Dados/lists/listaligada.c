#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define MAX 50
#define INVALIDO -1

typedef struct 
{
    int chave;
    int prox;
}ELEMENTO;

typedef struct 
{
    ELEMENTO array[MAX];
    int inicio;
    int disp;
}LISTA;

void inicializa(LISTA *l) 
{
    l->inicio = INVALIDO;
    l->disp = 0;
    for(int i=0; i<MAX; i++) {
        l->array[i].prox = i+1;
    }
    l->array[MAX-1].prox = INVALIDO;
}


bool inserir_ord(LISTA *l, ELEMENTO el) {
    int anterior = INVALIDO;
    int pos = l->inicio;
    
    if(l->disp == INVALIDO)
      return false;
      
    while(pos != INVALIDO && l->array[pos].chave < el.chave) {
        anterior = pos;
        pos = l->array[pos].prox;
    }
    
    int disp = l->disp;
    l->disp = l->array[disp].prox;
    
    if(anterior == INVALIDO) {
        int antigo_prox = l->inicio;
        l->array[disp].chave = el.chave;
        l->array[disp].prox = antigo_prox;
        l->inicio = disp;
        }
    else {
        int antigo_prox = l->array[anterior].prox;
	l->array[anterior].prox = disp;
    	l->array[disp].chave = el.chave;
      	l->array[disp].prox = antigo_prox;
	}
	 
	return true;
}




int tamanho_lista(LISTA *l) 
{
    int tamanho = 0;
    int pos_atual = l->inicio;
    while(pos_atual != INVALIDO) {
        tamanho ++;
        pos_atual = l->array[pos_atual].prox;
        }
    return tamanho;
}

void exibir_lista(LISTA *l) {
	printf("Conteudo da lista (%d): ", tamanho_lista(l));
	for (int pos = l->inicio;
		pos != INVALIDO;
		pos = l->array[pos].prox) {
		
		printf("%d ", l->array[pos].chave);
	}
	printf("\n");
}

int main() {
    LISTA l;
    
    
    inicializa(&l);
    srand(time(NULL));
    for(int i =0; i<8; i++) {
             ELEMENTO el = {.chave = rand()%100 };
             inserir_ord(&l, el); 
    }
    tamanho_lista(&l);
    exibir_lista(&l);
    return 0;
}
