#include <time.h>
#include <stdio.h>
#include <stdlib.h>
/* Implementar e comparar o desempenho de sete algoritmos de ordenação: Insertion
Sort, Selection Sort, Bubble Sort melhorado, Shell Sort, Merge Sort, Heap Sort e Quick Sort
aleatório. A comparação deve incluir medições de tempo de execução, número de comparações e
número de movimentações realizadas em conjuntos de dados de tamanhos diferentes.
*/
 


typedef struct {
  int chave;
  int campoDaEstrutura[1000];
} Registro1000;
typedef Registro1000 reg;

/*
typedef struct {
int chave;
int campoDaEstrutura[1];
} Registro1;
typedef Registro1 reg;
*/
//É PRECISO TROCAR MANUALMENTE

//Insertion Sort
void insertion_sort(reg vetor[] , int tamanho, int *mov, int *comp) {
    int j;
    
    reg aux;
    for(int k=1; k<tamanho; k++ ) {
        (*comp)++;
        aux.chave = vetor[k].chave;
        (*mov)++;
        
        j = k - 1;
        while(j>=0 && aux.chave < vetor[j].chave ) {
            (*comp)++;
            (*mov)++;
            vetor[j+1] = vetor[j];
            j--;
        }
        (*comp)++;
        vetor[j+1]  = aux;
        (*mov)++; 
    }
}


//Selection Sort
void selection_sort(reg vetor[], int tamanho, int *mov, int *comp) {
    for (int i = 0; i < tamanho - 1; i++) {  // Última posição não precisa ser verificada
        int indice_menor = i;
        
        for (int j = i + 1; j < tamanho; j++) {
            (*comp)++;  // Contagem da comparação no if
            if (vetor[j].chave < vetor[indice_menor].chave) {
                indice_menor = j;
            }
        }

        // Só troca se necessário
        if (indice_menor != i) {
            reg aux = vetor[i];
            vetor[i] = vetor[indice_menor];
            vetor[indice_menor] = aux;
            *mov += 3;  // Incrementa as movimentações
        }
    }
}


//Bubble Sort melhorado
void bubble_sort(reg vetor[], int tamanho, int *mov, int *comp) {
    for(int j=1; j<tamanho; j++){
        (*comp)++;
        int cont = 0;
        for(int i=0; i<tamanho-j; i++){
            (*comp)++;
            if(vetor[i].chave > vetor[i+1].chave) {
               reg aux = vetor[i+1];
               vetor[i+1] = vetor[i];
               vetor[i]= aux;
               *mov= *mov +3;
               (*comp) ++;
                cont ++;
            }
            (*comp) ++;
        }
      (*comp)++;
    if(cont == 0 ){
      return ;
    }
    
    }

}



//Merge Sort 
void merge(reg vetor[], int i_min, int i_max, int meio, int *mov, int *comp) {
    int i, j, k;
    int n1 = meio - i_min + 1;  // Subvetor esquerdo (L)
    int n2 = i_max - meio;      // Subvetor direito (R)
    
    // Alocação dinâmica para os subvetores temporários Esq e Dir
    reg *Esq = (reg *)malloc(n1 * sizeof(reg));
    reg *Dir = (reg *)malloc(n2 * sizeof(reg));

    // Verificação de alocação de memória
    if (Esq == NULL || Dir == NULL) {
        fprintf(stderr, "Erro ao alocar memória para subvetores temporários.\n");
        exit(1);
    }

    // Copiar os dados para os subvetores temporários Esq e Dir
    for (i = 0; i < n1; i++) {
        Esq[i] = vetor[i_min + i];
        (*mov)++;
    }
    for (j = 0; j < n2; j++) {
        Dir[j] = vetor[meio + 1 + j];
        (*mov)++;
    }

    // Mesclando os subvetores de volta para o vetor original
    i = 0;
    j = 0;
    k = i_min;

    while (i < n1 && j < n2) {
        (*comp)++;
        if (Esq[i].chave <= Dir[j].chave) {
            vetor[k] = Esq[i];
            i++;
        } else {
            vetor[k] = Dir[j];
            j++;
        }
        (*mov)++;
        k++;
    }

    // Copiar os elementos restantes de Esq[], se houver
    while (i < n1) {
        vetor[k] = Esq[i];
        i++;
        k++;
        (*mov)++;
    }

    // Copiar os elementos restantes de Dir[], se houver
    while (j < n2) {
        vetor[k] = Dir[j];
        j++;
        k++;
        (*mov)++;
    }

    // Liberar a memória alocada para os subvetores temporários
    free(Esq);
    free(Dir);
}


void merge_sort(reg vetor[], int i_min, int i_max, int *mov, int *comp) {
    if (i_min < i_max) {
        int meio = (i_min + i_max) / 2;  // Encontrar o meio do vetor

        merge_sort(vetor, i_min, meio, mov, comp);        // Ordena a primeira metade
        merge_sort(vetor, meio + 1, i_max, mov, comp);    // Ordena a segunda metade
        merge(vetor, i_min, i_max, meio, mov, comp);      // Junta as duas metades ordenadas
    }
}



//Shell Sort
void shell_sort(reg vetor[], int tamanho, int *mov, int *comp) {
    int i, j, h;
    reg aux;

    // Calcula o intervalo inicial h usando a sequência de Knuth.
    for (h = 1; h < tamanho; h = 3*h + 1)
        (*comp)++; // Contando a comparação no cálculo de h.

    while (h > 0) {
        h = (h - 1) / 3;
        (*comp)++; // Comparação para verificar h > 0 no laço while.
        
        for (j = h; j < tamanho; j++) {
            (*comp)++; // Comparação j < tamanho no laço for.
            aux.chave = vetor[j].chave;
            (*mov)++; // Movimentação ao copiar chave.
            i = j;
            
            (*comp)++; // Comparação do início do while interno.
            while (i >= h && vetor[i - h].chave > aux.chave) {
                (*comp)++; // Contagem para a segunda condição do while.
                vetor[i] = vetor[i - h];
                i -= h;
                (*mov)++; // Movimentação ao deslocar o elemento.
            }
            (*comp)++; // Comparação que falhou no while interno.
            
            vetor[i].chave = aux.chave;
            (*mov)++; // Movimentação ao colocar chave na posição correta.
        }
        (*comp)++; // Comparação que falhou no for.
    }
    (*comp)++; // Comparação que falhou no while externo.
}





//Heap Sort
void heap_max (reg vetor[], int tamanho, int i, int *mov, int *comp) {
    int no_pai = i;
    
    int filho_esq = 2*i + 1;
    int filho_dir = 2*i + 2;
    
    (*comp)++;
    if(filho_esq < tamanho && vetor[filho_esq].chave > vetor[no_pai].chave) {
        no_pai = filho_esq;
        }    
    
    (*comp)++;
    if(filho_dir < tamanho && vetor[filho_dir].chave > vetor[no_pai].chave) {
            no_pai = filho_dir;
        }
    (*comp)++;
    if(no_pai != i) {
        reg aux = vetor[i];
        vetor[i] = vetor[no_pai];
        vetor[no_pai] = aux;
        *mov = *mov +3;
        heap_max(vetor, tamanho, no_pai, mov, comp);
    
    }

}
void heap_sort(reg vetor[], int tamanho, int *mov, int *comp) {

    // Faz o heap maximo
    
    for (int i = tamanho / 2 - 1; i >= 0; i--) {
        (*comp)++;
        heap_max(vetor, tamanho, i, mov, comp);
    }
    (*comp)++;

    
    for (int i = tamanho - 1; i > 0; i-- ) {
        (*comp)++;
        // Move a semente para o fim
        reg temp = vetor[0]; 
        vetor[0] = vetor[i];
        vetor[i] = temp;
        *mov = *mov + 3;

        // Chama o heap maximo para verificar se foi mantida a propriedade para os elementos da subarvore
        heap_max(vetor, i, 0, mov, comp);
    }
    (*comp)++;
}






//Quick Sort aleatório


int particao(reg vetor[], int p, int r, int *mov, int *comp) {
  int x = vetor[r].chave;
  int i = p - 1;
  for(int j=p; j < r; j++) {
    (*comp)++;
    if (vetor[j].chave <= x) {
      i = i + 1;
      reg aux = vetor[i]; 
      vetor[i] = vetor[j];
      vetor[j]= aux;
      *mov = *mov + 3;
      (*comp)++;
    }
    (*comp)++;
  }
  (*comp)++;
  *mov = *mov + 3;
  reg aux = vetor[i+1];
  vetor[i+1]= vetor[r];
  vetor[r] = aux;
  return i + 1;

}

int particaoAleatoria(reg vetor[], int p, int r, int *mov, int *comp) {
  int deslocamento, i ;
  reg temp;
  time_t t;
  /* Inicializa gerador de número aleatorio */
  srand((unsigned) time(&t));
  // Escolhe um numero aleatorio entre p e r
  deslocamento = rand() % (r-p+1); //retorna um int entre 0 e (r-p)
  i = p + deslocamento; // i eh tal que p <= i <= r
  // Troca de posicao A[i] e A[r]
  temp = vetor[r];
  vetor[r]= vetor[i];
  vetor[i] = temp;
  *mov = *mov +3;
  return particao(vetor, p, r, mov, comp);
}

void quick_sort(reg vetor[], int p, int r, int *mov, int *comp) {
 (*comp) ++;
 if (p < r) {
 int q;
 q = particaoAleatoria(vetor, p, r, mov, comp);
 quick_sort(vetor, p, q - 1, mov, comp);
 quick_sort(vetor, q + 1, r, mov, comp);
    }
}



int main() {


  FILE *arquivos[9];

  FILE *saida; 

  const char *nomesarquivos[] = {
      "10000_aleatorio.txt",
      "1000_aleatorio.txt",
      "100_aleatorio.txt",
      "10000_crescente.txt",
      "1000_crescente.txt",
      "100_crescente.txt",
      "10000_decrescente.txt",
      "1000_decrescente.txt",
      "100_decrescente.txt"
  };
    
  for (int i = 0; i < 9; i++) {
    arquivos[i] = fopen(nomesarquivos[i], "r");
    
    if (arquivos[i] == NULL) {
      printf("Erro ao abrir o arquivo: %s\n", nomesarquivos[i]);
      for (int j = 0; j < i; j++) {
        fclose(arquivos[j]);
      }
      return -1;
    }
  }

  reg *vetor[9];
  int tamanho;

  for (int i = 0; i < 9; i++) {
    if (i % 3 == 0) tamanho = 10000;
    else if (i % 3 == 1) tamanho = 1000;
    else tamanho = 100;

    vetor[i] = malloc(tamanho * sizeof(reg));
    if (vetor[i] == NULL) {
      printf("Erro de alocação de memória\n");
      return -1;
    }

    int indice = 0;
    while (fscanf(arquivos[i], "%d", &vetor[i][indice].chave) == 1) {
      indice++;
    }
    fclose(arquivos[i]);  // Fecha cada arquivo após a leitura
  }


   
  saida = fopen("resp.txt", "a");
  if (saida == NULL) {
    perror("Erro ao abrir arquivo");
    return 1;
  }

  int *mov = malloc(sizeof(int));
  int *comp = malloc(sizeof(int));
  if (!mov || !comp) {
    perror("Erro de alocação de memória");
    return 1;
  }
  

  //Medir tempo, numero de movimentações e comparações de cada algoritmo de ordenação
  struct timespec hora_inicio, hora_fim;
  for (int j = 0; j < 9; j++) {
    *comp = 0;
    *mov = 0;

    // Define o tamanho correto com base no arquivo atual
    tamanho = (j % 3 == 0) ? 10000 : (j % 3 == 1) ? 1000 : 100;
    
    clock_gettime(CLOCK_MONOTONIC, &hora_inicio);
    merge_sort(vetor[j],0, tamanho-1, mov, comp); //Ainda é preciso alterar manualmente a função a ser chamada a cada execução. Tambem se deve alterar o nome no fprintf
    clock_gettime(CLOCK_MONOTONIC, &hora_fim);

    long int tempo = (hora_fim.tv_sec - hora_inicio.tv_sec) * 1000000000L + (hora_fim.tv_nsec - hora_inicio.tv_nsec);

    // Define o tipo do array para a saída correta
    const char *tipo = (j < 3) ? "Aleatorio" : (j < 6) ? "Crescente" : "Decrescente";
    
        
    fprintf(saida, "MergeSort(Array %s de tamanho %d). Tempo = %ld, Movimentações: %d, Comparações: %d\n", tipo, tamanho, tempo, *mov, *comp);
    free(vetor[j]);
  }
  
  free(mov);
  free(comp);
  fclose(saida);

}

