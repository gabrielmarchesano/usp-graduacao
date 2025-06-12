#include "/home/gabriel-marhchesano/each-si/aed2/grafo/func/graphsCore/core.c"

int laços(vertice *g) {
    int cout = 0;
    for(int i=1; i<=V; i++){
        NO *aux = g[i].inicio;
        while(aux) {
            if(aux->adjc == i) {
                cout ++;
                continue;
            }
            aux = aux->prox;
        }
    }
    return cout;
}

void main(){}

