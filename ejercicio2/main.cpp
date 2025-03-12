#include <iostream>
#include <fstream>
using namespace std;

enum nivelSeguridad {DEBUG, INFO, WARNING, ERROR, CRITICAL, SECURITY};

// punto a
void logMessage(string msg, nivelSeguridad nivel){
    ofstream archivo_log("log.txt", ios::app);

    if (!archivo_log){
        cerr << "error al abrir los archivos" << endl;
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

// punto b
void logMessage(string msg_de_error, string archivo, int linea) {
    ofstream archivo_log("log.txt", ios::app);

    if (!archivo_log){
        cerr << "error al abrir los archivos" << endl;
        return;
    }

    archivo_log << "[ERROR] <" << msg_de_error << "> \n  ->Archivo: " << archivo << "\n  ->Linea: " << linea << endl;
    archivo_log.close();
}

void logMessage(string msg_de_acceso, string usuario){
    ofstream archivo_log("log.txt", ios::app);

    if (!archivo_log){
        cerr << "error al abrir los archivos" << endl;
        return;
    }

    archivo_log << "[SECURITY] Usuario: " << usuario << " - " << msg_de_acceso << endl;
    archivo_log.close();
}



int main() {
    // Pruebas de las diferentes funcionalidades de log
    logMessage("Inicializando sistema...", INFO);
    logMessage("Conectando a la base de datos...", DEBUG);
    logMessage("Advertencia: Uso de memoria alto", WARNING);
    logMessage("Error en módulo de autenticación", "auth.cpp", 45);
    logMessage("Acceso permitido", "usuario123", SECURITY);
    logMessage("Acceso denegado", "usuario456", SECURITY);
 

    cout << "Mensajes de log registrados en 'log.txt'" << endl;
    return 0;
}
