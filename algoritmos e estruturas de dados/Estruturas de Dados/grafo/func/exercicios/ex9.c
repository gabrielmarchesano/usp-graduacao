#include "/home/gabriel-marhchesano/each-si/aed2/grafo/func/graphsCore/core.c"

vertice* Subtração(vertice *g, vertice *n){
      vertice *resp = copiarGrafo(g);
      for(int i=1; i<=V; i++){
          NO *atual = n[i].inicio;
          while(atual){
              excluirAresta(g, i, atual->adjc);
              atual=atual->prox;
          }
      }
      return resp;
}
