#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;

// Fusiona dos subarreglos de arr[].
// El primer subarreglo es arr[left..mid]
// El segundo es arr[mid+1..right]
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Crear vectores temporales
    vector<int> L(n1), R(n2);

    // Copiar datos en vectores temporales L[] y R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0;
    int k = left;

    // Fusionar nuevamente los vectores
    // temporales en arr[left..right]
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copiar los elementos restantes de L[], 
    // si los hay
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copiar los elementos restantes de R[], 
    // si los hay
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// El comienzo es para el índice izquierdo
// y el final es el índice derecho del
// subconjunto de arr que se va a ordenar
void mergeSort(vector<int>& arr, int left, int right) {
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
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

    if (ordenar == true) {
        auto start = chrono::high_resolution_clock::now();
        mergeSort(numeros, 0, tamano - 1);
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
// GeeksforGeeks. (n.d.). *Merge Sort – Data Structure and Algorithms Tutorials*. Recuperado 31 de Agosto, 2024, de https://www.geeksforgeeks.org/merge-sort/
// Fue ligeramente modificado para abrir y procesar archivos .txt.

