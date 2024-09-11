#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <chrono>

using namespace std;

// Función para Selection Sort
void selectionSort(vector<int>& vec, int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (vec[j] < vec[min_idx])
                min_idx = j;
        }
        if (min_idx != i)
            swap(vec[min_idx], vec[i]);
    }
}

// Función para guardar el arreglo ordenado en un archivo
void saveArrayToFile(const vector<int>& vec, const string& filename) {
    ofstream archivo("../DataSets/arreglos/" + filename + ".txt");
    if (archivo.is_open()) {
        for (int num : vec) {
            archivo << num << endl;
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo para guardar." << endl;
    }
}

// Prueba de la función
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

    if (ordenar) {
        auto start = chrono::high_resolution_clock::now();
        selectionSort(numeros, tamano);
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


// Base del código sacada de:
// rathbhupendra. (n.d.). *C++ program for implementation of selection sort*. GeeksforGeeks. https://www.geeksforgeeks.org/selection-sort-algorithm-2/
// Fue modificado para abrir y procesar archivos .txt y trabajar con vectores en vez de arreglos.
