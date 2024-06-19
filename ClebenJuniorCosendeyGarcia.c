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
    printf("entrei em criaArvB+\n");

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
    NO* novo = (NO*) malloc (sizeof(NO));
    novo->folha = filho->folha;
    novo->numChaves = t - 1;
    int j;
    for(j = 0; j < novo->numChaves; j++)
        novo->chave[j]  = filho->chave[j + t];
    
    if(!(filho->folha)){
        for(j = 0; j < t; j++){
            novo->filhos[j] = filho->filhos[j + t];
        }
    }
    //ajusta filho
    filho->numChaves = t - 1;
    //ajusta pai
    for(j = pai->numChaves; j > i; j--)
        pai->filhos[j + 1] = pai->filhos[j];
    
    pai->filhos[i + 1] = novo;

    for(j = pai->numChaves - 1; j >= i; j--)
        pai->chave[j + 1] = pai->chave[j];

    pai->chave[i] = filho->chave[t];

    pai->numChaves++;
}

void insercaoNaoCheio(NO* no, int ch){
    printf("to na funcao insercao nao cheio e ch = %d\n", ch);
    int i = no->numChaves;
    if(no->folha){
        while(i > 0 && ch < no->chave[i - 1]){
            no->chave[i] = no->chave[i - 1];
            i--;
        }

        no->chave[i] = ch;
        no->numChaves++;
    }
    else{
        while(i > 0 && ch < no->chave[i - 1])
            i--;
        
        i++;

        if(no->numChaves == ((2*t) - 1))
            divide(no, i, no->filhos[i]);
    
        insercaoNaoCheio(no->filhos[i], ch);
    }
}

void insercao(ArvBMais* arvB, int ch){
    printf("inserindo chave: %d\n", ch);
    NO* raiz = arvB->raiz;

    if(raiz->numChaves == ((2*t) - 1)){
        printf("ta cheio\n");
        NO* novo = (NO*) malloc(sizeof(NO));
        arvB->raiz = novo;
        novo->folha = false;
        novo->numChaves = 0;
        novo->filhos[0] = raiz;
        divide(novo, 0, raiz);
        insercaoNaoCheio(novo, ch);
    }
    
    else {
        printf("nao ta cheio\n");
        insercaoNaoCheio(raiz, ch);
    }
}

void remocao(ArvBMais* arvB, int ch){
    NO* raiz = arvB->raiz;
    
    if(!(raiz->numChaves))
        return;
}

/*
void imprime(NO* no, FILE* saida){
    if(!no){
        fprintf(saida, "n tem no pra imprimir");
        return;
    }

    fprintf(saida, "(");

    int i;
    for(i = 0; i < no->numChaves; i++){
        if(!(no->folha)){
            imprime(no->filhos[i], saida);
            
        }
        fprintf(saida, "%d", no->chave[i]);
        
        if(i < no->numChaves)
            fprintf(saida, " ");

    }
    fprintf(saida, ")");
}
*/

void imprime(NO* no){    
    if(!no){
        printf("n tem no pra imprimir");
        return;
    }
    printf("to na funcao imprime. no chave 0 = %d e no numChaves = %d\n", no->chave[0], no->numChaves);

    printf("(");

    int i;
    for(i = 0; i < no->numChaves; i++){
        if(!(no->folha))
            imprime(no->filhos[i]);

        printf("%d", no->chave[i]);
        
        if(no->folha == false || i < (no->numChaves - 1))
            printf(" ");
        }

    printf(")");
}

/*
void leitura(ArvBMais* arvB, FILE* entrada, FILE* saida){
    char comando;
    int valor;
    while(true){
        fscanf(entrada, "%c", &comando);
        if (comando != 'p')
            fscanf(entrada, "%d", &valor);
        
        if(comando == 'i')
            insere(&arvB, valor);

        if(comando == 'r') 
            //remover
        
        if(comando == 'p')
            imprime(arvB->raiz, saida);

        if(comando == 'f')
            break;
    }
}
*/

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
                if(arvB->raiz->numChaves == 0)
                    printf("Vazia");          
                else
                    imprime(arvB->raiz);  
                
                printf("\n");
            }

        }
    }

}

int main(int argc, char* argv[]){
    printf("programa funcionando\n");

    //char* nome_entrada = argv[1];
    //char* nome_saida = argv[2];

    printf("depois dos chars\n");

    //FILE* entrada = fopen(nome_entrada, "r");
    //FILE* saida = fopen(nome_saida, "w");

    printf("depois dos FILEs\n");

    ArvBMais* arvBMais = (ArvBMais*) malloc (sizeof(ArvBMais));

    printf("antes da funcao de crir a arvore\n");

    criaArvoreBMais(arvBMais);

    printf("depois de criaArvB+ e antes de leitura\n");

    //leitura(arvBMais, entrada, saida);
    
    leitura(arvBMais);
    

    //fclose(entrada);
    //fclose(saida);
}
