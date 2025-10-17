#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

int* ids = nullptr;
double* pesos = nullptr;
string* destinos = nullptr;
int* prioridades = nullptr;
char* estados = nullptr;

int capacidad = 50;
int totalPaquetes = 0;
int indiceFrenteCola = 0;

void inicializarSistema() {
    ids = new int[capacidad];
    pesos = new double[capacidad];
    destinos = new string[capacidad];
    prioridades = new int[capacidad];
    estados = new char[capacidad];
    
    cout << "--- Sistema de Despacho Logístico MegaEnvío (Modo Punteros) ---\n\n";
    cout << "Inicializando sistema con capacidad para " << capacidad << " paquetes...\n";
    cout << "Capacidad actual: " << capacidad << ". Paquetes en cola: 0.\n\n";
}

void expandirCapacidad() {
    int nuevaCapacidad = capacidad * 2;
    
    int* nuevosIds = new int[nuevaCapacidad];
    double* nuevosPesos = new double[nuevaCapacidad];
    string* nuevosDestinos = new string[nuevaCapacidad];
    int* nuevasPrioridades = new int[nuevaCapacidad];
    char* nuevosEstados = new char[nuevaCapacidad];
    
    for (int i = 0; i < totalPaquetes; i++) {
        nuevosIds[i] = ids[i];
        nuevosPesos[i] = pesos[i];
        nuevosDestinos[i] = destinos[i];
        nuevasPrioridades[i] = prioridades[i];
        nuevosEstados[i] = estados[i];
    }
    
    delete[] ids;
    delete[] pesos;
    delete[] destinos;
    delete[] prioridades;
    delete[] estados;
    
    ids = nuevosIds;
    pesos = nuevosPesos;
    destinos = nuevosDestinos;
    prioridades = nuevasPrioridades;
    estados = nuevosEstados;
    
    capacidad = nuevaCapacidad;
    
    cout << "Capacidad expandida a " << capacidad << " paquetes.\n";
}

void agregarPaquete() {
    if (totalPaquetes >= capacidad) {
        expandirCapacidad();
    }
    
    int id, prioridad;
    double peso;
    string destino;
    
    cout << "Ingrese ID: ";
    cin >> id;
    
    cout << "Ingrese Peso (kg): ";
    cin >> peso;
    
    cout << "Ingrese Destino: ";
    cin.ignore();
    getline(cin, destino);
    
    cout << "Ingrese Prioridad (1-3): ";
    cin >> prioridad;
    
    ids[totalPaquetes] = id;
    pesos[totalPaquetes] = peso;
    destinos[totalPaquetes] = destino;
    prioridades[totalPaquetes] = prioridad;
    estados[totalPaquetes] = 'E';
    
    totalPaquetes++;
    
    cout << "Paquete " << id << " encolado. Capacidad utilizada: " 
         << totalPaquetes << "/" << capacidad << ".\n";
}

void despacharPaquete() {
    bool encontrado = false;
    
    for (int i = indiceFrenteCola; i < totalPaquetes; i++) {
        if (estados[i] == 'E') {
            cout << "Despachando paquete...\n";
            cout << "Paquete " << ids[i] << " despachado con éxito. Estado: 'D'.\n";
            estados[i] = 'D';
            indiceFrenteCola = i + 1;
            encontrado = true;
            break;
        }
    }
    
    if (!encontrado) {
        cout << "No hay paquetes en cola para despachar.\n";
    }
}

void inspeccionarFrenteCola() {
    bool encontrado = false;
    
    for (int i = indiceFrenteCola; i < totalPaquetes; i++) {
        if (estados[i] == 'E') {
            cout << "Frente de la cola:\n";
            cout << "  ID: " << ids[i] << " | Peso: " << pesos[i] << " kg | Destino: " 
                 << destinos[i] << " | Prioridad: ";
            
            if (prioridades[i] == 1) cout << "Alta\n";
            else if (prioridades[i] == 2) cout << "Media\n";
            else cout << "Baja\n";
            
            encontrado = true;
            break;
        }
    }
    
    if (!encontrado) {
        cout << "No hay paquetes en cola.\n";
    }
}

void reportePorDestino() {
    string destinoBuscado;
    cout << "Ingrese el destino para el reporte: ";
    cin.ignore();
    getline(cin, destinoBuscado);
    
    int contador = 0;
    double sumaPesos = 0.0;
    
    for (int i = 0; i < totalPaquetes; i++) {
        if (estados[i] == 'E' && destinos[i] == destinoBuscado) {
            contador++;
            sumaPesos += pesos[i];
        }
    }
    
    cout << "Reporte para destino '" << destinoBuscado << "':\n";
    cout << "  Paquetes En Cola: " << contador << "\n";
    
    if (contador > 0) {
        double promedio = sumaPesos / contador;
        cout << fixed << setprecision(2);
        cout << "  Peso Promedio: " << promedio << " kg\n";
    } else {
        cout << "  Peso Promedio: 0.00 kg\n";
    }
}

void liberarMemoria() {
    cout << "Liberando " << capacidad << " bloques de memoria asignada...\n";
    
    delete[] ids;
    delete[] pesos;
    delete[] destinos;
    delete[] prioridades;
    delete[] estados;
    
    ids = nullptr;
    pesos = nullptr;
    destinos = nullptr;
    prioridades = nullptr;
    estados = nullptr;
    
    cout << "Sistema cerrado. ¡Memoria libre!\n";
}

int main() {
    inicializarSistema();
    
    int opcion;
    do {
        cout << "\nSeleccione una operación:\n";
        cout << "1. Agregar Paquete (Encolar)\n";
        cout << "2. Despachar Paquete (Desencolar)\n";
        cout << "3. Inspeccionar Frente de Cola\n";
        cout << "4. Reporte por Destino\n";
        cout << "5. Salir (Liberar Memoria)\n";
        cout << "\nOpción seleccionada: ";
        cin >> opcion;
        cout << "\n";
        
        switch (opcion) {
            case 1:
                agregarPaquete();
                break;
            case 2:
                despacharPaquete();
                break;
            case 3:
                inspeccionarFrenteCola();
                break;
            case 4:
                reportePorDestino();
                break;
            case 5:
                liberarMemoria();
                break;
            default:
                cout << "Opción inválida. Intente de nuevo.\n";
        }
    } while (opcion != 5);
    
    return 0;
}