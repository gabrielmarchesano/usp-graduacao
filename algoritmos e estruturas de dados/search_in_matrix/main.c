/*
Devido ao uso da biblioteca math.h, no momento da compilação é necessário que a compilaçao seja completada com o comando -lm
Sendo assim compilei desta forma: gcc ep1_15453229.c -lm -o ep1_15453229
Exemplo de execução do programa : ./ep1_15453229 16 entrada.txt saida.txt
Na execução a ordem dos parametros é <(numero, arquivo de entrada, arquivo de saida)> tal como no exemplo acima

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>



void posicoes(int **m, int *ix_max, int *iy_max, int *ix_min, int *iy_min, int *max, int *min, int N) {

//Função percorre a matriz, e quando encontra o valor máximo e mínimo, e as variaveis de indice/posiçao recebem os valores de linha e coluna para o qual se encontra o valor encontrado. 
//No caso em que pode haver mais de um valor que seja igual ao máximo e/ou mínimo, o goto min e goto fim são executados para que o valor de linha e coluna recebidos sejam o de menor linha, e menor coluna, nessa ordem de prioridade. A forma na qual ocorrem as iterações garante que essa condição ocorra.

      
      for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                  if(m[i][j] == *max) {
                        *ix_max = i;
                        *iy_max = j;
                        goto min;
                  }
                  
            }
      }  
      min:               
      for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                  if(m[i][j] == *min) {
                        *ix_min = i;
                        *iy_min = j;
                        goto fim;
                  }
                  
            }
      }
   fim:
}

int acha_max(int **m, int l_esq, int c_esq ,int l_dir, int c_dir) {
//A função define um máximo atual, que recebe o valor máximo dentre os 4 valores da matriz 2x2. Esse valor é calculado pela função fmax, que compara inteiros, da biblioteca math.h
      int max_atual;
      max_atual = fmax(fmax(m[l_esq][c_esq], m[l_esq][c_dir]), fmax(m[l_dir][c_esq], m[l_dir][c_dir]));
          
      return max_atual;             
}


int acha_min(int **m, int l_esq, int c_esq ,int l_dir, int c_dir) {
//A função define um minímo atual, que recebe o valor mínimo dentre os 4 valores da matriz 2x2. Esse valor é calculado pela função fmin, que compara inteiros dois inteiros, da biblioteca math.h
      int min_atual;
      min_atual = fmin(fmin(m[l_esq][c_esq], m[l_esq][c_dir]), fmin(m[l_dir][c_esq], m[l_dir][c_dir]));
          
      return min_atual;
}
 
 
 
void div_conq(int **m, int l_esq, int c_esq , int l_dir, int c_dir, int *max, int *min) {

//Aqui ocorre a divisão e conquista. A matriz é dividida recusivamente em 4 quadrantes até formar uma matriz 2x2, quando ocorre a chamada das funções acha_max e acha_min. Os valores máximo e mínimo encontrado na matriz 2x2 são comparados com o máximo e mínimo das matrizes 2x2 que foram analizadas anteriormente, resultando no máximo global ao fim das chamadas recursivas
//Caso a matriz seja 1x1, isto é, um único elemento, o valor máximo e mínimo é o próprio

      if(l_esq == l_dir && c_esq == c_dir) {
          *max = m[l_esq][c_esq];
          *min = m[l_esq][c_esq];
      }
        
      else if (l_dir - l_esq == 1 && c_dir - c_esq == 1) {
            *max= fmax(acha_max(m, l_esq, c_esq, l_dir, c_dir), *max);
            *min= fmin(acha_min(m, l_esq, c_esq, l_dir, c_dir), *min);
      }
  
      else {    
            int l_meio = (l_esq + l_dir)/2; 
            int c_meio = (c_esq + c_dir)/2;
        
            div_conq(m, l_esq, c_esq, l_meio, c_meio, max, min);
            div_conq(m , l_esq, c_meio+1, l_meio, c_dir, max, min);
            div_conq(m, l_meio +1 ,c_esq, l_dir, c_meio, max, min);
            div_conq(m, l_meio + 1,c_meio + 1, l_dir, c_dir, max, min);
          
      } 
       
return ;   
}


int main(int argc , char *argv[]) {
      
      //Verifica se o número de argumentos passados no terminal está correta
      if(argc != 4) {
            printf("Os parâmetro passados no terminal são inválidos");
            return -1;
      }
      
      int **matriz; //Matriz será criada a partir de um ponteiro duplo
      int N = atoi(argv[1]); //N é a ordem da matriz
      
      //Verificando se o N é uma potência de 2. Sendo N máximo 64
      int test = N;
      if(test<1 || test>64) {
            printf("Tamanho da matriz invalido");
            return 1;
      } 
      else {
            while(test>1) { 
                  if(test%2 == 0){
                        test = test/2;
                
                  }
                  else {
                        printf("Tamanho da matriz invalido");
                        return 1;
                  }
            }
      }
      
       
      
      //Cria a matriz NxN usando alocação dinamica
      matriz = (int **)malloc(N * sizeof(int *));  
      for (int i = 0; i < N; i++)  {
            matriz[i] = (int *)malloc(N * sizeof(int));  
      }
      
      
      FILE *entrada, *saida; //cria os ponteiros para arquivo
      
        
      // Abra o arquivo para leitura
      entrada = fopen(argv[2], "r");
      if (entrada == NULL) {
            perror("Erro ao abrir o arquivo");
            return 1;
      }
      
      //cria um array auxiliar para armazenar os valores da matriz do arquivo entrada
      int *aux;   
      aux = (int*)malloc((N*N)*sizeof(int));
      
      int indice = 0;
      // Leitura da matriz a partir do arquivo
      while (!feof(entrada)) {     
      // Leia a matriz e armazene os valores no array auxiliar
            while (fscanf(entrada, "%d", &aux[indice]) == 1) {
                  indice++;
            }
      }
      
      //Verifica se o tamanho da matriz do arquivo é de fato o valor de N passado como parâmetro no terminal"
      int tamanho = (indice +1)/N;
      if(tamanho != N) {
            printf("O valor passado como parametro nao corresponde ao tamanho da matriz do arquivo de entrada");
            return 1;
      }
      
      // Fecha o arquivo após a leitura
      fclose(entrada);
    
  
      //Passa os valores do array auxiliar para a matriz criada no início
      int k=0;
      for (int i = 0; i < N; i++) {  
            for (int j = 0; j < N; j++) {
                   matriz[i][j] = aux[k];
                   k++;
            }
      }
      //Libera a memória do array auxiliar
      free(aux);
      
      //Verifica se os valores passados na matriz são válidos, isto é, pertencem ao intervalo (0,255)
      for(int a=0; a<N; a++){
            for(int b=0; b<N; b++){
                  if(matriz[a][b] < 0 || matriz[a][b] > 255){
                        printf("Valor invalido na pos(%d, %d)",a, b);
                        return 1;
                  }
            }
      }
      
      //Como os valores max_global min_global seram passados como argumentos para a função em que ocorrerá a divisão e conquista, e na que encontra o mínimo da função, convem que o valor inicial seja um valor que esteja fora do intervalo entre 0 e 255. No caso do máximo um valor menor que 0 e do mínimo um maior que 255, assim não prejudicando as comparações entre valores para encontrar maximo e minimo;
      int max_global = -1;
      int min_global = 256; 
      
      
      //Essas variáveis representam as posições de linha e coluna em que os valores máximo e mínimo se encontram na matriz
      int posl_max, posc_max, posl_min, posc_min; 
      
      //Chamada das funções que realizam a divisão e conquista, e a busca pelas posições   
      div_conq(matriz, 0, 0, N - 1, N - 1, &max_global, &min_global); 
      //printf("%d", N );
      posicoes(matriz, &posl_max, &posc_max, &posl_min, &posc_min, &max_global, &min_global, N);
      
      
      //Libera memória da matriz
      for (int i = 0; i < N; i++)  {
          free (matriz[i]);  }
      free(matriz);  
        
        
      //Abre o arquivo de saída 
      saida = fopen(argv[3], "w+");
      if (saida == NULL) {
            perror("Erro ao abrir o arquivo");
            return 1;
      }
      
      //Escreve no arquivo de saída
      fprintf(saida, "min = %d; pos = (%d, %d)\nmax = %d; pos(%d, %d)", min_global, posl_min, posc_min, max_global, posl_max, posc_max);
     
      //Fecha o arquivo de saída
      fclose(saida);
  
      return 0;
}




