#include <stdio.h>
#include <stdlib.h>
int main(){
    int x, contador = 0;
    scanf("%d", &x);
    if(x != 1){
        for(int i = 2; i*i <= x; i++){
            if(x %i == 0) contador++;
        }
        if(contador == 0) printf("%d eh primo", x);
        else printf("%d nao eh primo", x);
    }
    else printf("1 nao eh primo");
    return 0;
}
