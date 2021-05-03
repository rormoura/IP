#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int linha;
    int coluna;
    char direcao[3];
}Palavra;

/*
A funcao realiza:
1 - Abre o arquivo.
2 - Armazena a dimensao da matriz
3 - Armazena a matriz de caracteres do arquivo na variavel matriz.
4 - Armazena a sequencia de palavras em Vet_Palavras.
5 - Retorna a matriz preenchida para a main.
*/
char **leCacaPalavras(int *N, char Vet_Palavras[30][20]){
    int i = 0, j = 0;
    char **matriz = NULL; // ponteiro "zerado"
    FILE *fileptr;
    fileptr = fopen("teste.txt", "rt"); // abrindo o arquivo
    if(fileptr == NULL){ // verificando se houve erro na abertura do arquivo
        printf("Erro na abertura do arquivo.\n");
        exit(1);
    }
    fscanf(fileptr, "%d", N); // le a dimensao da matriz
    matriz = (char **) realloc(matriz, (*N) * sizeof(char *)); // alocando as linhas
    if(matriz == NULL){ // verificando se houve erro na alocacao da matriz
        printf("Erro na alocacao da matriz.\n");
        exit(1);
    }
    for(i = 0; i < (*N); i++){
        matriz[i] = (char *) malloc((*N) * sizeof(char)); // alocando as colunas
        if(matriz[i] == NULL){ // verificando se houve erro na alocacao da matriz
            printf("Erro na alocacao da matriz.\n");
            exit(1);
        }
    }
    for(i = 0; i < (*N); i++){
        for(j = 0; j < (*N); j++){
            fscanf(fileptr, " %c", &matriz[i][j]); // lendo os caracteres que compoem o caca-palavras
        }
    }
    i = 0;
    while(!feof(fileptr)){ // enquanto o arquivo nao acabar, armazena em Vet_Palavras[i] a palavra que deseja ser procurada
        fscanf(fileptr, " %s", Vet_Palavras[i]);
        i++;
    }
    fclose(fileptr); // fechando o arquivo
    return matriz; // retornando para a main a matriz preenchida
}

/*
Raciocinio das funcoes das direcoes: Cada funcao percorre a matriz que contem o caca-palavras
numa determinada direcao, armazenando cada caractere numa string temporaria.
Depois compara essa string temporaria com a palavra que esta sendo procurada,
se forem iguais a funcao retorna 1 para ProcuraPalavra(), caso contrario, retorna 0.
*/
// iteracao NORTE: as linhas sao subtraidas de uma unidade, as colunas sao mantidas
int proc_N(char **matriz, int N, char Vet_Palavras[30][20], int i, int j, int m){
    int k = 0;
    char palavratmp[strlen(Vet_Palavras[m])];
    for(k = 0; i >= 0 && k < strlen(palavratmp); i--, k++){
        palavratmp[k] = matriz[i][j];
    }
    if(strcmp(palavratmp, Vet_Palavras[m]) == 0) return 1;
    return 0;
}
// iteracao NORDESTE: as linhas sao subtraidas de uma unidade, as colunas sao acrescidas de uma unidade
int proc_NE(char **matriz, int N, char Vet_Palavras[30][20], int i, int j, int m){
    int k = 0;
    char palavratmp[strlen(Vet_Palavras[m])];
    for(k = 0; i >= 0 && j < N && k < strlen(palavratmp); i--, j++, k++){
        palavratmp[k] = matriz[i][j];
    }
    if(strcmp(palavratmp, Vet_Palavras[m]) == 0) return 1;
    return 0;
}
// iteracao LESTE: as linhas sao mantidas, as colunas sao acrescidas de uma unidade
int proc_L(char **matriz, int N, char Vet_Palavras[30][20], int i, int j, int m){
    int k = 0;
    char palavratmp[strlen(Vet_Palavras[m])];
    for(k = 0; j < N && k < strlen(palavratmp); j++, k++){
        palavratmp[k] = matriz[i][j];
    }
    if(strcmp(palavratmp, Vet_Palavras[m]) == 0) return 1;
    return 0;
}
// iteracao SUDESTE: ambas linhas e colunas sao acrescidas de uma unidade
int proc_SE(char **matriz, int N, char Vet_Palavras[30][20], int i, int j, int m){
    int k = 0;
    char palavratmp[strlen(Vet_Palavras[m])];
    for(k = 0; j < N && i < N && k < strlen(palavratmp); j++, i++, k++){
        palavratmp[k] = matriz[i][j];
    }
    if(strcmp(palavratmp, Vet_Palavras[m]) == 0) return 1;
    return 0;
}
// iteracao SUL: as linhas sao acrescidas de uma unidade, as colunas sao mantidas
int proc_S(char **matriz, int N, char Vet_Palavras[30][20], int i, int j, int m){
    int k = 0;
    char palavratmp[strlen(Vet_Palavras[m])];
    for(k = 0; i < N && k < strlen(palavratmp); i++, k++){
        palavratmp[k] = matriz[i][j];
    }
    if(strcmp(palavratmp, Vet_Palavras[m]) == 0) return 1;
    return 0;
}
// iteracao SUDOESTE: as linhas sao acrescidas de uma unidade, as colunas sao subtraidas de uma unidade
int proc_SO(char **matriz, int N, char Vet_Palavras[30][20], int i, int j, int m){
    int k = 0;
    char palavratmp[strlen(Vet_Palavras[m])];
    for(k = 0; i < N && j >= 0 && k < strlen(palavratmp); i++, j--, k++){
        palavratmp[k] = matriz[i][j];
    }
    if(strcmp(palavratmp, Vet_Palavras[m]) == 0) return 1;
    return 0;
}
// iteracao OESTE: as linhas sao mantidas, as colunas sao subtraidas de uma unidade
int proc_O(char **matriz, int N, char Vet_Palavras[30][20], int i, int j, int m){
    int k = 0;
    char palavratmp[strlen(Vet_Palavras[m])];
    for(k = 0; j >= 0 && k < strlen(palavratmp); j--, k++){
        palavratmp[k] = matriz[i][j];
    }
    if(strcmp(palavratmp, Vet_Palavras[m]) == 0) return 1;
    return 0;
}
// iteracao NOROESTE: ambas linhas e colunas sao subtraidas de uma unidade
int proc_NO(char **matriz, int N, char Vet_Palavras[30][20], int i, int j, int m){
    int k = 0;
    char palavratmp[strlen(Vet_Palavras[m])];
    for(k = 0; i >= 0 && j >= 0 && k < strlen(palavratmp); i--, j--, k++){
        palavratmp[k] = matriz[i][j];
    }
    if(strcmp(palavratmp, Vet_Palavras[m]) == 0) return 1;
    return 0;
}
/*
A funcao tem tres lacos for aninhados: o primeiro eh para varrer cada primeiro
caractere de cada palavra presente Vet_Palavras. O segundo e o terceiro sao as linhas
e as colunas, respectivamente, da matriz (caca-palavras).
Se o caractere for igual a primeira letra da palavra que esta sendo procurada, a funcao
entra num if e comeca a chamar cada uma das oitos funcoes correspondentes as direcoes.
Se a funcao da direcao retorna 1, Vet_Encontradas eh atualizado com as informacoes referentes a palavra
encontrada.
Ao final a funcao retorna o Vet_Encontradas para a main.
*/
Palavra *ProcuraPalavra(char **matriz, int N, char Vet_Palavras[30][20], int *tam){
    Palavra *Vet_Encontradas = NULL;
    int i = 0, j = 0, k = 0;
    for(k = 0; k < 30; k++){ // procura as 30 palavras no caca-palavras (variavel matriz)
        for(i = 0; i < N; i++){
            for(j = 0; j < N; j++){
                if(matriz[i][j] == Vet_Palavras[k][0]){
                    if(proc_N(matriz, N, Vet_Palavras, i, j, k)){ // NORTE
                        Vet_Encontradas = (Palavra *) realloc(Vet_Encontradas, ((*tam)+1) * sizeof(Palavra));
                        if(Vet_Encontradas == NULL){
                            printf("Erro na alocacao do vetor.\n");
                            exit(1);
                        }
                        Vet_Encontradas[(*tam)].linha = i; // linha onde a primeira letra da palavra procurada foi encontrada
                        Vet_Encontradas[(*tam)].coluna = j; // coluna onde a primeira letra da palavra procurada foi encontrada
                        strcpy(Vet_Encontradas[(*tam)].direcao, "N"); // direcao para onde as letras estao dispostas
                        i = N + 1;
                        j = N + 1;
                        (*tam)++;
                    }
                    else if(proc_NE(matriz, N, Vet_Palavras, i, j, k)){ // NORDESTE
                        Vet_Encontradas = (Palavra *) realloc(Vet_Encontradas, ((*tam)+1) * sizeof(Palavra));
                        if(Vet_Encontradas == NULL){
                            printf("Erro na alocacao do vetor.\n");
                            exit(1);
                        }
                        Vet_Encontradas[(*tam)].linha = i; // linha onde a primeira letra da palavra procurada foi encontrada
                        Vet_Encontradas[(*tam)].coluna = j; // coluna onde a primeira letra da palavra procurada foi encontrada
                        strcpy(Vet_Encontradas[(*tam)].direcao, "NE"); // direcao para onde as letras estao dispostas
                        i = N + 1;
                        j = N + 1;
                        (*tam)++;
                    }
                    else if(proc_L(matriz, N, Vet_Palavras, i, j, k)){ // LESTE
                        Vet_Encontradas = (Palavra *) realloc(Vet_Encontradas, ((*tam)+1) * sizeof(Palavra));
                        if(Vet_Encontradas == NULL){
                            printf("Erro na alocacao do vetor.\n");
                            exit(1);
                        }
                        Vet_Encontradas[(*tam)].linha = i; // linha onde a primeira letra da palavra procurada foi encontrada
                        Vet_Encontradas[(*tam)].coluna = j; // coluna onde a primeira letra da palavra procurada foi encontrada
                        strcpy(Vet_Encontradas[(*tam)].direcao, "L"); // direcao para onde as letras estao dispostas
                        i = N + 1;
                        j = N + 1;
                        (*tam)++;
                    }
                    else if(proc_SE(matriz, N, Vet_Palavras, i, j, k)){ // SUDESTE
                        Vet_Encontradas = (Palavra *) realloc(Vet_Encontradas, ((*tam)+1) * sizeof(Palavra));
                        if(Vet_Encontradas == NULL){
                            printf("Erro na alocacao do vetor.\n");
                            exit(1);
                        }
                        Vet_Encontradas[(*tam)].linha = i; // linha onde a primeira letra da palavra procurada foi encontrada
                        Vet_Encontradas[(*tam)].coluna = j; // coluna onde a primeira letra da palavra procurada foi encontrada
                        strcpy(Vet_Encontradas[(*tam)].direcao, "SE"); // direcao para onde as letras estao dispostas
                        i = N + 1;
                        j = N + 1;
                        (*tam)++;
                    }
                    else if(proc_S(matriz, N, Vet_Palavras, i, j, k)){ // SUL
                        Vet_Encontradas = (Palavra *) realloc(Vet_Encontradas, ((*tam)+1) * sizeof(Palavra));
                        if(Vet_Encontradas == NULL){
                            printf("Erro na alocacao do vetor.\n");
                            exit(1);
                        }
                        Vet_Encontradas[(*tam)].linha = i; // linha onde a primeira letra da palavra procurada foi encontrada
                        Vet_Encontradas[(*tam)].coluna = j; // coluna onde a primeira letra da palavra procurada foi encontrada
                        strcpy(Vet_Encontradas[(*tam)].direcao, "S"); // direcao para onde as letras estao dispostas
                        i = N + 1;
                        j = N + 1;
                        (*tam)++;
                    }
                    else if(proc_SO(matriz, N, Vet_Palavras, i, j, k)){ // SUDOESTE
                        Vet_Encontradas = (Palavra *) realloc(Vet_Encontradas, ((*tam)+1) * sizeof(Palavra));
                        if(Vet_Encontradas == NULL){
                            printf("Erro na alocacao do vetor.\n");
                            exit(1);
                        }
                        Vet_Encontradas[(*tam)].linha = i; // linha onde a primeira letra da palavra procurada foi encontrada
                        Vet_Encontradas[(*tam)].coluna = j; // coluna onde a primeira letra da palavra procurada foi encontrada
                        strcpy(Vet_Encontradas[(*tam)].direcao, "SO"); // direcao para onde as letras estao dispostas
                        i = N + 1;
                        j = N + 1;
                        (*tam)++;
                    }
                    else if(proc_O(matriz, N, Vet_Palavras, i, j, k)){ // OESTE
                        Vet_Encontradas = (Palavra *) realloc(Vet_Encontradas, ((*tam)+1) * sizeof(Palavra));
                        if(Vet_Encontradas == NULL){
                            printf("Erro na alocacao do vetor.\n");
                            exit(1);
                        }
                        Vet_Encontradas[(*tam)].linha = i; // linha onde a primeira letra da palavra procurada foi encontrada
                        Vet_Encontradas[(*tam)].coluna = j; // coluna onde a primeira letra da palavra procurada foi encontrada
                        strcpy(Vet_Encontradas[(*tam)].direcao, "O"); // direcao para onde as letras estao dispostas
                        i = N + 1;
                        j = N + 1;
                        (*tam)++;
                    }
                    else if(proc_NO(matriz, N, Vet_Palavras, i, j, k)){ // NOROESTE
                        Vet_Encontradas = (Palavra *) realloc(Vet_Encontradas, ((*tam)+1) * sizeof(Palavra));
                        if(Vet_Encontradas == NULL){
                            printf("Erro na alocacao do vetor.\n");
                            exit(1);
                        }
                        Vet_Encontradas[(*tam)].linha = i; // linha onde a primeira letra da palavra procurada foi encontrada
                        Vet_Encontradas[(*tam)].coluna = j; // coluna onde a primeira letra da palavra procurada foi encontrada
                        strcpy(Vet_Encontradas[(*tam)].direcao, "NO"); // direcao para onde as letras estao dispostas
                        i = N + 1;
                        j = N + 1;
                        (*tam)++;
                    }
                }
            }
        }
    }
    return Vet_Encontradas;
}
/*
A Funcao abre um arquivo binario com "wb" e escvre nele, por meio da funcao
fscanf, o vetor Vet_Encontradas que contem as estruturas das palavras encontradas.
*/
void EscreveEncontradas(Palavra *Vet_Encontradas, int tam){
    FILE *fileptr;
    fileptr = fopen("Palavras_Encontradas.bin", "wb"); // abrindo arquivo
    if(fileptr == NULL){
        printf("Erro na abertura do arquivo.\n");
        exit(1);
    }
    fwrite(Vet_Encontradas, sizeof(Palavra), tam, fileptr);
    printf("Operacao realizada com sucesso.\n");
    fclose(fileptr);
}
int main(){
    Palavra *Vet_Encontradas = NULL; // vetor dinamico de estrutura Palavra
    int i = 0, tam = 0, N = 0; // N = dimensao da matriz, tam = tamanho de Vet_Encontradas
    char **matriz; // o ponteiro que vai receber a matriz
    char Vet_Palavras[30][20];
    // Lendo o arquivo
    matriz = leCacaPalavras(&N, Vet_Palavras);
    // Procurando pelas palavras
    Vet_Encontradas = ProcuraPalavra(matriz, N, Vet_Palavras, &tam);
    // Escrevendo em um novo arquivo o vetor de estrutura CacaPalavra
    EscreveEncontradas(Vet_Encontradas, tam);
    // Dando free nos ponteiros
    free(Vet_Encontradas);
    for(i = 0; i < N; i++) free(matriz[i]);
    free(matriz);
    // fim :)
    return 0;
}
