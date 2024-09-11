// Programa CPP para implementar el algoritmo de multiplicación de matrices de Strassen
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <cmath>
#include <chrono>

using namespace std;
typedef long long lld;

// Función para multiplicar dos matrices
inline lld** MatrixMultiply(lld** a, lld** b, int n, int l, int m)
{
    // Crear una matriz de resultados c con dimensiones n x m
    lld** c = new lld*[n];
    for (int i = 0; i < n; i++)
        c[i] = new lld[m];

    // Inicializar la matriz resultado c con ceros y realizar la multiplicación
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            c[i][j] = 0; // Inicializar el valor en la posición (i, j) de la matriz resultado
            for (int k = 0; k < l; k++) {
                // Realizar la multiplicación de las matrices a y b
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return c; // Devolver la matriz resultado
}

// Función para multiplicar matrices utilizando el algoritmo de Strassen
inline lld** Strassen(lld** a, lld** b, int n, int l, int m)
{
    // Si las dimensiones son 1, realiza una multiplicación de matrices simple
    if (n == 1 || l == 1 || m == 1)
        return MatrixMultiply(a, b, n, l, m);

    // Crear una matriz de resultados c con dimensiones n x m
    lld** c = new lld*[n];
    for (int i = 0; i < n; i++)
        c[i] = new lld[m];

    // Ajustar las dimensiones para la división en submatrices
    int adjN = (n >> 1) + (n & 1); // Número ajustado de filas
    int adjL = (l >> 1) + (l & 1); // Número ajustado de columnas en la primera matriz
    int adjM = (m >> 1) + (m & 1); // Número ajustado de columnas en la segunda matriz

    // Crear submatrices para la matriz a
    lld**** As = new lld***[2];
    for (int x = 0; x < 2; x++) {
        As[x] = new lld**[2];
        for (int y = 0; y < 2; y++) {
            As[x][y] = new lld*[adjN];
            for (int i = 0; i < adjN; i++) {
                As[x][y][i] = new lld[adjL];
                for (int j = 0; j < adjL; j++) {
                    int I = i + (x & 1) * adjN; // Índice ajustado para filas
                    int J = j + (y & 1) * adjL; // Índice ajustado para columnas
                    // Asignar valor a la submatriz As[x][y]
                    As[x][y][i][j] = (I < n && J < l) ? a[I][J] : 0;
                }
            }
        }
    }

    // Crear submatrices para la matriz b
    lld**** Bs = new lld***[2];
    for (int x = 0; x < 2; x++) {
        Bs[x] = new lld**[2];
        for (int y = 0; y < 2; y++) {
            Bs[x][y] = new lld*[adjN];
            for (int i = 0; i < adjL; i++) {
                Bs[x][y][i] = new lld[adjM];
                for (int j = 0; j < adjM; j++) {
                    int I = i + (x & 1) * adjL; // Índice ajustado para filas
                    int J = j + (y & 1) * adjM; // Índice ajustado para columnas
                    // Asignar valor a la submatriz Bs[x][y]
                    Bs[x][y][i][j] = (I < l && J < m) ? b[I][J] : 0;
                }
            }
        }
    }

    // Crear submatrices auxiliares para los cálculos intermedios
    lld*** s = new lld**[10];
    for (int i = 0; i < 10; i++) {
        switch (i) {
        case 0:
            // S0 = B01 - B11
            s[i] = new lld*[adjL];
            for (int j = 0; j < adjL; j++) {
                s[i][j] = new lld[adjM];
                for (int k = 0; k < adjM; k++) {
                    s[i][j][k] = Bs[0][1][j][k] - Bs[1][1][j][k];
                }
            }
            break;
        case 1:
            // S1 = A00 + A01
            s[i] = new lld*[adjN];
            for (int j = 0; j < adjN; j++) {
                s[i][j] = new lld[adjL];
                for (int k = 0; k < adjL; k++) {
                    s[i][j][k] = As[0][0][j][k] + As[0][1][j][k];
                }
            }
            break;
        case 2:
            // S2 = A10 + A11
            s[i] = new lld*[adjN];
            for (int j = 0; j < adjN; j++) {
                s[i][j] = new lld[adjL];
                for (int k = 0; k < adjL; k++) {
                    s[i][j][k] = As[1][0][j][k] + As[1][1][j][k];
                }
            }
            break;
        case 3:
            // S3 = B10 - B00
            s[i] = new lld*[adjL];
            for (int j = 0; j < adjL; j++) {
                s[i][j] = new lld[adjM];
                for (int k = 0; k < adjM; k++) {
                    s[i][j][k] = Bs[1][0][j][k] - Bs[0][0][j][k];
                }
            }
            break;
        case 4:
            // S4 = A00 + A11
            s[i] = new lld*[adjN];
            for (int j = 0; j < adjN; j++) {
                s[i][j] = new lld[adjL];
                for (int k = 0; k < adjL; k++) {
                    s[i][j][k] = As[0][0][j][k] + As[1][1][j][k];
                }
            }
            break;
        case 5:
            // S5 = B00 + B11
            s[i] = new lld*[adjL];
            for (int j = 0; j < adjL; j++) {
                s[i][j] = new lld[adjM];
                for (int k = 0; k < adjM; k++) {
                    s[i][j][k] = Bs[0][0][j][k] + Bs[1][1][j][k];
                }
            }
            break;
        case 6:
            // S6 = A01 - A11
            s[i] = new lld*[adjN];
            for (int j = 0; j < adjN; j++) {
                s[i][j] = new lld[adjL];
                for (int k = 0; k < adjL; k++) {
                    s[i][j][k] = As[0][1][j][k] - As[1][1][j][k];
                }
            }
            break;
        case 7:
            // S7 = B10 + B11
            s[i] = new lld*[adjL];
            for (int j = 0; j < adjL; j++) {
                s[i][j] = new lld[adjM];
                for (int k = 0; k < adjM; k++) {
                    s[i][j][k] = Bs[1][0][j][k] + Bs[1][1][j][k];
                }
            }
            break;
        case 8:
            // S8 = A00 - A10
            s[i] = new lld*[adjN];
            for (int j = 0; j < adjN; j++) {
                s[i][j] = new lld[adjL];
                for (int k = 0; k < adjL; k++) {
                    s[i][j][k] = As[0][0][j][k] - As[1][0][j][k];
                }
            }
            break;
        case 9:
            // S9 = B00 + B01
            s[i] = new lld*[adjL];
            for (int j = 0; j < adjL; j++) {
                s[i][j] = new lld[adjM];
                for (int k = 0; k < adjM; k++) {
                    s[i][j][k] = Bs[0][0][j][k] + Bs[0][1][j][k];
                }
            }
            break;
        }
    }

	// Crea un array de 7 matrices para almacenar los resultados de las multiplicaciones recursivas de Strassen
	lld*** p = new lld**[7];

	// Realiza las multiplicaciones de Strassen recursivas con submatrices y almacena los resultados en 'p'
	p[0] = Strassen(As[0][0], s[0], adjN, adjL, adjM); // Multiplicación (A11 + A22) * (B11 + B22)
	p[1] = Strassen(s[1], Bs[1][1], adjN, adjL, adjM); // Multiplicación (A21 + A22) * B22
	p[2] = Strassen(s[2], Bs[0][0], adjN, adjL, adjM); // Multiplicación A11 * (B12 - B22)
	p[3] = Strassen(As[1][1], s[3], adjN, adjL, adjM); // Multiplicación A22 * (B21 - B11)
	p[4] = Strassen(s[4], s[5], adjN, adjL, adjM); // Multiplicación (A11 + A12) * B22
	p[5] = Strassen(s[6], s[7], adjN, adjL, adjM); // Multiplicación (A21 - A11) * (B11 + B12)
	p[6] = Strassen(s[8], s[9], adjN, adjL, adjM); // Multiplicación (A12 - A22) * (B21 + B22)

	// Llena la matriz resultado 'c' con los resultados combinados de las submatrices calculadas
	for (int i = 0; i < adjN; i++) {
		for (int j = 0; j < adjM; j++) {
			c[i][j] = p[4][i][j] + p[3][i][j] - p[1][i][j] + p[5][i][j];
			// Calcula los elementos de la submatriz superior derecha
			if (j + adjM < m)
				c[i][j + adjM] = p[0][i][j] + p[1][i][j];
			// Calcula los elementos de la submatriz inferior izquierda
			if (i + adjN < n)
				c[i + adjN][j] = p[2][i][j] + p[3][i][j];
			// Calcula los elementos de la submatriz inferior derecha
			if (i + adjN < n && j + adjM < m)
				c[i + adjN][j + adjM] = p[4][i][j] + p[0][i][j] - p[2][i][j] - p[6][i][j];
		}
	}

	// Libera la memoria utilizada para las matrices 'As'
	for (int x = 0; x < 2; x++) {
		for (int y = 0; y < 2; y++) {
			for (int i = 0; i < adjN; i++) {
				delete[] As[x][y][i]; // Libera cada fila de la submatriz
			}
			delete[] As[x][y]; // Libera las submatrices
		}
		delete[] As[x]; // Libera las matrices de nivel superior
	}
	delete[] As; // Libera el array de matrices 'As'

	// Libera la memoria utilizada para las matrices 'Bs'
	for (int x = 0; x < 2; x++) {
		for (int y = 0; y < 2; y++) {
			for (int i = 0; i < adjL; i++) {
				delete[] Bs[x][y][i]; // Libera cada fila de la submatriz
			}
			delete[] Bs[x][y]; // Libera las submatrices
		}
		delete[] Bs[x]; // Libera las matrices de nivel superior
	}
	delete[] Bs; // Libera el array de matrices 'Bs'

	// Libera la memoria utilizada para las matrices 's'
	for (int i = 0; i < 10; i++) {
		switch (i) {
		case 0:
		case 3:
		case 5:
		case 7:
		case 9:
			for (int j = 0; j < adjL; j++) {
				delete[] s[i][j]; // Libera cada fila de las matrices correspondientes
			}
			break;
		case 1:
		case 2:
		case 4:
		case 6:
		case 8:
			for (int j = 0; j < adjN; j++) {
				delete[] s[i][j]; // Libera cada fila de las matrices correspondientes
			}
			break;
		}
		delete[] s[i]; // Libera las matrices
	}
	delete[] s; // Libera el array de matrices 's'

	// Libera la memoria utilizada para las matrices 'p'
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < (n >> 1); j++) {
			delete[] p[i][j]; // Libera cada fila de las matrices correspondientes
		}
		delete[] p[i]; // Libera las matrices
	}
	delete[] p; // Libera el array de matrices 'p'

	// Retorna la matriz resultado 'c'
	return c;
}

// Función para leer una matriz desde un archivo txt
lld** leerMatriz(const string& archivo, int& filas, int& columnas) {
    ifstream inFile(archivo);
    if (!inFile.is_open()) {
        cerr << "Error al abrir el archivo " << archivo << endl;
        exit(1);
    }

    // Leer todos los elementos en un vector
    vector<lld> elementos;
    lld valor;
    while (inFile >> valor) {
        elementos.push_back(valor);
    }
    inFile.close();

    // Determinar el tamaño de la matriz (asumimos matriz cuadrada)
    int totalElementos = elementos.size();
    int tamano = sqrt(totalElementos);

    if (tamano * tamano != totalElementos) {
        cerr << "El numero total de elementos no forma una matriz cuadrada" << endl;
        exit(1);
    }

    // Asignar dimensiones de la matriz
    filas = columnas = tamano;

    // Crear la matriz y llenar con los elementos
    lld** matriz = new lld*[filas];
    for (int i = 0; i < filas; i++) {
        matriz[i] = new lld[columnas];
        for (int j = 0; j < columnas; j++) {
            matriz[i][j] = elementos[i * columnas + j];
        }
    }
    return matriz;
}

// Función para guardar una matriz en un archivo txt
void guardarMatriz(const string& filename, lld** matriz, int filas, int columnas) {
    ofstream outFile("../DataSets/matrices/" + filename + ".txt");
    if (!outFile.is_open()) {
        cerr << "Error al abrir el archivo " << filename << ".txt" << endl;
        exit(1);
    }

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            outFile << matriz[i][j] << " ";
        }
        outFile << endl;
    }
    outFile.close();
}

int main() {
	lld** matA = nullptr;
    lld** matB = nullptr;
    int filasA, columnasA, filasB, columnasB;

    string archivoSalida;
    cout << "Ingrese el nombre del archivo para guardar el resultado (ej. resultado): " << endl;
    cin >> archivoSalida;
    cout << " " << endl;

	matA = leerMatriz("../DataSets/matrices/random_matrix_1.txt", filasA, columnasA);
    matB = leerMatriz("../DataSets/matrices/random_matrix_2.txt", filasB, columnasB);


	// Verificar si las dimensiones son compatibles para la multiplicación
	if (columnasA != filasB) {
		cerr << "Las dimensiones de las matrices no son compatibles para la multiplicación." << endl;
		return 1;
	}

	// Medir tiempo de ejecución del algoritmo
	auto start = chrono::high_resolution_clock::now(); // Tiempo inicial
	lld** matC = Strassen(matA, matB, filasA, columnasA, columnasB);
	auto end = chrono::high_resolution_clock::now(); // Tiempo final

	chrono::duration<double, milli> duration_ms = end - start; // Duración en milisegundos

	// Imprimir el tiempo que tomó la multiplicación
	cout << "Tiempo de ejecucion de la multiplicacion: " << duration_ms.count() << " milisegundos" << endl;
	cout << " " << endl;

	// Guardar el resultado de la multiplicación en un archivo
    guardarMatriz(archivoSalida, matC, filasA, columnasB);
    cout << "Producto guardado en el archivo: " << archivoSalida << ".txt" << endl;

	// Liberar memoria
	for (int i = 0; i < filasA; i++) {
		delete[] matA[i];
	}
	delete[] matA;

	for (int i = 0; i < filasB; i++) {
		delete[] matB[i];
	}
	delete[] matB;

	for (int i = 0; i < filasA; i++) {
		delete[] matC[i];
	}
	delete[] matC;

    return 0;
}

