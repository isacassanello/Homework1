#include <iostream>
#include <fstream>
using namespace std;

enum nivelSeguridad {DEBUG = 1, INFO, WARNING, ERROR, CRITICAL, SECURITY};

// Punto a
void logMessage(string msg, nivelSeguridad nivel){
    ofstream archivo_log("log.txt", ios::app);

    if (!archivo_log){
        cerr << "Error al abrir los archivos" << endl;
        return;
    }

    string etiqueta;
    switch (nivel){
        case nivelSeguridad::DEBUG: etiqueta = "[DEBUG]"; break;
        case nivelSeguridad::INFO: etiqueta = "[INFO]"; break;
        case nivelSeguridad::WARNING: etiqueta = "[WARNING]"; break;
        case nivelSeguridad::ERROR: etiqueta = "[ERROR]"; break;
        case nivelSeguridad::CRITICAL: etiqueta = "[CRITICAL]"; break;
    }

    archivo_log << etiqueta << " <" << msg << ">" << endl;

    archivo_log.close();
}

// Punto b
void logMessage(string msg_de_error, string archivo, int linea) {
    ofstream archivo_log("log.txt", ios::app);

    if (!archivo_log){
        cerr << "Error al abrir los archivos" << endl;
        return;
    }

    archivo_log << "[ERROR]\n  ->Mensaje de error: " << msg_de_error << "> \n  ->Archivo: " << archivo << "\n  ->Linea: " << linea << endl;
    archivo_log.close();
}

void logMessage(string msg_de_acceso, string usuario){
    ofstream archivo_log("log.txt", ios::app);

    if (!archivo_log){
        cerr << "Error al abrir los archivos" << endl;
        return;
    }

    archivo_log << "[SECURITY]\n  ->Usuario: " << usuario << "\n  ->Mensaje de acceso: " << msg_de_acceso << endl;
    archivo_log.close();
}

// Funcion para que el usuario ingrese por la terminal el nivel de seguridad y sus derivados
void ingresarMensajes(){
    int opcion; 
    string msg, archivo, usuario;
    int linea;

    while (true){
        cout << "Seleccione un nivel de seguridad (el numero):\n    1) DEBUG\n    2) INFO\n    3) WARNING\n    4) ERROR\n    5) CRITICAL\n    6) SECURITY\n    7) Salir\n";
        cout << "Opcion: ";
        cin >> opcion;
        cin.ignore();

        if (opcion == 7){
            cout << "Saliendo del programa." << endl; break;
        }

        if (opcion < 1 || opcion > 6){
            cout << "Nivel de seguridad inexistente. Ingrese nuevamente\n";
            continue;
        }

        if (opcion == 4){
            cout << "Indique el mensaje de error: ";
            getline(cin, msg);

            cout << "Indique en qué archivo donde se encuentra el error: ";
            getline(cin, archivo);

            cout << "Indique la linea donde se encuentra el error dentro del archivo: ";
            cin >> linea;
            cin.ignore();

            logMessage(msg, archivo, linea);
        
        } else if (opcion == 6){
            cout << "Ingrese su nombre de usuario: ";
            getline(cin, usuario);

            cout << "Ingrese el mensaje de acceso: ";
            getline(cin, msg);

            logMessage(msg, usuario);
        
        } else {
            cout << "Ingrese el mensaje: ";
            getline(cin, msg);

            logMessage(msg, static_cast<nivelSeguridad>(opcion));
        }
    }
}



int main() {
    ingresarMensajes();
    cout << "Mensajes de log registrados en 'log.txt'" << endl;
    return 0;
}
