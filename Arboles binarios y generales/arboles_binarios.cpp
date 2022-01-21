/* TAD Árboles binarios

especificación ARBOLES_BINARIOS[ELEM]
usa BOOLEANOS, NATURALES
tipos arbol-bin
operaciones
        arbol_vacio    :                              ->  arbol-bin {constructora}
        plantar        : arbol-bin elemento arbol-bin ->  arbol-bin {constructora}
        raiz           : arbol-bin                    ->p elemento
        hijo_iz        : arbol-bin                    ->p arbol-bin
        hijo_dr        : arbol-bin                    ->p arbol-bin
        es_arbol_vacio : arbol-bin                    ->  bool
        altura         : arbol-bin                    ->  nat
        num_nodos      : arbol-bin                    ->  nat
        num_hojas      : arbol-bin                    ->  nat
        especular      : arbol-bin                    ->  arbol-bin
variables
        e : elemento
        iz,dr : arbol-bin
ecuaciones
        hijo_iz(arbol_vacio) = error
        hijo_iz(plantar(iz,e,dr)) = iz
        hijo_dr(arbol_vacio) = error
        hijo_dr(plantar(iz,e,dr)) = dr
        raiz(arbol_vacio) = error
        raiz(plantar(iz,e,dr)) = e
        es_arbol_vacio(arbol_vacio) = cierto
        es_arbol_vacio(plantar(iz,e,dr)) = falso

        altura(arbol_vacio) = 0
        altura(plantar(iz,e,dr)) = 1 + max(altura(iz), altura(dr))
        num_nodos(arbol_vacio) = 0
        num_nodos(plantar(iz,e,dr)) = 1 + num_nodos(iz) + num_nodos(dr))
        num_hojas(arbol_vacio) = 0
        num_hojas(plantar(iz,e,dr)) = 1 <= es_arbol_vacio(iz) && es_arbol_vacio(dr)
        num_hojas(plantar(iz,e,dr)) = num_hojas(iz) + num_hojas(dr) <= no es_arbol_vacio(iz) || no es_arbol_vacio(dr)
        especular(arbol_vacio) = arbol_vacio
        especular(plantar(iz,e,dr)) = plantar(especular(dr), e, especular(iz))
fespecificación
*/

// ÁRBOL BINARIO: nodo con dos hijos
// ÁRBOL GENERAL: nodo con número variable de hijos ([0,grado]). A diferencia de los árboles
// binarios puede ser vacío
//                     raíz
//                       |
//                     rama
//                     /   \
//                   hoja  hoja

// ÁRBOL GENERAL => ÁRBOL BINARIO


#include <iostream>
using namespace std;

template <typename e>
struct nodo_arb
{
        e            dato;
        nodo_arb<e>* iz = NULL;  //puntero
        nodo_arb<e>* dr = NULL;
};

template <typename e>
using Abb = nodo_arb<e> *; // utilizar using en vez de typedef cuando se usa template

template <typename e>
Abb<e> arbol_vacio()
{
        return (NULL);
}

template <typename e>
bool es_arbol_vacio(Abb<e> arb)
{
        return (arb==NULL);
}

template <typename e>
e raiz(nodo_arb<e> arb) // no es un puntero
{
        return(arb.dato);
}

template <typename e>
Abb<e> hijo_iz(nodo_arb<e> arb)
{
        return (arb.iz);
}

template <typename e>
Abb<e> hijo_dr(nodo_arb<e> arb)
{
        return (arb.dr);
}

template <typename e>
void  plantar(Abb<e> &arb, e elemento) // e, no <e>
{
        if (es_arbol_vacio(arb))
        {
                arb = new nodo_arb<e>;
                arb->dato = elemento;
                //arb->iz = NULL;
                //arb->dr = NULL;
        }
        else if (arb->dato < elemento) // utilizar solo <= (no >=)
                plantar(arb->dr, elemento);
        else if(!(arb->dato == elemento)) // para no incluir los repetidos
                plantar(arb->iz, elemento);
}

//altura = número de nodos de la rama más larga
template <typename e>
int altura(Abb<e> arb)
{
        if (es_arbol_vacio(arb))
                return (0);
        else
                return (1 + max(altura(arb->iz), altura(arb->dr)));
}       

template <typename e>
int     num_nodos(Abb<e> arb)
{
        if (es_arbol_vacio(arb))
                return (0);
        else
                return (1 + num_nodos(arb->dr) + num_nodos(arb->iz));
}

// hojas = nodos cuyos dos hijos son vacios
template <typename e>
int     num_hojas(Abb<e> arb)
{
        if (es_arbol_vacio(arb))
                return (0);
        if (es_arbol_vacio(arb->iz) && es_arbol_vacio(arb->dr))
                return (1);
        else
                return (num_hojas(arb->dr) + num_hojas(arb->iz));
}

// imagen especular: intercambiando los hijos izquierdo y derecho
template <typename e>
void especular(Abb<e> &arb)
{
        Abb<e> aux;

        if (!es_arbol_vacio(arb))
        {
                especular(arb->iz);
                especular(arb->dr);
                aux = arb->iz;
                arb->iz = arb->dr;
                arb->dr = aux;
        }
}

template <typename e>
void printBT(const string& prefix, Abb<e> node, bool isLeft)
{
    if(!es_arbol_vacio(node))
    {
        cout << prefix;
        cout << (isLeft ? "iz├──" : "dr└──" );
        cout << node->dato << endl;
        printBT( prefix + (isLeft ? "│   " : "    "), node->iz, true);
        printBT( prefix + (isLeft ? "│   " : "    "), node->dr, false);
    }
}

// Declaramos un nuevo operador para mostrar por pantalla el arbol
template <typename T>
ostream & operator << (ostream & o, Abb<T> a)
{
       if(es_arbol_vacio(a)){
         o << "*" ;
       }
       else{
          o << "(" << a->dato << "," << a->iz << "," << a->dr << ")";
       }
       return o;
}

template <typename e>
void liberar(Abb<e> &arb)
{
        if (!es_arbol_vacio(arb))
        {
                liberar(arb->iz);
                liberar(arb->dr);
                delete arb;
        }
}


template <typename e>
Abb<e> copiar(Abb<e> arb)
{
        Abb<e> *aux = new nodo_arb<e>;
        if (es_arbol_vacio(arb))
        {
                aux = NULL;
        }
        else
        {
                aux->dato = arb->dato;
                aux->dr = copiar(arb->dr); 
                aux->iz = copiar(arb->iz);
        }
        return aux;
}