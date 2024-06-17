#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define t 3

typedef int TipoChave;

typedef struct str_no {
    TipoChave chave[2*t - 1];
    struct str_no* filhos[2*t];
    int numChaves;
    bool folha;
} NO;

typedef struct {
    NO* raiz;
} ArvBMais;

bool criaArvoreBMais(ArvBMais* arvore){
    NO* x;
    if(!(x = (NO*) malloc (sizeof(NO)))) {
        return false;
    }

    x->folha = true;
    x->numChaves = 0;
    arvore->raiz = x;
    return true;
}

void leitura(ArvBMais* arvB, FILE* entrada){
    char comando;
    int valor;
    while(true){
        scanf("%c", &comando);
        if (comando != 'p')
            scanf("%d", valor);
        
        if(comando == 'i')
            //inserir

        if(comando == 'r') 
            //remover
        
        if(comando == 'p')
            //imprimir

        if(comando == 'f')
            break;
    }
}

int main(int argc, char* argv[]){
    printf("programa funcionando\n");
    char* entrada = argv[1];
    char* saida = argv[2];
    FILE* fp;
    fp = fopen(entrada, "r");

    ArvBMais arvB;

    leitura(&arvB, entrada);
}
