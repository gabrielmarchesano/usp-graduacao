//--------------------------------------------------------------
// GABRIEL FERNANDES MARCHESANO
//--------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

// INFORME O NRO DO GRUPO CONFORME PLANILHA DIVULGADA
int grupo() {
  return 0;
}

// 15453229
int nroUSP1() {
    return 0;
}

// E O SEGUNDO NROUSP AQUI, SE HOUVER
int nroUSP2() {
    return 0;
}

typedef struct s{
    struct s* prox;
    int adjc;
} NOG;

typedef struct {
    NOG* inicio;
} vertice;

typedef struct {
    int V;
    int A;
    int *ij;
    vertice* g;
} grafo

typedef struct e{
    struct e* prox;
    int value;
}ELEMENTO;

typedef struct {
    ELEMENTO* inicio;
    ELEMENTO* fim;
}FILA;
                                                     
 
void larg(vertice *g, int i, int ij[]) {
    zerarflags(g)//definir
    FILA *f;
    inicializarFila(&f); 
    entrarFila(&f, i);
    g[i].flag = 1;
    while(f){
        i = sairFila(&f);
        g[i].flag = 2;
        NO *p = g[i].inicio;
        while(p){
            if(g[p->adj].flag == 0) {
                g[p->adj].flag = 1;
                entrarFila(&f, p->adj);
            }
            p = p->prox;
        }    
    }
}


// elemento da lista de resposta - NAO ALTERE ESTA DEFINICAO
typedef struct estr {
      int adj; // um nro. de vertice
      struct estr *prox;
} NO;


// funcao principal
NO *equidistantes(int V, int A, int ij[], int *v1, int *v2);

//------------------------------------------
// O EP consiste em implementar esta funcao
// e outras funcoes auxiliares que esta
// necessitar
//------------------------------------------
NO *equidistantes(int V, int A, int ij[], int *v1, int *v2)
{       
          
	NO* resp = NULL;
        
	// seu codigo AQUI
	//...

	return resp;
}



//---------------------------------------------------------
// use main() para fazer chamadas de teste ao seu programa
//---------------------------------------------------------
int main() {


	// aqui vc pode incluir codigo de teste - mas não precisa entregar isso




	// o EP sera testado com uma serie de chamadas como esta
	NO* teste = null;
	teste = NO *equidistantes(int V, int A, int ij[], int *v1, int *v2);

}

// por favor nao inclua nenhum código abaixo da função main()
