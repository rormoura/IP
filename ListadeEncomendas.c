#include <stdio.h>
#include <stdlib.h>
/*
estrutura que descreve cada encomenda
*/
typedef struct{
    int id_encomenda;
    char endereco[100];
    char destinatario[100];
} encomenda;
/*
Para encontrar o tamanho exato de encomendas, a fim de alocar somente o necesario para o vetor, uso a
funcao fseek() deslocando o cursor do arquivo para o final dele, logo apos, utilizo a funcao
ftell() que, nesse caso, retorna a quantidade de bytes do arquivo; por isso a quantidade de
encomendas eh ftell(fileptr)/sizeof(encomenda).
*/
encomenda * obterEncomendas(int *qtEncomendas){
    int i = 0;
    encomenda *vetor = NULL;
    FILE *fileptr;
    fileptr = fopen("C:\\Users\\Pichau\\Desktop\\teywhrhrtrtg.txt", "r"); // abrindo o arquivo
    if(fileptr == NULL){ // verificando se houve erro na abertura do arquivo
        printf("Erro na abertura do arquivo.\n");
        exit(1);
    }
    fseek(fileptr, 0, SEEK_END); // movimento o cursor para o final do arquivo
    *qtEncomendas = ftell(fileptr)/sizeof(encomenda); // o resultado da divisao da a quantidade de encomendas
    vetor = (encomenda *) malloc(26*sizeof(encomenda)); // alocando o vetor de encomendas
    if(vetor == NULL){ // verificando se houve erro na alocacao do vetor
        printf("Erro na alocacao do vetor.\n");
        exit(1);
    }
    while(!feof(fileptr)){
        fscanf(fileptr, "%d", &vetor[i].id_encomenda);
        fscanf(fileptr, "%s", vetor[i].endereco);
        fscanf(fileptr, "%s", vetor[i].destinatario);
        i++;
    }
    fclose(fileptr); // fechando o arquivo
    return vetor; // retorna o vetor alocado e preenchido
}
/*
Primeiramente, a funcao procura no vetor de encomendas se ha o id digitado por Josue.
Se sim, a ultima encomenda do vetor toma o lugar da encomenda ja entregue
e tanto o vetor como a qtEncomendas sao subtraidos de uma unidade. Por fim, eh impressa a
quantidade restante de encomendas. A variavel flag faz com que uma vez encontrada a encomenda,
o programa saia do laco for e retorne para a main. Se nao encontrado o id, eh mostrada uma mensagem dizendo que
o id digitado nao foi encontrado e ,entao, o programa volta para a main.
*/
void entregarEncomenda(int id, encomenda *encomendas, int *qtEncomendas){
    int i = 0, flag = 1;
    for(i = 0; i < (*qtEncomendas) && flag; i++){
        if(id == encomendas[i].id_encomenda){
            encomendas[i] = encomendas[(*qtEncomendas-1)];
            (*qtEncomendas)--;
            encomendas = (encomenda *) realloc(encomendas, (*qtEncomendas)*sizeof(encomenda));
            if(encomendas == NULL){ // verifica se houve erro na realocacao do vetor
                printf("Erro na alocacao do vetor.\n.");
                exit(1);
            }
            printf("Entregas restantes: %d.\n", *qtEncomendas);
            flag = 0;
        }
    }
    if(flag == 1) printf("ID nao encontrado.\n");
}

/*
A funcao abre o arquivo no modo de escrita (wb) e, por isso, reescreve o arquivo
com o novo vetor de encomendas (com as encomendas entregues removidas). Por fim, eh impressa
a mensagem "Entregas finalizadas." e o programa acaba.
*/
void finalizarEntregas(encomenda *encomendas, int qtEncomendas){
    FILE *fileptr;
    fileptr = fopen("C:\\Users\\Pichau\\Desktop\\teywhrhrtrtg.txt", "w");
    if(fileptr == NULL){
        printf("Erro na abertura do arquivo.\n");
        exit(1);
    }
    fread(encomendas, sizeof(encomenda), qtEncomendas, fileptr);
    printf("Entregas finalizadas.\n");
    fclose(fileptr); // fechando o arquivo
}

int main(){
    int qtEncomendas = 0, escolha = 0, id = 0;
    encomenda *encomendas = NULL;
    encomendas = obterEncomendas(&qtEncomendas);
    /*while(escolha != 2){
        printf("Opcoes:\n");
        printf("\t1 - Remover encomenda entregue.\n\t2 - Finalizar entregas.\n\t");
        scanf("%d", &escolha);
        if(escolha == 1){
            printf("Digite o id da encomenda entregue: ");
            scanf("%d", &id);
            entregarEncomenda(id, encomendas, &qtEncomendas);
        }
        else{
            finalizarEntregas(encomendas, qtEncomendas);
        }
    }
    */
    for(int i = 0; i < 26; i++){
        printf("%d\n", encomendas[i].id_encomenda);
        printf("%s\n", encomendas[i].endereco);
        printf("%s\n", encomendas[i].destinatario);
    }
    free(encomendas); // dando free no vetor de encomendas
}
