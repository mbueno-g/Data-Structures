
// La especificación e implementación de forma abstracta de los 3 recorridos en profundidad de árboles
// binarios de búsqueda es igual que la de arboles binarios por ser estos un caso particular
// de árbol binario

/*
especificación RECORRIDOS-PROF-ARBOLES-BINARIOS-BÚSQUEDA[ELEM]
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


#include "arboles_binarios_busqueda.cpp"

template <typename e>
void preorden(ABB<e> arb)
{
    if (!es_abb_vacio(arb))
    {
        cout << arb->dato << " ";
        preorden(arb->iz);
        preorden(arb->dr);
    }
}


template <typename e>
void inorden(ABB<e> arb)
{
    if (!es_abb_vacio(arb))
    {
        preorden(arb->iz);
        cout << arb->dato << " ";
        preorden(arb->dr);
    }
}


template <typename e>
void postorden(ABB<e> arb)
{
    if (!es_abb_vacio(arb))
    {
        preorden(arb->iz);
        preorden(arb->dr);
        cout << arb->dato << " ";
    }
}


