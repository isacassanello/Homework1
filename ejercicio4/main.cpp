#include <iostream>
#include <chrono>
using namespace std;

// Punto a
bool comparar_strings(const char* str1, const char* str2){
    // si ambos punteros apuntan al final 
    if (*str1 == '\0' && *str2 == '\0') return true;

    if (*str1 != *str2) return false;

    return comparar_strings(str1 + 1, str2 + 1);
}

int main(){
    const char* text1 = "La programacion en C++ es poderosa y permite optimizaciones increibles";
    const char* text2 = "La programacion en C++ es poderosa y permite optimizaciones increibles";
    const char* text3 = "La programacion en C++ es flexible y permite optimizaciones increibles";

    // medir el tiempo de comparación entre text1 y text2
    auto startTime = chrono::high_resolution_clock::now();
    bool resultado1 = comparar_strings(text1, text2);
    auto endTime = chrono::high_resolution_clock::now();
    auto elapsedTime = chrono::duration_cast<chrono::nanoseconds>(endTime - startTime);
    
    cout << "Comparando text1 y text2: " << (resultado1 ? "Iguales" : "Diferentes") << endl;
    cout << "Tiempo de ejecucion: " << elapsedTime.count() << " nanosegundos\n\n"; // no corre esta linea


    // medir el tiempo de comparación entre text1 y text3
    startTime = chrono::high_resolution_clock::now();
    bool resultado2 = comparar_strings(text1, text3);
    endTime = chrono::high_resolution_clock::now();
    elapsedTime = chrono::duration_cast<chrono::nanoseconds>(endTime - startTime);

    cout << "Comparando text1 y text3: " << (resultado2 ? "Iguales " : "Diferentes ") << endl;
    cout << "Tiempo de ejecucion: " << elapsedTime.count() << " nanosegundos\n"; // no corre esta linea

    return 0;
}