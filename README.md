# Algoritmos de Ordenamiento

## Descripción

Este repositorio contiene implementaciones de varios algoritmos de ordenamiento en C++.
Puedes usar estos códigos con los datasets que elijas generar para medir sus rendimientos.

## Estructura del Repositorio

- `Algoritmos/` - Contiene los códigos fuente de los algoritmos de ordenamiento en C++.
  - `MergeSort.cpp` - Implementación del algoritmo de Merge Sort
  - `OptiMat.cpp` - Implementación del algoritmo iterativo cúbico optimizado de multiplicación de matrices.
  - `QuickSort.cpp` - Implementación del algoritmo de Quick Sort.
  - `SelectionSort.cpp` - Implementación del algoritmo de Selection Sort.
  - `Sort.cpp` - Implementación de la función Sort.
  - `Strassen.cpp` - Implementación del algoritmo de Strassen.
  - `TradMat.cpp` - Implementación del algoritmo iterativo cúbico tradicional de multiplicación de matrices.

- `DataSets/` - Contiene conjuntos de datos para las pruebas.
  - `arreglos/` - Carpeta que contiene archivos de texto con datos en formato de arreglo.
  - `matrices/` - Carpeta que contiene archivos de texto con datos en formato de matriz.
  - `generadorDataset.py` - Script en Python para generar conjuntos de datos de prueba.
  

## Instrucciones de Uso

Una vez copiado el repositorio...
  1. Usar el código `generadorDataset.py` para generar conjuntos de datos a elección (al final del código se encuentran comentados llamados predefinidos a las funciones).
  2. En las carpetas de arreglos y matrices se encuentran archivos predefinidos en caso de preferirlos.
  3. En caso de crear matrices, se debe modificar los nombres de las matrices generadas a random_matrix_1 y random_matrix_2 en caso de ser cuadradas o random_matrix_3 y random_matrix_4 en caso de ser rectangulares.
  4. Compilar y ejecutar el código en C++ del algoritmo que se desea utilizar.
  5. Seguir instrucciones que se muestren en pantalla tras la ejecución.
