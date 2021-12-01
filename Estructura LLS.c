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

/* Menus */
int menu_general();
int menu_insertar();
int menu_eliminar();
int menu_cantidad();
int menu_clonar();

/* Creación de nodos */
enlace CrearNodo(int);
void InsertarInicio (enlace*,enlace);
void InsertarFinal(enlace*,enlace);
void InsertarPosicionX(enlace*,int,enlace);
void InsertarAcendente(enlace*,enlace);

/* Transformaciones de Listas */
void TransformarLCS(enlace*);
void TransformarLLS(enlace*);

void Imprimir(enlace);

/* Eliminación de nodos */
void Eliminar_InfoX(enlace*,int,int);
void Eliminar_PosicionX(enlace*,int);

/* Cantidad de nodos */
int Largo(enlace);
int Largo_Recursivo(enlace);
int CantidadNodos_InfoX(enlace,int);

/* Buscar nodos */
enlace Buscar(enlace,int);
enlace BuscarRecursivo(enlace,int);
void BuscarPosiciones(enlace*,int,int*);

/* Copia con nodos de ciertas caracteristicas */
void GenerarListaImpar(enlace*,enlace*);
void GenerarListaPar(enlace*,enlace*);

/* Elimina todos los nodos */
void FormatearLLS(enlace*);

void InvertirSentidoLLS(enlace*);
void OrdenarAcendente(enlace*);
void OrdenarAcendenteArreglo(enlace*);

int main()
{
    /* Esta es la declaración de la Cabecera a la LLS. Inicialmente está apuntando a nada */
    enlace Cabecera = NULL;
    enlace LLS_clon=NULL;
    int input,delete;
    int opcion_menu=1;
    while(opcion_menu!=9){
        printf("_____________________________________________________________________________\n\n");
        opcion_menu=menu_general();
        switch(opcion_menu){
            case -1:for(int i=0;i<5;i++){
                        printf("\nIngrese valor del nuevo nodo: ");
                        scanf("%d",&input);
                        enlace nuevo_nodo = CrearNodo(input);
                        InsertarFinal(&Cabecera,nuevo_nodo);
                    }            
            break;
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
                        case 4: InsertarAcendente(&Cabecera,nuevo_nodo);
                        break;
                    }
                    printf("\n"); Imprimir(Cabecera);
            break;
            case 2: printf("\n"); Imprimir(Cabecera);
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
                    printf("\nValor de los nodos a buscar: ");
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
            break;
            case 6: switch(menu_clonar()){
                        case 1: printf("\nLLS Original: "); Imprimir(Cabecera);
                                GenerarListaPar(&Cabecera,&LLS_clon);
                                printf("\nLLS Clon: "); Imprimir(LLS_clon);
                        break;
                        case 2: printf("\nLLS Original: "); Imprimir(Cabecera);
                                GenerarListaImpar(&Cabecera,&LLS_clon);
                                printf("\nLLS Clon: "); Imprimir(LLS_clon);
                        break;
                    }
            break;
            case 7: switch(menu_ordenar()){
                        case 1: InvertirSentidoLLS(&Cabecera);
                        break;
                        case 2: OrdenarAcendenteArreglo(&Cabecera);
                        break; 
                    
                    }  
                    printf("\n"); Imprimir(Cabecera);                  
            break;
            case 8: FormatearLLS(&Cabecera);
                    printf("\nLa lista se ha vaciado...\n");
            break;
            case 9: printf("_____________________________________________________________________________\n\n");
                    printf("Saliendo del programa...\n");
            break;
            default: printf("\nOpcion ingresada invalida. Intentelo Nuevamente...\n");
            break;
        }
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
    printf("6) Clonar Lista\n");
    printf("7) Ordenar Lista\n");
    printf("8) Formatear LLS\n");
    printf("9) Salir\n");
    
    printf("\nSelecione una opcion: ");
    scanf("%d",&opcion_menu);
    return opcion_menu;
}

/* MENUS */
int menu_insertar(){
    int opcion_menu;
    printf("\n1) Insertar nuevo nodo al Inicio\n");
    printf("2) Insertar nuevo nodo al Final\n");
    printf("3) Insertar nuevo nodo en Posicion X\n");
    printf("4) Insertar nuevo nodo en orden acendente\n");
    
    printf("\nSelecione una opcion: ");
    scanf("%d",&opcion_menu);
    return opcion_menu;
}
int menu_eliminar(){
    int opcion_menu;
    printf("\n1) Eliminar nodo con info X\n");
    printf("2) Eliminar nodo en Posicion X\n");
    
    printf("\nSelecione una opcion: ");
    scanf("%d",&opcion_menu);
    return opcion_menu;
}
int menu_cantidad(){
    int opcion_menu;
    printf("\n1) Cantidad total de nodos\n");
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
int menu_clonar(){
    int opcion_menu;
    printf("\n1) Clonar lista con nodos de informacion par\n");
    printf("2) Clonar lista con nodos de informacion impar\n");

    printf("\nSelecione una opcion: ");
    scanf("%d",&opcion_menu);
    return opcion_menu;
}
int menu_ordenar(){
    int opcion_menu;
    printf("1) Invertir Lista\n");
    printf("2) Ordenar de forma acendente\n");

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

/* Funciones que ingresan un nuevo nodo a la lista */
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
void InsertarAcendente(enlace *C,enlace nodo){
    if(*C==NULL){
        *C=nodo;
        return;
    }
    if(nodo->info<(*C)->info){
        nodo->siguiente=*C;
        *C=nodo;
        return;
    }
    enlace aux=*C;
    while(aux->siguiente!=NULL){
        if(aux->info<nodo->info && (aux->siguiente)->info>nodo->info){
            nodo->siguiente=aux->siguiente;
            aux->siguiente=nodo;
            return;
        }
        aux=aux->siguiente;
    }
    aux->siguiente=nodo;
}
void TransformarLCS(enlace *C){
    if(*C==NULL)
        return;
    enlace aux=*C;
    while(aux->siguiente!=NULL)
        aux=aux->siguiente;
    aux->siguiente=*C;
}
void TransformarLLS(enlace *C){
    if(*C==NULL)
        return;
    enlace aux=*C;
    while(aux->siguiente!=*C)
        aux=aux->siguiente;
    aux->siguiente=NULL;
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
void GenerarListaPar(enlace *C,enlace *LLS_Copia){
    FormatearLLS(LLS_Copia);
    enlace aux=*C;
    for(int i=0;i<Largo_Recursivo(*C);i++){ //Recorremos toda la LLS original
        if(aux->info%2==0){
            enlace copia_nodo=CrearNodo(aux->info);
            InsertarFinal(LLS_Copia,copia_nodo);
        }
        aux=aux->siguiente;
    }
}
void GenerarListaImpar(enlace *C,enlace *LLS_Copia){
    FormatearLLS(LLS_Copia);
    enlace aux=*C;
    for(int i=0;i<Largo_Recursivo(*C);i++){ //Recorremos toda la LLS original
        if(aux->info%2==1){
            enlace copia_nodo=CrearNodo(aux->info);
            InsertarFinal(LLS_Copia,copia_nodo);
        }
        aux=aux->siguiente;
    }
}

/* Función que formatea una LLS*/
void FormatearLLS(enlace *C){
    while(*C!=NULL){
        enlace basura=*C;
        *C=(*C)->siguiente;
        free(basura);
    }
}

/* Implementar una función que invierta el sentido de los enlaces de una LLS "L" de largo mayor que 100. */
void InvertirSentidoLLS(enlace *C){
    enlace Next,Anterior=NULL;
    while(*C!=NULL){
        Next=(*C)->siguiente;
        (*C)->siguiente=Anterior;
        Anterior=*C;
        *C=Next;
    }
    *C=Anterior;
}
void OrdenarAcendenteArreglo(enlace *C){
    if(*C==NULL || Largo(*C)==1)
        return;
    enlace Cabecera=*C;
    enlace Menor_Anterior=CrearNodo(0);
    int CONT=1,X=1,largo=Largo(*C);
    while(CONT<largo){
        enlace aux=Cabecera;
        enlace Menor=Cabecera;
        enlace anterior=aux;    
        int cont=0;
        while(aux->siguiente!=NULL){
            if(Menor->info>aux->siguiente->info){
                anterior=aux;
                Menor=aux->siguiente;
                cont++;
            }
            aux=aux->siguiente;
        }
        if(X==1){
            *C=Menor;
            X=-1;
        }
        if(cont!=0){            
            anterior->siguiente=Menor->siguiente;
            Menor->siguiente=Cabecera;
            Menor_Anterior->siguiente=Menor;
            Menor_Anterior=Menor;
        }else{
            Cabecera=Cabecera->siguiente;
            Menor_Anterior=Menor;
        }            
        CONT++;
    }    
}