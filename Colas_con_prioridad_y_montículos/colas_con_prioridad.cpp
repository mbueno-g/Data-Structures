
/* TAD COLAS CON PRIORIDAD

especificación COLAS-CON-PRIORIDAD[ELEM<=]
usa BOOLEANOS
tipos colapr
operaciones
        cp_vacia    :                 ->  colapr {constructora}
        añadir      : colapr elemento ->  colapr {constructora}
        minimo      : colapr          ->p elemento
        eliminar_min: colapr          ->p colapr
        es_cp_vacia : colapr          ->  bool
variables
        e,f : elemento
        cp : colapr
ecuaciones
        añadir(añadir(cp,e),f) = añadir(añadir(cp,f),e)
        minimo(cp_vacio) = error
        minimo(añadir(cp_vacia,e)) = e
        minimo(añadir(añadir(cp,e),f)) = minimo(añadir(cp,e)) <= minimo(añadir(cp,e)) <= f
        minimo(añadir(añadir(cp,e),f)) = f <= minimo(añadir(cp,e)) > f
        eliminar_min(cp_vacia) = error
        eliminar_min(añadir(cp_vacia,e)) = cp_vacia
        eliminar_min(añadir(añadir(cp,e),f)) = añadir(eliminar_min(añadir(cp,e),f) <= minimo(añadir(cp,e)) <= f
        eliminar_min(añadir(añadir(cp,e),f)) = añadir(cp,e) <= minimo(añadir(cp,e)) > f
        es_cp_vacia(cp_vacia) = cierto
        es_cp_vacia(añadir(cp,e)) = falso
fespecificación

Las constructoras no son libres, ya que el orden en el que se añader los
elementos no importa: el mínimo siempre será el mismo, independientemente
del orden de inserción.
*/

#include <iostream>

using namespace std;

template <typename T>
struct nodo
{
    T dato;
    nodo<T> *iz = NULL;
    nodo<T> *dr = NULL;
};

template <typename T>
using cp = nodo<T> *;


template <typename T>
cp<T> cp_vacia()
{
    return (NULL);
}

template <typename T>
bool es_cp_vacia(cp<T> cola)
{
    return (cola==NULL);
}

template <typename T>
int altura(cp<T> arb)
{
        if (es_cp_vacia(arb))
                return (0);
        else
                return (1 + max(altura(arb->iz), altura(arb->dr)));
}       

template <typename T>
bool es_completo(cp<T> cola)
{
    if (es_cp_vacia(cola))
        return (true);
    else
        return (es_completo(cola->iz) && es_completo(cola->dr) && altura(cola->iz) == altura(cola->dr));
}

template <typename T>
bool es_semicompleto(cp<T> cola)
{
    if (es_cp_vacia(cola))
        return (true);
    else
        return (es_completo(cola) || (altura(cola->iz) == altura(cola->dr) && es_completo(cola->iz) && es_semicompleto(cola->dr)) 
                || (altura(cola->iz) == altura(cola->dr) + 1 && es_semicompleto(cola->iz) && es_completo(cola->dr)));
}


/*
utilizamos un MONTÍCULO DE MÁXIMOS: árbol binario semicompleto donde el elemento
en la raíz es mayor que todos los elementos en el hijo izquierdo y en el hijo
derecho, y ambos hijos son a su vez un montículo de máximos. Así, la raíz del árbol
contiene el máximo de todos los elementos en el árbol
*/


template <typename T>
void flotar(cp<T> &cola, T elemento)
{
    while(es_cp_vacia(cola))

}


template <typename T>
void flotar(cp<T> &cola, int j)
{
    int i = cola.ultimo;
    T aux;
    while (i != 0 && cola.dato[i] > cola.dato[i/2])
    {
        aux = cola.dato[i];
        cola.dato[i] = cola.dato[i/2];
        cola.dato[i/2] = aux;
        i = i/2;
    }
}


template <typename T>
void aniadir_max(cp<T> & cola, T elemento)
{
    if (es_cp_vacia(cola))
    {
        cola = new nodo<T>;
        cola->dato = elemento;
    }
    else if (es_cp_vacia(cola->iz))
        aniadir_max(cola->iz, elemento);
    else if (!es_cp_vacia(cola->iz) && es_cp_vacia(cola->dr))
        aniadir_max(cola->dr, elemento);
    else if (!es_completo(cola->iz))
        aniadir_max(cola->iz, elemento);
    else if (!es_completo(cola))
        aniadir_max(cola->dr, elemento);
    else
        aniadir_max(cola->iz, elemento);
    flotar(cola, elemento);
}

template <typename e>
void printBT(const string& prefix, cp<e> node, bool isLeft)
{
    if(!es_cp_vacia(node))
    {
        cout << prefix;
        cout << (isLeft ? "iz├──" : "dr└──" );
        cout << node->dato << endl;
        printBT( prefix + (isLeft ? "│   " : "    "), node->iz, true);
        printBT( prefix + (isLeft ? "│   " : "    "), node->dr, false);
    }
}

int main()
{
    cp<int> cola;

    cola = cp_vacia<int>();
    aniadir_max(cola, 70);
    aniadir_max(cola, 60);
    aniadir_max(cola, 50);
    aniadir_max(cola, 40);
    aniadir_max(cola, 30);
    aniadir_max(cola, 20);
    aniadir_max(cola, 10);
    aniadir_max(cola, 0);
    aniadir_max(cola, -10);
    aniadir_max(cola,-20);
    aniadir_max(cola,-30);
    aniadir_max(cola,-40);
    aniadir_max(cola,-50);
    aniadir_max(cola, 80);
    printBT("", cola, false);

    return (0);
}
