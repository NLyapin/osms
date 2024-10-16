#include <iostream>
#include <cmath>

using namespace std;

// Функция для расчета корреляции между двумя массивами
int calculateCorrelation(int a[], int b[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i] * b[i];
    }
    return sum;
}

// Функция для расчета нормализованной корреляции
double calculateNormalizedCorrelation(int a[], int b[], int n) {
    int correlationValue = calculateCorrelation(a, b, n); // Получение корреляции
    int sumA = 0, sumB = 0;

    // Вычисление суммы квадратов для каждого массива
    for (int i = 0; i < n; i++) {
        sumA += a[i] * a[i];
        sumB += b[i] * b[i];
    } 
    // Нормализация корреляции
    double result = static_cast<double>(correlationValue) / sqrt(sumA * sumB);
    return result;
}

int main() {
    int n = 8; // Размер массива
    int a[] = {9, 1, 8, -2, -2, -4, 1, 3}; // Массив a
    int b[] = {5, 6, 5, 0, -5, -6, 2, 5}; // Массив b
    int c[] = {-4, -1, 3, -9, 2, -1, 4, -1}; // Массив c

    // Расчет корреляции между массивами
    double correlationAB = calculateCorrelation(a, b, n);
    double correlationAC = calculateCorrelation(a, c, n);
    double correlationBC = calculateCorrelation(b, c, n);

    // Расчет нормализованной корреляции
    double normalizedCorrelationAB = calculateNormalizedCorrelation(a, b, n);
    double normalizedCorrelationAC = calculateNormalizedCorrelation(a, c, n);
    double normalizedCorrelationBC = calculateNormalizedCorrelation(b, c, n);

    // Вывод результатов корреляции
    cout << "Корреляция между массивами a, b и c:" << endl;
    cout << "\\ |  a  |  b  |  c" << endl;
    cout << "a |  -  | " << correlationAB << " | " << correlationAC << endl;
    cout << "b | " << correlationAB << " |  -  | " << correlationBC << endl;
    cout << "c | " << correlationAC << " | " << correlationBC << " |  -" << endl << endl;

    // Вывод результатов нормализованной корреляции
    cout << "Нормализованная корреляция между массивами a, b и c:" << endl;
    cout << "\\ |  a  |  b  |  c" << endl;
    cout << "a |  -  | " << normalizedCorrelationAB << " | " << normalizedCorrelationAC << endl;
    cout << "b | " << normalizedCorrelationAB << " |  -  | " << normalizedCorrelationBC << endl;
    cout << "c | " << normalizedCorrelationAC << " | " << normalizedCorrelationBC << " |  -" << endl;

    return 0;
}
