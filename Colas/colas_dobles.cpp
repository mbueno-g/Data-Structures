/* COLAS DOBLEMENTE ENLAZADAS

especificación DOBLECOLAS[ELEM]
usa BOOLEANOS
tipos doble-cola
operaciones
        cola_vacia    :                     ->  doble-cola {constructora}
        poner_detras  : doble-cola elemento ->  doble-cola {constructora}
        poner_delante : elemento doble-cola ->  doble-cola
        quitar_ult    : doble-cola          ->p doble-cola
        ultimo        : doble-cola          ->p elemento
        quitar_prim   : doble-cola          ->p doble-cola
        primero       : doble-cola          ->p elemento
        es_cola_vacia : doble-cola          ->  bool
variable
        e,f : elemento
        c : doble-cola
ecuaciones
        poner-delante(e,cola_vacia) = poner_detras(cola_vacia, e)
        poner_delante(e,poner_detras(c,f)) = poner_detras(poner_detras(e,c),f)
        quitar_ult(cola_vacia) = error
        quitar_ult(poner_detras(c,e)) = c
        ultimo(cola_vacia) = error
        ultimo(poner_detras(c,e)) = e
        quitar_prim(cola_vacia) = error
        quitar_prim(poner_detras(c,e)) = cola_vacia <= es_cola_vacia(c)
        quitar_prim(poner_detras(c,e)) = poner_detras(quitar_prim(c),e) <= !es_cola_vacia(c)
        primero(cola_vacia) = error
        primero(poner_detras(c,e)) = e <= es_cola_vacia(c)
        primero(poner_detras(c,e)) = primero(c) <= !es_cola_vacia(c)
        es_cola_vacia(cola_vacia) = cierto
        es_cola_vacia(poner_detras(c,e)) = falso
fespecificación
*/

template <typename T>
struct nodo
{
    T dato;
    nodo<T> *sig = NULL;
    nodo<T> *ant = NULL;
};

template <typename T>
struct cola
{
    nodo<T> *primero;
    nodo<T> *ultimo;
};

template <typename T>
cola<T> cola_vacia()
{
    cola<T> new_nodo;
    new_nodo.primero = NULL;
    new_nodo.ultimo = NULL;
    return (new_nodo);
}

template <typename T>
bool es_cola_vacia(cola<T> c)
{
    return (c.primero==NULL && c.ultimo == NULL);
}

template <typename T>
void poner_detras(cola<T> &c, T elemento)
{
    nodo<T> new_nodo = new nodo<T>;
    new_nodo.dato = elemento;
    new_nodo.sig = NULL;
    if (c.primero == NULL)
    {
        c.primero = new_nodo;
        new_nodo.ant = NULL;
    }
    else
    {
        c.ultimo->sig = new_nodo;
        new_nodo.ant = c.ultimo;
    }
    c.ultimo = new_nodo;
}

template <typename T>
void poner_delante(cola<T> &c, T elemento)
{
    nodo<T> new_nodo = new nodo<T>;
    new_nodo.dato = elemento;
    new_nodo.ant = NULL;
    if (c.primero == NULL)
    {
        new_nodo.sig = NULL,
        c.primero = new_nodo;
    }
    else
    {
        new_nodo.sig = c.primero;
        c.primero->ant = new_nodo;
        new_nodo.sig = new_nodo;
    }
    c.primero = new_nodo;
}

template <typename T>
void quitar_ult(cola<T> &c)
{
    if (es_cola_vacia(c))
        throw runtime_error("La cola está vacía");
    else
    {
        nodo<T> *aux = c.ultimo;
        c.ultimo = aux->ant;
        if (c.ultimo == NULL) // cola vacía
            c.primero = NULL;
        else
            c.ultimo->sig = NULL;
        delete aux;
    }
}

template <typename T>
T ultimo(cola<T> c)
{
    if (es_cola_vacia(c))
        throw runtime_error("Cola vacía");
    else
        return (c.ultimo->dato);
}

template <typename T>
void quitar_prim(cola<T> & c)
{
    if (es_cola_vacia(c))
        throw runtime_error("Cola vacía");
    else
    {
        nodo<T> *aux = c.primero;
        c.primero = aux->sig;
        if (c.primero == NULL)
            c.ultimo = NULL;
        else
            c.primero->ant = NULL;
        delete aux;
    }
}

template <typename T>
T primero(cola<T> c)
{
    if (es_cola_vacia(c))
        throw runtime_error("Cola vacía");
    else
        return(c.primero->dato);
}


template <typename T>
cola<T> copiar(cola<T> c)
{
    nodo<T> *s;
    nodo<T> *r;
    nodo<T> *t;
    cola<T> d;
    if (c.primero == NULL)
    {
        d.primero = NULL;
        d.ultimo = NULL;
    }
    else
    {
        r = c.primero;
        t = new nodo<T>;
        t->dato = r->dato;
        t->ant = NULL;
        s = t;
        while (r->sig != NULL)
        {
            r = r->sig;
            t = new nodo<T>;
            t->dato = r->dato;
            t->ant = s;
            s->sig = t;
            s = t;
        }
        s->sig = NULL;
        d.ultimo = s;
    }
    return (d);
}


template <typename T>
void liberar(cola<T> &c)
{
    nodo<T> *aux = c.primero;

    while(aux != NULL)
    {
        nodo<T> * n = aux;
        aux = aux->sig;
        liberar(n);
    }
}
