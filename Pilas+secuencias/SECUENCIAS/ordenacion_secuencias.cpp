
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
