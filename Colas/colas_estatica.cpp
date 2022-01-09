
#include <iostream>

using namespace std;

const int MAX_ELEMS = 100;
// necesitamos acceso al comienzco y al final de la cola ya que las posiciones que se
// van quedando libres son las del principio, así evitamos desplazar los elementos

struct cola
{
    elemento dato[MAX_ELEMS];
    int primero; // [0,N-1];
    int ultimo; // [0,N-1]
    int tamaño;
};

// Definimos la función sig para crear una estructura circula
// sig(i) = i si 0<= i < N -1 ; 0 si i == N-1
// i = i % (N-1)
