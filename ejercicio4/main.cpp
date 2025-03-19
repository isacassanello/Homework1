#include <iostream>
#include <chrono>
using namespace std;

// Punto a - funcion recursiva para comparar dos strings (en tiempo de ejecucion)
bool comparar_strings(const char* str1, const char* str2){
    // si ambos punteros apuntan al final 
    if (*str1 == '\0' && *str2 == '\0') return true;
    
    if (*str1 != *str2) return false;

    return comparar_strings(str1 + 1, str2 + 1);
}

// Punto c - Comparacion en tiempo de compilacion con constexpr
// Usa constexpr para realizar la comparacion en tiempo de compilacion
constexpr bool comparar_constexpr(const char* str1, const char* str2){
    return (str1 == str2) ? (*str1 == '\0' || comparar_constexpr(str1 + 1, str2 + 1)) : false;
    // (str1 == str2) compara el primer caracter de str1 con el primer caracter de str2
    // si son distintos, la función devuelve false (esto se maneja en la parte del : false)
    // si son iguales, entonces se pasa a la siguiente parte de la expresión condicional
    // si se llego al final de la cadena (el caracter nulo \0), significa que ambas cadenas eran iguales hasta el final, por lo que devuelve true
    // si no hemos llegado al final (\0), se llama recursivamente a la misma función para comparar los siguientes caracteres (str1 + 1 y str2 + 1)
}

int main(){
    const char* text1 = "La programacion en C++ es poderosa y permite optimizaciones increibles";
    const char* text2 = "La programacion en C++ es poderosa y permite optimizaciones increibles";
    const char* text3 = "La programacion en C++ es flexible y permite optimizaciones increibles";

    cout << "==================== COMPARACION EN TIEMPO DE EJECUCION ====================\n";

    // punto b - medir el tiempo de comparación entre text1 y text2
    auto startTime = chrono::high_resolution_clock::now();
    bool resultado1 = comparar_strings(text1, text2);
    auto endTime = chrono::high_resolution_clock::now();
    auto elapsedTime = chrono::duration_cast<chrono::nanoseconds>(endTime - startTime);
    
    cout << "Comparando text1 y text2: " << (resultado1 ? "Iguales" : "Diferentes") << endl;
    cout << "Tiempo de ejecucion: " << elapsedTime.count() << " nanosegundos\n\n"; // no corre esta linea

    // punto b - medir el tiempo de comparación entre text1 y text3
    startTime = chrono::high_resolution_clock::now();
    bool resultado2 = comparar_strings(text1, text3);
    endTime = chrono::high_resolution_clock::now();
    elapsedTime = chrono::duration_cast<chrono::nanoseconds>(endTime - startTime);

    cout << "Comparando text1 y text3: " << (resultado2 ? "Iguales " : "Diferentes ") << endl;
    cout << "Tiempo de ejecucion: " << elapsedTime.count() << " nanosegundos\n"; // no corre esta linea

    cout << "\n================= COMPARACION EN TIEMPO DE COMPILACION =================\n";

    // punto c - comparacion en tiempo de compilacion con constexpr
    constexpr const char* text1_constexpr = "La programacion en C++ es poderosa y permite optimizaciones increibles";
    constexpr const char* text2_constexpr = "La programacion en C++ es poderosa y permite optimizaciones increibles";
    constexpr const char* text3_constexpr = "La programacion en C++ es flexible y permite optimizaciones increibles";

    constexpr bool resultado_constexpr1 = comparar_constexpr(text1_constexpr, text2_constexpr);
    constexpr bool resultado_constexpr2 = comparar_constexpr(text1_constexpr, text3_constexpr);

    startTime = chrono::high_resolution_clock::now();
    bool resultado_constexpr_runtime1 = resultado_constexpr1;
    endTime = chrono::high_resolution_clock::now();
    elapsedTime = chrono::duration_cast<chrono::nanoseconds>(endTime - startTime);

    cout << "Comparacion en tiempo de compilacion (text1 vs text2): " << (resultado_constexpr_runtime1 ? "Iguales" : "Diferentes") << endl;
    cout << "Tiempo de ejecucion: " << elapsedTime.count() << " nanosegundos\n\n";

    startTime = chrono::high_resolution_clock::now();
    bool resultado_constexpr_runtime2 = resultado_constexpr2;
    endTime = chrono::high_resolution_clock::now();
    elapsedTime = chrono::duration_cast<chrono::nanoseconds>(endTime - startTime);

    cout << "Comparacion en tiempo de compilacion (text1 vs text3): " << (resultado_constexpr_runtime2 ? "Iguales" : "Diferentes") << endl;
    cout << "Tiempo de ejecucion: " << elapsedTime.count() << " nanosegundos\n";

    cout << "===========================================================================\n";

    return 0;
}

/*
CONCLUSION
    - la version en tiempo de ejecucion (punto b) mide el tiempo real de comparacion de los strings y depende de la longitud del texto
    - la version en tiempo de compilacion (punto c) preevalua el resultado en la fase de compilación, eliminando el costo en tiempo de ejecucion
    - la diferencia clave es que el compilador ya conoce el resultado en la versión `constexpr`, por lo que su tiempo de ejecucion es casi nulo
*/

/*
Elijo char* ya que string no es un tipo constxpr, lo que uso en el ejercicio c para analizar el tiempo de compilacion
*/