#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;

// Función para guardar el vector ordenado en un archivo
void saveArrayToFile(const vector<int>& arr, const string& filename) {
    ofstream archivo("../DataSets/arreglos/" + filename + ".txt");
    if (archivo.is_open()) {
        for (int num : arr) {
            archivo << num << endl;
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo para guardar." << endl;
    }
}


int main() {
    vector<int> numeros;
    int numero;
    size_t tamano;

    // Elegir el conjunto de datos a ordenar
    int eleccion;
    cout << "Elija el DataSet a ordenar" << endl;
    cout << "(1) Lista aleatoria, (2) Lista semiordenada o (3) Lista parcialmente ordenada" << endl;
    cin >> eleccion;

    string archivoSalida;
    cout << "Ingrese el nombre del archivo para guardar la lista ordenada (ej. resultado): " << endl;
    cin >> archivoSalida;

    bool ordenar = false;

    // Abrir y guardar contenido de archivo txt seleccionado
    switch (eleccion) {
    case 1: {
        ifstream archivo("../DataSets/arreglos/random_generate.txt");

        while (archivo >> numero) {
            numeros.push_back(numero);
        }
        archivo.close();
        tamano = numeros.size();
        ordenar = true;
        break;
    }

    case 2: {
        ifstream archivo("../DataSets/arreglos/semiorder.txt");

        while (archivo >> numero) {
            numeros.push_back(numero);
        }
        archivo.close();
        tamano = numeros.size();
        ordenar = true;
        break;
    }
    
    case 3: {
        ifstream archivo("../DataSets/arreglos/partially.txt");

        while (archivo >> numero) {
            numeros.push_back(numero);
        }
        archivo.close();
        tamano = numeros.size();
        ordenar = true;
        break;
    }

    default:
        cout << "Opcion no valida." << endl;
        break;
    }    
    
    if (ordenar == true) { 
        auto start = chrono::high_resolution_clock::now();
        sort(numeros.begin(), numeros.end());
        auto end = chrono::high_resolution_clock::now();

        // Medir la duración en milisegundos
        chrono::duration<double, milli> duration_ms = end - start;
    
        // Mostrar el tiempo de ejecución en milisegundos
        cout << " " << endl;
        cout << "Tiempo de ejecucion del algoritmo: " << duration_ms.count() << " milisegundos" << endl;
        cout << " " << endl;

        // Guardar el arreglo ordenado en el archivo especificado
        saveArrayToFile(numeros, archivoSalida);
        cout << "Lista ordenada guardada en el archivo: " << archivoSalida << ".txt" << endl;
    }
    return 0;
}
