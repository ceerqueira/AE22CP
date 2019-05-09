
#include <stdio.h>
#include <stdlib.h>


typedef struct item Item;
typedef struct vertice Vertice;
typedef struct grafo Grafo;
typedef struct aresta Aresta;


struct item {
  int chave;
};

struct aresta{
    Item item;
    Aresta *prox;
};

struct vertice {
  struct vertice *prox;
  Aresta *inicio;
  Item item;
};

struct grafo {
  Vertice *inicio;
};

Grafo * cria_grafo_vazio() {
  Grafo *g = malloc(sizeof(Grafo));
  g->inicio = NULL;
  return g;
}

int verifica_grafo_vazio(Grafo *g) {
  // se a primeira ainda aponta para NULL, ent�o est� vazia
  return g->inicio == NULL;
}

int verifica_aresta_vazia(Vertice *v) {
  // se a primeira ainda aponta para NULL, ent�o est� vazia
  return v->inicio == NULL;
}

int verifica_vertice(Grafo *g, int vertice){
    //verificar se ja existe este vertice
        Vertice *teste = g->inicio;
        while (teste->prox != NULL ){
            if(teste->item.chave == vertice){
                printf("O VERTICE %d JA EXISTE.\n",vertice);
                return 1;
            }
            teste = teste->prox;
        }
        return 0;
}

void inserir_vertice(Grafo *g, int vertice){

    //verifica se grafo esta vazio.
    Vertice *novo = malloc(sizeof(Vertice));

    novo->item.chave=vertice;
    novo->prox = NULL;
    novo->inicio=NULL;

    if(verifica_grafo_vazio(g)){
        g->inicio = novo;
    }else{
        if(verifica_vertice(g,vertice))
          return;
        Vertice *aux = g->inicio;
        while (aux->prox != NULL){
            aux = aux->prox;
        }

        aux->prox = novo;
    }
}

void imprime(Grafo *g){
    //verificar se ja existe este vertice
        Vertice *teste = g->inicio;
        printf("Vertice:\n");
        while (teste != NULL){
            printf("\n[%d]",teste->item.chave );
            Aresta *aux = teste->inicio;
            while(aux != NULL){
                 printf(" -> [%d]",aux->item.chave );
                 aux = aux->prox;
            }
            teste = teste->prox;
            }
            printf("\n");
        return;
}

Vertice * busca_vertice(Grafo *g, int vertice){ //retorna o endereço do Vertice.
  Vertice *aux = g->inicio;
  while (aux != NULL && g->inicio !=NULL){
    if (aux->item.chave == vertice){
      return aux;
    }
    aux = aux->prox;
  }
  printf("VERTICE NAO ENCONTRADO\n");
  return NULL;

}



int verifica_aresta(Vertice *v, int aresta){
    //verificar se ja existe esta aresta
        Aresta *teste = v->inicio;
        while (teste!= NULL ){
            if(teste->item.chave == aresta){
                return 1;
            }
            teste = teste->prox;
        }
        return 0;
}


void inserir_aresta(Grafo *g,int aresta_1, int aresta_2){
  Aresta *nova_aresta_1 = malloc(sizeof(Aresta));
  Aresta *nova_aresta_2 = malloc(sizeof(Aresta));

  Vertice *auxiliar_1 = busca_vertice(g,aresta_1);
  Vertice *auxiliar_2 = busca_vertice(g,aresta_2);
  // faz a verificacao para saber se existem Os vertices solititados
  if(auxiliar_1 != NULL && auxiliar_2 != NULL){

    //se o vertice nao tiver nenhuma aresta ele vai inserir no inicio
    if(verifica_aresta_vazia(auxiliar_1)){
       auxiliar_1->inicio = nova_aresta_1;
    }else{

      if(verifica_aresta(auxiliar_1,aresta_2)){
        printf("A ARESTA %d JA EXISTE.\n",aresta_2 );
        return;
      }


      Aresta *aux = auxiliar_1->inicio;
      while(aux->prox != NULL){
          aux = aux->prox;
        }
        aux -> prox = nova_aresta_1;
    }

      nova_aresta_1->item.chave = aresta_2;
      nova_aresta_1->prox = NULL;


    if(verifica_aresta_vazia(auxiliar_2)){
         auxiliar_2->inicio = nova_aresta_2;
      }else{
        Aresta *aux = auxiliar_2->inicio;
        while(aux->prox != NULL){
            aux = aux->prox;
          }
          aux -> prox = nova_aresta_2;
      }

        nova_aresta_2->item.chave = aresta_1;
        nova_aresta_2->prox = NULL;
      }
}


void remover_arestas(Grafo *g,int aresta_1, int aresta_2 ){
    Vertice *auxiliar_1 = busca_vertice(g,aresta_1);
    Vertice *auxiliar_2 = busca_vertice(g,aresta_2);

    //VERIFICANDO SE AS ARESTA DO VERTICE ESTAO VAZIA
    if(verifica_aresta_vazia(auxiliar_1) ){
        printf("O VERTICE %d ESTA VAZIO\n", auxiliar_1->item.chave);
        return;
    }

    if(verifica_aresta_vazia(auxiliar_2) ){
        printf("O VERTICE %d ESTA VAZIO\n", auxiliar_2->item.chave);
        return;
    }


    //REMOVENDO ARESTA 2
    Aresta *anterior = auxiliar_1->inicio;
    if(anterior->item.chave == aresta_2){
        Aresta *remover = anterior;
        // liga a anterior com a próxima da que vai ser removida
        if(anterior->prox == NULL){
            auxiliar_1->inicio == NULL;
            free(remover);
        }else{
            auxiliar_1->inicio = remover->prox;
            free(remover);
        }

    }else{
        while(anterior->prox->item.chave != aresta_2){
          anterior = anterior->prox;
        }
        // será removida aquela que vem depois da aresta com o item da chave buscada
        Aresta *remover = anterior->prox;
        // liga a anterior com a próxima da que vai ser removida
        anterior->prox = remover->prox;
        free(remover);
    }

/*
    //REMOVENDO ARESTA 1
    Aresta *anterior_2 = auxiliar_2->inicio;
    if(anterior_2->item.chave == aresta_1){
        Aresta *remover_2 = anterior_2;
        // liga a anterior com a próxima da que vai ser removida
        if(anterior_2->prox == NULL){
            auxiliar_2->inicio == NULL;
            free(remover_2);
        }else{
            auxiliar_2->inicio = remover_2->prox;
            free(remover_2);
        }

    }else{
        while(anterior_2->prox->item.chave != aresta_1){
              anterior_2 = anterior_2->prox;
            }
        // será removida aquela que vem depois da aresta com o item da chave buscada
        Aresta *remover_2 = anterior_2->prox;
        // liga a anterior com a próxima da que vai ser removida
        anterior_2->prox = remover_2->prox;
        free(remover_2);
    }
    */
}
int main (void){
    Grafo *g=cria_grafo_vazio();
    inserir_vertice(g,5);
    inserir_vertice(g,6);
    inserir_vertice(g,7);
    inserir_vertice(g,8);
    inserir_vertice(g,9);
    inserir_vertice(g,10);
    inserir_aresta(g,5,6);
    inserir_aresta(g,5,7);
    inserir_aresta(g,5,8);
    inserir_aresta(g,5,9);
    inserir_aresta(g,5,10);
    inserir_aresta(g,7,6);
    imprime(g);
    remover_arestas(g,5,6);
    imprime(g);


   // remover_arestas(g,8,9);



    //inserir_aresta(g,7,7);
}
