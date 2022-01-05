
// La implementación de pilas sobre memoria estática tienen el inconveniente de que
// el tamaño de la estructura queda restringido por la capacidad del soporte de 
// almacenamiento, es decir, el tamaño del vector datos.

#include <iostream>

using namespace std;

typedef int elemento; //(otra forma que sustituye template)

const int MAX_ELEM = 100;

struct Pila
{
    elemento datos[MAX_ELEM];
    int ind_cima;
};

Pila pila_vacia(){
	Pila p;

	p.ind_cima = -1;
	return p;
}

void apilar(elemento e, Pila & p){
	if ((p.ind_cima + 1)==MAX_ELEM){
		cout<<"Error: Pila llena.";
	}
	else{
		p.ind_cima = p.ind_cima + 1;
		p.datos[p.ind_cima]=e;
	}
}

elemento cima(Pila p){
	return (p.datos[p.ind_cima]);
}

void desapilar(Pila & p){
	if(p.ind_cima==-1)
		cout<<"Error. Pila vacia";
	else
		(p.ind_cima)--;
}

bool es_pila_vacia(Pila p)
{
    return (p.ind_cima == -1);
}

void mostrar(Pila p){
	int indice;
	indice=p.ind_cima;
	while (indice >= 0){
		cout<<"\t"<<p.datos[indice]<<endl;
		indice--;
	}
}

int profundidad(Pila p){
	return (p.ind_cima + 1);
}

