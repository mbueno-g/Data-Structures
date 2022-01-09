/* TAD: PILAS

especificación PILAS[ELEM]
usa BOOLEANOS, NATURALES
tipos pila
operaciones
        pila_vacía    :               -> pila {constructora}
        apilar        : elemento pila -> pila {constructora}
        desapilar     : pila          ->p pila
        cima          : pila          ->p elemento
        es_pila_vacia : pila          -> bool
        profundidad   : pila          -> nat
        fondo         : pila          ->p elemento
        inversa       : pila          -> pila
        duplicar      : pila          -> pila
        concatenar    : pila pila     -> pila
        entremezclar  : pila pila     -> pila
operaciones privadas
        apilar_inversa: pila pila     -> pila
variables
        e,f : elemento
        p,q : pila
ecuaciones
        desapilar(pila_vacía) = error
        desapilar(apilar(e,p)) = p
        cima(pila_vacia) = error
        cima(apilar(e,p)) = e
        es_pila_vacia(pila_vacia)  = cierto
        es_pila_vacia(apilar(e,p)) = falso

        profundidad(pila_vacia) = 0
        profundidad(apilar(e,p)) = 1 + profundidad(p)
        fondo(pila_vacia) = error
        fondo(apilar(e,p)) = e <= es_pila_vacia(p)
        fondo(apilar(e,p)) = e <= !es_pila_vacia(p)
        apilar_inversa(pila_vacia,p) = p
        apilar_inversa(apilar(e,p),q) = aplicar_inversa(p,apilar(e,q))
        inversa(p) = apilar_inversa(p,pila_vacia)
        duplicar(pila_vacia) = pila_vacia
        duplicar(apilar(e,p)) = apilar(e, apilar(e,duplicar(p)))
        concatenar(p,pila_vacia) = p
        concatenar(p, apilar(e,q)) = apilar(e, concatenar(p,q))
        concatenar(p,q) = apilar_inversa(inversa(q),p)
        entremezclar(pila_vacia, pila_vacia) = pila_vacia
        entremezclar(apilar(e,p),q) = apilar(e,entremezclar(p,q)) <= profundidad(p) + 1 > profundidad(q)
        entremezclar(p,apilar(e,q)) = apilar(e,entremezclar(p,q)) <= profundidad(p) <= profunidad(q) + 1
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
pila<elemento>* pila_vacia()
{
    return (NULL);
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

// no hace falta un auxiliar para recorrer la pila
template <typename elemento>
int profundidad(pila<elemento>* p)
{
    int cont;

    cont = 0;
    while (!es_pila_vacia(p))
    {
        cont++;
        p = p->sig;
    }
    return (cont);
}


template <typename e>
pila<e>* copiar_pila(pila<e>* p)
{
    pila<e> *aux = new pila<e>;
    pila<e> *s;
    pila<e> *t;
    pila<e> *r;

    if (es_pila_vacia(p))
        return (NULL);
    r = p;
    aux = pila_vacia<e>();
    aux->dato = r->dato;
    s = aux; // para no mover el puntero de aux
    while(r->sig != NULL)
    {
        r = r->sig;
        t = new pila<e>; // para crear un nuevo nodo e ir enlazando los sig nodos
        t = NULL;
        t->dato = r->dato;
        s->sig = t;
        s = t;
    }
    s->sig = NULL;
    return (aux);
}