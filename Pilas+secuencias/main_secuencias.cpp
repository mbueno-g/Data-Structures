#include "ordenacion_secuencias.cpp"

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
    sec_ord = sec; // no sirve de nada porque al ser una estructura tambien se actualiza sec
    ordenar_burbuja(sec_ord);
    liberar(sec);
    return 0;
}