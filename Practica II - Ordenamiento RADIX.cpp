/// Practica II - Ordenamiento RADIX
/// Equipo 3
/// Sergio Josue Maldonado Calcáneo
/// Asdrubal Palafox
/// Abdel Bustamante
/// Roberto Fuentes Gallardo


#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

using namespace std;

typedef struct head {
    struct Multi *liga;
} Head;

typedef struct Nodo {
    int inf;
    struct Nodo *sig;
}Nodo;

typedef struct Multi{
    int inf;
    struct Nodo *derecha;
    struct Multi *abajo;
}Multi;

void Imprimir (Nodo *lista){

    if (lista == NULL)
        cout<<"La cola esta vacia !!\n";
    else{
        cout<<("\n");
        while (lista != NULL) {
            cout<<lista->inf<<"  ";
            lista =  lista->sig;
        }
    }
    cout<<("\n");
}

void Limpiar (Multi *multilista){
    Nodo *tempp = NULL;
    while( multilista != NULL){
            tempp = multilista->derecha;
            free(multilista);
            multilista->derecha = tempp;
        }
    }

void Limpiari (Nodo *multilista){
    Nodo* tempp = NULL;
    while( multilista != NULL){
            tempp = multilista->sig;
            free(multilista);
            multilista = tempp;
        }
    }

void ImprimirMultilista (Multi *multilista){

    Nodo *iterador=NULL;

    if (multilista == NULL)
        cout<<"\n La multilista esta vacia !!\n";
    else{
        cout<<("\n");
        while (multilista != NULL) {
            cout<<"\n["<<multilista->inf<<"]"<<" --> ";

            iterador = multilista->derecha;

            while(iterador != NULL){
                cout<<iterador->inf<<" -> ";
                iterador = iterador->sig;
            }
            cout<<("\n");
            multilista = multilista->abajo;
        }
    }
    cout<<("\n");


}

Nodo *AgregaDato (Nodo *lista, int num){                     /// Ingresa elementos

     Nodo *lp = lista;

     if (lista != NULL) {
        while (lista->sig != NULL)
                lista = lista->sig;
                lista->sig = (struct Nodo *) malloc(sizeof(Nodo));
                lista = lista->sig;
                lista->sig = NULL;
                lista->inf = num;
        }
     else
        {
         lista =  (struct Nodo *) malloc (sizeof (Nodo));
         lista->sig = NULL;
         lista->inf = num;
         lp = lista;
        }

        return lp;
}

int Mayor (Nodo *lista, int mayori[]){                       /// Digitos  y Numero Mayor
    int mayor = 0, i=0, residuo;
    Nodo *lp = lista;
    if(lista==NULL){
        cout<<"Lista vacia";
    }else{
        while(lista != NULL){
            if(lista->inf > mayor){
                mayor = lista->inf;
            }
            lista = lista->sig;
        }
        mayori[0]=mayor;
    }

    while(mayor/10 > 0){
         mayor = mayor/10;
         i++;
    }

    return i;
}

int SacarResiduo (int n, int digitos){
    for(int i=1; i<digitos; i++ ){
        n = n/10;
    }
    return n%10;
}

Multi *Ordenar (Nodo *lista, Multi *multilista, int digito){ /// Ordena la lista lineal en multilista
    Multi *lp = multilista;
    Multi *head = multilista;
    Multi *aux = NULL;
    Multi *iterador = multilista;
    Nodo  *auxlista = NULL;
    Nodo *listaDer = NULL;

    int residuo, dato = 0, j = 0;
    bool ban = false;
    bool ban1 = false;
    bool ban2 = false;

    while(lista != NULL){
            residuo = SacarResiduo(lista->inf, digito);
            //dato = lista->inf;
            //residuo = dato%digito;
            if(multilista != NULL){
                    lp = head;

                    while (lp->abajo != NULL){  /// Recorre la multilista

                        if( lp->inf == residuo && ban == false ){ /// Si ya existe un Nodo con el mismo residuo.
                          listaDer = lp->derecha;
                          listaDer = (struct Nodo *) malloc (sizeof (Nodo));
                          listaDer = lp->derecha;
                          while(listaDer->sig != NULL){
                            listaDer = listaDer->sig;
                          }
                            listaDer->sig = (struct Nodo *) malloc (sizeof (Nodo));
                            listaDer = listaDer->sig;
                            listaDer->inf = lista->inf;
                            listaDer->sig = NULL;
                            ban=true;
                        }
                        if( lp->inf > residuo && ban == false ){ /// Si residuo es menor que Nodo, se coloca antes ( CORRECTO )
                            aux = (struct Multi *)malloc(sizeof (Multi));
                            aux->inf = residuo;
                            aux->abajo = NULL;
                            listaDer = listaDer->sig;
                            listaDer =  (struct Nodo *) malloc (sizeof (Nodo));
                            listaDer->inf = lista->inf;
                            aux->derecha = listaDer;
                            listaDer->sig = NULL;
                            if(head->inf > aux->inf){
                                aux->abajo = head;
                                head = aux;
                                ban = true;
                                ban2 = true;
                            }else{
                                iterador->abajo = aux;
                                aux->abajo = lp;
                                lp = aux;
                                ban = true;
                                ban2 = true;
                            }
                        }
                        iterador = lp;
                        lp = lp->abajo;
                        ban1 = true;
                    } ///-------------------- Fin de lp
                    if( lp->inf == residuo && ban == false && lp->abajo==NULL){ /// Si ya existe un Nodo con el mismo residuo.
                          listaDer = lp->derecha;
                          listaDer = (struct Nodo *) malloc (sizeof (Nodo));
                          listaDer = lp->derecha;
                          while(listaDer->sig != NULL){
                            listaDer = listaDer->sig;
                          }
                            listaDer->sig = (struct Nodo *) malloc (sizeof (Nodo));
                            listaDer = listaDer->sig;
                            listaDer->inf = lista->inf;
                            listaDer->sig = NULL;
                            ban=true;
                            ban1 = true;
                        }
                    if( lp->inf > residuo && ban == false && ban1 == false ){ /// Opcion que es para 1 solo nodo ( CORRECTO )

                            aux = (struct Multi *)malloc(sizeof (Multi));
                            aux->inf = residuo;
                            aux->abajo = NULL;
                            listaDer = listaDer->sig;
                            listaDer =  (struct Nodo *) malloc (sizeof (Nodo));
                            listaDer->inf = lista->inf;
                            aux->derecha = listaDer;
                            listaDer->sig = NULL;
                            head = aux;
                            aux->abajo = lp;
                            iterador = lp;
                            ban = true;
                            ban1 = true;
                        }
                    if( lp->inf > residuo && ban == false && lp->abajo == NULL ){ /// ( CORRECTO )
                            aux = (struct Multi *)malloc(sizeof (Multi));
                            aux->inf = residuo;
                            aux->abajo = NULL;
                            listaDer = listaDer->sig;
                            listaDer =  (struct Nodo *) malloc (sizeof (Nodo));
                            listaDer->inf = lista->inf;
                            aux->derecha = listaDer;
                            listaDer->sig = NULL;
                            iterador->abajo = aux;
                            aux->abajo = lp;
                            iterador = lp;
                            ban = true;
                            ban1 = true;
                    }
                        else{
                            if( ban == false ){ /// Va enseguida
                                aux = (struct Multi *)malloc(sizeof (Multi));
                                aux->inf = residuo;
                                aux->abajo = NULL;
                                listaDer = listaDer->sig;
                                listaDer =  (struct Nodo *) malloc (sizeof (Nodo));
                                listaDer->inf = lista->inf;
                                aux->derecha = listaDer;
                                listaDer->sig = NULL;
                                iterador = lp;
                                lp ->abajo = aux;
                                lp = lp->abajo;

                                ban=true;
                            }
                        }
                    ban = false;
            }else{                   /// En caso de que no haya ninguún elemento en la multilista

                multilista =  (struct Multi *) malloc (sizeof (Multi));
                listaDer =  (struct Nodo *) malloc (sizeof (Nodo));
                multilista->abajo = NULL;
                multilista->inf = residuo;

                multilista->derecha = listaDer;
                listaDer->inf = lista->inf;
                listaDer->sig = NULL;

                lp = multilista;
                head = multilista;
            }
            lista = lista->sig;
    } /// Fin de la creacion de la multilista

    return head;
}

Nodo *OrdenarLineal (Multi *multilista){
    Nodo *head = NULL;

    Nodo *lista = NULL;


    Nodo *aux = NULL;
    Nodo *auxlista = NULL;

    int i=0;

    if(multilista == NULL){
        cout<<"\n La multilista está vacía";

    }else{
        lista = (struct Nodo *) malloc (sizeof (Nodo));
        aux = (struct Nodo *) malloc (sizeof (Nodo));

        while( multilista != NULL){
                if(head == NULL){
                    lista = multilista->derecha;
                    head = lista;
                    aux = lista;
                }else{
                    lista = multilista->derecha;
                    aux->sig = lista;
                    aux = lista;
                }
                while (aux->sig != NULL){
                    aux = aux->sig;
                }
                multilista = multilista->abajo;
        }
    }

    return head;
}




int main(){                       //------------------------ Main
    int num, digitos, mayori[1], mayor, i=0, digito;
    struct Nodo *lista;
    struct Multi *multilista;
    multilista = NULL;
    lista = NULL;
    cout<<"            Metodo de Ordenamiento RADIX\n\n";
    cout<<" Ingresa los datos. Al terminar, ingrese 0 y presione enter: \n\n";
    while(num != 0){
        cin>>num;
        if(num != 0){
            lista=AgregaDato(lista, num);
        }
    }
    //Imprimir (lista);
    cout<<"\n";
    digitos = Mayor(lista, mayori)+1;               // Contiene los digitos del numero mas grande en la lista
    mayor = mayori[0];
    cout<<"\nEl mayor es: "<<mayor;
    cout<<"\nLos digitos son: "<<digitos<<"\n";
    digito = 1;
    for (i=0; i<digitos; i++){
        multilista = Ordenar(lista, multilista, digito);
        ImprimirMultilista(multilista);
        digito++;
        lista = OrdenarLineal(multilista);
        multilista=NULL;
        Imprimir(lista);
        cout<<"\n";
        cout<<"\n";
    }
    cout<<"\nLa lista ordenada es: \n";
    Imprimir(lista);

    Limpiar(multilista);
    Limpiari(lista);
}
