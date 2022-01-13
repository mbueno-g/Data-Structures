

// MONTÍCULO DE MÁXIMOS

#include <iostream>

using namespace std;

const int N = 100;

template <typename T>
struct nodo
{
    T dato[N];
    int ultimo = -1;
};

// raiz . posicion 0
// hijo_iz . posicion 2i+1
// hijo_dr . posicion 2i+2
// padre . i//2

/* Como un montículo es un arbol binario semicompleto no vamos a encontrar
huecos en el vector*/


template <typename T>
using cp = nodo<T> ;

template <typename T>
void cp_vacia(cp<T> &cola)
{
    cola.ultimo = -1;
}

template <typename T>
bool es_cp_vacia(cp<T> cola)
{
    return (cola.ultimo == -1);
}
// O(1)


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
void aniadir(cp<T> &cola, T elemento)
{
    if (cola.ultimo == N-1)
        throw runtime_error("Espacio insuficience");
    else
    {
        cola.ultimo++;
        cola.dato[cola.ultimo] = elemento;
        flotar(cola, cola.ultimo);
    }
}
// O(log cola.ultimo):ya que la altura de un arbol semicompleto es log(n) siendo n el número de nodos

template <typename T>
void hundir(cp<T> &cola)
{
    int i = 0;
    int m;
    T aux;
    bool fin = false;

    while ((2*i)+1 < cola.ultimo && !fin)
    {
        if ((2*i)+2 < cola.ultimo && cola.dato[(2*i)+2] > cola.dato[(2*i)+1])
            m = (2*i)+2;
        else
            m = (2*i)+1;
        if (cola.dato[m] > cola.dato[i])
        {
            aux = cola.dato[i];
            cola.dato[i] = cola.dato[m];
            cola.dato[m] = aux;
            i = m;
        }
        else
            fin = true;
    }
}

template <typename T>
void eliminar_max(cp<T> & cola)
{
    if (es_cp_vacia(cola))
        throw runtime_error("Montículo vacío");
    else
    {
        cola.dato[0] = cola.dato[cola.ultimo];
        cola.ultimo--;
        hundir(cola);
    }
}
// O(log cola.ultimo) : el coste es proporcional a la altura del montículo
// porque en cada iteración del bucle se baja un nivel en el arbol.
// Y sabaemos que la altura es logaritmica con respector al número de elementos en el montículo



int main()
{
    cp<int> cola;

    cp_vacia<int>(cola);
    aniadir(cola, 70);
    aniadir(cola, 50);
    aniadir(cola, 60);
    aniadir(cola, 80);
    aniadir(cola, 100);
    /*aniadir(cola, 40);
    aniadir(cola, 30);
    eliminar_max(cola);*/
    
    cout << cola.ultimo << endl;

    int i = 0;
    while(i <= cola.ultimo)
    {
        cout << cola.dato[i] << " ";
        i++;
    }
    cout << endl;
}

