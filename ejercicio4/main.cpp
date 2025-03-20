#include <iostream>
#include <chrono>
using namespace std;

// Punto a - Funcion recursiva para comparar dos strings (en tiempo de ejecucion)
// Elijo char* ya que string no es compatible con constxpr, lo que uso en el item c para analizar el tiempo de compilacion
bool comparar_strings(const char* str1, const char* str2){
    
    if (*str1 == '\0' && *str2 == '\0') return true; // si ambos punteros apuntan al final del string
    
    if (*str1 != *str2) return false;

    return comparar_strings(str1 + 1, str2 + 1); // los caracteres avanzan en simultaneo
}

// Punto c - Funcion recursiva para comparar dos strings (en tiempo de compilacion con constexpr)
// Uso constexpr porque fuerza al compilador a realizar la comparacion en la fase de compilacion en lugar de ejecucion
// misma logica que la funcion del punto a
constexpr bool comparar_constexpr(const char* str1, const char* str2){
   if (*str1 == '\0' && *str2 == '\0') return true;
    
   if (*str1 != *str2) return false;

   return comparar_constexpr(str1 + 1, str2 + 1);
}

int main(){
    const char text1[] = "Estoy probando el cuarto punto del Homework de la materia Paradigmas de la Programacion, ojala que este bien";
    const char text2[] = "Estoy probando el cuarto punto del Homework de la materia Paradigmas de la Programacion, ojala que este bien";
    const char text3[] = "Estoy probando el cuarto punto del Homework de la materia Paradigmas de la Programacion";

    cout << "==================== COMPARACION EN TIEMPO DE EJECUCION ====================\n";

    // punto b - medir el tiempo de comparación entre text1 y text2
    auto startTime = chrono::high_resolution_clock::now();
    bool resultado1 = comparar_strings(text1, text2);
    auto endTime = chrono::high_resolution_clock::now();
    auto elapsedTime = chrono::duration_cast<chrono::nanoseconds>(endTime - startTime);
    
    cout << "Comparando text1 y text2: " << (resultado1 ? "Iguales" : "Diferentes") << endl; 
    /*
    resultado1 es un tipo bool, entonces si resultado1 == 1 (true) devuelve el string antes del : , osea "Iguales"
                                         si resultado1 == 0 (false) devuelve el string despues del : , osea "Diferentes"
    */
    cout << "Tiempo de ejecucion: " << elapsedTime.count() << " nanosegundos\n\n"; 

    // punto b - medir el tiempo de comparación entre text1 y text3
    startTime = chrono::high_resolution_clock::now();
    bool resultado2 = comparar_strings(text1, text3);
    endTime = chrono::high_resolution_clock::now();
    elapsedTime = chrono::duration_cast<chrono::nanoseconds>(endTime - startTime);

    cout << "Comparando text1 y text3: " << (resultado2 ? "Iguales " : "Diferentes ") << endl;
    cout << "Tiempo de ejecucion: " << elapsedTime.count() << " nanosegundos\n"; 

    cout << "\n================= COMPARACION EN TIEMPO DE COMPILACION =================\n";

    // punto c - comparacion en tiempo de compilacion con constexpr
    constexpr const char text1_constexpr[] = "Estoy probando el cuarto punto del Homework de la materia Paradigmas de la Programacion, ojala que este bien";
    constexpr const char text2_constexpr[] = "Estoy probando el cuarto punto del Homework de la materia Paradigmas de la Programacion, ojala que este bien";
    constexpr const char text3_constexpr[] = "Estoy probando el cuarto punto del Homework de la materia Paradigmas de la Programacion";

    startTime = chrono::high_resolution_clock::now();
    constexpr bool resultado_constexpr1 = comparar_constexpr(text1_constexpr, text2_constexpr);
    endTime = chrono::high_resolution_clock::now();
    elapsedTime = chrono::duration_cast<chrono::nanoseconds>(endTime - startTime);

    cout << "Comparacion en tiempo de compilacion (text1 vs text2): " << (resultado_constexpr1 ? "Iguales" : "Diferentes") << endl;
    cout << "Tiempo de ejecucion: " << elapsedTime.count() << " nanosegundos\n\n";

    startTime = chrono::high_resolution_clock::now();
    constexpr bool resultado_constexpr2 = comparar_constexpr(text1_constexpr, text3_constexpr);
    endTime = chrono::high_resolution_clock::now();
    elapsedTime = chrono::duration_cast<chrono::nanoseconds>(endTime - startTime);

    cout << "Comparacion en tiempo de compilacion (text1 vs text3): " << (resultado_constexpr2 ? "Iguales" : "Diferentes") << endl;
    cout << "Tiempo de ejecucion: " << elapsedTime.count() << " nanosegundos\n";

    cout << "===========================================================================\n";

    return 0;
}

/*
====================== CONCLUSIÓN ======================
Diferencia entre tiempo de ejecucion y tiempo de compilacion:
    - La comparacion en tiempo de ejecucion (comparar_strings) evalua los textos en cada ejecucion del programa
    - La comparacion en tiempo de compilacion (comparar_constexpr) es resuelta por el compilador antes de que el programa corra

Eficiencia:
    - En compilacion, el resultado ya esta disponible y no consume tiempo de ejecución, es por eso que es mas rapida
    - En ejecucion, la funcion debe recorrer cada caracter en cada comparacion

Conclusión:
    - La version con 'constexpr' es mas rapida porque el resultado ya se conoce en la fase de compilacion
*/