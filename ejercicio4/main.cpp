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
   // si ambos punteros apuntan al final 
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
Elijo char* ya que string no es un tipo constxpr, lo que uso en el ejercicio c para analizar el tiempo de compilacion
*/