#include <iostream>
#include <fstream>
#include <stdexcept>
using namespace std;

enum nivelSeguridad {DEBUG = 1, INFO, WARNING, ERROR, CRITICAL, TEST, SECURITY};

// Punto a
void logMensaje(string msj, nivelSeguridad nivel){
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
        case nivelSeguridad::TEST: etiqueta = "[TEST]"; break; // nivel de seguridad personalizado
        case nivelSeguridad::SECURITY: break; // pongo esto solo para que no me salte un warning en la compilacion
    }

    archivo_log << etiqueta << " <" << msj << ">" << endl;

    archivo_log.close();
}

// Punto b
void logMensaje(string msj_de_error, string archivo, int linea) {
    ofstream archivo_log("log.txt", ios::app);

    if (!archivo_log){
        cerr << "Error al abrir los archivos" << endl;
        return;
    }

    archivo_log << "[ERROR]\n  ->Mensaje de error: " << msj_de_error << "> \n  ->Archivo: " << archivo << "\n  ->Linea: " << linea << endl;
    archivo_log.close();
}

void logMensaje(string msj_de_acceso, string usuario){
    ofstream archivo_log("log.txt", ios::app);

    if (!archivo_log){
        cerr << "Error al abrir los archivos" << endl;
        return;
    }

    archivo_log << "[SECURITY]\n  ->Usuario: " << usuario << "\n  ->Mensaje de acceso: " << msj_de_acceso << endl;
    archivo_log.close();
}

// Funcion para limpiar la entrada si el usuario ingresa algo invalido
void limpiarBuffer() {
    cin.clear(); // restablece el estado de cin en caso de error
    string basura;
    getline(cin, basura); // Consume la línea incorrecta para evitar loops infinitos
}


int main() {
    int opcion, linea, agregar_detalles; 
    string msj, archivo, usuario;

    while (true){
        cout << "Seleccione un nivel de seguridad (el numero):\n    1) DEBUG\n    2) INFO\n    3) WARNING\n    4) ERROR\n    5) CRITICAL\n    6) TEST\n    7) SECURITY\n    8) Simular error\n    9) Salir\n";
        cout << "Opcion: ";
        cin >> opcion;
        cin.ignore();
        // asumo que el usuario ingresa un int y no otra variable tipo string, char, etc

        if (opcion == 9){
            cout << "Saliendo del programa." << endl; break;
        }

        if (opcion == 8){
            try {
                throw runtime_error("Se ha producido un error en el sistema");
            } catch (const exception &e) {
                logMensaje(e.what(), __FILE__, __LINE__); 
                cerr << "Error crítico detectado. Revise el log." << endl;
                return 1; 
            }
        }
        
        if (opcion < 1 || opcion > 7){
            cout << "Nivel de seguridad inexistente. Ingrese nuevamente\n";
            continue;
        }

        if (opcion == 4){
            cout << "¿Desea ingresar detalles del archivo y línea? (si = 0 | no = 1): "; 
            // asumo que el usuario ingresa 0 o 1 y no otro numero u otra variable
            cin >> agregar_detalles;
            cin.ignore();

            if (agregar_detalles == 0){
                cout << "Indique el mensaje de error: ";
                getline(cin, msj);

                cout << "Indique en qué archivo donde se encuentra el error: ";
                getline(cin, archivo);

                cout << "Indique la linea donde se encuentra el error dentro del archivo: ";
                cin >> linea;
                cin.ignore();

                logMensaje(msj, archivo, linea);

            } else {
                cout << "Indique el mensaje de error: ";
                getline(cin, msj);

                logMensaje(msj, static_cast<nivelSeguridad>(opcion));
            }

        } else if (opcion == 7){
            cout << "Ingrese su nombre de usuario: ";
            getline(cin, usuario);

            cout << "Ingrese el mensaje de acceso: ";
            getline(cin, msj);

            logMensaje(msj, usuario);
        
        } else {
            cout << "Ingrese el mensaje: ";
            getline(cin, msj);

            logMensaje(msj, static_cast<nivelSeguridad>(opcion));
        }
    }
    cout << "Mensajes de log registrados en 'log.txt'" << endl;

    return 0;
}