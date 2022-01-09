
#include <iostream>

using namespace std;

//typedef ABB<entrada> Tabla_frec;

#include "arboles_binarios_busqueda.cpp"


ABB<entrada> tabla_vacia()
{
    return (NULL);
}

template <typename T>
void show(Secuencia<T> sec) {
    nodo_sec<T>* aux = sec.primero;
    while (aux->sig != NULL) {
        if (aux == sec.anterior) {
            cout << FLECHA;
        }
        cout << "(" << aux->sig->dato.letra << "," << aux->sig->dato.frec << ")" << ";";
        aux = aux->sig;
    }
    cout << endl;
}

template <typename e>
void mostrar(const string& prefix, ABB<e> node, bool isLeft)
{
    if(!es_abb_vacio(node))
    {
        cout << prefix;
        cout << (isLeft ? "iz├──" : "dr└──" );
        cout << "(" << node->dato.letra << "," << node->dato.frec << ")" << endl;
        mostrar( prefix + (isLeft ? "│   " : "    "), node->iz, true);
        mostrar( prefix + (isLeft ? "│   " : "    "), node->dr, false);
    }
}


/*int main()
{
    string mensaje;
    Secuencia<entrada> s;

    cout << "Introduce un mensaje: " << endl;
    getline(cin,mensaje);

    ABB<entrada> a = tabla_vacia();
    for(int i=0 ; i<mensaje.length(); ++i)
    {
        aniadir(a,mensaje[i]);
    }
    mostrar("", a, false);
    s = in_orden(a);
    show(s);
    return (0);
}*/