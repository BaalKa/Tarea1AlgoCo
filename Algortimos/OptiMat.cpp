#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>

using namespace std;

// Función para transponer una matriz
vector<vector<int>> transposeMatrix(const vector<vector<int>>& B) {
    int rows = B.size();
    int cols = B[0].size();
    vector<vector<int>> B_transpose(cols, vector<int>(rows));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            B_transpose[j][i] = B[i][j]; // Transponer filas y columnas
        }
    }

    return B_transpose;
}

// Función para multiplicar dos matrices usando B transpuesta
bool multiplyMatricesOptimized(const vector<vector<int>>& A, const vector<vector<int>>& B_transposed, vector<vector<int>>& C) {
    int m = A.size();        // Número de filas en A
    int n = A[0].size();     // Número de columnas en A (también filas en B original)
    int p = B_transposed.size(); // Número de columnas en B original (ahora filas en B_transposed)

    // Inicializar la matriz C con ceros
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < p; ++j) {
            C[i][j] = 0;
        }
    }

    // Medir el tiempo de multiplicación
    auto start = chrono::high_resolution_clock::now(); // Tiempo inicial

    // Multiplicación optimizada usando B transpuesta
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < p; ++j) {
            for (int k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * B_transposed[j][k];
            }
        }
    }

    auto end = chrono::high_resolution_clock::now(); // Tiempo final
    chrono::duration<double, milli> duration_ms = end - start; // Duración en milisegundos

    // Imprimir el tiempo que tomó la multiplicación
    cout << "Tiempo de ejecucion de la multiplicacion optimizada: " << duration_ms.count() << " milisegundos" << endl;
    cout << " " << endl;
    return true;
}

// Función para guardar una matriz en un archivo
void saveMatrixToFile(const vector<vector<int>>& matrix, const string& filename) {
    ofstream file("../DataSets/matrices/" + filename + ".txt");
    if (!file) {
        cerr << "Error al abrir el archivo " << filename << ".txt" << endl;
        return;
    }

    // Guardar la matriz en el archivo
    for (const auto& row : matrix) {
        for (int elem : row) {
            file << elem << " ";
        }
        file << endl;
    }

    file.close();
}


// Función para leer una matriz desde un .txt
vector<vector<int>> readMatrixFromFile(const string& filename) {
    ifstream file(filename);
    vector<vector<int>> matrix;

    // Verificar si se abrió correctamente    
    if (!file) {
        cerr << "Error al abrir el archivo " << filename << endl;
        return matrix;
    }

    // Generar matriz desde el txt
    string line;
    while (getline(file, line)) {
        vector<int> row;
        stringstream ss(line);
        int value;
        while (ss >> value) {
            row.push_back(value);
        }
        matrix.push_back(row);
    }

    file.close();
    return matrix;
}

int main() {
    // Seleccionar txts a multiplicar
    int decision;
    cout << "Desea multiplicar matrices de dimensiones iguales o distintas?" << endl << "(1) iguales, (2) distintas" << endl;
    cin >> decision;
    cout << " " << endl;

    string archivoSalida;
    cout << "Ingrese el nombre del archivo para guardar el resultado (ej. resultado): " << endl;
    cin >> archivoSalida;
    cout << " " << endl;

    // Usar los txt seleccionados
    switch (decision) {
    case 1: {
        // Leer las matrices desde los archivos
        vector<vector<int>> A = readMatrixFromFile("../DataSets/matrices/random_matrix_1.txt");
        vector<vector<int>> B = readMatrixFromFile("../DataSets/matrices/random_matrix_2.txt");

        // Verificar que ambas matrices hayan sido leídas correctamente
        if (A.empty() || B.empty()) {
            cerr << "Error al leer las matrices desde los archivos." << endl;
            return 1;
        }

        // Transponer la matriz B para optimizar la multiplicación
        vector<vector<int>> B_transposed = transposeMatrix(B);

        // Definir la matriz resultado C con dimensiones adecuadas
        vector<vector<int>> C(A.size(), vector<int>(B[0].size()));

        // Multiplicar las matrices optimizadamente
        if (multiplyMatricesOptimized(A, B_transposed, C)) {
            // Guardar la matriz resultado en un archivo
            saveMatrixToFile(C, archivoSalida);
            cout << "Producto guardado en el archivo: " << archivoSalida << ".txt" << endl;
        }
        break;
    }

    case 2: {
        // Leer las matrices desde los archivos
        vector<vector<int>> A = readMatrixFromFile("../DataSets/matrices/random_matrix_3.txt");
        vector<vector<int>> B = readMatrixFromFile("../DataSets/matrices/random_matrix_4.txt");

        // Verificar que ambas matrices hayan sido leídas correctamente
        if (A.empty() || B.empty()) {
            cerr << "Error al leer las matrices desde los archivos." << endl;
            return 1;
        }

        // Transponer la matriz B para optimizar la multiplicación
        vector<vector<int>> B_transposed = transposeMatrix(B);

        // Definir la matriz resultado C con dimensiones adecuadas
        vector<vector<int>> C(A.size(), vector<int>(B[0].size()));

        // Multiplicar las matrices optimizadamente
        if (multiplyMatricesOptimized(A, B_transposed, C)) {
            // Guardar la matriz resultado en un archivo
            saveMatrixToFile(C, archivoSalida);
            cout << "Producto guardado en el archivo: " << archivoSalida << ".txt" << endl;
        }
        break;
    }
    
    default:
        cout << "Opcion no valida." << endl;
        break;
    }

    return 0;
}
