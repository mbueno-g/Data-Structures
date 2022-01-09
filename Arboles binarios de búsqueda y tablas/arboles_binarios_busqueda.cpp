/* TAD Arboles binarios de búsqueda

parámetro ELEM=<
usa BOOLEANOS, ELEM=
operaciones
        _<_ : elemento elemento -> bool
        _>_ : elemento elemento -> bool
variables
        x,y,z : elemento
ecuaciones
        x < x          = falso                       {antirreflexidad}
        x < z          = cierto <= x < y  and  y < z {transitividad}
        x < y or y < x = cierto <= x != y            {totalidad}
fparámetro

parámetro ELEM=
usa BOOLEANOS
tipos elemento
operaciones
        _==_ : elemento elemento -> bool
        _!=_ : elemento elemento -> bool
variables
        x,y : elemento
ecuaciones
        (x==y) = cierto <= x=y
        x=y <= (x==y) = cierto
        x != y = no (x==y)
fparámetro

especificación ARBOLES-BINARIOS-DE-BÚSQUEDA[ELEM=<]
usa BOOLEANOS
tipos arbol-bb
operaciones
        abb_vacio    :                            ->  arbol-bb {constructora}
        plantar      : arbol-bb elemento arbol-bb ->p arbol-bb {constructora}
        insertar     : elemento arbol-bb          ->  arbol-bb
        esta         : elemento arbol-bb          ->  bool
        minimo       : arbol-bb                   ->p elemento
        maximo       : arbol-bb                   ->p elemento
        eliminar     : elemento arbol-bb          ->  arbol-bb
        es_abb_vacio : arbol-bb                   ->  bool
variables
        e,f : elemento
        iz,dr : arbol-bb
ecuaciones
        plantar(iz,e,dr) = error <= no (es_abb_vacio(iz) or e > maximo(iz)) or
                                    no (es_abb_vacio(dr) or e < minimo(dr))
        insertar(e, abb_vacio)        = plantar(abb_vacio, e, abb_vacio)
        insertar(e, plantar(iz,e,dr)) = plantar(iz,e,dr)
        insertar(e, plantar(iz,f,dr)) = plantar(insertar(e,iz),f,dr) <= e < f
        insertar(e, plantar(iz,f,dr)) = plantar(iz,f,insertar(e,dr)) <= e > f
        esta(e,abb_vacio)               = falso
        esta(e,plantar(iz,e,dr))        = cierto
        esta(e,plantar(iz,f,dr))        = esta(e,iz) <= e < f
        esta(e,plantar(iz,f,dr))        = esta(e,dr) <= e > f
        minimo(abb_vacio)               = error
        minimo(plantar(abb_vacio,e,dr)) = e
        minimo(plantar(iz,e,dr))        = maximo(dr) <= no es_abb_vacio(dr)
        eliminar(e,abb_vacio)           = abb_vacio
        eliminar(e,plantar(iz,e,abb_vacio)) = iz
        eliminar(e,plantar(abb_vacio,e,dr)) = dr
        eliminar(e,plantar(iz,e,dr)) = plantar(iz,minimo(dr),eliminar(minimo(dr),dr)) 
                                       <= no es_abb_vacio(iz) || no es_abb_vacio(dr)
        eliminar(e,plantar(iz,f,dr)) = plantar(eliminar(e,iz), f,dr) <= e < f
        eliminar(e,plantar(iz,f,dr)) = plantar(iz,f,eliminar(e,dr)) <= e > f
        es_abb_vacio(abb_vacio) = cierto
        es_abb_vacio(plantar(iz,e,dr)) = falso
fespecificación
*/

// Los árboles binarios de búsqueda son un caso particular de los arboles binarios.
// Los árboles binarios de búsqueda al igual que los binarios tienen dos hijos pero 
// en este caso el hijo izquierdo tienen valores menores que la clave de la raiz y el hijo
// derecho tiene valores mayores


#include <iostream>

using namespace std;

#include "secuencias.cpp"

struct entrada
{
    char letra;
    int frec;
};

bool operator <=(entrada e1, entrada e2){
     return e1.letra <= e2.letra;
}
bool operator ==(entrada e1, entrada e2){
     return e1.letra == e2.letra;
}

template <typename e>
struct nodo_abb
{
        e dato;
        nodo_abb<e> *iz = NULL;
        nodo_abb<e> *dr = NULL;
};

template <typename e>
using ABB = nodo_abb<e> *;

template <typename e>
ABB<e> abb_vacio()
{
        return (NULL);
}
// O(1) : coste constante


template <typename e>
bool es_abb_vacio(ABB<e> arb)
{
        return (arb==NULL);
}
// O(1) : coste constante


template <typename e>
ABB<e> plantar(ABB<e> iz, e elemento, ABB<e> dr)
{
        ABB<e> arb;

        arb = new nodo_abb<e>;
        arb->dato = elemento;
        arb->iz = iz;
        arb->dr = dr;
        return arb;
}
// O(1) : coste constante (no hace una copia)


/*template <typename e>
void  insertar(ABB<e> &arb, e elemento) // e, no <e>
{
        if (es_abb_vacio(arb))
        {
                arb = new nodo_abb<e>;
                arb->dato = elemento;
                //arb->iz = NULL;
                //arb->dr = NULL;
        }
        else if (arb->dato < elemento) // utilizar solo <= (no >=)
                insertar(arb->dr, elemento);
        else if(!(arb->dato == elemento)) // para no incluir los repetidos
                insertar(arb->iz, elemento);
}*/
/* O(n) con n la altura del arbol : coste proporcinal a la altura del árbol (llama recursivamente a los hijos)
 en el peor de los casos, cuando todos los nodos tienen solo un hijo no vacío, las llamadas recursivas recorren
 todo el arbol, luego el coste es lineal con respecto al número de elementos del árbol
 Para evitar este caso degenerado existen implementaciones que mantienen el arbol equilibrado.
 Así la altura de un arbol equilibrado de n nodos está en O(log n)
*/

template <typename e>
void  insertar(ABB<e> &arb, e elemento)
{
        if (es_abb_vacio(arb))
        {
                arb = new nodo_abb<entrada>;
                arb->dato = elemento;
        }
        else if (arb->dato == elemento)
                arb->dato.frec += elemento.frec;
        else if (arb->dato <= elemento) 
                insertar(arb->dr, elemento);
        else
                insertar(arb->iz, elemento);
}

void aniadir(ABB<entrada> &t, char c)
{
    entrada e;

    e.letra = c;
    e.frec = 1;
    insertar(t, e);
}



template <typename e>
bool esta(e elemento, ABB<e> arb)
{
        if (es_abb_vacio(arb))
                return(false);
        else
        {
                if (elemento == arb->dato)
                        return (true);
                else if (elemento > arb->dato)
                        esta(elemento, arb->dr);
                else
                        esta(elemento, arb->iz);
        }
}
// O(n) con n la altura del arbol

// minimo de un arbol binario de búsqueda es el elemento más a la izquierda
template <typename e>
e minimo(ABB<e> arb)
{
        //if (es_abb_vacio(arb))
        if (es_abb_vacio(arb->iz))
                return (arb->dato);
        else
                return (minimo(arb->iz));
}
// O(n) con n la altura del arbol


// mánimo de un arbol binario de búsqueda es el elemento más a la derecha
template <typename e>
e maximo(ABB<e> arb)
{
        //if (es_abb_vacio(arb))
        if (es_abb_vacio(arb->dr))
                return (arb->dato);
        else
                return (maximo(arb->dr));
}
// O(n) con n la altura del arbol


template <typename e>
void liberar(ABB<e> &arb)
{
        if (!es_abb_vacio(arb))
        {
                liberar(arb->iz);
                liberar(arb->dr);
                delete arb;
        }
}

template <typename e>
ABB<e> eliminar(e elemento, ABB<e> arb)
{
        if (!es_abb_vacio(arb))
        {
                if (arb->dato == elemento)
                {
                        if (es_abb_vacio(arb->iz))
                                arb = arb->dr;
                        else if (es_abb_vacio(arb->dr))
                                arb = arb->iz;
                        else
                        {
                                arb = plantar(arb->iz, minimo(arb->dr), eliminar(minimo(arb->dr), arb->dr)); 
                        }
                }
                else if (elemento < arb->dato)
                        arb = plantar(eliminar(elemento, arb->iz), arb->dato, arb->dr);
                else if (elemento > arb->dato)
                        arb = plantar(arb->iz, arb->dato, eliminar(elemento, arb->dr));
        }
        return (arb);
}
// O(n) con n la altura del arbol


template <typename e>
void eliminar2(e elemento, ABB<e> &arb)
{
        ABB<e> aux;

        if (!es_abb_vacio(arb))
        {
                if (arb->dato == elemento)
                {
                        if (es_abb_vacio(arb->iz))
                        {
                                aux = arb;
                                arb = arb->dr;
                                liberar(aux);
                        }
                        else if (es_abb_vacio(arb->dr))
                        {
                                aux = arb;
                                arb = arb->iz;
                                liberar(aux);
                        }
                        else if (!es_abb_vacio(arb->iz) || !es_abb_vacio(arb->dr))
                        {
                                eliminar_aux(arb, arb->dr);
                                //arb = plantar(arb->iz, minimo(arb->dr), eliminar2(minimo(arb->dr), arb->dr)); 
                        }
                }
                else if (elemento < arb->dato)
                        eliminar2(elemento, arb->iz);
                        //arb = plantar(eliminar2(elemento, arb->iz), arb->dato, arb->dr);
                else if (elemento > arb->dato)
                        eliminar2(elemento, arb->dr);
                        //arb = plantar(arb->iz, arb->dato, eliminar2(elemento, arb->dr));
        }
}

template <typename e>
void eliminar_aux(ABB<e> &a, ABB<e> &b)
{
        ABB<e> aux;

        if (!es_abb_vacio(b->iz))
                eliminar_aux(a,b->iz);
        else
        {
                /*cout << "a "<< endl;
                printBT("", a, false);
                cout << "b" << endl;
                printBT("", b, false);*/
                a->dato = b->dato;
                aux = b;
                b = b->dr;
                //liberar(aux);
        }
}

template <typename T>
void in_orden_aux(const ABB<T> & a,Secuencia<T> & s){
     if(!es_abb_vacio(a)){
          in_orden_aux(a->iz, s);
          insertar(a->dato,s);
          in_orden_aux( a->dr, s);
     }
}

template <typename T>
Secuencia<T> in_orden(const ABB<T> & a){
     Secuencia<T> result = crear<T>();
     in_orden_aux(a,result);
     return result;
}


template <typename e>
void printBT(const string& prefix, ABB<e> node, bool isLeft)
{
    if(!es_abb_vacio(node))
    {
        cout << prefix;
        cout << (isLeft ? "iz├──" : "dr└──" );
        cout << node->dato << endl;
        printBT( prefix + (isLeft ? "│   " : "    "), node->iz, true);
        printBT( prefix + (isLeft ? "│   " : "    "), node->dr, false);
    }
}


/*int main()
{
    ABB<int> a;

    
    a = abb_vacio<int>(); //llamar indicando el tipo
    insertar(a, 5);
    insertar(a,3);
    insertar(a, 1);
    insertar(a,2);
    insertar(a,6);
    insertar(a,7);
    insertar(a,1);

    printBT("", a, false);

    cout << "Eliminamos la raiz" << endl;
    eliminar2(5,a);
    printBT("", a, false);
    liberar(a);
    return (0);
}*/

