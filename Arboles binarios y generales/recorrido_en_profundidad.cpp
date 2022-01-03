/*
especificación RECORRIDOS-PROF-ARBOLES-BINARIOS[ELEM]
usa ÁRBOLES-BINARIOS[ELEM], LISTAS[ELEM]
operaciones
        preorden  : arbol-bin  ->  lista
        inorden   : arbol-bin  ->  lista
        postorden : arbol-bin  ->  lista
variables
        e : elemento
        iz,dr: arbol-bin
ecuaciones
        preorden(arbol_vacio) = []
        preorden(planta(iz,e,dr)) = [e] ++ (preorden(iz) ++ preorden(dr))
        inorden(arbol1_vacio) = []
        inorden(plantar(iz,e,dr)) = (inorden(iz)) ++ ([e] ++ inorden(dr))
        postorden(arbol_vacio) = []
        postorden(plantar(iz,e,dr)) = (postorden(iz)) ++ (postorden(dr) ++ [e])
fespecificación
*/

// PREORDEN: RAIZ + HIJO_IZ + HIJO_DR
// INORDEN : HIJO_IZ + RAIZ + HIJO_DR
// POSTORDEN : HIJO_IZ + HIJO_DR + RAIZ

#include "arboles_binarios.cpp"

template <typename e>
void preorden(Abb<e> arb)
{
    if (!es_arbol_vacio(arb))
    {
        cout << arb->dato << " ";
        preorden(arb->iz);
        preorden(arb->dr);
    }
}


template <typename e>
void inorden(Abb<e> arb)
{
    if (!es_arbol_vacio(arb))
    {
        preorden(arb->iz);
        cout << arb->dato << " ";
        preorden(arb->dr);
    }
}


template <typename e>
void postorden(Abb<e> arb)
{
    if (!es_arbol_vacio(arb))
    {
        preorden(arb->iz);
        preorden(arb->dr);
        cout << arb->dato << " ";
    }
}

//reconstruir el arbol a partir de la lista en inorden y preorden


// secuencia a arbol y viceversa


int main()
{
    Abb<int> a;
    
    a = arbol_vacio<int>(); //llamar indicando el tipo
    plantar(a, 5);
    plantar(a,3);
    plantar(a, 1);
    plantar(a,2);
    plantar(a,6);
    plantar(a,7);
    plantar(a,1);

    preorden(a);
}