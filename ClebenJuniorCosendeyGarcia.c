#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define t 3
#define MAX (2*t - 1)

typedef int TipoChave;

typedef struct str_no {
    TipoChave chave[MAX];
    struct str_no* filhos[2*t];
    int numChaves;
    bool folha;
} NO;

typedef struct {
    NO* raiz;
} ArvBMais;

bool criaArvoreBMais(ArvBMais* arvore){
    //printf("entrei em criaArvB+\n");

    NO* no;

    if(!(no = (NO*) malloc (sizeof(NO)))) {
        return false;
    }

    no->folha = true;
    no->numChaves = 0;
    arvore->raiz = no;
    return true;
}

void divide(NO* pai, int i, NO* filho){
    //aloca e inicializa novo
    NO* no = (NO*) malloc (sizeof(NO));
    no->folha = filho->folha;
    no->numChaves = t - 1;
    
    if(no->folha)
        no->numChaves++;
    
    int j;
    
    for(j = 0; j < no->numChaves; j++){
        if(no->folha)
           no->chave[j]  = filho->chave[j + t - 1];
        else 
            no->chave[j]  = filho->chave[j + t];
    }
    
    if(!(filho->folha)){
        for(j = 0; j < t; j++){
            no->filhos[j] = filho->filhos[j + t];
        }
    }

    //ajusta filho
    filho->numChaves = t - 1;

    //ajusta pai
    for(j = pai->numChaves; j > i; j--)
        pai->filhos[j + 1] = pai->filhos[j];
    
    pai->filhos[i + 1] = no;

    for(j = pai->numChaves - 1; j >= i; j--)
        pai->chave[j + 1] = pai->chave[j];

    pai->chave[i] = filho->chave[t - 1];
    pai->numChaves++;
}


void insercaoNaoCheio(NO* no, int ch){
    //printf("to na funcao insercao nao cheio e ch = %d\n", ch);
    int i = no->numChaves - 1;
    if(no->folha){
        while(i >= 0 && ch < no->chave[i]){
            no->chave[i + 1] = no->chave[i];
            i--;
        }

        no->chave[i + 1] = ch;
        no->numChaves++;
    }

    else {
        while(i >= 0 && ch < no->chave[i])
            i--;
        
        i++;

        if(no->filhos[i]->numChaves == MAX){
            divide(no, i, no->filhos[i]);

            if(ch > no->chave[i])
                i++;
        }

        insercaoNaoCheio(no->filhos[i], ch);
    }
}

void insercao(ArvBMais* arvB, int ch){
    //printf("inserindo chave: %d\n", ch);
    NO* raiz = arvB->raiz;

    if(raiz->numChaves == MAX){
        //printf("ta cheio\n");
        NO* novo = (NO*) malloc(sizeof(NO));
        arvB->raiz = novo;
        novo->folha = false;
        novo->numChaves = 0;
        novo->filhos[0] = raiz;
        divide(novo, 0, raiz);
        insercaoNaoCheio(novo, ch);
    }
    
    else {
        //printf("nao ta cheio\n");
        insercaoNaoCheio(raiz, ch);
    }
}

void remocao(ArvBMais* arvB, int ch){
    NO* raiz = arvB->raiz;
    
    if(!(raiz->numChaves))
        return;
}

//pra imprimir em arquivo
void imprime(NO* no, FILE* saida){    
    if(!no->numChaves){
        fprintf(saida, "Vazia");
        return;
    }

    fprintf(saida, "(");
    int i;
    for(i = 0; i < no->numChaves; i++){
        if(!(no->folha)){
            imprime(no->filhos[i], saida);
            fprintf(saida, " %d ", no->chave[i]);
        }
        else {
            fprintf(saida, "%d", no->chave[i]);
            if(i < no->numChaves - 1){
                fprintf(saida, " ");
            }
        }
    }
    if(!no->folha)
        imprime(no->filhos[no->numChaves], saida);
    
    fprintf(saida, ")");
}

// pra imprimir no terminal 
/*
void imprime(NO* no){    
    if(!no->numChaves){
        printf("Vazia");
        return;
    }

    printf("(");
    int i;
    for(i = 0; i < no->numChaves; i++){
        if(!(no->folha)){
            imprime(no->filhos[i]);
            printf(" %d ", no->chave[i]);
        }
        else {
            printf("%d", no->chave[i]);
            if(i < no->numChaves - 1){
                printf(" ");
            }
        }
    }
    if(!no->folha)
        imprime(no->filhos[no->numChaves]);
    
    printf(")");
}
*/

// pra ler de arquivo

void leitura(ArvBMais* arvB, FILE* entrada, FILE* saida){
    //printf("funcao leitura\n");
    char comando;
    int valor;

    while(true){
        //printf("insira um comando.\n");
        fscanf(entrada, "%c", &comando);
        
        if(comando != '\n'){
            //printf("o comando atual é: %c\n", comando);
            
            if(comando == 'f')
                break;
        
            if(comando == 'i'){
                //printf("o comando eh i vou tentar inserir\n");

                //printf("insira um valor\n");
                fscanf(entrada, "%d", &valor);
                //printf("o valor atual é: %d\n", valor);

                insercao(arvB, valor);
            }

            if(comando == 'r'){
                //printf("o comando eh r vou tentar remover\n");

                //printf("insira um valor\n");
                fscanf(entrada, "%d", &valor);
                //printf("o valor atual é: %d\n", valor);

                remocao(arvB, valor);
            }
            
            if(comando == 'p'){
                //printf("o comando é p vou tentar imprimir\n");
                imprime(arvB->raiz, saida);
                fprintf(saida, "\n");
            }
        }
    }
}

// pra ler do terminal
/*
void leitura(ArvBMais* arvB){
    printf("funcao leitura\n");
    char comando;
    int valor;

    while(true){
        printf("insira um comando.\n");
        scanf("%c", &comando);
        
        if(comando != '\n'){
            printf("o comando atual é: %c\n", comando);
            
            if(comando == 'f')
                break;
        
            if(comando == 'i'){
                printf("o comando eh i vou tentar inserir\n");

                printf("insira um valor\n");
                scanf("%d", &valor);
                printf("o valor atual é: %d\n", valor);

                insercao(arvB, valor);
            }

            if(comando == 'r'){
                printf("o comando eh r vou tentar remover\n");

                printf("insira um valor\n");
                scanf("%d", &valor);
                printf("o valor atual é: %d\n", valor);

                remocao(arvB, valor);
            }
            
            if(comando == 'p'){
                printf("o comando é p vou tentar imprimir\n");
                imprime(arvB->raiz);
                printf("\n");
            }

        }
    }

}
*/

int main(int argc, char* argv[]){
    //printf("programa funcionando\n");

    char* nome_entrada = argv[1];
    char* nome_saida = argv[2];

    //printf("depois dos chars\n");

    FILE* entrada = fopen(nome_entrada, "r");
    FILE* saida = fopen(nome_saida, "w");

    //printf("depois dos FILEs\n");

    ArvBMais* arvBMais = (ArvBMais*) malloc (sizeof(ArvBMais));

    //printf("antes da funcao de crir a arvore\n");

    criaArvoreBMais(arvBMais);

    //printf("depois de criaArvB+ e antes de leitura\n");

    leitura(arvBMais, entrada, saida);
    
    //leitura(arvBMais);
    

    fclose(entrada);
    fclose(saida);
}
