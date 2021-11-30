#include <stdio.h>
#include <stdlib.h> 
/* Esta es nuestra declaración de nodo */
typedef struct nodo{
    int info;
    struct nodo * siguiente; 
} t_nodo,*enlace;

enlace CrearNodo(int input){
    enlace nodo;
    nodo =(enlace)malloc(sizeof(t_nodo)); // Solicitamos un fragmento de memoria de tamaño sizeof(t_nodo). Similar a definir el tamaño de un arreglo.
    nodo->info=input;
    nodo->siguiente=NULL;
    return nodo;
}
void InsertarFinal(enlace *Cabecera,enlace nuevo_nodo){
    if(*Cabecera==NULL){
        *Cabecera=nuevo_nodo;
        return;
    }
    enlace aux=*Cabecera;
    while(aux->siguiente!=NULL)
        aux=aux->siguiente;
    aux->siguiente=nuevo_nodo;

}
void imprimirLLS(enlace Cabecera){
    enlace aux=Cabecera;
    while(aux!=NULL){
        printf("[%d] ",aux->info);
        aux=aux->siguiente;
    }
}
void Insertarinicio(enlace *Cabecera,enlace nuevo_nodo){
    if(*Cabecera==NULL){
        *Cabecera=nuevo_nodo;
        return;
    }
    nuevo_nodo->siguiente=*Cabecera;
    *Cabecera=nuevo_nodo;
}
void InsertarAcendente(enlace *Cabecera,enlace nuevo_nodo){
    if(*Cabecera==NULL){
        *Cabecera=nuevo_nodo;
        return;
    }
    if(nuevo_nodo->info<(*Cabecera)->info){
        nuevo_nodo->siguiente=*Cabecera;
        *Cabecera=nuevo_nodo;
        return;
    }
    enlace aux=*Cabecera;
    while(aux->siguiente!=NULL){
        if(aux->info<nuevo_nodo->info && (aux->siguiente)->info>nuevo_nodo->info){
            nuevo_nodo->siguiente=aux->siguiente;
            aux->siguiente=nuevo_nodo;
            return;
        }
        aux=aux->siguiente;
    }
    aux->siguiente=nuevo_nodo;
}
int main(){
    enlace Cabecera=NULL;
    for(int i=0;i<10;i++){
        int input;
        printf("\n");
        printf("Ingrese valor del nodo: ");
        scanf("%d",&input);
        
        enlace nuevo_nodo=CrearNodo(input);
        //InsertarFinal(&Cabecera,nuevo_nodo);
        InsertarAcendente(&Cabecera,nuevo_nodo);
        imprimirLLS(Cabecera);
    }
    return 0;
}