#include <iostream>
using namespace std;

// Funcion para crear una matriz cuadrada de tamaño nxn y llenarla de valores consecutivos
int** crearMatriz(int n){
    int** matriz = new int*[n]; // crea un arreglo de punteros para las filas
    if (!matriz) { 
        cerr << "Error: No se pudo asignar memoria para la matriz" << endl;
        return nullptr;
    }
    
    int valor = 1; // valor inicial del contador para llenar la matriz con valores consecutivos

    for (int i = 0; i < n; i++){ // bucle para recorrer cada fila
        matriz[i] = new int[n]; // asigno memoria para cada fila
        if (!matriz[i]) { 
            cerr << "Error: No se pudo asignar memoria para la fila" << endl;
            return nullptr;
        }
        
        for (int j = 0; j < n; j++){ // bucle para recorrer cada columna dentro de la fila
            matriz[i][j] = valor++; // asigno los valores consecutivos 
        }
    }

    return matriz;
}

// Funcion para imprimir la matriz en orden descendente, arrancando desde la posicion de la ultima fila y la ultima columna hasta las primeras
void imprimirMatrizDescendente(int n, int** matriz){
    cout << "\nMatriz en orden descendiente:\n";
    for (int i = n * n - 1; i >= 0; i--){ // bucle que recorre la matriz de atras hacia adelante (del ultimo elemento al primero)
        int fila = i / n; // como n es el numero de columnas, la division entera i/n me da la fila
        int col = i % n; // i % n da el resto de la division, lo que corresponde a la columna
        cout << "M[" << fila << "][" << col << "] = " << matriz[fila][col] << endl; 
    }
}

int main(){
    int n;
    cout << "Ingresar un valor de n: ";
    cin >> n;

    if (n <= 1){
        cout << "El valor a ingresar debe ser mayor a 1" << endl;
        return 1;
    }

    int** matriz = crearMatriz(n);
    if (!matriz) return 1;
    imprimirMatrizDescendente(n, matriz);

    for (int i = 0; i < n; i++) {
        delete[] matriz[i]; // liberar cada fila de la matriz
    }
    delete[] matriz; // liberar el arreglo de punteros

    return 0;
}