
/* TAD ARBOLES GENERALES

bosque = lista de arboles

especificacion ARBOLES-GENERALES[ELEM]
usa BOOLEANOS, NATURALES
tipos arbol, bosque
operaciones
        plantar      : elemento bosque ->  arbol  {constructora}
        bosque_vacio :                 ->  bosque {constructora}
        añadir_arbol : arbol bosque    ->  bosque {constructora}
        raiz         : arbol           ->  elemento
        hijos        : arbol           ->  bosque
        num_hijos    : arbol           ->  nat
        longitud     : bosque          ->  nat
        subarbol     : arbol nat       ->p arbol
        _[]          : bosque nat      ->p arbol
        es_hoja      : arbol           ->  bool

        altura       : arbol           ->  nat
        num_nodos    : arbol           ->  nat  
        num_hojas    : arbol           ->  nat 
        grado        : arbol           ->  nat 
operaciones privadas
        altura_bosque: bosque          -> nat
        num_nodos_bosque: bosque          -> nat
        num_hojas_bosque: bosque          -> nat
        grado_bosque  : bosque          -> nat
variables
        e : elemento
        a : arbol
        b : bosque
        i : nat
ecuaciones
        raiz(planta(e,b)) = e
        hijos(plantar(e,b)) = b
        num_hijos(plantar(e,b)) = longitud(b)
        longitud(bosque_vacio) = 0     (un bosque vacio tiene una hoja)
        longitud(añadir_arbol(a,b)) = 1 + longitud(b)
        subarbol(plantar(e,b),i) = b[i]  (un subarbol es un hijo i-esimo)
        b[i] = error <= i == 0 || i > longitud(b)
        añadir_arbol(a,b)[1] = a
        añadir_arbol(a,b)[i] = b[i-1] <= 1<i && i <= longitud(b)+1
        es_hoja(a) = (num_hijos(a)==0)

        altura(plantar(e,b)) = 1 + altura_bosque(b)
        altura_bosque(bosque_vacio) = 0
        altura_bosque(añadir_bosque(a,b)) = max(altura(a), altura_bosque(b))
        num_nodos(plantar(e,b)) = 1 + num_nodos_bosque(b)
        num_nodos_bosque(bosque_vacio) = 0
        num_nodos_bosque(añadir_arbol(a,b)) = num_nodos(a) + num_nodos_bosque(b)
        num_hojas(plantar(e,bosque_vacio)) = 1
        num_hojas(plantar(e,añadir_arbol(a,b))) = num_hojas_bosque(añadir_arbol(a,b))
        num_hojas_bosque(bosque_vacio) = 0
        num_hojas_bosque(añadir_arbol(a,b)) = num_hijas(a) + num_hojas_bosque(b)
        grado(plantar(e,b)) = max(longitud(b), grado_bosque(b))
        grado_bosque(bosque_vacio) = 0
        grado_bosque(añadir_arbol(a,b)) = max(grado(a), grado_bosque(b))
fespecificacion
*/

//Primogénito = primero hijos
//Sig_her = resto de hijos

template <typename T>
struct nodo
{
    T dato;
    nodo<T> * primog;
    nodo<T> * sig_her;
};

template <typename T>
using arbol = nodo<T> *;

template <typename T>
using bosque = nodo<T> *;


// crear el primogénito
template <typename T>
arbol<T> plantar(T elemento, bosque<T> &b)
{
    arbol<T> *a = new arbol<T>;
    a->dato = elemento;
    a->primog = b;
    a->sig_herm = NULL;
    return (a);
}
// O(1)

template <typename T>
bosque<T> bosque_vacio()
{
    return(NULL);
}

//añadir otro hijo, despues de haberlo creado con plantar
template <typename T>
void aniadir_arbol(arbol<T> &a, bosque<T> &b)
{
    a->sig_her = b;
    b = a;
}

template <typename T>
T raiz(arbol<T> a)
{
    return(a->dato);
}

template <typename T>
bosque<T> hijos(arbol<T> a)
{
    return(a->primog);
}

template <typename T>
int longitud(bosque<T> b)
{
    arbol<T> c;
    c = b;
    n = 0;
    while (c!= NULL)
    {
        n++;
        c = c->sig_her;
    }
    return (n);
}
// O(n) :  lineal con respecto al numero de arboles en el bosque

template <typename T>
int num_hijos(arbol<T> a)
{
    return (longitud(a->primog));
}

template <typename T>
arbol<T> consultar(bosque<T> b, int i)
{
    if (i==0)
        throw runtime_error("Indice no valido");
    else
    {
        arbol<T> h = b;
        j = 1;
        while (h!= NULL && j!=i)
        {
            j++;
            h=h->sig_her;
        }
        if (h==NULL)
            throw runtime_error("Indice no valido")
        else
            return h;
    }
}
// O(i)


template <typename T>
arbol<T> subarbol(arbol<T> a, int i)
{
    return(consultar(a->primog, i));
}
// O(i) : lineal con respecto al valor del segundo argumento


template <typename T>
bool es_hoja(arbol<T> a)
{
    return (a->primog == NULL);
}


template <typename T>
void preorden(arbol<T> a)
{
    bosque<T> b;
    cout << a->dato << " "; // raiz
    b = hijos(a);
    int n = longitud(b);
    for(int i=0; i<n;i++)
    {
        preorden(consultar(b,i));
    }
}

template <typename T>
void preorden(arbol<T> a)
{
    bosque<T> b;
    b = hijos(a);
    int n = longitud(b);
    for(int i=0; i<n;i++)
    {
        preorden(consultar(b,i));
    }
    cout << a->dato << " "; // raiz
}

//FRONTERA: valores de las hojas del arbol tomados de izquierda a derecha

template <typename T>
void frontera(arbol<T> a)
{
    bosque<T> b;
    if (es_hoja(a))
        cout << a->dato << " " ;
    else
        b = hijos(a);
        int n = longitud(b);
        for (int i=0; i<n; i++)
        {
            frontera(consultar(b,i));
        }
}
