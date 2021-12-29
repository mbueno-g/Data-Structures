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

template <typename elemento>
struct pila
{
    elemento dato;
    pila *sig;
};

template <typename elemento>
pila<elemento>* pila_vacia(pila<elemento>* &p)
{
    p = NULL;
    return p;
}

template <typename elemento>
void apilar(elemento e, pila<elemento>* & p)
{
    pila<elemento>* aux;

    aux = new pila<elemento>;
    aux->dato = e;
    aux->sig = p;
    p = aux;
}

template <typename elemento>
void desapilar(pila<elemento>* & p)
{
    pila<elemento>* aux;

    aux = p->sig;
    delete p;
    p = aux;
}

template <typename elemento>
elemento cima(pila<elemento>* p)
{
    return (p->dato);
}

template <typename elemento>
bool es_pila_vacia(pila<elemento>* p)
{
    return (p == NULL);
}

template <typename elemento>
void liberar(pila<elemento>* & p)
{
    while (!es_pila_vacia(p))
    {
        desapilar(p);
    }
}

template <typename elemento>
void mostrar(pila<elemento>* p)
{
    while (p != NULL)
    {
        cout << p->dato << endl;
        p = p->sig;
    }
}

int main()
{
    pila<int>* p;
    int i;

    p = pila_vacia(p);
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