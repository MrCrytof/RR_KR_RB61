
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Виділяє динамічну пам'ять для квадратної матриці N x N.
 *
 * @param N Розмірність матриці.
 * @return double** Вказівник на створену матрицю або NULL у разі помилки.
 */
double **memory_alloc(int N);

/**
 * @brief Заповнює матрицю значеннями, введеними користувачем.
 *
 * @param Arr Вказівник на матрицю.
 * @param N Розмірність матриці.
 */
void fill_arr(double **Arr, int N);

/**
 * @brief Обчислює суму всіх елементів заданого рядка матриці.
 *
 * @param Arr Вказівник на матрицю.
 * @param row Номер рядка.
 * @param N Кількість елементів у рядку.
 * @return double Сума елементів рядка.
 */
double row_sum(double **Arr, int row, int N);

/**
 * @brief Копіює матрицю A у B та сортує її рядки за спаданням сум елементів.
 *
 * @param A Початкова матриця.
 * @param B Матриця для збереження відсортованого результату.
 * @param N Розмірність матриць.
 */
void sort_matrix(double **A, double **B, int N);

/**
 * @brief Виводить матрицю на екран.
 *
 * @param Arr Вказівник на матрицю.
 * @param N Розмірність матриці.
 * @param name Назва матриці.
 */
void print(double **Arr, int N, char name);

/**
 * @brief Звільняє динамічно виділену пам'ять матриці.
 *
 * @param Arr Вказівник на матрицю.
 * @param N Кількість рядків матриці.
 */
void clear_memory(double **Arr, int N);

int main() {

    int N;

    printf("Enter matrix size N: ");
    if (scanf("%d", &N) != 1 || N <= 0) {
        printf("Error: N must be greater than 0.\n");
        return 1;
    }

    // Виділення пам'яті для матриць A та B
    double **A = memory_alloc(N);
    double **B = memory_alloc(N);

    if (A == NULL || B == NULL) {
        printf("Memory allocation error.\n");

        if (A != NULL) clear_memory(A, N);
        if (B != NULL) clear_memory(B, N);

        return 1;
    }

    // Заповнення початкової матриці
    printf("\n=== Filling matrix A ===\n");
    fill_arr(A, N);

    // Сортування рядків матриці
    sort_matrix(A, B, N);

    // Виведення результатів
    print(A, N, 'A');
    print(B, N, 'B');

    // Звільнення пам'яті
    clear_memory(A, N);
    clear_memory(B, N);

    return 0;
}

// Виділення пам'яті для матриці
double **memory_alloc(int N) {
    double **Arr = (double **)malloc(N * sizeof(double *));

    if (Arr == NULL) {
        return NULL;
    }

    for (int i = 0; i < N; i++) {
        Arr[i] = (double *)malloc(N * sizeof(double));

        if (Arr[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(Arr[j]);
            }
            free(Arr);
            return NULL;
        }
    }

    return Arr;
}

// Введення елементів матриці
void fill_arr(double **Arr, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("Enter element [%d][%d]: ", i, j);
            scanf("%lf", &Arr[i][j]);
        }
    }
}

// Обчислення суми елементів заданого рядка
double row_sum(double **Arr, int row, int N) {
    double sum = 0;

    for (int j = 0; j < N; j++) {
        sum += Arr[row][j];
    }

    return sum;
}

// Копіювання матриці та сортування її рядків за спаданням сум
void sort_matrix(double **A, double **B, int N) {

    // Копіювання елементів матриці A у матрицю B
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            B[i][j] = A[i][j];
        }
    }

    // Сортування рядків методом бульбашки
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - 1 - i; j++) {

            // Порівняння сум сусідніх рядків
            if (row_sum(B, j, N) < row_sum(B, j + 1, N)) {

                // Обмін рядків місцями
                double *temp = B[j];
                B[j] = B[j + 1];
                B[j + 1] = temp;
            }
        }
    }
}

// Виведення матриці на екран
void print(double **Arr, int N, char name) {
    printf("\nMatrix %c (%dx%d):\n", name, N, N);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%8.2lf ", Arr[i][j]);
        }
        printf("\n");
    }
}

// Звільнення виділеної пам'яті
void clear_memory(double **Arr, int N) {
    for (int i = 0; i < N; i++) {
        free(Arr[i]);
    }

    free(Arr);
}
