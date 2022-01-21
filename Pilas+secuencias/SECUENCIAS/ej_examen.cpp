
#include <iostream>

using namespace std;

const string FLECHA = "↓";

template <typename T>
struct nodo
{
    T dato;
    nodo<T> *sig=NULL;
};

template <typename T>
struct secuencia
{
    nodo<T> *primero;
    nodo<T> *anterior;
};

template <typename T>
secuencia<T> crear()
{
    secuencia<T> sec;

    sec.primero = new nodo<T>;
    sec.anterior = sec.primero;
    return sec;
}

template <typename T>
bool es_sec_vacia(secuencia<T> s)
{
    return(s.primero->sig = NULL);
}

template <typename T>
bool fin(secuencia<T> s)
{
    return(s.anterior->sig == NULL);
}

template <typename T>
void aniadir(secuencia<T> &s, T elemento)
{
    nodo<T> * new_nodo = new nodo<T>;

    new_nodo->dato = elemento;
    new_nodo->sig = s.anterior->sig; 
    s.anterior->sig = new_nodo; // para conectar el anterior anterior con el nuevo
    s.anterior = new_nodo; 
}

template <typename T>
void eliminar(secuencia<T> &s) //eliminar punto de interes
{
    if (fin(s))
        throw runtime_error("FIN DE LA SECUENCIA");
    else
    {
        nodo<T> *aux = s.anterior->sig;
        s.anterior->sig = aux->sig;
        delete aux;
    }
}

template <typename T>
T actual(secuencia<T> s)
{
   if (s.anterior->sig == NULL)
        throw runtime_error("final de la secuencia");
    else
    {
        return (s.anterior->sig->dato);
    }
}

template <typename T>
void avanzar(secuencia<T> &s)
{
    if (fin(s))
        throw runtime_error("FINAL DE LA SECUENCIA");
    else
        s.anterior = s.anterior->sig;
}

template <typename T>
void reiniciar(secuencia<T> &s)
{
    s.anterior = s.primero;
}

template <typename T>
void mostrar(secuencia<T> sec) {
    nodo<T>* aux = sec.primero;
    while (aux->sig != NULL) {
        if (aux == sec.anterior) {
            cout << FLECHA;
        }
        cout << aux->sig->dato << " ";
        aux = aux->sig;
    }
    cout << endl;
}

template <typename T>
bool sec_ordenada(secuencia<T> s)
{
    reiniciar(s);
    while(1)
    {
        if (!fin(s))
            return (true);
        T act = actual(s);
        avanzar(s);
        T act2 = actual(s);
        if (act2 < act)
            return (false);
    }
    return (true);
}

template <typename T>
void fusionar(secuencia<T> &s1, secuencia<T> &s2)
{
    reiniciar(s1);
    reiniciar(s2);
    while(!fin(s1))
    {
        if (!(actual(s1) < actual(s2)))
        {
            nodo<T> *aux = s2.anterior->sig;
            T dato_s2 = aux->dato;
            s2.anterior = aux->sig;
            aux->sig = s1.anterior->sig;
            s1.anterior->sig = aux;
        }
        else
            avanzar(s1);
    }
    if (!fin(s2))
        s1.anterior->sig = s2.anterior->sig;
}
//  O(n): tiempo lineal en la suma de las longitures de las dos secuencias


int main()
{
    secuencia<int> s1 = crear<int>();

    aniadir(s1, 1);
    aniadir(s1,3);
    aniadir(s1,4);
    aniadir(s1,6);

    secuencia<int> s2 = crear<int>();

    aniadir(s2, 2);
    aniadir(s2,5);
    aniadir(s2,7);
    fusionar(s1,s2);
    reiniciar(s1);
    while(!fin(s1))
    {
        cout << s1.anterior->sig->dato << " ";
        avanzar(s1);
    }
    cout << endl;
}