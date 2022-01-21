/* TAD COLAS - fifo (First In, First Out)

especifiación COLAS[ELEM]
usa BOOLEANOS
tipos cola
operaciones
        cola_vacia    :               ->  cola {constructora}
        pedir_vez     : cola elemento ->  cola {constructora}
        avanzar       : cola          ->p cola
        primero       : cola          ->p elemento
        es_cola_vacia : cola          ->  bool
        ultimo        : cola          ->p elemento
        inversa       : cola          ->  cola
        concatenar    : cola cola     ->  cola
variables
        e : elemento
        c,d : cola
ecuaciones
        avanzar(cola_vacia) = error
        avanzar(pedir_vez(c,e)) = cola_vacia <= es_cola_vacia(c)
        avanzar(pedir_vez(c,e)) = pedir_vez(avanzar(c),e)) <= no es_cola_vacia(c)
        primero(cola_vacia) = error
        primero(pedir_vez(c,e)) = e <= es_cola_vacia(c)
        primero(pedir_vez(c,e)) = primero(c) <= no es_cola_vacia(c)
        es_cola_vacia(cola_vacia) = cierto
        es_cola_vacia(pedir_vez(c,e)) = falso

        ultimo(cola_vacia) = error
        ultimo(pedir_vez(c,e)) = e
        inversa(cola_vacia) = cola_vacia
        inversa(c) = perdir_vez(inversa(avanzar(c)), primero(c)) <= !es_cola_vacia(c)
        concatenar(c,cola_vacia) = c
        concatenar(c,pedir_vez(d,e)) = pedir_vez(concatenar(c,d),e)

fespecificación
*/

#include <iostream>

using namespace std;

typedef int elemento;

struct nodo_cola
{
        elemento dato;
        nodo_cola * sig;
};

struct cola
{
        nodo_cola * primero = NULL;
        nodo_cola * ultimo = NULL;
};

cola cola_vacia(){
	cola c;
        //c.primero = NULL;
        //c.ultimo = NULL;
	return c;
}

bool esColaVacia(cola c) {
    return (c.primero==NULL && c.ultimo==NULL);
}


void pedir_vez(elemento e, cola & c){
	nodo_cola* aux=new nodo_cola;
	aux->dato=e;
	aux->sig=NULL;
	if(c.primero==NULL){
		c.primero=aux;
	}
	else{
		(c.ultimo)->sig=aux;
	}
	c.ultimo=aux;
}

elemento primero(cola c){
	return (c.primero)->dato;
}

void avanzar(cola & c){
	nodo_cola* aux=new nodo_cola;
	if(c.primero==NULL){
		cout<<"Error. Cola vacía";
		delete(aux);
	}
	else{
		aux=c.primero;
		c.primero=aux->sig;
		if(c.primero==NULL){
			c.ultimo=NULL;
			delete(aux);
		}
	}
}

void mostrar_cola(cola c){
	nodo_cola* aux;
	aux = c.primero;
	while (aux != NULL){
		if ((aux->sig)==NULL){
			cout<<aux->dato<<"."<<endl;
		}
		else{cout<<aux->dato<<", ";
		}
		
		aux=aux->sig;
	}
	delete(aux);
}

int profundidad_cola(cola c){
	nodo_cola* aux;
	int contador=0;
	aux= c.primero;
	while(aux!=NULL){
		contador++;
		aux=aux->sig;
	}
	delete(aux);
	return contador;
}

void liberar(cola & c){
	nodo_cola* aux;//Esto reserva memoria que se habría que eliminar
	c.ultimo=c.primero;
	while ((c.ultimo->sig)!=NULL){
		c.primero=(c.primero)->sig;
		delete(c.ultimo);
		c.ultimo=c.primero;
	}
	aux=c.primero;
	c.primero=NULL;
	c.ultimo=NULL;
	delete(aux);
}
