#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;

// Función para imprimir un vector
void printVector(vector<int>& arr) {
    cout << "Arreglo ordenado:" << endl;
    for (int i = 0; i < arr.size(); i++)
        cout << arr[i] << " ";
    cout << endl;
}

// Probar función sort
int main() {
    vector<int> numeros;
    int numero;
    size_t tamano;

  // Elegir el conjunto de datos a ordenar
    int eleccion;
    cout << "Elija el DataSet a ordenar" << endl;
    cout << "(1) Lista aleatoria, (2) Lista semiordenada o (3) Lista parcialmente ordenada" << endl;
    cin >> eleccion;

    bool ordenar = false;

    // Abrir y guardar contenido de archivo txt seleccionado
    switch (eleccion) {
    case 1: {
        ifstream archivo("../DataSets/random_generate.txt");

        while (archivo >> numero) {
            numeros.push_back(numero);
        }
        archivo.close();
        tamano = numeros.size();
        ordenar = true;
        break;
    }

    case 2: {
        ifstream archivo("../DataSets/semiorder.txt");

        while (archivo >> numero) {
            numeros.push_back(numero);
        }
        archivo.close();
        tamano = numeros.size();
        ordenar = true;
        break;
    }
    
    case 3: {
        ifstream archivo("../DataSets/partially.txt");

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

        // Imprimir el arreglo ordenado
        printVector(numeros);
    }
    return 0;
}

// Código sacado de:
// GeeksforGeeks. (n.d.). *Internal details of std::sort() in C++*. Recuperado 31 de Agosto, 2024, de https://www.geeksforgeeks.org/internal-details-of-stdsort-in-c/
// Fue ligeramente modificado para abrir y procesar archivos .txt.