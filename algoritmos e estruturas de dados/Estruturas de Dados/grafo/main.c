#include "core.c"


typedef struct s{
    struct s* prox;
    int adjc;
}NO;

typedef struct {
    NO* inicio;
}vertice;


void inicializar(vertice *g){
    int i=0;
    for(i=1;i<=V;i++){
        g[i].inicio = NULL;
    }
}

NO* arestaExiste(vertice *g, int i, int j, NO* *ant){
    *ant= NULL;
    NO* p = g[i].inicio;
    while(p){
        if(p->adjc==j)return p;
        *ant = p;
        p=p->prox;
    }
    return NULL;
}


//Funções que retornem o grau de entrada e saída de um vértice:

//Grau de saída: Qtdade de arestas que partem de um vértice k
int grauSaida(vertice *g, int k) {
    int gsaida = 0;
    NO *atual = g[k].inicio;
    while(atual){
        atual=atual->prox;
        gsaida = gsaida + 1;
    }
    printf("Grau de saida: %d\n", gsaida);
    return gsaida;
}


//Grau de entrada: Qtdade de arestas que incidem em um vertice k
int grauEntrada(vertice *g, int k){
    int gentrada = 0;
    NO *ant, *atual;
    for(int i=1; i<=V; i++){
    atual = arestaExiste(g, i, k, &ant);
    if(atual) gentrada = gentrada + 1;
    }
    printf("Grau de entrada: %d\n", gentrada);
    return gentrada;

}

bool inserirAresta(vertice *g, int i, int j) {
    NO *ant;
    NO *atual = arestaExiste(g, i, j, &ant);
    if(atual) return false;
    NO *novo = (NO*)malloc(sizeof(NO));
    novo->adjc = j;
    novo->prox = g[i].inicio;
    g[i].inicio = novo;
    return true;
}

bool excluirAresta(vertice *g, int i, int j){
    NO *ant;
    NO *atual = arestaExiste(g, i, j, &ant);
    if(!atual) return false;
    if(ant) ant->prox= atual->prox;
    else g[i].inicio = atual->prox;
    free(atual);
    return true;
}


vertice* copiarGrafo(vertice *g){
    vertice *h = (vertice*)malloc(sizeof(vertice)*(V+1));
    //inicializarGrafo(h); //menos eficiente
    int i;
    for(i=1;i<=V;i++){
        NO *p = g[i].inicio;
        h[i].inicio = NULL;
        while(p){
            NO *novo = (NO*)malloc(sizeof(NO));
            novo->adjc = p->adjc;
            novo->prox = h[i].inicio;
            h[i].inicio = novo;
            p = p->prox;
        }
    }
    return h;
}


//Cria um grafo n transposto de g
vertice* grafoTransposto(vertice *g){
    vertice *n = (vertice*)malloc(sizeof(vertice)*(V+1));
    //inicializarGrafo(n); //menos eficiente
    int i;
    NO *p;
    for(i=1;i<=V;i++){
        n[i].inicio = NULL; 
        p = g[i].inicio; 
    }
    for(i=1;i<=V;i++) {     
        while(p){
            NO *novo = (NO*)malloc(sizeof(NO));
            novo->adjc = i;
            novo->prox = n[p->adjc].inicio;
            n[p->adjc].inicio = novo;
            p = p->prox;
        }
    }    
    return n;
}    
    



int main(){

vertice *g = (vertice*)malloc((V+1)*sizeof(vertice));
inicializar(g);
inserirAresta(g, 3, 5);
inserirAresta(g, 2, 1);
inserirAresta(g, 1, 3);
inserirAresta(g, 1, 4);
inserirAresta(g, 4, 5);
grauEntrada(g, 2);
grauSaida(g,1);
printf("sepa funcionou");

return 1;
}
