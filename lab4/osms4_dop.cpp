#include <iostream>
#include <cmath>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm> 

using namespace std;

const int REGISTER_SIZE = 5;

void shiftX(int x[REGISTER_SIZE]){
    int8_t shiftedElement = (x[3] + x[4]) % 2;

    for (int i = REGISTER_SIZE - 1; i > 0; i--){
        x[i] = x[i - 1];
    }
    x[0] = shiftedElement;
}

void shiftY(int y[REGISTER_SIZE]){
    int8_t shiftedElement = (y[1] + y[4]) % 2;

    for (int i = REGISTER_SIZE - 1; i > 0; i--){
        y[i] = y[i - 1];
    }
    y[0] = shiftedElement;
}

void goldSequence(int x[REGISTER_SIZE], int y[REGISTER_SIZE], 
                  int result[], int length){
    for(int i = 0; i < length; i++){
        result[i] = (x[4] + y[4]) % 2;
        shiftX(x);
        shiftY(y);
    }
}

void shiftElements(int a[], int length){
    int8_t shiftedElement = a[0];

    for (int i = 0; i < length - 1; i++){
        a[i] = a[i + 1];
    }
    a[length - 1] = shiftedElement;
}

void autocorrelation(int sequence[], int length, double result[]) {
    for (int i = 0; i < length+1; i++) {
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

int correlation(int x[], int y[], int length){
    int sum=0;
    for(int i=0; i<length; i++){
        sum+=x[i]*y[i];
    }
    return sum;
}

bool isBalanced(int sequence[], int length){
    int countOnes = 0;
    int countZeros = 0;
    for(int i = 0; i < length; i++){
        if(sequence[i] == 1)
            countOnes++;
        else
            countZeros++;
    }
    return abs(countOnes - countZeros) <= 1;
}

bool checkCyclomaticity(int sequence[], int length) {
    vector<int> runLengths;
    int currentRunLength = 1;

    for (int i = 1; i < length; i++) {
        if (sequence[i] == sequence[i - 1]) {
            currentRunLength++;
        } else {
            runLengths.push_back(currentRunLength);
            currentRunLength = 1;
        }
    }
    runLengths.push_back(currentRunLength);

    vector<int> runCounts(length + 1, 0);
    for (int runLength : runLengths) {
        runCounts[runLength]++;
    }

    double tolerance = 0.7;
    if (length > 20) {
        tolerance = 0.6;
    }
    if (length > 40) {
        tolerance = 0.5;
    }

    int totalRuns = runLengths.size();
    
    for (int i = 1; i <= 4; i++) {  
        double expectedCount = totalRuns * pow(0.5, i);
        if (expectedCount >= 1) {  
            double ratio = (double)runCounts[i] / expectedCount;
            if (abs(ratio - 1) > tolerance) {
                return false;
            }
        }
    }

    return true;
}
void printAutocorrelationTable(int sequence[], int length, double autocorr[]) {
    cout << endl;
    cout << "Shift | Sequence              | Autocorrelation | Balance | Cyclicity | Is Gold Seq" << endl;
    cout << "------+-----------------------+-----------------+---------+-----------+------------" << endl;

    int shifted_sequence[length];

    for (int shift = 0; shift < length + 1; shift++) {
        for (int i = 0; i < length; i++) {
            shifted_sequence[i] = sequence[(i - shift + length) % length];
        }

        bool balanced = isBalanced(shifted_sequence, length);
        bool cyclomatic = checkCyclomaticity(shifted_sequence, length);
        bool isGold = balanced && cyclomatic;

        cout << shift << "     | ";
        for (int i = 0; i < length; i++) {
            cout << shifted_sequence[i];
        }
        cout << " | " << autocorr[shift];
        cout << "      | " << (balanced ? "+" : "-");
        cout << "       | " << (cyclomatic ? "+" : "-");
        cout << "        | " << (isGold ? "+" : "-");
        cout << endl;
    }
}

bool generateSequence(int sequence[], int length) {
    const int MAX_ATTEMPTS = 1000; // Максимальное количество попыток генерации
    
    for(int attempt = 0; attempt < MAX_ATTEMPTS; attempt++) {
        vector<int> temp(length, -1); // Временная последовательность
        int remainingPositions = length;
        int ones = length / 2 + (length % 2); // Для баланса
        int zeros = length / 2;
        
        // Сначала генерируем серии длиной 1
        int expectedSeries1 = length / 3; // Примерно половина всех серий
        for(int i = 0; i < expectedSeries1 && remainingPositions >= 2; i++) {
            int pos = rand() % (remainingPositions - 1);
            int actualPos = 0;
            int count = 0;
            
            // Находим свободную позицию
            for(int j = 0; j < length; j++) {
                if(temp[j] == -1) {
                    if(count == pos) {
                        actualPos = j;
                        break;
                    }
                    count++;
                }
            }
            
            // Проверяем, можем ли поставить 1 и 0
            if(ones > 0 && zeros > 0) {
                if(rand() % 2 == 0) {
                    temp[actualPos] = 1;
                    temp[actualPos + 1] = 0;
                    ones--;
                    zeros--;
                } else {
                    temp[actualPos] = 0;
                    temp[actualPos + 1] = 1;
                    ones--;
                    zeros--;
                }
                remainingPositions -= 2;
            }
        }
        
        // Генерируем серии длиной 2
        int expectedSeries2 = length / 6; // Примерно четверть всех серий
        for(int i = 0; i < expectedSeries2 && remainingPositions >= 3; i++) {
            int pos = rand() % (remainingPositions - 2);
            int actualPos = 0;
            int count = 0;
            
            for(int j = 0; j < length; j++) {
                if(temp[j] == -1) {
                    if(count == pos) {
                        actualPos = j;
                        break;
                    }
                    count++;
                }
            }
            
            if(ones >= 2 && zeros >= 1) {
                temp[actualPos] = 1;
                temp[actualPos + 1] = 1;
                temp[actualPos + 2] = 0;
                ones -= 2;
                zeros--;
                remainingPositions -= 3;
            } else if(zeros >= 2 && ones >= 1) {
                temp[actualPos] = 0;
                temp[actualPos + 1] = 0;
                temp[actualPos + 2] = 1;
                zeros -= 2;
                ones--;
                remainingPositions -= 3;
            }
        }
        
        // Заполняем оставшиеся позиции чередующимися значениями
        bool useOne = rand() % 2 == 0;
        for(int i = 0; i < length; i++) {
            if(temp[i] == -1) {
                if(useOne && ones > 0) {
                    temp[i] = 1;
                    ones--;
                } else if(!useOne && zeros > 0) {
                    temp[i] = 0;
                    zeros--;
                } else if(ones > 0) {
                    temp[i] = 1;
                    ones--;
                } else {
                    temp[i] = 0;
                    zeros--;
                }
                useOne = !useOne;
            }
        }
        
        // Копируем временную последовательность в выходной массив
        for(int i = 0; i < length; i++) {
            sequence[i] = temp[i];
        }
        
        // Проверяем, удовлетворяет ли последовательность всем критериям
        if(isBalanced(sequence, length) && checkCyclomaticity(sequence, length)) {
            return true;
        }
    }
    
    return false;
}

int main(){
    srand(time(0)); 

    int registerX[REGISTER_SIZE] = {0, 1, 1, 0, 0}; 
    int registerY[REGISTER_SIZE] = {1, 0, 0, 1, 1}; 

    int registerX1[REGISTER_SIZE] = {0, 1, 1, 0, 1}; 
    int registerY1[REGISTER_SIZE] = {0, 1, 1, 1, 0}; 

    int length = pow(2,REGISTER_SIZE) - 1;
    int goldSeq1[length];
    int goldSeq2[length];
    goldSequence(registerX, registerY, goldSeq1, length);
    goldSequence(registerX1, registerY1, goldSeq2, length);

    cout<<"\n\n\n";
    cout << "Gold sequence (0, 1, 1, 0, 0 and 1, 0, 0, 1, 1): ";
    for (int i = 0; i < length; i++)
    {
        cout << goldSeq1[i] << " ";
    }

    double autocorr1[length+1];
    autocorrelation(goldSeq1, length, autocorr1);

    printAutocorrelationTable(goldSeq1, length, autocorr1);

    cout<<"\n\n\n";
    cout << "Gold sequence (0, 1, 1, 0, 1 and 0, 1, 1, 1, 0): ";
    for (int i = 0; i < length; i++)
    {
        cout << goldSeq2[i] << " ";
    }
    
    double autocorr2[length+1];
    autocorrelation(goldSeq2, length, autocorr2);

    printAutocorrelationTable(goldSeq2, length, autocorr2);

    cout << endl; 
    double result;
    result = correlation(goldSeq1, goldSeq2, length);
    cout << "Gold1 and Gold2 correlation: " << result << endl;

    // Генерация последовательности без подтверждения
    int userSequence[length];
    bool success = generateSequence(userSequence, length);
    if(success){
        cout << "\nGenerated sequence that satisfies all criteria: ";
        for(int i = 0; i < length; i++){
            cout << userSequence[i] << " ";
        }

        double userAutocorr[length+1];
        autocorrelation(userSequence, length, userAutocorr);

        printAutocorrelationTable(userSequence, length, userAutocorr);
    } else {
        cout << "The sequence was not obtained...\n";
    }

    return 0;
}
