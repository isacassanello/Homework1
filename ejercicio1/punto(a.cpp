#include <iostream>
using namespace std;

void crearMatriz(int n){
    int matriz[n][n];
    int valor = 1;

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            matriz[i][j] = valor++;
        }
    }

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
}

int main(){
    int n;
    cout << "Ingresar un valor de n: ";
    cin >> n;

    if (n<= 1){
        cout << "El valor a ingresar debe ser mayor a 1" << endl;
        return 1;
    }

    crearMatriz(n);

    return 0;
}