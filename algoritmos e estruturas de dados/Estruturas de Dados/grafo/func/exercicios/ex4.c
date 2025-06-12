#include "/home/gabriel-marhchesano/each-si/aed2/grafo/func/graphsCore/core.c"

vertice* grafoTransposto(vertice *g){
    vertice *n = (vertice*)malloc(sizeof(vertice)*(V+1));
    //inicializarGrafo(n); //menos eficiente
    int i;
    
    for(i=1;i<=V;i++){
        n[i].inicio = NULL; 
    }
    
    for(i=1;i<=V;i++) {
        NO *p = g[i].inicio;
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

void main(){}
