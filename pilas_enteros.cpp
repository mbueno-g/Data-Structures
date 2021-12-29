/* TAD: PILAS

especificación PILAS[ELEM]
usa BOOLEANOS
tipos pila
operaciones
        pila_vacía    :               -> pila {constructora}
        apilar        : elemento pila -> pila {constructora}
        desapilar     : pila          ->p pila
        cima          : pila          ->p elemento
        es_pila_vacia : pila          -> bool
variables
        e : elemento
        p : pila
ecuaciones
        desapilar(pila_vacía) = error
        desapilar(apilar(e,p)) = p
        cima(pila_vacia) = error
        cima(apilar(e,p)) = e
        es_pila_vacia(pila_vacia)  = cierto
        es_pila_vacia(apilar(e,p)) = falso
fespecificación
*/

#include<iostream>

using namespace std;

typedef int elemento;

struct nodo_pila
{
    elemento dato;
    nodo_pila *sig;
};

typedef nodo_pila* pila;

pila pila_vacia();
void apilar(elemento e, pila & p);
void desapilar(pila & p);
elemento cima(pila p);
bool es_pila_vacia(pila p);

void liberar(pila & p);
void mostrar(pila p);

pila pila_vacia()
{
    return NULL;
}

void apilar(elemento e, pila & p)
{
    pila aux;

    aux = new nodo_pila;
    aux->dato = e;
    aux->sig = p;
    p = aux;
}

void desapilar(pila & p)
{
    pila aux;

    aux = p->sig;
    delete p;
    p = aux;
}

elemento cima(pila p)
{
    return (p->dato);
}

bool es_pila_vacia(pila p)
{
    return (p == NULL);
}

void liberar(pila & p)
{
    while (!es_pila_vacia(p))
    {
        desapilar(p);
    }
}

void mostrar(pila p)
{
    while (p != NULL)
    {
        cout << p->dato << endl;
        p = p->sig;
    }
}

int main()
{
    pila p;
    int i;

    p = pila_vacia();
    cout << "Introduce un número: ";
    cin >> i;
    while (i > 0)
    {
        apilar(i,p);
        i--;
    }
    cout << "La pila es: " << endl;
    mostrar(p);
    cout << "---------------" << endl;
    desapilar(p);
    cout << "Si despilamos un elemento: " << endl;
    mostrar(p);
    cout << "---------------" << endl;
    cout << "Si apilamos el número 11" << endl;
    apilar(11, p);
    mostrar(p);
    cout << "---------------" << endl;
    liberar(p);
    return(0);
}