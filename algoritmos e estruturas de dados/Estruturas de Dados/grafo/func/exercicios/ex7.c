#include "/home/gabriel-marhchesano/each-si/aed2/grafo/func/graphsCore/core.c"

vertice* CostHigherThanC(vertice *g, int c) {
    vertice *new = (vertice*)malloc((V+1)*sizeof(vertice));
    inicializar(new);
    for(int i = 1; i<=V; i++){
        NO* atual = g[i].inicio;
        while(atual){
            if(atual->peso > c){
                NO *novo = (NO*)malloc(sizeof(NO));
                novo->adjc = atual->adjc;
                novo->peso = atual->peso;
                novo->prox = new[i].inicio;
                new[i].inicio = novo;
            }
            atual = atual->prox;
        }
    }
    return new;
    
}

void main(){}
