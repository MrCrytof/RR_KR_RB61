#include <stdio.h>

int main() {
    int N;
    double a, S = 1.0;
    double power = 1.0;

    // Введення початкових даних
    printf("Enter a: ");
    scanf("%lf", &a);

    printf("Enter N: ");
    scanf("%d", &N);

    // Перевірка значення N
    if (N < 1) {
        printf("Error: N must be greater than or equal to 1.\n");
        return 1;
    }

    // Обчислення суми ряду
    for (int n = 1; n <= N; n++) {

        // Обчислення a^n без використання pow()
        power *= a;

        double denominator = a + n;

        // Перевірка знаменника
        if (denominator == 0.0) {
            continue;
        }

        // Визначення знака та додавання члена до суми
        if (n % 2 == 0) {
            S += power / denominator;
        }
        else {
            S -= power / denominator;
        }
    }

    // Виведення результату
    printf("The sum of the series is: %.10lf\n", S);

    return 0;
}