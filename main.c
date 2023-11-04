#include <stdio.h>
#include <stdlib.h>

#define LEOPARDO "L";
#define TIGRE "T";

static int num_leopardos = 6;

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
    int nivel=0;
    printf("1--2--3   Columnas\n");
    printf("---%c---   Nivel: %d\n",raiz->ocupado[0],nivel);
    
    
    nodo* actual=raiz->abajo;
    while (actual!=NULL)
    {
        nivel++;
        printf("|--|--|\n");
        printf("%c--%c--%c   Nivel: %d\n",actual->izquierda->ocupado[0],actual->ocupado[0],actual->derecha->ocupado[0],nivel);
        actual=actual->abajo;
    }
    
}



void annadir_vivel(){

}



void mover_leopardo(nodo* pieza, nodo* casilla){
    if(casilla != NULL){
        if(casilla->ocupado[0] == " "){
            casilla->ocupado[0] = pieza->ocupado[0];
            pieza->ocupado[0] = " ";
        } else{
            printf("No se puede mover la pieza. Espacio ocupado\n");
        }
    } else{
        printf("No se puede mover la pieza. Borde del tablero\n");
    }
}


void mover_tigre_izquierda(nodo* pieza){
    if(pieza->izquierda != NULL){
        nodo* campo_izquierda = pieza->izquierda;
        if(campo_izquierda->ocupado[0] == "L"){
            if(campo_izquierda->izquierda != NULL && campo_izquierda->izquierda->ocupado[0] == " "){
                pieza->ocupado[0] = " ";
                campo_izquierda->ocupado[0] = " ";
                campo_izquierda->izquierda->ocupado[0] = "T";
                num_leopardos--;
            }
        } else{
            campo_izquierda->ocupado[0] = pieza->ocupado[0];
            pieza->ocupado[0] = " ";
        }
    } else{
        printf("No se puede mover la pieza. Borde del tablero\n");
    }
}


void mover_tigre_derecha(nodo* pieza){
    if(pieza->derecha != NULL){
        nodo* campo_derecha = pieza->derecha;
        if(campo_derecha->ocupado[0] == "L"){
            if(campo_derecha->derecha != NULL && campo_derecha->derecha->ocupado[0] == " "){
                pieza->ocupado[0] = " ";
                campo_derecha->ocupado[0] = " ";
                campo_derecha->derecha->ocupado[0] = "T";
                num_leopardos--;
            }
        } else{
            campo_derecha->ocupado[0] = pieza->ocupado[0];
            pieza->ocupado[0] = " ";
        }
    } else{
        printf("No se puede mover la pieza. Borde del tablero\n");
    }
}


void mover_tigre_arriba(nodo* pieza){
    if(pieza->arriba != NULL){
        nodo* campo_arriba = pieza->arriba;
        if(campo_arriba->ocupado[0] == "L"){
            if(campo_arriba->arriba != NULL && campo_arriba->arriba->ocupado[0] == " "){
                pieza->ocupado[0] = " ";
                campo_arriba->ocupado[0] = " ";
                campo_arriba->arriba->ocupado[0] = "T";
                num_leopardos--;
            }
        } else{
            campo_arriba->ocupado[0] = pieza->ocupado[0];
            pieza->ocupado[0] = " ";
        }
    } else{
        printf("No se puede mover la pieza. Borde del tablero\n");
    }
}


void mover_tigre_abajo(nodo* pieza){
    if(pieza->abajo != NULL){
        nodo* campo_abajo = pieza->abajo;
        if(campo_abajo->ocupado[0] == "L"){
            if(campo_abajo->abajo != NULL && campo_abajo->abajo->ocupado[0] == " "){
                pieza->ocupado[0] = " ";
                campo_abajo->ocupado[0] = " ";
                campo_abajo->abajo->ocupado[0] = "T";
                num_leopardos--;
                
            }
        } else{
            campo_abajo->ocupado[0] = pieza->ocupado[0];
            pieza->ocupado[0] = " ";
        }
    } else{
        printf("No se puede mover la pieza. Borde del tablero\n");
    }
}


int main(){

    return 0;
}
