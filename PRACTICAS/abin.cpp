#include "abin.h"

template <typename T>
const typename Abin<T>::nodo Abin<T>::NODO_NULO(nullptr);

template <typename T>
inline Abin<T>::Abin() : r(NODO_NULO) {}

template <typename T>
inline void Abin<T>::insertarRaiz(const T& e)
{
    assert(r == NODO_NULO); // Árbol vacío
    r = new celda(e);
}

template <typename T>
inline void Abin<T>::insertarHijoIzqdo(nodo n, const T& e)
{
    assert(n != NODO_NULO);
    assert(n->hizq == NODO_NULO); // No existe hijo izqdo.
    n->hizq = new celda(e, n);
}

template <typename T>
inline void Abin<T>::insertarHijoDrcho(nodo n, const T& e)
{
    assert(n != NODO_NULO);
    assert(n->hder == NODO_NULO); // No existe hijo drcho.
    n->hder = new celda(e, n);
}

template <typename T>
inline void Abin<T>::eliminarHijoIzqdo(nodo n)
{
    assert(n != NODO_NULO);
    assert(n->hizq != NODO_NULO); // Existe hijo izqdo.
    assert(n->hizq->hizq == NODO_NULO && // Hijo izqdo. 
    n->hizq->hder == NODO_NULO); // es hoja.
    delete n->hizq;
    n->hizq = NODO_NULO;
}

template <typename T>
inline void Abin<T>::eliminarHijoDrcho(nodo n)
{
    assert(n != NODO_NULO);
    assert(n->hder != NODO_NULO); // Existe hijo drcho.
    assert(n->hder->hizq == NODO_NULO && // Hijo drcho.
    n->hder->hder == NODO_NULO); // es hoja
    delete n->hder;
    n->hder = NODO_NULO;
}


template <typename T>
inline void Abin<T>::eliminarRaiz()
{
    assert(r != NODO_NULO); // Árbol no vacío.
    assert(r->hizq == NODO_NULO &&
    r->hder == NODO_NULO); // La raíz es hoja.
    delete r;
    r = NODO_NULO;
}


template <typename T> inline bool Abin<T>::arbolVacio() const
{ return (r == NODO_NULO); }


template <typename T>
inline const T& Abin<T>::elemento(nodo n) const
{
    assert(n != NODO_NULO);
    return n->elto;
}


template <typename T>
inline T& Abin<T>::elemento(nodo n)
{
    assert(n != NODO_NULO);
    return n->elto;
}


template <typename T>
inline typename Abin<T>::nodo Abin<T>::raiz() const
{ return r; }


template <typename T> inline
typename Abin<T>::nodo Abin<T>::padre(nodo n) const
{
    assert(n != NODO_NULO);
    return n->padre;
}


template <typename T> inline
typename Abin<T>::nodo Abin<T>::hijoIzqdo(nodo n) const
{
    assert(n != NODO_NULO);
    return n->hizq;
}


template <typename T> inline
typename Abin<T>::nodo Abin<T>::hijoDrcho(nodo n) const
{
    assert(n != NODO_NULO);
    return n->hder;
}


template <typename T>
inline Abin<T>::Abin(const Abin<T>& A)
{
    r = copiar(A.r); // Copiar raíz y descendientes.
}


template <typename T>
Abin<T>& Abin<T>::operator =(const Abin<T>& A)
{
    if (this != &A) // Evitar autoasignación.
        {
            this->~Abin(); // Vaciar el árbol.
            r = copiar(A.r); // Copiar raíz y descendientes.
        }
    return *this;
}


template <typename T>
inline Abin<T>::~Abin()
{
    destruirNodos(r); // Vaciar el árbol.
}


/*--------------------------------------------------------*/
/* Métodos privados */
/*--------------------------------------------------------*/
// Destruye un nodo y todos sus descendientes
template <typename T>
void Abin<T>::destruirNodos(nodo& n)
{
    if (n != NODO_NULO)
        {
            destruirNodos(n->hizq);
            destruirNodos(n->hder);
            delete n;
            n = NODO_NULO;
        }
    }


// Devuelve una copia de un nodo y todos sus descendientes
template <typename T>
typename Abin<T>::nodo Abin<T>::copiar(nodo n)
{
    nodo m = NODO_NULO;
    if (n != NODO_NULO) {
        m = new celda(n->elto); // Copiar n.
        m->hizq = copiar(n->hizq); // Copiar subárbol izqdo.
        if (m->hizq != NODO_NULO) m->hizq->padre = m;
        m->hder = copiar(n->hder); // Copiar subárbol drcho.
        if (m->hder != NODO_NULO) m->hder->padre = m;
    }
    return m;
}


/*Resolucion del profesor
si altura(hderecho)>altura(hizquierdo)
    devolver true
sino
    si altura(hizquierdo)>altura(hderecho)
        devolver true
    sino
        pseudocompleto(hderecho) AND psedocompleto(hizquierdo)
*/

/*-----------------------------RESOLUCIONES DE LA P1 Y LA P2--------------------------------*/

/*Problema 1 de la Práctica 1
    Implementar un subprograma que calcule el numero de nodos de un arbol*/

template <typename T>
int numNodos_rec(Abin<T>& A, typename Abin<T>::nodo n){

    if (n == Abin<T>::NODO_NULO){

        return 0;

    }else{

        return 1 + numNodos_rec(A, A.hijoDrcho(n)) + numNodos_rec(A, A.hijoIzqdo(n));

    }

}

template <typename T>
int numNodos(Abin<T>& A){

    if (!A.arbolVacio()){

        return numNodos_rec(A, A.raiz());

    }else{

        return 0;

    }

}


/*Problema 2 de la Práctica 1
    Implementar un subprograma que calcule la altura de un arbol binario*/

template <typename T>
int alturaBinario_rec(Abin<T>& A, typename Abin<T>::nodo n){

    if (n == Abin<T>::NODO_NULO){

        return -1;

    }else{

        return 1 + std::max(alturaBinario_rec(A, A.hijoDrcho(n)), alturaBinario_rec(A, A.hijoIzqdo(n)));

    }

}

template <typename T>
int alturaBinario(Abin<T>& A){

    if (!A.arbolVacio()){

        return alturaBinario_rec(A, A.raiz());

    }else{

        return 0;

    }

}


/*Problema 3 de la Práctica 3
    Dados un arbol binario y un nodo del mismo, determine la profundidad de dicho nodo en el arbol.*/

template <typename T>
int profNodo_rec(Abin<T>& A, typename Abin<T>::nodo nodo_profundo, typename Abin<T>::nodo n){

    if (A.hijoDrcho(n) != nodo_profundo){

        /*Al ser un OR sabemos que entrara en el if si uno de los dos se da o los dos*/

        return 1 + profNodo_rec(A, nodo_profundo, A.hijoDrcho(n));

    }else{

        if (A.hijoIzqdo(n) != nodo_profundo){

            return 1 + profNodo_rec(A, nodo_profundo, A.hijoIzqdo(n));
        
        }

    }


}

template <typename T>
int profNodo(Abin<T>& A, typename Abin<T>::nodo nodo_profundo){

    if (!A.arbolVacio() || A.raiz() != Abin<T>::NODO_NULO){

        return profNodo_rec(A, nodo_profundo, A.raiz());

    }

}

/*Problemas 4 y 5 hechos en sus respectivas representaciones vectoriales y vecrel*/

/*Problema 6 de la Práctica 1
    Hacer un subprograma que determine el nivel de desequilibrio de un arbol binario, definido como
    el maximo desequilibrio de todos sus nodos
    El desequilibrio es la diferencia de la altura de los subarboles.*/
template <typename T>
int altura (Abin<T>& A, typename Abin<T>::nodo n){
    if (n == Abin<T>::NODO_NULO){
        return -1;
    }else{
        return 1 + std::max(altura(A, A.hijoDrcho(n)), altura(A, A.hijoIzqdo(n)));
    }
}

template <typename T>
int difaltura (Abin<T>& A, typename Abin<T>::nodo n){
    return std::abs(altura(A, A.hijoDrcho(n)) - altura(A, A.hijoIzqdo(n)));
    }


template <typename T>
int desequilibrio(Abin<T>& A, typename Abin<T>::nodo n){
    if (n == Abin<T>::NODO_NULO){
        return 0;
    }else{
        return std::max(difaltura(A, n), std::max(desequilibrio(A, A.hijoIzqdo(n)), desequilibrio(A, A.hijoDrcho(n))));
    }
}

template <typename T>
int funcion_desequilibrio(Abin<T>& A){
    return desequilibrio(A, A.raiz());
}

/*Ejercicio 7 de la Práctica 1
    Un arbol se denomina pseudocompleto cuando en el penúltimo nivel, cada uno de sus nodos tiene
    2 o ningun hijo. */

template <typename T>
bool pseudocompleto_rec(Abin<T>& a, typename Abin<T>::nodo n){
    if ( altura(a.hijoDrcho(n)) > altura(a.hijoIzqdo(n)) ){
        return true;
    }else{
        if ( altura(a.hijoIzqdo(n)) > altura(a.hijoDrcho(n)) ){
            return true;
        }else{
            return pseudocompleto_rec(a.hijoDrcho(n)) && pseudocompleto_rec(a.hijoIzqdo(n));
        }
    }
}

template <typename T>
bool pseudocompleto(Abin<T>& a){
    if (a.arbolVacio()){
        return false;
    }else{
        return pseudocompleto(a, a.raiz());
    }
}


/*------------------------------------------------------------------------------------------*/
