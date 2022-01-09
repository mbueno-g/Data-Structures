
/* TAD TABLAS

especificaciones TABLAS[CLAVES, VALORES-MODIFICABLES]
usa BOOLEANOS
tipos tabla
operaciones 
        tabla_vacia    :                   -> tabla {constructora}
        insertar_tabla : clave valor tabla -> tabla {constructora}
        esta_tabla     : clave tabla       -> bool
        consultar_tabla: clave tabla       ->p valor
        eliminar_tabla : clave tabla       -> tabla
        es_tabla_vacia : tabla
variables
        c,d : clave
        v,w : valor
        t : tabla
ecuaciones
        insertar_tabla(c,w,insertar_tabla(c,v,t)) = insertar_tabla(c,combinar(v,w),t)
        insertar_tabla(d,w,insertar_tabla(c,v,t)) = insertar_tabla(c,v,insertar_tabla(d,w,t)) <= c!=d
        esta_tabla(c,tabla_vacia) = falso
        esta_tabla(c,insertar_tabla(d,v,t)) = c==d || esta_tabla(c,t)
        consultar_tabla(c,t) = error <= !esta_tabla(c,t)
        consultar_tabla(c,insertar_tabla(c,v,t)) = v <= !es_tabla(c,t)
        consultar_tabla(c,insertar_tabla(c,v,t)) = combinar(consultar_tabla(c,t),v) <= esta_tabla(c,t)
        consultar_tabla(c,insetar_tabla(d,v,t)) = consultar_tabla(c,t) <= c!=d
        eliminar_tabla(c,tabla_vacia) = tabla_vacia
        eliminar_tabla(c,insertar_tabla(c,v,t)) = eliminar_tabla(c,t)
        eliminar_tabla(c,insertar_tabla(d,v,t)) = eliminar_tabla(d,v,eliminar_tabla(c,t)) <= c!=d
        es_tabla_vacia(tabla_vacia) = cierto
        es_tabla_vacia(insertar_tabla(c,v,t)) = falso
fespeficicación

Las constructoras no son libres ya que insertar dos valores asociados a la
misma clave es equivalente a insertar la combinacion de ambos en el orden
apropiado: el valor que estaba en la tabla se combina con el nuevo.

*/
/* Los arboles de búsqueda con claves están diseñados para implementar tablas
cuyas claves tengan orden.
*/

#include "arboles_binarios_claves.cpp"

template <typename c, typename v>
using tabla = ABB<c,v>;


template <typename c, typename v>
tabla<c,v> tabla_vacia()
{
        return (abb_vacio());
}

template <typename c, typename v>
void insertar_tabla(c clave, v valor, tabla<c,v> t)
{
        insertar(clave, valor, t);
}

template <typename c, typename v>
bool esta_tabla(c clave, tabla<c,v> t)
{
        return(esta(c,t));
}

template <typename c, typename v>
v consultar_tabla(c clave, tabla<c,v> t)
{
        return (consultar(c,t));
}

template <typename c, typename v>
void eliminar_tabla(c clave, tabla<c,v> t)
{
        eliminar(c,t);
}

template <typename c, typename v>
bool es_tabla_vacia(tabla<c,v> t)
{
        return(es_abb_vacio(t));
}


// RECORRER ORDENADA
