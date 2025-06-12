#include "/home/gabriel-marhchesano/each-si/aed2/grafo/func/graphsCore/core.c"
#include "/home/gabriel-marhchesano/each-si/aed2/grafo/search/queue/queue.c"
//EX26
typedef struct list{
    int valor;
    struct list *prox;
}LISTA;

//FUNÇÕES DE INICIALIZAR E INSERIR NA LISTA
 
void inicializarLista(LISTA *l){
    l = (LISTA*)malloc(sizeof(LISTA));
    l->prox = NULL;
}
void inserirLista(LISTA *l, int i){
    LISTA *novo, *aux;
    aux = l;
    while (aux)
    {
        if(aux->valor == i){
        return;
        }
        aux = aux->prox;
    }
    novo = (LISTA*)malloc(sizeof(LISTA));
    novo->valor = i;
    novo->prox = aux->prox;
    aux->prox = novo;
    free(aux);
    return;
    
}

LISTA* func(vertice *g, int i, int k){
    NO *p = g[i].inicio;
    LISTA *l; inicializarLista(l);
    while (p)
    {
        if(p->nmsg>=k){
            inserirLista(l, p->adjc);
        }
        p = p->prox;
    }
    for(int j = 1; j<=V; j++){
        if(j=i) continue;
        NO *f = g[j].inicio;
        while (f)
        {
            if(f->adjc = i && f->nmsg >=k){
                inserirLista(l, j);
            }
            f = f->prox;
        }        
    }
    return l;
}

//ex27

LISTA* voo(vertice *g, int a, int b, int c){
    //zerarflags(g);
    LISTA *l; inicializarLista(l);
    FILA *f; inicializarFila(f);
    entrarFila(f, a);
    g[a].flag = 1;
    g[a].via = 0;
    while (f){
        a = sairFila(f);
        g[a].flag = 2;
        NO*p = g[a].inicio;
        while (p){
            if(p->adjc == b){
                int aux = g[b].via; //via = vertice anterior ao b
                while (aux>=0){
                    inserirLista(l, aux);
                    aux = g[aux].via;   
                }
                return l;
            }
            if(g[p->adjc].flag == 0 && p->cia == c){
                entrarFila(f, p->adjc);
                g[p->adjc].flag = 1;
            }
            p = p->prox;
        }
    }
    return l;
}
//ex28

vertice* localCidade(vertice *g, int i, int x){
    //zerarflags(g);
    FILA *f; inicializarFila(f);
    entrarFila(f, i);
    g[i].flag = 1;
    while(f){
        i = sairFila(f);
        g[i].flag = 2;
        NO *p = g[i].inicio;
        while (p){
            if(g[p->adjc].local == x){return &g[p->adjc];}
            if(g[p->adjc].flag == 0){
                entrarFila(f, p->adjc);
                g[p->adjc].flag = 1;
            }
            p = p->prox;
        }  
    }
    return NULL;
}

//EX21 - Grafo Complementar
vertice* grafocomplementar(vertice *g){
    vertice *new = (vertice*)malloc((V+1)*sizeof(vertice));
    inicializar(new);
    for(int i=1; i<=V; i++){
        for(int j=1; j<=V; j++){
            NO *ant;
            if(arestaExiste(g, i, j, &ant) == NULL){
                inserirAresta(new, i, j);
            }
        }        
    }
    return new;
}


void main(){}