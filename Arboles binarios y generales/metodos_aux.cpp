
#include "arboles_binarios.cpp"

template <typename e>
Abb<e> copiar_arbol(Abb<e> arb)
{
        Abb<e> b;

        b = NULL; // SUPER IMPORTANTE
        if (es_arbol_vacio(arb))
                return (NULL);
        else
        {
                plantar(b,arb->dato);
                b->iz = copiar_arbol(arb->iz);
                b->dr = copiar_arbol(arb->dr);
        }
        return (b);
}

// Equilibrado = si la diferencia entre las alturas de sus hijos es como mucho 1 y 
// ambos hijos tambien están equilibrados
template <typename e>
bool esta_equilibrado(Abb<e> arb)
{
    if (es_arbol_vacio(arb))
        return (true);
    return (abs(altura(arb->iz)-altura(arb->dr)) <= 1 && esta_equilibrado(arb->dr) && esta_equilibrado(arb->iz));
}

template <typename e>
bool es_zurdo(Abb<e> arb)
{
    int nodos_iz;
    int nodos_dr;

    if (es_arbol_vacio(arb) || (es_arbol_vacio(arb->iz) && es_arbol_vacio(arb->dr)))
        return (true);
    nodos_iz = num_nodos(arb->iz);
    nodos_dr = num_nodos(arb->dr);
    return (nodos_iz > nodos_dr && es_zurdo(arb->iz) && es_zurdo(arb->dr));
}

//distancia = longitud del único camino que conecta dos nodos
//diámetro = distancia máxima sobre todos los pares de nodos
template <typename e>
int diametro(Abb<e> arb)
{
    if (es_arbol_vacio(arb))
        return (0);
    return (1 + max(diametro(arb->iz), diametro(arb->dr)));
}// coste O(n) siendo n el número de nodos del arbol



int     main()
{
        Abb<int> a;
        Abb<int> iz;
        Abb<int> copia;
        
        a = arbol_vacio<int>(); //llamar indicando el tipo
        plantar(a, 5);
        plantar(a,3);
        plantar(a, 1);
        plantar(a,2);
        plantar(a,6);
        plantar(a,7);
        plantar(a,1);
        cout << raiz(*a) << endl; // mandar el contenido del puntero
        iz = hijo_iz(*a);
        printBT("", iz,false);
        printBT("",a,false);
        cout << a << endl; // operador << definido

        cout << "Altura " << altura(a) << endl;
        cout << "Num nodos " << num_nodos(a) << endl;
        cout << "Num hojas " << num_hojas(a) << endl;
        cout << "Diámetro " << diametro(a) << endl;

        copia = copiar_arbol(a);
        printBT("",copia,false);

        cout << "Equilibrado " << esta_equilibrado(a) <<endl; // no
        plantar(a,4);
        cout << "Equilibrado " << esta_equilibrado(a) <<endl;

        especular(a);
        printBT("",a,false);
        liberar(a);        
        return (0);
}

//            4
//           /  \
//          3    5
//         /       \
//        1         6
//         \
//          2
