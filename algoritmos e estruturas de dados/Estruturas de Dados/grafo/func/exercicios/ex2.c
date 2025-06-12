#include "/home/gabriel-marhchesano/each-si/aed2/grafo/func/graphsCore/core.c"

void removeArestas(vertice *g) { //ex3 FALTA ARRUMAR
    for(int i=1; i<=V; i++){
        NO *atual = g[i].inicio;
        while(atual) {
            NO *ant = atual;
            atual = atual->prox;
            free(ant);
        }
        free(atual);
    }    
}
void removeLaços(vertice *g) { //ex2 FALTA ARRUMAR
    for(int i=1; i<=V; i++){
        NO *aux = g[i].inicio;
        while(aux) {
            NO *ant = aux;
            if(ant->adjc == i) {
            free(ant);
            aux = aux->prox;
        }
    }
}

void main(void){ 
    return;
}
