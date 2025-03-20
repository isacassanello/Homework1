#include <iostream>
#include <fstream>
#include <stdexcept> // libreria para manejo de excepciones (errores en tiempo de ejecucion)
using namespace std;

enum nivelSeguridad {DEBUG = 1, INFO, WARNING, ERROR, CRITICAL, TEST, SECURITY};
// Defino cada nivel con un numero para que se puedan representar con ese valor numerico. Esto me sirve cuando el usuario ingresa por consola qué nivel de seguridad quiere usar


// Punto a - Funcion para registrar eventos en un archivo de log, asignandoles una etiqueta segun su nivel de seguridad
void logMensaje(string msj, nivelSeguridad nivel){
    ofstream archivo_log("log.txt", ios::app);

    if (!archivo_log){
        cerr << "Error al abrir los archivos" << endl;
        return;
    }

    // asigno la etiqueta correspondiente al nivel de seguridad proporcionado
    string etiqueta;
    switch (nivel){
        case nivelSeguridad::DEBUG: etiqueta = "[DEBUG]"; break;
        case nivelSeguridad::INFO: etiqueta = "[INFO]"; break;
        case nivelSeguridad::WARNING: etiqueta = "[WARNING]"; break;
        case nivelSeguridad::ERROR: etiqueta = "[ERROR]"; break;
        case nivelSeguridad::CRITICAL: etiqueta = "[CRITICAL]"; break;
        case nivelSeguridad::TEST: etiqueta = "[TEST]"; break; // nivel de seguridad personalizado
        case nivelSeguridad::SECURITY: break; // manejo SECURITY sin etiqueta asignada para que no salte un warning en la compilacion
    }

    archivo_log << etiqueta << " <" << msj << ">" << endl;

    archivo_log.close();
}


// Punto b - Funcion para registrar errores en el log, incluyendo detalles sobre el archivo y la línea donde ocurrio
void logMensaje(string msj_de_error, string archivo, int linea) {
    ofstream archivo_log("log.txt", ios::app);

    if (!archivo_log){
        cerr << "Error al abrir los archivos" << endl;
        return;
    }

    archivo_log << "[ERROR]\n  ->Mensaje de error: " << msj_de_error << "> \n  ->Archivo: " << archivo << "\n  ->Linea: " << linea << endl;
    archivo_log.close();
}


// Funcion para registrar eventos de seguridad, incluyendo un acceso de usuario y el mensaje de acceso
void logMensaje(string msj_de_acceso, string usuario){
    ofstream archivo_log("log.txt", ios::app);

    if (!archivo_log){
        cerr << "Error al abrir los archivos" << endl;
        return;
    }

    archivo_log << "[SECURITY]\n  ->Usuario: " << usuario << "\n  ->Mensaje de acceso: " << msj_de_acceso << endl;
    archivo_log.close();
}


int main() {
    int opcion, agregar_detalles, linea; 
    /*
        - opcion: numero que ingresa el usuario por la terminal para seleccionar qué nivel de seguridad desea usar, o si prefiere forzar un error, o salir del programa
        - agregar_detalles: para determinar que funcion logMensaje usar cuando se selecciona el nivel de seguridad ERROR
        - linea: numero de linea en el que se declara el error cuando se selecciona el nivel de seguridad ERROR
    */
    string msj, archivo, usuario; 
    /*
        - msj: mensaje que ingresa el usuario por terminal para los niveles de seguridad
        - archivo: archivo que declara el usuario cuando se quieren registrar errores (en la seleccion del nivel de seguridad ERROR)
        - usuario: para registrar un mensaje de “Acceso de Usuario” (en la seleccion del nivel de seguridad SECURITY)
    */

    while (true){
        cout << "Seleccione un nivel de seguridad (el numero):\n    1) DEBUG\n    2) INFO\n    3) WARNING\n    4) ERROR\n    5) CRITICAL\n    6) TEST\n    7) SECURITY\n    8) Forzar un error\n    9) Salir\n";
        cout << "Opcion: ";
        cin >> opcion; // asumo que el usuario ingresa un int y no otra variable tipo string, char, etc
        cin.ignore();

        // caso: Salir
        if (opcion == 9){
            cout << "Saliendo del programa" << endl; break;
        }

        // caso: forzar un error
        if (opcion == 8){
            try {
                throw runtime_error("Se ha producido un error en el sistema");
            } catch (const exception &e) {
                logMensaje(e.what(), __FILE__, __LINE__); 
                cerr << "Error crítico detectado. Revise el log" << endl;
                return 1; 
            }
        }
        
        // reviso si la opcion ingresada es valida
        if (opcion < 1 || opcion > 7){
            cout << "Nivel de seguridad inexistente. Ingrese nuevamente\n";
            continue;
        }
        
         // caso: ERROR -> manejo especial ya que puede usar 2 funciones de logMensaje
        if (opcion == 4){
            cout << "¿Desea ingresar detalles del archivo y línea? (si = 0 | no = 1): "; // asumo que el usuario ingresa 0 o 1 y no otro numero u otra variable
            cin >> agregar_detalles;
            cin.ignore();

            if (agregar_detalles == 0){
                cout << "Indique el mensaje de error: ";
                getline(cin, msj);

                cout << "Indique en qué archivo donde se encuentra el error: ";
                getline(cin, archivo);

                cout << "Indique la linea donde se encuentra el error dentro del archivo: ";
                cin >> linea; // asumo que ingresa un numero
                cin.ignore();

                logMensaje(msj, archivo, linea);

            } else {
                cout << "Indique el mensaje de error: ";
                getline(cin, msj);

                logMensaje(msj, static_cast<nivelSeguridad>(opcion));
            }

        // caso: SECURITY
        } else if (opcion == 7){
            cout << "Ingrese su nombre de usuario: ";
            getline(cin, usuario);

            cout << "Ingrese el mensaje de acceso: ";
            getline(cin, msj);

            logMensaje(msj, usuario);
        
        // casos: el resto de los niveles de seguridad
        } else {
            cout << "Ingrese el mensaje: ";
            getline(cin, msj);

            logMensaje(msj, static_cast<nivelSeguridad>(opcion));
        }
    }
    cout << "Mensajes de log registrados en 'log.txt'" << endl;

    return 0;
}