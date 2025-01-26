#include <iostream>
#include <omp.h>

using namespace std;

int main() {

    std::cout << "Verificando la ejecución de las directivas OMP!\n"; // Mensaje inicial

    // Primero verificamos si OpenMP está funcionando
#ifdef _OPENMP
    std::cout << "OMP disponible y funcionando" << std::endl; 
#endif

    int N = 1000;  // Tamaño de los arreglos
    int A[N], B[N], R[N]; // Declaramos los arreglos A, B y el arreglo de resultados R

    // Inicializamos los arreglos A y B con valores
    for (int i = 0; i < N; i++) {
        A[i] = i + 1;  // Siguiendo imagen guia: A (1, 2, 3, ...)
        B[i] = i + 11; // Siguiendo imagen guia:  B (11, 12, 13, ...)
    }

    // Imprimimos los arreglos A y B en una sola línea
    cout << "Arreglo A: ";
    for (int i = 0; i < N; i++) {
        cout << A[i] << " ";
    }
    cout << endl;

    cout << "Arreglo B: ";
    for (int i = 0; i < N; i++) {
        cout << B[i] << " ";
    }
    cout << endl;

    int main_thread = omp_get_thread_num(); // Obtenemos el ID del hilo principal
    cout << "Hilo principal " << main_thread << "\n" << endl; 

    //OpenMP
    #pragma omp parallel for 
    for (int i = 0; i < N; i++) {
        int thread_id = omp_get_thread_num(); // Obtenemos el ID del hilo actual

        // Sección crítica para evitar que varios hilos impriman a la vez
        #pragma omp critical 
        {
            cout << "Hilo " << thread_id << " iniciado." << endl; 
        }

        R[i] = A[i] + B[i]; //Suma de los elementos de A y B
    }

    // Imprimimos algunos elementos para verificar la suma
    cout << "\nAlgunos elementos de los arreglos:" << endl;
    for (int i = 0; i < 10; i++) {
        cout << "A[" << i << "] + B[" << i << "] = " << R[i] << endl;
    }

    return 0;
}
