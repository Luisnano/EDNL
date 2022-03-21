/*Problema 5 de la Práctica 1
    Crear funciones que calculen la altura y la profundidad de un nodo.
    En la implementacion vectorial, es decir, tenemos punteros a padre, hijo derecho e hijo izquierdo*/

template <typename T>
int profundidad (Abin<T>& A, typename Abin<T>::nodo n){
    if (n == A.raiz()){
        return 0;
    }else{
        return 1 + profundidad(A, A.padre(n));
    }
}

template <typename T>
int altura (Abin<T>& A, typename Abin<T>::nodo n){
    if (n == Abin<T>::NODO_NULO){
        return -1;
    }else{
        return 1 + std::max(altura(A, A.hijoDrcho(n)), altura(A, A.hijoIzqdo(n)));
    }
}