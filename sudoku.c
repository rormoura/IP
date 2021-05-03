#include <stdio.h>
#include <stdlib.h>

/*
a funcao, primeiramente, aloca dinamicamente uma matriz que ira receber os elementos do arquivo;
depois ela abre o arquivo em modo leitura e usa a fucao fscanf para armazenar na matriz alocada
os elementos do arquivo; se a funcao fopen retornar NULL, a funcao apresenta uma mensagem de erro
e retorna NULL para main
*/
int ** bin2pd(){
    FILE *fileptr = NULL;
    int i = 0, j = 0, **matriz;
    matriz = (int **) calloc(9, sizeof(int *));
    for(i = 0; i < 9; i++){
        matriz[i] = (int *) calloc(9, sizeof(int));
    }
    fileptr = fopen("C:\\Users\\Pichau\\Desktop\\2020.3\\testehoje.txt", "rt"); // abrindo o arquivo
    if(fileptr != NULL){ // conferindo se a abertura ocorreu com sucesso
        for(i = 0; i < 9; i++){
            for(j = 0; j < 9; j++){ // lendo os elementos da matriz que esta no arquivo
                if(j != 8) fscanf(fileptr ,"%d ", &matriz[i][j]);
                else fscanf(fileptr ,"%d\n", &matriz[i][j]);
            }
        }
        fclose(fileptr);
        return matriz;
    }
    printf("Erro na abertura do arquivo\n");
    fclose(fileptr);
    return NULL;
}

/*
Raciocinio da funcao: a funcao consiste em verificar se cada numero ,de 1 a 9,
aparece na submatriz determinada por i e j. Um ponto importante dessa funcao eh que
passamos a array numeros[9] e a matriz por referencia, por isso, a funcao submatriz3x3()
pode trabalhar com a array numeros[9] corretamente. Por outro lado, i e j sao passados
por valor, desse modo, os lacos for da funcao submatriz3x3() nao sao afetados.
*/
void submatriz3x3(int *numeros, int **matriz, int i, int j){
    int a = 0, b = 0;
    for(a = i; a < i+3; a++){
        for(b = j; b < j+3; b++){
            if(matriz[a][b] == 1) numeros[0]++;
            else if(matriz[a][b] == 2) numeros[1]++;
            else if(matriz[a][b] == 3) numeros[2]++;
            else if(matriz[a][b] == 4) numeros[3]++;
            else if(matriz[a][b] == 5) numeros[4]++;
            else if(matriz[a][b] == 6) numeros[5]++;
            else if(matriz[a][b] == 7) numeros[6]++;
            else if(matriz[a][b] == 8) numeros[7]++;
            else if(matriz[a][b] == 9) numeros[8]++;
        }
    }
}

/*
Raciocinio da funcao: primeiro criei duas arrays, a array erroInt[9] armazena se alguma
das nove submatrizes 3x3 possui um erro, ja a array numeros[9] armazena a quantidade
de vezes que cada numero (de 1 a 9) aparece numa submatriz 3x3.
Depois disso, a funcao entra em dois lacos for e chama a funcao submatrizr3x3() que
opera segundo os parametros dados.
Por fim,a funcao verifica se em alguma das submatrizes 3x3 ha um erro.
Se houver a funcao retorna o indice da respectiva submatriz.
*/
int verificaMatInterna(int **matriz){
    int erroInt[9], numeros[9], submatriz = -1;
    int i = 0, j = 0, l = 0, k = 0;
    for(i = 0; i < 9; i++){
        erroInt[i] = 0;
        numeros[i] = 0;
    }
    for(i = 0; i <= 6; i+= 3){
        for(j = 0; j <= 6; j+= 3){
            submatriz3x3(numeros, matriz, i, j);
            for(l = 0; l < 9; l++){
                if(numeros[l] != 1) erroInt[k]++;
            }
            for(l = 0; l < 9; l++){
                numeros[l] = 0;
            }
            k++; // eh esperado que o k inicie em 0 e termine em 8
        }
    }
    for(i = 0; i < 9; i++){
        if(erroInt[i] > 0) submatriz = i;
    }
    return submatriz;
}

/*
Raciocinio da funcao: Nessa funcao criei duas matrizes 9x9 (linha e coluna) que
vao ser preenchidas pela numero de ocorrencia de cada numero (de 1 a 9) em cada linha
e coluna. O esperado de um sudoku correto eh que em cada linha e em cada coluna, os
numeros aparecam somente uma vez.
*/
int verificaMatGlobal(int **matriz){
    int erroGlobal = 0;
    int linha[9][9], coluna[9][9], i = 0, j = 0;
    for(i = 0; i < 9; i++){
        for(j = 0; j < 9; j++){
            linha[i][j] = 0;
            coluna[i][j] = 0;
        }
    }
    for(i = 0; i < 9; i++){
        for(j = 0; j < 9; j++){ // verificando linhas
            if(matriz[i][j] == 1) linha[i][0]++;
            else if(matriz[i][j] == 2) linha[i][1]++;
            else if(matriz[i][j] == 3) linha[i][2]++;
            else if(matriz[i][j] == 4) linha[i][3]++;
            else if(matriz[i][j] == 5) linha[i][4]++;
            else if(matriz[i][j] == 6) linha[i][5]++;
            else if(matriz[i][j] == 7) linha[i][6]++;
            else if(matriz[i][j] == 8) linha[i][7]++;
            else if(matriz[i][j] == 9) linha[i][8]++;
        }
    }
    for(i = 0; i < 9; i++){
        for(j = 0; j < 9; j++){ // verificando colunas
            if(matriz[j][i] == 1) coluna[i][0]++;
            else if(matriz[j][i] == 2) coluna[i][1]++;
            else if(matriz[j][i] == 3) coluna[i][2]++;
            else if(matriz[j][i] == 4) coluna[i][3]++;
            else if(matriz[j][i] == 5) coluna[i][4]++;
            else if(matriz[j][i] == 6) coluna[i][5]++;
            else if(matriz[j][i] == 7) coluna[i][6]++;
            else if(matriz[j][i] == 8) coluna[i][7]++;
            else if(matriz[j][i] == 9) coluna[i][8]++;
        }
    }
    for(i = 0; i < 9; i++){
        for(j = 0; j < 9; j++){ // verificando cada numero nas linhas e colunas
            if(linha[i][j] != 1 || coluna[i][j] != 1) erroGlobal = 1;
        }
    }
    return erroGlobal;
}
int main(){
    int **matriz = NULL, i = 0, j = 0;
    int erroInt = 0, erroGlobal = 0;
    matriz = (int **) calloc(9, sizeof(int *)); // alocando as linhas
    for(i = 0; i < 9; i++){
        matriz[i] = (int *) calloc(9, sizeof(int)); // alocando as colunas
    }
    matriz = bin2pd();
    for(i = 0; i < 9; i++){
        for(j = 0; j < 9; j++){
            printf("%d%c", matriz[i][j], j == 8 ? '\n' : ' ');
        }
    }
    if(matriz != NULL){
        erroInt = verificaMatInterna(matriz);
        erroGlobal = verificaMatGlobal(matriz);
        if(erroInt != -1 && erroGlobal == 0){
            printf("Solucao Invalida!\nErro na submatriz %d.", erroInt+1);
        }
        else if(erroInt == -1 && erroGlobal == 1){
            printf("Solucao Invalida!\nErro na matrizGlobal.");
        }
        else if(erroInt != -1 && erroGlobal == 1){
            printf("Solucao Invalida!\nErro na submatriz %d.", erroInt+1);
        }
        else printf("Solucao Valida!");
    }
    // dando free nos ponteiros
    for(i = 0; i < 9; i++){
        free(matriz[i]);
    }
    free(matriz);
    return 0;
}
