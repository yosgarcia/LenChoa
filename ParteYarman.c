#define NULL 0
#include <stdio.h>
#include <stdlib.h>
#define LEOPARDO 'L'
#define TIGRE 'T'
#define VACIO 'O'
#define clrscr() printf("\e[1;1H\e[2J")
static int num_leopardos = 6;
typedef struct nodo
{
    int identificador;
    struct nodo *izquierda, *derecha, *arriba, *abajo;
    char ocupado[2];
} nodo;

nodo *inicializar_raiz()
{
    nodo *raiz = calloc(1, sizeof(nodo));
    raiz->identificador = 1;
    raiz->ocupado[0] = VACIO;
    raiz->ocupado[1] = '\0';
    raiz->arriba=NULL;
    raiz->abajo=NULL;
    raiz->derecha=NULL;
    raiz->izquierda=NULL;
    return raiz;
}
nodo *inicializar_nodo(int identificador)
{
    nodo *nuevo_novo = calloc(1, sizeof(nodo));
    nuevo_novo->identificador = identificador;
    nuevo_novo->ocupado[0] = VACIO;
    nuevo_novo->ocupado[1] = '\0';
    nuevo_novo->arriba=NULL;
    nuevo_novo->abajo=NULL;
    nuevo_novo->derecha=NULL;
    nuevo_novo->izquierda=NULL;
    return nuevo_novo;
}
void inicializar_niveles(nodo *raiz, int niveles)
{
    if (niveles <= 0)
    {
        return;
    }
    nodo *actual = raiz;
    //inicializar los nodos
    actual->izquierda = inicializar_nodo(2);
    actual->abajo = inicializar_nodo(3);
    actual->derecha = inicializar_nodo(4);

    //Reasignarlos
    nodo *centro_actual = actual->abajo;
    nodo *izquierdo_actual = actual->izquierda;
    nodo *derecho_actual = actual->derecha;

    //Definir los parentescos
    centro_actual->arriba=raiz;
    izquierdo_actual->arriba=raiz;
    derecho_actual->arriba=raiz;

    centro_actual->izquierda=izquierdo_actual;
    centro_actual->derecha=derecho_actual;

    izquierdo_actual->derecha=centro_actual;
    derecho_actual->izquierda=centro_actual;
    

   
    for (int i = 1; i < niveles; i++)
    {

        // Creacion de los 3 nodos
        // printf("%d--%d--%d\n",izquierdo_actual->identificador,centro_actual->identificador,derecho_actual->identificador);

        izquierdo_actual->abajo = inicializar_nodo((i * 3) + 2);
        izquierdo_actual->abajo->arriba = izquierdo_actual;

        centro_actual->abajo = inicializar_nodo((i * 3) + 3);
        centro_actual->abajo->arriba = centro_actual;

        derecho_actual->abajo = inicializar_nodo((i * 3) + 4);
        derecho_actual->abajo->arriba = derecho_actual;

        // Bajar 1 nivel
        izquierdo_actual = izquierdo_actual->abajo;
        derecho_actual = derecho_actual->abajo;
        centro_actual = centro_actual->abajo;

        // Creacion de las relaciones
        izquierdo_actual->derecha = centro_actual;
        centro_actual->izquierda = izquierdo_actual;

        centro_actual->derecha = derecho_actual;
        derecho_actual->izquierda = centro_actual;
    }
}

void imprimir_tablero(nodo *raiz)
{
    int nivel = 0;
    printf("-------   Numero de Espacio:\n");
    printf("---%c---    %d\n", raiz->ocupado[0], raiz->identificador);

    nodo *actual = raiz->abajo;
    while (actual != NULL)
    {
        nivel++;
        printf("|--|--|\n");
        printf("%c--%c--%c   %d--%d--%d\n", actual->izquierda->ocupado[0], actual->ocupado[0], actual->derecha->ocupado[0], actual->izquierda->identificador, actual->identificador, actual->derecha->identificador);
        actual = actual->abajo;
    }
}


int mover_leopardo(nodo *pieza, nodo *casilla)
{
    if (casilla != NULL)
    {
        // Validamos si la casilla esta vacia
        if (casilla->ocupado[0] == VACIO)
        {
            // Se desplaza a la posicion vacia
            casilla->ocupado[0] = pieza->ocupado[0];
            pieza->ocupado[0] = VACIO;
            return 0;
        }
        else
        {
            printf("No se puede mover la pieza. Espacio ocupado\n");
            return 1;
        }
    }
    else
    {
        printf("No se puede mover la pieza. Borde del tablero\n");
        return 1;
    }
}



nodo *mover_tigre_izquierda(nodo *pieza)
{
    if (pieza->izquierda != NULL)
    {
        nodo *campo_izquierda = pieza->izquierda;
        // Validamos si a la izquierda hay un leopardo
         
        if (campo_izquierda->ocupado[0] == LEOPARDO)
        {
            // Validamos si hay un espacio vacio a la izquierda del leopardo para comerlo
            if (campo_izquierda->izquierda != NULL )
            {
                if (campo_izquierda->izquierda->ocupado[0] == VACIO)
                {
                     pieza->ocupado[0] = VACIO;
                campo_izquierda->ocupado[0] = VACIO;
                campo_izquierda->izquierda->ocupado[0] = TIGRE;
                num_leopardos--;
                return campo_izquierda->izquierda;
                }
                else{
                    printf("No se puede mover la pieza. Campo ocupado y borde despues\n");
        return pieza;
                }
                
             
            }
            else{
                printf("No se puede mover la pieza. Campo ocupado y borde despues\n");
        return pieza;
            }
        }
        else
        {
            // Se desplaza a la posicion vacia
            campo_izquierda->ocupado[0] = pieza->ocupado[0];
            pieza->ocupado[0] = VACIO;
            return campo_izquierda;
        }
    }
    else
    {
        printf("No se puede mover la pieza. Borde del tablero\n");
        return pieza;
    }
    printf("No se puede mover la pieza. \n");
    return pieza;
}


nodo *mover_tigre_derecha(nodo *pieza)
{
    if (pieza->derecha != NULL)
    {
        nodo *campo_derecha = pieza->derecha;
        // Validamos si a la derecha hay un leopardo
        if (campo_derecha->ocupado[0] == LEOPARDO)
        {
            // Validamos si hay un espacio vacio a la derecha del leopardo para comerlo
            if (campo_derecha->derecha != NULL )
            {
                if (campo_derecha->derecha->ocupado[0] == VACIO)
                {
                     pieza->ocupado[0] = VACIO;
                campo_derecha->ocupado[0] = VACIO;
                campo_derecha->derecha->ocupado[0] = TIGRE;
                num_leopardos--;
                return campo_derecha->derecha;
                }
            }
        }
        else
        {
            // Se desplaza a la posicion vacia
            campo_derecha->ocupado[0] = pieza->ocupado[0];
            pieza->ocupado[0] = VACIO;
            return campo_derecha;
        }
    }
    else
    {
        printf("No se puede mover la pieza. Borde del tablero\n");
        return pieza;
    }
    printf("No se puede mover la pieza. \n");
    return pieza;
}

nodo *mover_tigre_arriba(nodo *pieza)
{
    if (pieza->arriba != NULL)
    {
        nodo *campo_arriba = pieza->arriba;
        // Validamos si arriba hay un leopardo
        if (campo_arriba->ocupado[0] == LEOPARDO)
        {
            // Validamos si hay un espacio vacio arriba del leopardo para comerlo
            if (campo_arriba->arriba != NULL  )
            {
                if (campo_arriba->arriba->ocupado[0] == VACIO)
                {
                    // Se hace el intercambio
                pieza->ocupado[0] = VACIO;
                campo_arriba->ocupado[0] = VACIO;
                campo_arriba->arriba->ocupado[0] = TIGRE;
                num_leopardos--;
                return campo_arriba->arriba;
                }
                
                
            }
        }
        else
        {
            // Se desplaza a la posicion vacia
            campo_arriba->ocupado[0] = pieza->ocupado[0];
            pieza->ocupado[0] = VACIO;
            return campo_arriba;
        }
    }
    else
    {
        printf("No se puede mover la pieza. Borde del tablero\n");
        return pieza;
    }
    printf("No se puede mover la pieza. \n");
    return pieza;
}

nodo *mover_tigre_abajo(nodo *pieza)
{
    if (pieza->abajo != NULL)
    {
        nodo *campo_abajo = pieza->abajo;
        // Validamos si abajo hay un leopardo
        if (campo_abajo->ocupado[0] == LEOPARDO)
        {
            // Validamos si hay un espacio vacio abajo del leopardo para comerlo
            if (campo_abajo->abajo != NULL  )
            {
                if (campo_abajo->abajo->ocupado[0] == VACIO)
                {
                     // Se hace el intercambio
                pieza->ocupado[0] = VACIO;
                campo_abajo->ocupado[0] = VACIO;
                campo_abajo->abajo->ocupado[0] = TIGRE;
                num_leopardos--;
                return campo_abajo->abajo;
                }
            }
        }
        else
        {
            // Se desplaza a la posicion vacia
            campo_abajo->ocupado[0] = pieza->ocupado[0];
            pieza->ocupado[0] = VACIO;
            return campo_abajo;
        }
    }
    else
    {
        printf("No se puede mover la pieza. Borde del tablero\n");
        return pieza;
    }
    printf("No se puede mover la pieza. \n");
    return pieza;
}


nodo *buscar_casilla(nodo *raiz, int identificador)
{
    if (identificador==1)
    {
        return raiz;
    }
    
    nodo *actual = raiz->derecha;

    // Recorre las filas en busqueda del nivel donde se encuentra la casilla
    while (actual->identificador < identificador)
    {
        actual = actual->abajo;
    }
    if (actual->identificador == identificador)
    {
        return actual;
    }
    // Recorremos los elementos del nivel
    while (actual->identificador > identificador)
    {
        actual = actual->izquierda;
    }
    if (actual->identificador == identificador)
    {
        return actual;
    }
    return NULL;
}



void poner_leopardo(nodo *raiz, int niveles)
{
    int pos_leopardo;
    nodo *casilla_leopardo;
    while (1)
    {

        printf("Donde desea poner el leopardo?\n");
        if (scanf("%d", &pos_leopardo) != 1)
        {
            printf("Entrada invalida digite un numero.\n");
            while (getchar() != '\n')
                ;
            continue;
        }
        if ((pos_leopardo > ((3 * niveles) + 2)) || (pos_leopardo < 1))
        {
            printf("Numero de Leopardo fuera de los limites del tablero\n");
            continue;
        }
        casilla_leopardo = buscar_casilla(raiz, pos_leopardo);
        if (casilla_leopardo->ocupado[0] != VACIO)
        {
            printf("Casilla Ocupada\n");
            continue;
        }
        casilla_leopardo->ocupado[0] = LEOPARDO;
        break;
    }
}



int validar_arriba(nodo* tigre){
    if (tigre->arriba != NULL)
    {
        nodo *campo_arriba = tigre->arriba;
        // Validamos si arriba hay un leopardo
        if (campo_arriba->ocupado[0] == LEOPARDO)
        {
            // Validamos si hay un espacio vacio arriba del leopardo para comerlo
            if (campo_arriba->arriba != NULL  )
            {
                if (campo_arriba->arriba->ocupado[0] == VACIO)
                {
                return 1;
                }
            }
        }
        else
        {
            return 1;
        }
    }
    else
    {
        return 0;
    }
    return 0;
}


int validar_abajo(nodo* tigre){
    if (tigre->abajo != NULL)
    {
        nodo *campo_abajo = tigre->abajo;
        // Validamos si abajo hay un leopardo
        if (campo_abajo->ocupado[0] == LEOPARDO)
        {
            if (campo_abajo->abajo != NULL  )
            {
                if (campo_abajo->abajo->ocupado[0] == VACIO)
                {
                return 1;
                }
            }
        }
        else
        {
            return 1;
        }
    }
    else
    {
        return 0;
    }
        return 0;
}



int validar_izquierda(nodo* tigre){
    if (tigre->izquierda != NULL)
    {
        nodo *campo_izquierda = tigre->izquierda;
        // Validamos si a la izquierda hay un leopardo
        if (campo_izquierda->ocupado[0] == LEOPARDO)
        {
            // Validamos si hay un espacio vacio a la izquierda del leopardo para comerlo
            if (campo_izquierda->izquierda != NULL )
            {
                if (campo_izquierda->izquierda->ocupado[0] == VACIO)
                {
                return 1;
                }
                else{
                    return 0;
                }
            }
            else{
                return 0;
            }
        }
        else
        {
            return 1;
        }
    }
    else
    {
        return 0;
    }
    return 0;
}

int validar_derecha(nodo* tigre){
    if (tigre->derecha != NULL)
    {
        nodo *campo_derecha = tigre->derecha;
        // Validamos si a la derecha hay un leopardo
        if (campo_derecha->ocupado[0] == LEOPARDO)
        {
            // Validamos si hay un espacio vacio a la derecha del leopardo para comerlo
            if (campo_derecha->derecha != NULL )
            {
                if (campo_derecha->derecha->ocupado[0] == VACIO)
                {
                return 1;
                }
            }
        }
        else
        {
            return 1;
        }
    }
    else
    {
        return 0;
    }
    return 0;

}

int verificar_tigre_inhabilitado(nodo *tigre)
{
    if (tigre->ocupado[0] == TIGRE)
    {
        return !validar_abajo(tigre) && !validar_arriba(tigre) && !validar_izquierda(tigre) && !validar_derecha(tigre);
    }
    return 0;
}




int main()
{
    printf("Bienvenido a Len Choa\n");
    printf("Digite la cantidad de niveles:\n");

    int niveles;
    int choice;
    while (1)
    {

        if (scanf("%d", &niveles) != 1)
        {
            printf("Entrada invalidad, digite un numero.\n");
            while (getchar() != '\n')
                ;

            continue;
        }
        if (niveles > 3)
        {

            break;
        }
        printf("El minimo de niveles es 4.\n");
    }
    nodo *raiz = inicializar_raiz();

    inicializar_niveles(raiz, niveles - 1);

    int gane = 0;
    int turno = 2;
    int movimiento_tigre;
    int movimiento_leopardo;
    printf("El tigre hace su aparicion\n");
    printf("Turno 1\n");
    raiz->ocupado[0] = TIGRE;
    nodo *pos_tigre_actual = raiz;
    nodo *nueva_pos_tigre;
    int leopardos_a_poner = 6;
    int pos_leopardo;
    nodo *leopardo_actual;
    int finalizar_turno_leopardo = 1;

    while (!gane)
    {
        clrscr();
        printf("Turno %d\n", turno);
        printf("Numero de Leopapis %d \n",num_leopardos);
        imprimir_tablero(raiz);
        if (!(turno % 2))
        {
            if (num_leopardos<4)
            {
                printf("Los leopardos son 3 o menos, el tigre gana\n");
                gane=1;
                break;
            }
            
            printf("Turno de los Leopardos\n");
            if (leopardos_a_poner)
            {
                poner_leopardo(raiz, niveles);
                leopardos_a_poner--;
                turno++;
                continue;
            }
            else
            {
                finalizar_turno_leopardo = 1;
                while (finalizar_turno_leopardo)
                {
                    pos_leopardo = -1;

                    printf("Que casilla desea mover?\n");
                    if (scanf("%d", &pos_leopardo) != 1)
                    {
                        printf("Entrada invalida digite un numero.\n");
                        while (getchar() != '\n')
                            ;
                        continue;
                    }
                    if ((pos_leopardo > ((3 * niveles) + 2)) || (pos_leopardo < 1))
                    {
                        printf("Numero de Leopardo fuera de los limites del tablero\n");
                        continue;
                    }
                    leopardo_actual = buscar_casilla(raiz, pos_leopardo);
                    if (leopardo_actual->ocupado[0] != LEOPARDO)
                    {
                        printf("La casilla no contiene un leopardo\n");
                        continue;
                    }

                    printf("A donde desea mover el Leopardo?\n");
                    printf("1. Arriba\n");
                    printf("2. Abajo\n");
                    printf("3. Izquierda\n");
                    printf("4. Derecha\n");
                    if (scanf("%d", &movimiento_leopardo) != 1)
                    {
                        printf("Entrada invalida digite un numero.\n");
                        while (getchar() != '\n')
                            ;
                        continue;
                    }
                    switch (movimiento_leopardo)
                    {
                    case 1:

                        if (!mover_leopardo(leopardo_actual, leopardo_actual->arriba))
                        {
                            finalizar_turno_leopardo = 0;
                        }

                        break;
                    case 2:
                        if (!mover_leopardo(leopardo_actual, leopardo_actual->abajo))
                        {
                            finalizar_turno_leopardo = 0;
                        }
                        // abajo
                        break;
                    case 3:
                        if (!mover_leopardo(leopardo_actual, leopardo_actual->izquierda))
                        {
                            finalizar_turno_leopardo = 0;
                        }
                        // izquierda
                        break;
                    case 4:
                        if (!mover_leopardo(leopardo_actual, leopardo_actual->derecha))
                        {
                            finalizar_turno_leopardo = 0;
                        }
                        // derecha
                        break;

                    default:
                        printf("Movimiento Invalido.\n");
                    }
                }
            turno++;
            continue;
            }
        }
        else
            if (!verificar_tigre_inhabilitado)
            {
                printf("El tigre no puede moverse, los leopardos ganan\n");
                gane=1;
                break;
            }
            
        {
            printf("Turno del Tigre\n");
            printf("A donde desea mover el tigre?\n");
            printf("1. Arriba\n");
            printf("2. Abajo\n");
            printf("3. Izquierda\n");
            printf("4. Derecha\n");
            if (scanf("%d", &movimiento_tigre) != 1)
            {
                printf("Entrada invalida digite un numero.\n");
                while (getchar() != '\n')
                    ;
                continue;
            }
            switch (movimiento_tigre)
            {
            case 1:

                nueva_pos_tigre = mover_tigre_arriba(pos_tigre_actual);
                if (nueva_pos_tigre->identificador != pos_tigre_actual->identificador)
                {
                    pos_tigre_actual = nueva_pos_tigre;
                    turno++;
                }

                break;
            case 2:
                nueva_pos_tigre = mover_tigre_abajo(pos_tigre_actual);
                if (nueva_pos_tigre->identificador != pos_tigre_actual->identificador)
                {
                    pos_tigre_actual = nueva_pos_tigre;
                    turno++;
                }
                break;
            case 3:
                nueva_pos_tigre = mover_tigre_izquierda(pos_tigre_actual);
                if (nueva_pos_tigre->identificador != pos_tigre_actual->identificador)
                {
                    pos_tigre_actual = nueva_pos_tigre;
                    turno++;
                }
                break;
            case 4:
                nueva_pos_tigre = mover_tigre_derecha(pos_tigre_actual);
                if (nueva_pos_tigre->identificador != pos_tigre_actual->identificador)
                {
                    pos_tigre_actual = nueva_pos_tigre;
                    turno++;
                }
                break;
                // turno tigre
            default:
                printf("Movimiento Invalido.\n");
            }
            while (getchar() != '\n')
                ;
        }
    }

    return 0;
}