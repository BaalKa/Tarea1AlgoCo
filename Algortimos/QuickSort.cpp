#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <chrono>

using namespace std;

int partition(vector<int>& arr, int low, int high) {
  
    // Elegir el pivote
    int pivot = arr[high];
  
    // Índice del elemento más pequeño e indica
    // la posición correcta del pivote encontrada hasta ahora
    int i = low - 1;

    // Recorrer arr[low..high] y mover todos los elementos
    // más pequeños al lado izquierdo. Los elementos de low 
    // a i son más pequeños después de cada iteración
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    
    // Mover el pivote después de los elementos más pequeños y
    // devolver su posición
    swap(arr[i + 1], arr[high]);  
    return i + 1;
}

// Implementación de la función QuickSort
void quickSort(vector<int>& arr, int low, int high) {
  
    if (low < high) {
      
        // pi es el índice de la partición devuelta del pivote
        int pi = partition(arr, low, high);

        // Llamadas recursivas para elementos menores
        // y elementos mayores o iguales
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

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
    cout << "Ingrese el nombre del archivo para guardar la lista ordenada (ej. resultado.txt): " << endl;
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
        quickSort(numeros, 0, tamano - 1);
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


// Código sacado de:
// GeeksforGeeks. (n.d.). *Quick Sort Algorithm*. Recuperado 31 de Agosto, 2024, de https://www.geeksforgeeks.org/quick-sort-algorithm/
// Fue ligeramente modificado para abrir y procesar archivos .txt.