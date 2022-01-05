
#include "pilas_template.cpp"

int main()
{
    pila<int>* p;
    int i;

    p = pila_vacia<int>();
    cout << "Introduce un número: ";
    cin >> i;
    while (i > 0)
    {
        apilar(i,p);
        i--;
    }
    cout << "La pila es: " << endl;
    mostrar(p);
    cout << "---------------" << endl;
    cout << "Si despilamos un elemento: " << endl;
    desapilar(p);
    mostrar(p);
    cout << "---------------" << endl;
    cout << "Si apilamos el número 11" << endl;
    apilar(11, p);
    mostrar(p);
    cout << "---------------" << endl;
    cout << "Copia de la pila: " << endl;
    pila<int> *c;
    c = copiar_pila(p);
    //cout << "La profundidad es: " << profundidad(p) << endl;
    //liberar(p);
    //mostrar(c);
    return(0);
}