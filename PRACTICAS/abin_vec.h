#ifndef ABIN_VEC0_H
#define ABIN_VEC0_H
#include <cassert>
template <typename T> class Abin {
public:
    typedef size_t nodo; // índice de la matriz
// entre 0 y maxNodos-1
    static const nodo NODO_NULO;
    explicit Abin(size_t maxNodos); // constructor
    void insertarRaiz(const T& e);
    void insertarHijoIzqdo(nodo n, const T& e);
    void insertarHijoDrcho(nodo n, const T& e);
    void eliminarHijoIzqdo(nodo n);
    void eliminarHijoDrcho(nodo n);
    void eliminarRaiz();
    bool arbolVacio() const;
    const T& elemento(nodo n) const; // acceso a elto, lectura
    T& elemento(nodo n); // acceso a elto, lectura/escritura
    nodo raiz() const;
    nodo padre(nodo n) const;
    nodo hijoIzqdo(nodo n) const;
    nodo hijoDrcho(nodo n) const;
    Abin(const Abin<T>& A); // ctor. de copia
    Abin<T>& operator =(const Abin<T>& A); // asig. de árboles
    ~Abin(); // destructor
private:
    struct celda {
        T elto;
        nodo padre, hizq, hder;
    };
    celda *nodos; // vector de nodos
    size_t maxNodos; // tamaño del vector
    size_t numNodos; // número de nodos del árbol
};

#endif 

