/******************************************************************************

Estructuras Lista Lineal Simple (LLS)

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h> 
/* Esta es nuestra declaración de nodo */
typedef struct nodo{
    int info;
    struct nodo * siguiente; 
} t_nodo,*enlace;

/* prototipos */
int menu_general();
int menu_insertar();
int menu_eliminar();
int menu_cantidad();
enlace CrearNodo(int);
void InsertarInicio (enlace*,enlace);
void InsertarFinal(enlace*,enlace);
void InsertarPosicionX(enlace*,int,enlace);
void Imprimir(enlace);
void Eliminar_InfoX(enlace*,int,int);
void Eliminar_PosicionX(enlace*,int);
int Largo(enlace);
int Largo_Recursivo(enlace);
int CantidadNodos_InfoX(enlace,int);
enlace Buscar(enlace,int);
enlace BuscarRecursivo(enlace,int);
void BuscarPosiciones(enlace*,int,int*);
void GenerarListaImpar(enlace*,enlace*);
void GenerarListaPar(enlace*,enlace*);

int main()
{
    /* Esta es la declaración de la Cabecera a la LLS. Inicialmente está apuntando a nada */
    enlace Cabecera = NULL;
    int input,delete;
    printf("_____________________________________________________________________________\n\n");
    int opcion_menu=menu_general();
    while(opcion_menu!=6){
        switch(opcion_menu){
            case 1: printf("\nIngrese valor del nuevo nodo: ");
                    scanf("%d",&input);
                    enlace nuevo_nodo = CrearNodo(input);
                    switch(menu_insertar()){
                        case 1: InsertarInicio(&Cabecera,nuevo_nodo);
                        break;
                        case 2: InsertarFinal(&Cabecera,nuevo_nodo);
                        break;
                        case 3: printf("\nIngrese posicion del nuevo nodo: ");
                                scanf("%d",&input);
                                InsertarPosicionX(&Cabecera,input,nuevo_nodo);
                        break;
                    }
                    printf("\n"); Imprimir(Cabecera);
            break;
            case 2: Imprimir(Cabecera);
            break;
            case 3: switch(menu_eliminar()){
                        case 1: printf("\nInformacion que quiere eliminar: ");
                                scanf("%d",&input);
                                printf("Cuantos nodos quiere eliminar: ");
                                scanf("%d",&delete);
                                Eliminar_InfoX(&Cabecera,input,delete);
                        break;
                        case 2: printf("\nPosicion del nodo que quiere eliminar: ");
                                scanf("%d",&input);
                                Eliminar_PosicionX(&Cabecera,input);
                        break;
                    }
                    printf("\n"); Imprimir(Cabecera);
            break;
            case 4: switch(menu_cantidad()){
                        case 1: printf("\nLargo de la LLS: %d\n",Largo(Cabecera));
                                //printf("Largo de la LLS: %d",Largo_Recursivo(Cabecera));
                        break;
                        case 2: printf("\nDe que Info quiere saber la cantidad: ");
                                scanf("%d",&input);
                                printf("\nLa cantidad de nodos con info %d es: %d\n",input,CantidadNodos_InfoX(Cabecera,input));
                        break;
                    }
            break;
            case 5: printf("\n"); Imprimir(Cabecera);
                    printf("Valor de los nodos a buscar: ");
                    scanf("%d",&input);
                    int cantidad_nodos=CantidadNodos_InfoX(Cabecera,input);
                    if(cantidad_nodos!=0){
                        int Posiciones[cantidad_nodos];
                        BuscarPosiciones(&Cabecera,input,Posiciones);
                        for(int i=0;i<cantidad_nodos;i++)
                            printf("\nPosicion %d",Posiciones[i]);
                        printf("\n");
                    }else
                        printf("\nNo se encontro nodo con info %d ...\n",input);
        }
        printf("_____________________________________________________________________________\n\n");
        opcion_menu=menu_general();
    }
 
    return 0;
}

/* Funciones que imprimen el menu y retornan la opción */
int menu_general(){
    int opcion_menu;
    printf("\tMENU\n\n");
    printf("1) Agregar nuevo nodo a la LLS\n");
    printf("2) Imprimir LLS\n");
    printf("3) Eliminar nodo\n");
    printf("4) Cantidad de nodos en la LLS\n");
    printf("5) Buscar posicion de un nodo\n");
    printf("6) Salir\n");
    
    printf("\nSelecione una opcion: ");
    scanf("%d",&opcion_menu);
    return opcion_menu;
}
int menu_insertar(){
    int opcion_menu;
    printf("\n1) Insertar nuevo nodo al Inicio\n");
    printf("2) Insertar nuevo nodo al Final\n");
    printf("3) Insertar nuevo nodo en Posicion X\n");
    
    printf("\nSelecione una opcion: ");
    scanf("%d",&opcion_menu);
    return opcion_menu;
}
int menu_eliminar(){
    int opcion_menu;
    printf("1) Eliminar nodo con info X\n");
    printf("2) Eliminar nodo en Posicion X\n");
    
    printf("\nSelecione una opcion: ");
    scanf("%d",&opcion_menu);
    return opcion_menu;
}
int menu_cantidad(){
    int opcion_menu;
    printf("1) Cantidad total de nodos\n");
    printf("2) Cantidad de nodos con info X\n");
    
    printf("\nSelecione una opcion: ");
    scanf("%d",&opcion_menu);
    return opcion_menu;
}
int menu_buscar(){
    int opcion_menu;
    printf("1) Cantidad total de nodos\n");
    printf("2) Cantidad de nodos con info X\n");
    
    printf("\nSelecione una opcion: ");
    scanf("%d",&opcion_menu);
    return opcion_menu;
}




























/* Función que recibe un int y retorna un nodo conteniendo dicho int */
enlace CrearNodo(int valor){
    enlace nuevo_nodo;
    //nuevo_nodo = (t_nodo *)malloc(sizeof(t_nodo));
    nuevo_nodo = (enlace)malloc(sizeof(t_nodo)); // Solicitamos un fragmento de memoria de tamaño sizeof(t_nodo). Similar a definir el tamaño de un arreglo.
    nuevo_nodo->info = valor;       // (*nuevo_nodo).info=valor;
    nuevo_nodo->siguiente = NULL;   //(*nuevo_nodo).siguiente=NULL;
    return nuevo_nodo; 
}

/* Funciones que ingresan un nuevo nodo AL INICIO y AL FINAL de la lista */
void InsertarInicio(enlace * C,enlace nodo){ // Ojo: C es un puntero a un puntero
    /* Chequeamos si la LLS está vacía, en cuyo caso Cabecera pasa a apuntar a nuevo nodo */
    if(*C == NULL){
      *C = nodo;
      nodo->siguiente=NULL;
      return;
    }
    nodo->siguiente = *C;
    *C = nodo;
}
void InsertarFinal(enlace * C,enlace nodo){
    if(*C==NULL){
        *C=nodo;
        nodo->siguiente=NULL;
        return;
    }
    enlace aux=*C;
    while(aux->siguiente!=NULL){
        aux=aux->siguiente;
    }
    aux->siguiente=nodo;
    nodo->siguiente=NULL;
}

/* Función que recorre de principio a fin la lista e imprime en consola el dato info */
void Imprimir(enlace C){
    if(C==NULL){
        printf("La lista esta vacia...\n");
        return;
    }
    enlace aux=C;
    while(aux!=NULL){
        printf("[%d]",aux->info);
        aux=aux->siguiente;
    }
    printf("\n");
}

/* Función que recorre de principio a fin la lista buscando LOS nodos con info X y elimina una cantidad determinada de nodos */
void Eliminar_InfoX(enlace *C,int X,int Cantidad){
    int contador=0;
    if(*C==NULL){ //Caso en que la lista está vacia. No hay nada para eliminar entonces
        return;
    }
    while((*C!=NULL && (*C)->info==X) && (contador<Cantidad || Cantidad==-1)){ //Caso en que el nodo a eliminar está apuntado por la cabecera
        enlace basura=*C;
        *C=(*C)->siguiente;
        free(basura);
        contador++;
    }
    enlace aux=*C;
    while((aux!=NULL && aux->siguiente!=NULL) && (contador<Cantidad || Cantidad==-1)){
        if(aux->siguiente->info==X){
            enlace basura=aux->siguiente;
            aux->siguiente=aux->siguiente->siguiente;
            free(basura);
            contador++;
        }
        else
            aux=aux->siguiente;
    }
}
void Eliminar_PosicionX(enlace *C,int posicion){
    enlace basura;
    if(Largo_Recursivo(*C)<posicion)
        return;
    if(posicion==1){
        basura=*C;
        *C=(*C)->siguiente;
        free(basura);
        return;
    }
    enlace aux=*C;
    for(int i=1;i<posicion-1;i++)
        aux=aux->siguiente;
    basura=aux->siguiente;
    aux->siguiente=aux->siguiente->siguiente;
    free(basura);   
}

/* Funciones que determina el largo de la LLS o cantidad de nodos con info X de la LLS*/
int Largo(enlace C){
    enlace aux=C;
    int contador=0;
    while(aux!=NULL){
        contador++;
        aux=aux->siguiente;
    }
    return contador;
}
int Largo_Recursivo(enlace C){
    if(C==NULL)
        return 0;
    return 1 + Largo_Recursivo(C->siguiente);
}
int CantidadNodos_InfoX(enlace C,int X){
    int cont=0;
    if(C==NULL)
        return 0;
    if(C->info==X)
        cont++;
    return cont + CantidadNodos_InfoX(C->siguiente,X);
}

/* Función que ingresa un nuevo nodo en la n-ésima posición */
void InsertarPosicionX(enlace *C,int n,enlace nodo){
    if(*C==NULL){ //En caso de que la LLS esté vacía, rellena la LLS con nodos de info=0 hasta incorporar el nuevo nodo en la posición que corresponde
        for(int i=1;i<n;i++)
            InsertarFinal(C,CrearNodo(0));
        InsertarFinal(C,nodo);
        return;
    }
    if(n==1){ //En caso de que se quiera insertar el nodo en la primera posición de la LLS.
        nodo->siguiente=*C;
        *C=nodo;
        if(nodo->siguiente->info==0) //Si inserta una posición ocupada por un "relleno" (info 0), el nuevo nodo lo reemplaza, para así mantener la posición de nodos posteriores.
            Eliminar_InfoX(C,0,1);
        return;
    }
    if(Largo_Recursivo(*C)<n){ //
        while(Largo_Recursivo(*C)<n-1){
            InsertarFinal(C,CrearNodo(0));
        }
        InsertarFinal(C,nodo);
        return;
    }
    enlace aux=*C;
    for(int i=1;i<n-1;i++)
        aux=aux->siguiente;
    nodo->siguiente=aux->siguiente;
    aux->siguiente=nodo;
    Eliminar_InfoX(&nodo,0,1); //Si inserta una posición ocupada por un "relleno" (info 0), el nuevo nodo lo reemplaza, para así mantener la posición de nodos posteriores.
}

/* Funciones que Buscan un nodo */
//Retornan el puntero al nodo con la info buscada o NULL en caso contrario;
enlace Buscar(enlace C, int X){
    enlace aux=C;
    while(aux!=NULL){
        if(aux->info==X)
            return aux;
        aux=aux->siguiente;
    }
    return NULL;
}
enlace BuscarRecursivo(enlace C,int X){
    if(C==NULL)
        return NULL;
    if(C->info==X)
        return C;
    return BuscarRecursivo(C->siguiente,X);
}
//Retorna las posiciones de los nodos con la info buscada. Las guarda en una arreglo.
void BuscarPosiciones(enlace *C,int X,int *arreglo){
    enlace aux=*C;
    int contador=0,i=0;
    while(aux!=NULL){
        contador++;
        if(aux->info==X){
            arreglo[i]=contador;
            i++;
        }
        aux=aux->siguiente;
    }
}

/* Función que genera una LLS copia con nodos de ciertas caracteristicas */
void GenerarListaImpar(enlace *C,enlace *LLS_Copia){
    enlace aux=*C;
    for(int i=0;i<Largo_Recursivo(*C);i++){ //Recorremos toda la LLS original
        if(aux->info%2==1){
            enlace copia_nodo=CrearNodo(aux->info);
            InsertarFinal(LLS_Copia,copia_nodo);
        }
        aux=aux->siguiente;
    }
}
void GenerarListaPar(enlace *C,enlace *LLS_Copia){
    enlace aux=*C;
    for(int i=0;i<Largo_Recursivo(*C);i++){ //Recorremos toda la LLS original
        if(aux->info%2==0){
            enlace copia_nodo=CrearNodo(aux->info);
            InsertarFinal(LLS_Copia,copia_nodo);
        }
        aux=aux->siguiente;
    }
}
