/* 
Descripción:
Programa que construye el arreglo de sufijos (Suffix Array)
de una cadena utilizando el algoritmo de "prefix doubling".

El arreglo de sufijos consiste en ordenar alfabéticamente
todos los sufijos de una cadena y almacenar sus posiciones
iniciales.

Para garantizar que todos los sufijos sean comparables,
se agrega un símbolo sentinela '$' al final de la cadena.

Equipo 4:
Gisselle Portilla - A01752371
Pablo Javier Arreola - A01747824

Fecha: 12 de marzo de 2026

Compilación:
g++ main.cpp -o programa

Ejecución con redirección:
./programa < test01.txt
./programa < test02.txt
./programa < test03.txt

Referencias:
GeeksforGeeks. (s. f.). Suffix Array for competitive programing.
Recuperado de https://www.geeksforgeeks.org/competitive-programming/suffix-arrays-for-competitive-programming/

freeCodeCamp Español. (s. f.). Hoja de trucos de Big-O.
Recuperado de https://www.freecodecamp.org/espanol/news/hoja-de-trucos-big-o/
*/

#include <iostream>
#include <vector>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;


/*
Función: compararSufijos

Propósito:
Comparar dos sufijos de la cadena utilizando los rangos
calculados en la iteración actual del algoritmo.

Parámetros:
- i: posición inicial del primer sufijo.
- j: posición inicial del segundo sufijo.
- k: tamaño actual del prefijo considerado (2^iteración).
- rank: vector con los rangos actuales de cada sufijo.
- n: longitud total de la cadena.

Valor de retorno:
- bool: true si el sufijo en i debe aparecer antes que el de j.

Complejidad:
O(1)
*/
bool compararSufijos(int i, int j, int k,
                     const vector<int>& rank,
                     int n) {

    if (rank[i] != rank[j])
        return rank[i] < rank[j];

    int ri = (i + k < n) ? rank[i + k] : -1;
    int rj = (j + k < n) ? rank[j + k] : -1;

    return ri < rj;
}


/*
Función: merge

Propósito:
Combinar dos subarreglos ordenados dentro del vector de
sufijos durante el proceso de Merge Sort.

Parámetros:
- sa: vector con los índices de los sufijos.
- left: índice inicial del subarreglo.
- mid: punto medio del subarreglo.
- right: índice final del subarreglo.
- k: tamaño actual del prefijo comparado.
- rank: vector con los rangos actuales.
- n: longitud de la cadena.

Complejidad:
O(n) para cada combinación.
*/
void merge(vector<int>& sa, int left, int mid, int right,
           int k, const vector<int>& rank, int n) {

    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1);
    vector<int> R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = sa[left + i];

    for (int j = 0; j < n2; j++)
        R[j] = sa[mid + 1 + j];

    int i = 0, j = 0, pos = left;

    while (i < n1 && j < n2) {

        if (compararSufijos(L[i], R[j], k, rank, n))
            sa[pos++] = L[i++];
        else
            sa[pos++] = R[j++];
    }

    while (i < n1)
        sa[pos++] = L[i++];

    while (j < n2)
        sa[pos++] = R[j++];
}


/*
Función: mergeSort

Propósito:
Ordenar el arreglo de sufijos utilizando el algoritmo
Merge Sort y la función de comparación de sufijos.

Parámetros:
- sa: vector con los índices de los sufijos.
- left: límite izquierdo del subarreglo.
- right: límite derecho del subarreglo.
- k: tamaño del prefijo considerado.
- rank: rangos actuales de los sufijos.
- n: longitud de la cadena.

Complejidad:
Peor caso: O(n log n)
*/
void mergeSort(vector<int>& sa, int left, int right,
               int k, const vector<int>& rank, int n) {

    if (left >= right)
        return;

    int mid = (left + right) / 2;

    mergeSort(sa, left, mid, k, rank, n);
    mergeSort(sa, mid + 1, right, k, rank, n);

    merge(sa, left, mid, right, k, rank, n);
}


/*
Función: construirSuffixArray

Propósito:
Construir el arreglo de sufijos de la cadena utilizando
el método de prefix doubling.

En cada iteración se ordenan los sufijos considerando
prefijos de longitud 2^k.

Parámetros:
- s: cadena de entrada (incluyendo el símbolo '$').

Valor de retorno:
- vector<int>: arreglo de sufijos ordenado.

Complejidad:
Peor caso aproximado: O(n log² n)
Debido a que en cada iteración se realiza un Merge Sort.
*/
vector<int> construirSuffixArray(string s) {

    int n = static_cast<int>(s.size());

    vector<int> sa(n);
    vector<int> rank(n);
    vector<int> tmp(n);

    for (int i = 0; i < n; i++) {
        sa[i] = i;
        rank[i] = s[i];
    }

    for (int k = 1; k < n; k *= 2) {

        mergeSort(sa, 0, n - 1, k, rank, n);

        tmp[sa[0]] = 0;

        for (int i = 1; i < n; i++) {

            if (compararSufijos(sa[i - 1], sa[i], k, rank, n))
                tmp[sa[i]] = tmp[sa[i - 1]] + 1;
            else
                tmp[sa[i]] = tmp[sa[i - 1]];
        }

        rank = tmp;
    }

    return sa;
}


/*
Función: imprimirSuffixArray

Propósito:
Mostrar todos los sufijos de la cadena en orden
lexicográfico junto con su posición original.

Parámetros:
- s: cadena original con '$'.
- sa: arreglo de sufijos construido.

Complejidad:
O(n²) en el peor caso debido al uso de substr.
*/
void imprimirSuffixArray(const string& s,
                         const vector<int>& sa) {

    for (size_t i = 0; i < sa.size(); i++)
        cout << s.substr(sa[i]) << " "
             << sa[i] + 1 << endl;
}


/*
Función principal

Propósito:
Leer una cadena desde la entrada estándar, agregar
el símbolo sentinela '$', construir su suffix array
e imprimir los sufijos ordenados.

Complejidad total:
Si n es la longitud del texto:

Construcción del suffix array:
O(n log² n)

Impresión:
O(n²) en el peor caso.
*/
int main() {

    string texto;
    cin >> texto;

    texto += "$";

    vector<int> suffixArray =
        construirSuffixArray(texto);

    imprimirSuffixArray(texto, suffixArray);

    return 0;
}/* 
Descripción:
Programa que construye el arreglo de sufijos (Suffix Array)
de una cadena utilizando el algoritmo de "prefix doubling".

El arreglo de sufijos consiste en ordenar alfabéticamente
todos los sufijos de una cadena y almacenar sus posiciones
iniciales.

Para garantizar que todos los sufijos sean comparables,
se agrega un símbolo sentinela '$' al final de la cadena.

Equipo 4:
Gisselle Portilla - A01752371
Pablo Javier Arreola - A01747824

Fecha: 12 de marzo de 2026

Compilación:
g++ main.cpp -o programa

Ejecución con redirección:
./programa < test01.txt
./programa < test02.txt
./programa < test03.txt

Referencias:
GeeksforGeeks. (s. f.). Suffix Array Set 1 (Introduction).
Recuperado de https://www.geeksforgeeks.org/suffix-array-set-1-introduction/

freeCodeCamp Español. (s. f.). Hoja de trucos de Big-O.
Recuperado de https://www.freecodecamp.org/espanol/news/hoja-de-trucos-big-o/
*/

#include <iostream>
#include <vector>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;


/*
Función: compararSufijos

Propósito:
Comparar dos sufijos de la cadena utilizando los rangos
calculados en la iteración actual del algoritmo.

Parámetros:
- i: posición inicial del primer sufijo.
- j: posición inicial del segundo sufijo.
- k: tamaño actual del prefijo considerado (2^iteración).
- rank: vector con los rangos actuales de cada sufijo.
- n: longitud total de la cadena.

Valor de retorno:
- bool: true si el sufijo en i debe aparecer antes que el de j.

Complejidad:
O(1)
*/
bool compararSufijos(int i, int j, int k,
                     const vector<int>& rank,
                     int n) {

    if (rank[i] != rank[j])
        return rank[i] < rank[j];

    int ri = (i + k < n) ? rank[i + k] : -1;
    int rj = (j + k < n) ? rank[j + k] : -1;

    return ri < rj;
}


/*
Función: merge

Propósito:
Combinar dos subarreglos ordenados dentro del vector de
sufijos durante el proceso de Merge Sort.

Parámetros:
- sa: vector con los índices de los sufijos.
- left: índice inicial del subarreglo.
- mid: punto medio del subarreglo.
- right: índice final del subarreglo.
- k: tamaño actual del prefijo comparado.
- rank: vector con los rangos actuales.
- n: longitud de la cadena.

Complejidad:
O(n) para cada combinación.
*/
void merge(vector<int>& sa, int left, int mid, int right,
           int k, const vector<int>& rank, int n) {

    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1);
    vector<int> R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = sa[left + i];

    for (int j = 0; j < n2; j++)
        R[j] = sa[mid + 1 + j];

    int i = 0, j = 0, pos = left;

    while (i < n1 && j < n2) {

        if (compararSufijos(L[i], R[j], k, rank, n))
            sa[pos++] = L[i++];
        else
            sa[pos++] = R[j++];
    }

    while (i < n1)
        sa[pos++] = L[i++];

    while (j < n2)
        sa[pos++] = R[j++];
}


/*
Función: mergeSort

Propósito:
Ordenar el arreglo de sufijos utilizando el algoritmo
Merge Sort y la función de comparación de sufijos.

Parámetros:
- sa: vector con los índices de los sufijos.
- left: límite izquierdo del subarreglo.
- right: límite derecho del subarreglo.
- k: tamaño del prefijo considerado.
- rank: rangos actuales de los sufijos.
- n: longitud de la cadena.

Complejidad:
Peor caso: O(n log n)
*/
void mergeSort(vector<int>& sa, int left, int right,
               int k, const vector<int>& rank, int n) {

    if (left >= right)
        return;

    int mid = (left + right) / 2;

    mergeSort(sa, left, mid, k, rank, n);
    mergeSort(sa, mid + 1, right, k, rank, n);

    merge(sa, left, mid, right, k, rank, n);
}


/*
Función: construirSuffixArray

Propósito:
Construir el arreglo de sufijos de la cadena utilizando
el método de prefix doubling.

En cada iteración se ordenan los sufijos considerando
prefijos de longitud 2^k.

Parámetros:
- s: cadena de entrada (incluyendo el símbolo '$').

Valor de retorno:
- vector<int>: arreglo de sufijos ordenado.

Complejidad:
Peor caso aproximado: O(n log² n)
Debido a que en cada iteración se realiza un Merge Sort.
*/
vector<int> construirSuffixArray(string s) {

    int n = static_cast<int>(s.size());

    vector<int> sa(n);
    vector<int> rank(n);
    vector<int> tmp(n);

    for (int i = 0; i < n; i++) {
        sa[i] = i;
        rank[i] = s[i];
    }

    for (int k = 1; k < n; k *= 2) {

        mergeSort(sa, 0, n - 1, k, rank, n);

        tmp[sa[0]] = 0;

        for (int i = 1; i < n; i++) {

            if (compararSufijos(sa[i - 1], sa[i], k, rank, n))
                tmp[sa[i]] = tmp[sa[i - 1]] + 1;
            else
                tmp[sa[i]] = tmp[sa[i - 1]];
        }

        rank = tmp;
    }

    return sa;
}


/*
Función: imprimirSuffixArray

Propósito:
Mostrar todos los sufijos de la cadena en orden
lexicográfico junto con su posición original.

Parámetros:
- s: cadena original con '$'.
- sa: arreglo de sufijos construido.

Complejidad:
O(n²) en el peor caso debido al uso de substr.
*/
void imprimirSuffixArray(const string& s,
                         const vector<int>& sa) {

    for (size_t i = 0; i < sa.size(); i++)
        cout << s.substr(sa[i]) << " "
             << sa[i] + 1 << endl;
}


/*
Función principal

Propósito:
Leer una cadena desde la entrada estándar, agregar
el símbolo sentinela '$', construir su suffix array
e imprimir los sufijos ordenados.

Complejidad total:
Si n es la longitud del texto:

Construcción del suffix array:
O(n log² n)

Impresión:
O(n²) en el peor caso.
*/
int main() {

    string texto;
    cin >> texto;

    texto += "$";

    vector<int> suffixArray =
        construirSuffixArray(texto);

    imprimirSuffixArray(texto, suffixArray);

    return 0;
}