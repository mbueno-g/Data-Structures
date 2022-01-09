
/* TAD ARBOLES BINARIOS DE BÚSQUEDA CON PARES

CLAVES = ELEM=


En los arboles de busqueda, cuando se inserta un elemento que ya está en el
árbol, este no se modifica. En esta version, podemos insertar un valor 
asociado a una clave que ya está en el arbol, posiblemente asociada a otro valor.

parámetro VALORES-MODIFICABLES
tipo valor
operaciones
        combinar : valor valor -> valor
fparámetro

espeficación ARBOLES-DE-BUSQUEDA-CON-PARES[CLAVES<,VALORES-MODIFICABLES]
usa BOOLEANOS
tipos arbol-bb
operaciones
        abb_vacio    :                               ->  arbol_bb {constructora}
        plantar      : arbol_bb clave valor arbol_bb ->p arbol_bb {constructora}
        insertar     : clave valor arbol_bb          ->  arbol_bb
        consultar    : clave arbol_bb                ->p valor
        esta         : clave arbol_bb                ->  bool
        minimo       : arbol_bb                      ->p clave
        maximo       : arbol_bb                      ->p clave
        eliminar     : clave arbol_bb                ->  arbol_bb
        es_abb_vacio : arbol_bb                      ->  bool
variables
        c,d : clave
        v,w : valor
        iz,dr : arbol_bb
ecuaciones
        plantar(iz,c,v,dr) = error <= !es_abb_vacio(iz) || c > maximo(iz) 
                                       || !es_abb_vacio(dr) || c <minimo(dr)
        insertar(c,v,abb_vacio) = plantar(abb_vacio,c,v,abb_vacio)
        insertar(c,v,plantar(iz,c,w,dr)) = plantar(iz,c,combinar(w,v),dr)
        insertar(c,v,plantar(iz,d,w,dr)) = plantar(insertar(c,v,iz),d,w,dr) <= c < d
        insertar(c,v,plantar(iz,d,w,dr)) = plantar(iz,d,w,insertar(c,v,dr)) <= c > d
        consultar(c,abb_vacio) = error
        consultar(c,plantar(iz,c,v,dr)) = v
        consultar(c,plantar(iz,d,w,dr)) = consultar(c,iz) <= c<d
        consultar(c,plantar(iz,d,w,dr)) = consultar(c,dr) <= c>d
        esta(c,abb_vacio) = falso
        esta(c,plantar(iz,c,v,dr)) = cierto
        esta(c,plantar(iz,d,w,dr)) = esta(c,iz) <= c<d
        esta(c,plantar(iz,d,w,dr)) = esta(c,dr) <= c>d
        minimo(abb_vacio) = error
        minimo(plantar(abb_vacio,c,v,dr)) = c
        minimo(plantar(iz,c,v,dr)) = minimo(iz) <= !es_abb_vacio(iz)
        maximo(abb_vacio) = error
        maximo(plantar(iz,c,v, abb_vacio)) = c
        maximo(plantar(iz,c,v,dr)) = maximo(dr) <= !es_abb_vacio(dr)
        eliminar(c,abb_vacio) = abb_vacio
        eliminar(c,plantar(iz,c,v,abb_vacio)) = iz
        eliminar(c,plantar(abb_vacio,c,v,dr)) = dr
        eliminar(c,plantar(iz,c,v,dr)) = plantar(iz,minimo(dr),consultar(minimo(dr)), eliminar(minimo(dr), dr))
                                                <= !es_abb_vacio(iz) && !es_abb_vacio(dr)
        eliminar(c,plantar(iz,d,w,dr)) = plantar(eliminar(c,iz),d,w,dr) <= c<d
        eliminar(c,plantar(iz,d,w,dr)) = plantar(iz,d,w,eliminar(c,dr)) <= c>d
        es_abb_vacio(abb_vacio) = cierto
        es_abb_vacio(plantar(iz,c,v,dr)) = falso
fespecificación
*/

#include <iostream>


template <typename c,v>
struct nodo_abb
{
        c clave;
        v valor;
        nodo_abb<c,v> *iz = NULL;
        nodo_abb<c,v> *dr = NULL;
};

/*
Se puede definir este TAD como:
template <typename entrada>
struct nodo_abb
{
        entrada datos;
        nodo_abb<entrada> *iz = NULL;
        nodo_abb<entrada> *dr = NULL;
};
donde
struct entrada
{
        char clave;
        int valor;
};
Y se defininen las operacionesÇ:
bool operator <=(entrada e1, entrada e2){
     return e1.letra <= e2.letra;
}
bool operator ==(entrada e1, entrada e2){
     return e1.letra == e2.letra;
}
*/

template <typename c, typename v>
using ABB = nodo_abb<c,v> *;

template <typename c, typename v>
ABB<c,v> abb_vacio()
{
        return (NULL);
}
// O(1) : coste constante


template <typename c, typename v>
bool es_abb_vacio(ABB<c,v> arb)
{
        return (arb==NULL);
}
// O(1) : coste constante

template <typename c, typename v>
bool esta(c clave, ABB<c,v> arb)
{
        if (es_abb_vacio(arb))
                return(false);
        else
        {
                if (clave == arb->clave)
                        return (true);
                else if (clave > arb->dato)
                        esta(clave, arb->dr);
                else
                        esta(clave, arb->iz);
        }
}
// O(n) con n la altura del arbol


// minimo de un arbol binario de búsqueda es el elemento más a la izquierda
template <typename c, typename v>
c minimo(ABB<c,v> arb)
{
        //if (es_abb_vacio(arb))
        if (es_abb_vacio(arb->iz))
                return (arb->clave);
        else
                return (minimo(arb->iz));
}
// O(n) con n la altura del arbol


// mánimo de un arbol binario de búsqueda es el elemento más a la derecha
template <typename c, typename v>
c maximo(ABB<e> arb)
{
        //if (es_abb_vacio(arb))
        if (es_abb_vacio(arb->dr))
                return (arb->clave);
        else
                return (maximo(arb->dr));
}
// O(n) con n la altura del arbol


template <typename c, typename v>
void insertar(c clave, v valor, ABB<c,v> &arb)
{
        if (es_abb_vacio(arb))
        {
                arb = new nodo_abb<c,v>;
                arb->clave = clave;
                arb->valor = valor; 
        }        
        else
        {
                if (clave == arb->clave)
                        combinar(arb->valor, valor);
                else if (clave < arb->clave)
                        insertar(clave, valor, arb->iz);
                else
                        insertar(clave, valor, arb->dr);
        }
}

template <typename c, typename v>
void combinar(v valor, v nuevo_valor)
{

}


template <typename c, typename v>
v consultar(c clave, ABB<c,v> arb)
{
        if (es_abb_vacio(arb))
                throw runtime_error("Clave no definida");
        else
        {
                if (clave == arb->clave)
                        return (arb->valor);
                else if (clave > arb->dato)
                        consultar(clave, arb->dr);
                else
                        consultar(clave, arb->iz);
        }
}
// O(n) con n la altura del arbol


// FALTA AÑADIR ELIMINAR