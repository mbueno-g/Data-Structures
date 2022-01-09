// SECUENCIA = estructura lineal con un punto de interés donde se realizan las modificaciones
// y las consultas. 
// La especificación está realizada a partir de un par de pilas que contienen la parte de
// la secuencia a la izquierda del punto de interés y el punto de interés y la parte de la secuencia
// a la derecha de este.

/* TAD SECUENCIAS

especificación SECUENCIAS[ELEM]
usa PILAS[ELEM], BOOLEANOS
tipos secuencia
operaciones
        crear              :                    ->  secuencia
        insertar           : secuencia elemento ->  secuencia
        eliminar           : secuancia          ->p secuencia
        actual             : secuencia          ->p elemento
        avanzar            : secuencia          ->p secuencia
        reiniciar          : secuencia          ->  secuencia
        fin                : secuencia          ->  bool
        es_secuencia_vacia : secuencia          ->  bool
operaciones privadas:
        <_,_> : pila pila -> secuencia {constructora}
variables
        e : elemento 
        s : secuencia
        iz,dr : pila
ecuaciones
        crear = <pila_vacia, pila_vacia>
        insertar(<iz,dr>, e) = <apilar(e,iz), dr>
        eliminar(<iz,pila_vacia>) = error
        eliminar(<iz,apilar(e,dr)>) = <iz,dr>
        actual(<iz,pila_vacia>) = error
        actual(<iz,aplilar(e,dr)>) = e
        avanzar(<iz,pila_vacia>) = error
        avanzar(<iz,apilar(e,dr)>) = <apilar(e,iz), dr>
        reiniciar(<pila_vacia,dr>) = <pila_vacia,dr>
        reiniciar(<apilar(e,iz), dr>) = reiniciar(<iz,apilar(e,dr)>)
        fin(<iz,dr>) = es_pila_vacia(dr)
        es_secuencia_vacia(<iz,dr>) = es_pila_vacia(iz) && es_pila_vacia(dr)
fespecificación
*/

//#include "pilas_template.cpp"

const string FLECHA = "↓";

template <typename T>
struct nodo_sec
{
    T dato;
    nodo_sec<T> * sig = NULL;
};

template <typename T>
struct Secuencia
{
    nodo_sec<T> * primero; // primer nodo de la secuencia = nodo fantasma
    nodo_sec<T> * anterior; // elemento anterior al actual = anterior al punto de interés
};

// Necesitamos acceder en tiempo constante al primer elemento de la secuencia (para reiniciar)
// y al punto de interés. Para no tener que diferenciar el caso en el que el punto de interés es el primer elemento
// de la secuencia creamos un nodo fantasma, asi todo nodo tiene un anterior.
template <typename T>
Secuencia<T> crear()
{
    Secuencia<T> s;

    s.primero = new nodo_sec<T>;
    s.anterior = s.primero;
    return s;
}

template <typename T>
bool es_sec_vacia(Secuencia<T> s)
{
    return (s.primero->sig == NULL);
}

template <typename T>
bool fin(Secuencia<T> s)
{
    return (s.anterior->sig == NULL);
}


// El elemento insertado pasa a ser el anterior al punto de interés
template <typename T>
void insertar( T elemento, Secuencia<T> &s)
{
    nodo_sec<T> * new_nodo = new nodo_sec<T>;

    new_nodo->dato = elemento;
    new_nodo->sig = s.anterior->sig;
    s.anterior->sig = new_nodo;
    s.anterior = new_nodo;
}


// se eliminar el nodo situado detrás del apuntado por anterior(anterior.sig)
template <typename T>
void eliminar(Secuencia<T> &s)
{
    if (s.anterior->sig == NULL)
        throw runtime_error("final de la secuencia");
    else
    {
        nodo_sec<T> *aux = s.anterior->sig;
        s.anterior->sig = aux->sig;
        delete aux;
    }
}

template <typename T>
T actual(Secuencia<T> s)
{
    if (s.anterior->sig == NULL)
        throw runtime_error("final de la secuencia");
    else
    {
        return (s.anterior->sig->dato);
    }
}


template <typename T>
void avanzar(Secuencia<T> &s)
{
    if (s.anterior->sig == NULL)
        throw runtime_error("Final de la secuencia");
    else
        s.anterior = s.anterior->sig;
}


template <typename T>
void avanzar2(Secuencia<T> &s)
{
    T dato;
    if (s.anterior->sig == NULL)
        throw runtime_error("Final de la secuencia");
    else
    {
        dato = actual(s);
        eliminar(s);
        insertar(dato, s);
    }
}

template<typename T>
void reiniciar(Secuencia<T>& s){
    s.anterior = s.primero;
}

template <typename T>
void liberar(Secuencia<T> &s)
{
    reiniciar(s);
    while(!fin(s))
        eliminar(s);
    delete s.primero;
}

//tambien podemos redefinir el operador << para mostrar una secuencia
template<typename T>
ostream & operator <<(ostream & o, Secuencia<T> s){
  nodo_sec<T> * aux = s.primero;
  while(aux->sig != NULL){
    if(aux == s.anterior){
      o << FLECHA;
    }
    o << aux->sig->dato;
    o <<  " ";
    aux = aux->sig;
  }
  o << endl;
  return o;
}

template <typename T>
void mostrar(Secuencia<T> sec) {
    nodo_sec<T>* aux = sec.primero;
    while (aux->sig != NULL) {
        if (aux == sec.anterior) {
            cout << FLECHA;
        }
        cout << aux->sig->dato << " ";
        aux = aux->sig;
    }
    cout << endl;
}


