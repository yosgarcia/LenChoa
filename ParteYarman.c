#define NULL 0
#include<stdio.h>
#include<stdlib.h>

typedef struct nodo{
    int identificador;
    struct nodo *izquierda,*derecha,*arriba,*abajo;
    char ocupado[2];
} nodo;


nodo* inicializar_raiz(){
    nodo* raiz = calloc(1,sizeof(nodo));
    raiz->identificador =1;
    return raiz;
}
nodo* inicializar_nodo(int identificador){
    nodo* nuevo_novo=calloc(1,sizeof(nodo));
    nuevo_novo->identificador=identificador;
    nuevo_novo->ocupado[0]=" ";
    nuevo_novo->ocupado[1]="\0";
    return nuevo_novo;

}
void inicializar_niveles(nodo* raiz, int niveles){
    if (niveles<=0){
        return;
    }
    nodo* actual = raiz;
    actual->izquierda=inicializar_nodo(2);
    // Que izquierda tenga de padre a la raiz
    actual->izquierda->arriba=actual;


    actual->abajo=inicializar_nodo(3);
    //Abajo de raiz tenga de hermano izquierda al izquierdo
    actual->abajo->izquierda=actual->izquierda;
    actual->izquierda->derecha=actual->abajo;
    actual->abajo->arriba=actual;

    //Inicializar el derecho mas su relacion de vecindad
    actual->derecha=inicializar_nodo(4);
    actual->derecha->arriba=actual;
    actual->derecha->izquierda=actual->abajo;
    actual->abajo->derecha=actual->derecha;
    
    
    nodo* centro_actual= actual->abajo;
    nodo* izquierdo_actual=actual->izquierda;
    nodo* derecho_actual=actual->derecha;
    for (int i = 1; i < niveles; i++)
    {
       
        //Creacion de los 3 nodos
        //printf("%d--%d--%d\n",izquierdo_actual->identificador,centro_actual->identificador,derecho_actual->identificador);
         

        izquierdo_actual->abajo=inicializar_nodo((i*3)+2);
        izquierdo_actual->abajo->arriba=izquierdo_actual;

        centro_actual->abajo=inicializar_nodo((i*3)+3);
        centro_actual->abajo->arriba=centro_actual;

        derecho_actual->abajo=inicializar_nodo((i*3)+4);
        derecho_actual->abajo->arriba=centro_actual;

        //Bajar 1 nivel
        izquierdo_actual=izquierdo_actual->abajo;
        derecho_actual=derecho_actual->abajo;
        centro_actual=centro_actual->abajo;

        //Creacion de las relaciones
        izquierdo_actual->derecha=centro_actual;
        centro_actual->izquierda=izquierdo_actual;

        centro_actual->derecha=derecho_actual;
        derecho_actual->izquierda=centro_actual;
        
    }
    
    




}

void imprimir_tablero(nodo* raiz){
    printf("---%d---\n",raiz->identificador);
    
    nodo* actual=raiz->abajo;
    while (actual!=NULL)
    {
        printf("|--|--|\n");
        printf("%d--%d--%d\n",actual->izquierda->identificador,actual->identificador,actual->derecha->identificador);
        actual=actual->abajo;
    }
    
}
void añadir_nivel(){

}
int main(){
    nodo* raiz= inicializar_raiz();
   
  
    inicializar_niveles(raiz,5);
    imprimir_tablero(raiz);
    return 0;
}