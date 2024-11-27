#include <iostream>
#include <cmath>

using namespace std;

const int REGISTER_SIZE = 5;

// Shift x registers
void shiftX(int x[REGISTER_SIZE]) {
    int8_t shiftedElement = (x[3] + x[4]) % 2;

    for (int i = 0; i < REGISTER_SIZE; i++) {
        x[REGISTER_SIZE - 1 - i] = x[REGISTER_SIZE - 2 - i];
    }
    x[0] = shiftedElement;
}

// Shift y registers
void shiftY(int y[REGISTER_SIZE]) {
    int8_t shiftedElement = (y[1] + y[4]) % 2;

    for (int i = 0; i < REGISTER_SIZE; i++) {
        y[REGISTER_SIZE - 1 - i] = y[REGISTER_SIZE - 2 - i];
    }
    y[0] = shiftedElement;
}

void goldSequence(int x[REGISTER_SIZE], int y[REGISTER_SIZE], int result[], int length) {
    for (int i = 0; i < length; i++) {
        result[i] = (x[4] + y[4]) % 2;
        shiftX(x);
        shiftY(y);
    }
}

void shiftElements(int a[], int length) {
    int8_t shiftedElement = a[length - 1];

    for (int i = 0; i < length - 1; i++) {
        a[length - 1 - i] = a[length - 2 - i];
    }
    a[0] = shiftedElement;
}

void autocorrelation(int sequence[], int length, double result[]) {
    for (int i = 0; i < length + 1; i++) {
        int shiftedSequence[length];

        for (int j = 0; j < length; j++) {
            shiftedSequence[j] = sequence[j];
        }

        for (int k = 0; k < i; k++) {
            shiftElements(shiftedSequence, length);
        }

        double correlation = 0;
        for (int j = 0; j < length; j++) {
            correlation += sequence[j] * shiftedSequence[j];
        }

        double sumSqA = 0, sumSqB = 0;
        for (int j = 0; j < length; j++) {
            sumSqA += sequence[j] * sequence[j];
            sumSqB += shiftedSequence[j] * shiftedSequence[j];
        }

        result[i] = correlation / sqrt(sumSqA * sumSqB);
    }
}

int correlation(int x[], int y[], int length) {
    int sum = 0;
    for (int i = 0; i < length; i++) {
        sum += x[i] * y[i];
    }
    return sum;
}

void printAutocorrelationTable(int sequence[], int length, double autocorr[]) {
    cout << endl;
    cout << "Shift | Sequence                                                   | Autocorrelation" << endl;
    cout << "------------------------------------------------------------------------------------" << endl;

    int shifted_sequence[length];

    for (int shift = 0; shift < length + 1; shift++) {
        // Добавление пробела для выравнивания, если shift меньше 10
        if (shift < 10) {
            cout << shift << "  ";  // Добавляем два пробела после одного числа
        } else {
            cout << shift << " ";  // Один пробел для чисел 10 и больше
        }
        
        cout << "| ";
        for (int i = 0; i < length; i++) {
            shifted_sequence[i] = sequence[(i + shift) % length];
            cout << shifted_sequence[i] << " ";
        }
        cout << "| " << autocorr[shift] << endl;
    }
}

int main() {
    int registerX[REGISTER_SIZE] = { 0, 1, 0, 0, 1 }; // 9
    int registerY[REGISTER_SIZE] = { 1, 0, 0, 0, 0 }; // 9 + 7 (16)

    int registerX1[REGISTER_SIZE] = { 0, 1, 0, 1, 0 }; // 10
    int registerY1[REGISTER_SIZE] = { 0, 1, 0, 1, 1 }; // 9 + 2 (11)

    int length = pow(2, REGISTER_SIZE) - 1;
    int goldSeq1[length];
    int goldSeq2[length];
    goldSequence(registerX, registerY, goldSeq1, length);
    goldSequence(registerX1, registerY1, goldSeq2, length);

    cout << "\n\n\n";
    cout << "Gold sequence (0, 1, 1, 0, 0 and 1, 0, 0, 1, 1): ";
    for (int i = 0; i < length; i++) {
        cout << goldSeq1[i] << " ";
    }

    double autocorr1[length + 1];
    autocorrelation(goldSeq1, length, autocorr1);

    printAutocorrelationTable(goldSeq1, length, autocorr1);

    cout << "\n\n\n";
    cout << "Gold sequence (0, 1, 1, 0, 1 and 0, 1, 1, 1, 0): ";
    for (int i = 0; i < length; i++) {
        cout << goldSeq2[i] << " ";
    }

    double autocorr2[length + 1];
    autocorrelation(goldSeq2, length, autocorr2);

    printAutocorrelationTable(goldSeq2, length, autocorr2);

    cout << endl;
    double result;
    result = correlation(goldSeq1, goldSeq2, length);
    cout << "Gold1 and Gold2 correlation: " << result << endl;
}
