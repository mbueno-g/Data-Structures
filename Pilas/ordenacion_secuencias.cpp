
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


int main()
{
    Secuencia<int> sec = crear<int>();
    insertar(3, sec);
    insertar(5, sec);
    insertar(4, sec);
    insertar(2, sec);
    insertar(4, sec);
    insertar(1, sec);
    cout << "La secuencia es: "<< endl;
    mostrar(sec);
  
    Secuencia<int> aux = crear<int>();
    insertar(13, aux);
    insertar(15, aux);
    insertar(14, aux);
    insertar(12, aux);
    insertar(14, aux);
    insertar(11, aux);
    reiniciar(aux);
    sec.anterior->sig = aux.primero->sig;
    cout << "Adjuntado una secuencia: " << endl;
    mostrar(sec);
    cout << sec;
    cout << "Avanzamos en la secuencia: " << endl;
    avanzar(sec);
    mostrar(sec);
    cout << "Reiniciamos la secuencia: " << endl;
    reiniciar(sec);
    mostrar(sec);
    cout << "La secuencia ordenada con quicksort es " << endl;
    Secuencia<int> sec_ord;
    sec_ord = quicksort(sec);
    mostrar(sec_ord);
    liberar(sec_ord);
    cout << "La secuencia ordenada por burbuja es " << endl;
    sec_ord = sec;
    ordenar_burbuja(sec_ord);
    liberar(sec);
    return 0;
}