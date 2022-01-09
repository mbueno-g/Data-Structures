
/* TAD ARBOLES HUFFMAN

parametro CODIGOS_HUFFMAN
tipos codigo_h
operaciones
        codigo_vacio:                   -> codigo_h
        _:_         : codigo_h codigo_h -> codigo_h
        0           :                   -> codigo_h
        1           :                   -> codigo_h
ecuaciones
        codigo_vacio:c = c
        c:codigo_vacio = c
        (a:b):c = a:(b:c)
fparametro

especificación ARBOLES-HUFFMAN[CLAVES]
usa BOOLEANOS,TABLA[CLAVES,CÓDIGOS-HUFFMAN], LISTA[CLAVES]
tipos arbol_h
operaciones
        hoja            : clave nat             ->  arbol_h {constructor}
        plantar         : arbol_h arbol_h       ->p arbol_h {constructor}
        cto_elementos   : arbol_h               ->  cto[clave]
        tabla_codigos   : arbol_h               ->  tabla[clave,codigo_h]
        pre_cero        : tabla[clave,codigo_h] ->  tabla[clave,codigo_h]
        pre_uno         : tabla[clave,codigo_h] ->  tabla[clave,codigo_h]
        combinar_tablas : tabla[clave,codigo_h] tabla[clave,codigo_h] -> tabla[clave,codigo_h]
        decodifica_elem : codigo_h arbol_h      ->p clave
        resto_dec       : codigo_h arbol_h      ->p lista[clave]
        decodifica      : codigo_h arbol_h      ->p lista[clave]
variables
        iz,dr : arbol_h
        c,d : clave
        v,w : valor
        f : nat
        cod : codigoh
        t,t1 : tabla[clave,codigo_h]
ecuaciones
        plantar(iz,dr) = error <= ! es_vacio(cto_elementos(iz), cto_elementos(dr))
        cto_elementos(hoja(c,f)) = aniadir(c,cto_vacio)
        cto_elementos(plantar(iz,dr)) = union(cto_elementos(iz), cto_elementos(dr))
        pre_cero(insertar_tabla(c,v,t)) = insertar(c, 0:consultar(c,insertar_tabla(c,v,t))),eliminar(c,t))
        pre_uno(insertar_tabla(c,v,t)) = insertar(c, 1:consultar(c,insertar_tabla(c,v,t))),eliminar(c,t))
        combinar_tablas(tabla_vacia,t1) = t1
        combinar_tablas(insertar_tabla(c,v,t),t1) = insertar_tabla(c,v,combinar_tablas(t,t1))
        tabla_codigos(plantar(izdo,dcho)) = combinar_tablas(pre_cero(izdo),pre_uno(dcho))
        decodifica_elem(cod,hoja(c,f)) = c
        decodifica_elem(codigo_vacío,plantar(izdo,dcho)) = error
        decodifica_elem(0:cod,plantar(izdo,dcho)) = decodifica_elem(cod,izdo)
        decodifica_elem(1:cod,plantar(izdo,dcho)) = decodifica_elem(cod,dcho)
        resto_dec(cod,hoja(c,f)) = cod
        resto_dec(codigo_vacío,plantar(izdo,dcho)) = error
        resto_dec(0:cod,plantar(izdo,dcho)) = resto_dec(cod,izdo)
        resto_dec(1:cod,plantar(izdo,dcho)) = resto_dec(cod,dcho)
        decodifica(cod,a) = decodifica_elem(cod,a) + decodifica(resto_dec(cod,a),a)
        decodifica(codigo_vacío,a) = lista_vacía()
*/

#include <iostream>
#include <queue>
#include <vector>
#include <locale>
#include <fstream>
#include <limits.h>

using namespace std;

//TABLAS
template <typename c, typename v>
struct nodo_tabla
{
        c clave;
        v valor;
        nodo_tabla<c,v> *iz = NULL;
        nodo_tabla<c,v> *dr = NULL;
};

template <typename c,typename v>
using tabla = nodo_tabla<c,v> *;

template <typename c,typename v>
bool es_tabla_vacia(tabla<c,v> a)
{
        return (a==NULL);
}

template <typename c, typename v>
void  aniadir(tabla<c,v> &arb, c clave, v valor)
{
        if (es_tabla_vacia(arb))
        {
                arb = new nodo_tabla<c,v>;
                arb->clave = clave;
                arb->valor = valor;
        }
        else if (arb->clave == clave)
                arb->valor += valor;
        else if (arb->clave <= clave) 
                aniadir(arb->dr, clave, valor);
        else
                aniadir(arb->iz,clave, valor);
}

template <typename c, typename v>
tabla<c,v> tabla_vacia()
{
    return (NULL);
}

//ÁRBOL HUFFMAN
struct arbol_h
{
        char data;
        int freq;
        arbol_h* left = NULL;
        arbol_h* right = NULL;
};

struct Compare
{
        bool operator()(arbol_h *h1, arbol_h *h2)
        {
                return (h1->freq > h2->freq);
        }
};

typedef vector<bool> cod_huffman;

vector<bool> operator += (vector<bool>v1, vector<bool> v2)
{
        return v2;
}

// Crea a partir de una cola de prioridad un arbol de Huffman
arbol_h* generar_arbol_huffman(priority_queue<arbol_h*, vector<arbol_h*>,Compare> & pq)
{
        while(pq.size() != 1)
        {
                arbol_h* left = pq.top();
                pq.pop();
                arbol_h* right = pq.top();
                pq.pop();
                arbol_h * node = new arbol_h;
                node->freq = left->freq + right->freq;
                node->left = left;
                node->right = right;
                pq.push(node);
                
        }
        return pq.top();
}

// crea una tabla donde cada nodo contiene la letra y su código
template <typename c, typename v>
void tabla_codigos(arbol_h *root, tabla<c,v> &cod, vector<bool> vec)
{
        if (root->left != NULL)
        {
                vec.push_back(0);
                tabla_codigos(root->left, cod, vec);
        }
        if (root->right != NULL)
        {
                vec.pop_back();
                vec.push_back(1);
                tabla_codigos(root->right, cod,vec);
        }
        if (root->left == NULL && root->right == NULL)
                aniadir(cod, root->data, vec);
}

// crea el arbol de Huffman a partir de una tabla de frecuencias: para ello primero crea un montículo
// que se utiliza para crear el árbol
template <typename c, typename v>
arbol_h* arbol_h_from_frecs(tabla<c,v> t, priority_queue<arbol_h*, vector<arbol_h*>,Compare> & pq)
{
        if (t != NULL)
        {
                arbol_h *new_node = new arbol_h;
                new_node->data = t->clave;
                new_node->freq = t->valor;
                pq.push(new_node);
                arbol_h_from_frecs(t->iz, pq);
                arbol_h_from_frecs(t->dr, pq);
        }
        return (generar_arbol_huffman(pq));
}

// busca en la tabla de códigos la letra dada y devuelve su código asociado
vector<bool> buscar_tabla(char letra, tabla<char,cod_huffman> cods)
{
        if (es_tabla_vacia(cods))
                throw runtime_error("Tabla vacía");
        if (letra == cods->clave)
                return (cods->valor);
        else if (letra < cods->clave)
                return (buscar_tabla(letra, cods->iz));
        else
                return (buscar_tabla(letra, cods->dr));
}

// codifica un mensaje sustituyendo cada letra por su código
vector<bool> codificar_mensaje(string mensaje, tabla<char,cod_huffman> cods)
{
        vector<bool> men_cod;
        vector<bool> aux;
        for(int i=0 ; i<mensaje.length(); ++i)
        {
                aux = buscar_tabla(mensaje[i], cods);
                for(int j=0; j < aux.size(); ++j)
                {
                        men_cod.push_back(aux[j]);
                }                
        }
        return men_cod;
}

int buscar_letra(vector<bool> men_cod, arbol_h *arb, int i, string &men)
{
        if (arb->left == NULL && arb->right == NULL)
        {
                men += arb->data;
                return (i);
        }
        else if (men_cod[i] == 1)
                return (buscar_letra(men_cod, arb->right, i+1, men));
        else
                return(buscar_letra(men_cod, arb->left, i+1, men));
}

// decodifica un mensaje utilizando el arbol de Huffman: según el número es un 0 o un 1 se mueve por el hijo iz o el dr
// y cuando llega a una rama obtiene la letra asociada al código
string decodificar_mensaje(vector<bool> men_cod, arbol_h *arb)
{
        int i = 0;
        string men;
        while(i < men_cod.size())
        {
                i = buscar_letra(men_cod, arb, i, men);
        }
        return (men);
}


ostream & operator <<(ostream & o, tabla<char, cod_huffman> node){
        int i = 0;
        int size= node->valor.size();
        o << "(" << node->clave << "," ;
        while(i < size)
        {
                o << node->valor[i];
                i++;
        }
        o << endl;
        return o;
}


template <typename c, typename v>
void mostrar(const string& prefix, tabla<c,v> node, bool isiz)
{
    if(!es_tabla_vacia(node))
    {
        cout << prefix;
        cout << (isiz ? "iz├──" : "dr└──" );
        cout << "(" << node->clave << "," << node->valor << ")" << endl;
        mostrar( prefix + (isiz ? "│   " : "    "), node->iz, true);
        mostrar( prefix + (isiz ? "│   " : "    "), node->dr, false);
    }
}

template <typename c, typename v>
void mostrar_cod(const string& prefix, tabla<c,v> node, bool isiz)
{
    if(!es_tabla_vacia(node))
    {
        cout << prefix;
        cout << (isiz ? "iz├──" : "dr└──" );
        int i = 0;
        int size= node->valor.size();
        cout << "(" << node->clave << "," ;
        while(i < size)
        {
                cout << node->valor[i];
                i++;
        }
        cout << ")" << endl;
        mostrar_cod( prefix + (isiz ? "│   " : "    "), node->iz, true);
        mostrar_cod( prefix + (isiz ? "│   " : "    "), node->dr, false);
    }
}

void mostrar_h(const string& prefix, arbol_h* node, bool isiz)
{
    if(node != NULL)
    {
        cout << prefix;
        cout << (isiz ? "iz├──" : "dr└──" );
        cout << "(" << node->data << "," << node->freq << ")" << endl;
        mostrar_h( prefix + (isiz ? "│   " : "    "), node->left, true);
        mostrar_h( prefix + (isiz ? "│   " : "    "), node->right, false);
    }
}

void mostrar_vector(vector<bool> vec)
{
        for (int i=0; i < vec.size(); ++i)
        {
                cout << vec[i];
        }
        cout << endl;
}

// guarda un vector bool en un archivo
void vector_bool_to_file(vector<bool> v, string file_name){
    ofstream f = ofstream(file_name);
    long num_bits = v.size();
    f << num_bits<<endl;
    for (int i=0; i<num_bits/CHAR_BIT; i++)
            f << v[i];
    f.close();
}

template <typename c, typename v>
void liberar(tabla<c,v> t)
{
        if (!es_tabla_vacia(t))
        {
                liberar(t->iz);
                liberar(t->dr);
                delete t;
        }
}

void liberar(arbol_h *a)
{
        if (a != NULL)
        {
                liberar(a->left);
                liberar(a->right);
                delete a;
        }
}

/*vector<bool> file_to_vector_bool(string file_name){
    long num_bits;
    vector<bool> result;
    ifstream f = ifstream(file_name);
    f >> num_bits;
    int c;
    string s;
    getline(f,s); 
    long pos = 0;
    for(long i =0; i<num_bits/CHAR_BIT; i++){
         c = f.get();
         for(long j = 0 ; j<CHAR_BIT;j++){
              result.push_back(c % 2);
              c = c/2;
              pos++;
         }
    }
    f.close();
    return result; 
}*/


int main()
{
        locale::global(locale("C.UTF-8"));
        string mensaje;
        cout << "Introduce un mensaje: " << endl;
        getline(cin,mensaje);
        cout << "El mensaje es: " << mensaje << endl;

        cout << "La tabla de frecuencias es: " << endl;
        tabla<char, int> t = tabla_vacia<char,int>();
        for(int i=0 ; i<mensaje.length(); ++i)
        {
                aniadir(t,mensaje[i],1);
        }
        mostrar("", t, false);

        cout << "El arbol de Huffman es: " << endl;
        priority_queue<arbol_h*, vector<arbol_h*>,Compare> pq;
        arbol_h *a = arbol_h_from_frecs(t, pq);
        mostrar_h("", a, false);

        cout << "La tabla de códigos es: " << endl;
        tabla<char,cod_huffman> cods = tabla_vacia<char, cod_huffman>(); //tabla
        tabla_codigos(a,cods, vector<bool>());
        mostrar_cod("", cods, false);

        cout << "El mensaje codificado es: ";
        vector<bool> men_cod = codificar_mensaje(mensaje, cods);
        mostrar_vector(men_cod);
        cout << "Guardamos el mensaje codificado en el archivo : mensaje_cod.txt" << endl;
        vector_bool_to_file(men_cod, "mensaje_cod.txt");

        //cout << "Recuperamos el mensaje codificado del archivo mensaje_cod.txt para decodificarlo" << endl;
        //vector<bool> men_cod_aux = file_to_vector_bool("mensaje_cod.txt");
        //mostrar_vector(men_cod_aux);
        string men = decodificar_mensaje(men_cod, a);
        cout << "El mensaje descodificado es: " << men << endl;
        cout << "¿Es la descodificación correcta? ";
        bool correcto = mensaje==men;
        if (correcto)
                cout << "true" << endl;
        else
                cout << "false" << endl;

        //Liberamos 
        liberar(t);
        liberar(cods);
        liberar(pq.top());  // liberar nodo de pq (priority queue) -> arbol_h
        return (0);
}
