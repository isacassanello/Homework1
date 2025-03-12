#include <iostream>
using namespace std;

int** crearMatriz(int n){
    int** matriz = new int*[n];
    int valor = 1;

    for (int i = 0; i < n; i++){
        matriz[i] = new int[n];
        for (int j = 0; j < n; j++){
            matriz[i][j] = valor++;
        }
    }

    return matriz;
}

void imprimirMatrizDescendente(int n, int** matriz){
    cout << "\nMatriz en orden descendiente:\n";
    for (int i = n * n - 1; i >= 0; i--){
        int fila = i / n;
        int col = i % n;
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
    imprimirMatrizDescendente(n, matriz);

    for (int i = 0; i < n; i++) {
        delete[] matriz[i];
    }
    delete[] matriz;

    return 0;
}