
#include "secuencias.cpp"

template <typename T>
void ordenar_burbuja(Secuencia<T> s)
{
    if (es_sec_vacia(s))
        throw runtime_error("Secuencia vacía");
    else
    {
        bool changed = true;
        T anterior;
        while(changed)
        {
            changed = false;
            reiniciar(s);
            anterior = actual(s);
            eliminar(s);
            while(!fin(s))
            {
                if (anterior <= actual(s))
                {
                    insertar(anterior, s);
                    anterior = actual(s);
                    eliminar(s);
                }
                else
                {
                    avanzar(s);
                    changed = true;
                }
            }
            insertar(anterior, s);
        }
        cout << changed << endl;
        mostrar(s);
    }
}


// no podemos mandar la secuencia por referencia porque sino se actualiza constantemente
// y no podemos hacer uso de la recursión
template <typename T>
Secuencia<T> quicksort(Secuencia<T> s)
{
    if (es_sec_vacia(s))
        return crear<T>();
    else
    {
        reiniciar(s);
        T pivote = actual(s);
        Secuencia<T> mayores = crear<T>();
        Secuencia<T> menores = crear<T>();
        Secuencia<T> iguales = crear<T>();
        Secuencia<T> resultado = crear<T>();
        while(!fin(s))
        {
            if(!(actual(s) <= pivote)) // solo utilizamos <=
                insertar(actual(s), mayores);
            else if (!(pivote <= actual(s)))
                insertar(actual(s), menores);
            else
                insertar(actual(s), iguales);
            avanzar(s);
        }
        Secuencia<T> mayores_ord = quicksort(mayores);
        Secuencia<T> menores_ord = quicksort(menores);
        while(!fin(menores_ord))
        {
            insertar(actual(menores_ord), resultado);
            avanzar(menores_ord);
        }
        reiniciar(iguales);
        while(!fin(iguales))
        {
            insertar(actual(iguales), resultado);
            avanzar(iguales);
        }
        while(!fin(mayores_ord))
        {
            insertar(actual(mayores_ord), resultado);
            avanzar(mayores_ord);
        }
        reiniciar(resultado);
        liberar(menores);
        liberar(mayores);
        liberar(iguales);
        liberar(menores_ord);
        liberar(mayores_ord);
        return (resultado);
    }
}


template <typename T>
void pivotar(Secuencia<T> s, Nodo_sec<T>* inic, Nodo_sec<T> *fin, T pivote, Nodo_sec<T> * & ult_menor, Nodo_sec<T> * & ult_igual ){
    ult_igual = inic;
    ult_menor = inic;
    Nodo_sec<T> * ult_mayor = inic;
    Nodo_sec<T> * aux;
    while(ult_mayor->sig != fin){
        if(!(pivote<=ult_mayor->sig->dato)){
            if(ult_mayor == ult_menor){//no hay mayores ni iguales
              ult_menor = ult_menor->sig;
              ult_igual = ult_menor->sig;
              ult_mayor = ult_menor->sig;
            }
            else{
              aux = ult_mayor->sig;
              ult_mayor->sig = aux->sig;
              aux->sig = ult_menor->sig;
              if(ult_igual == ult_menor){//no hay iguales
                ult_menor->sig = aux;
                ult_menor = aux;
                ult_igual = aux;
              }
              else{
                ult_menor->sig = aux;
                ult_menor = aux;
              }
          }
        }
        else if(!(ult_mayor->sig->dato<=pivote)){
            ult_mayor = ult_mayor->sig;
        }
        else{
          if(ult_mayor == ult_igual){//no hay mayores
            ult_mayor = ult_mayor->sig;
            ult_igual = ult_igual->sig;
          }
          else{
          aux = ult_mayor->sig;
          ult_mayor->sig = aux->sig;
          aux->sig = ult_igual->sig;
          ult_igual->sig = aux;
          ult_igual = aux;
          }
        }
    }
}


template <typename T>
void pivotar(Secuencia<T> s, Nodo_sec<T>* inic, Nodo_sec<T> *fin, T pivote, Nodo_sec<T> * & ult_menor, Nodo_sec<T> * & ult_igual ){
    ult_igual = inic;
    ult_menor = inic;
    Nodo_sec<T> * ult_mayor = inic;
    Nodo_sec<T> * aux;
    while(ult_mayor->sig != fin)
    {
        if(!(pivote<=ult_mayor->sig->dato))
        {
            if(ult_mayor == ult_menor)
            {//no hay mayores ni iguales
            ult_menor = ult_menor->sig;
            ult_igual = ult_menor->sig;
            ult_mayor = ult_menor->sig;
            }
            else
            {
                aux = ult_mayor->sig;
                ult_mayor->sig = aux->sig;
                aux->sig = ult_menor->sig;
                if(ult_igual == ult_menor)
                {//no hay iguales
                ult_menor->sig = aux;
                ult_menor = aux;
                ult_igual = aux;
                }
                else
                {
                    ult_menor->sig = aux;
                    ult_menor = aux;
                }
            }
        }
        else if(!(ult_mayor->sig->dato<=pivote))
        {
            ult_mayor = ult_mayor->sig;
        }
        else
        {
            if(ult_mayor == ult_igual)
            {//no hay mayores
                ult_mayor = ult_mayor->sig;
                ult_igual = ult_igual->sig;
            }
            else{
                aux = ult_mayor->sig;
                ult_mayor->sig = aux->sig;
                aux->sig = ult_igual->sig;
                ult_igual->sig = aux;
                ult_igual = aux;
            }
        }
    }
}


template <typename T> // T debe tener definido el operador <=
 //ordena la secuencia s
void quick_sort_in_situ(Secuencia<T> s, Nodo_sec<T>* inic, Nodo_sec<T> *fin){
 if(inic->sig!=fin){
 Nodo_sec<T> *ult_menor, *ult_igual;
 T p = inic->sig->dato;
 pivotar(s,inic,fin,p,ult_menor,ult_igual);
 quick_sort_in_situ(s,inic,ult_menor->sig);
 quick_sort_in_situ(s,ult_igual,fin);
 }
}