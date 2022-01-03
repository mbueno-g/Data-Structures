/* TAD COLAS - fifo (First In, First Out)

especifiación COLAS[ELEM]
usa BOOLEANOS
tipos cola
operaciones
        cola_vacia    :               ->  cola {constructora}
        pedir_vez     : cola elemento ->  cola {constructora}
        avanzar       : cola          ->p cola
        primero       : cola          ->p elemento
        es_cola_vacia : cola          ->  bool
variables
        e : elemento
        c : cola
ecuaciones
        avanzar(cola_vacia) = error
        avanzar(pedir_vez(c,e)) = cola_vacia <= es_cola_vacia(c)
        avanzar(pedir_vez(c,e)) = pedir_vez(avanzar(c),e)) <= no es_cola_vacia(c)
        primero(cola_vacia) = error
        primero(pedir_vez(c,e)) = e <= es_cola_vacia(c)
        primero(pedir_vez(c,e)) = primero(c) <= no es_cola_vacia(c)
        es_cola_vacia(cola_vacia) = cierto
        es_cola_vacia(pedir_vez(c,e)) = falso
fespecificación
*/