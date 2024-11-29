#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <fstream>

#define DATA_SIZE 250

void generate_random_data(std::vector<uint32_t> &data, size_t size) {
    data.clear();
    for (size_t i = 0; i < size; i++) {
        data.push_back(rand() % 2);
    }
}

uint32_t calculate_crc(const std::vector<uint32_t> &data) {
    uint32_t crc = 0xFFFFFFFF;
    for (size_t i = 0; i < data.size(); i++) {
        crc ^= data[i];
        for (int j = 0; j < 8; j++) {
            if (crc & 1)
                crc = (crc >> 1) ^ 0xEDB88320;
            else
                crc >>= 1;
        }
    }
    return ~crc;
}

bool check_data(const std::vector<uint32_t> &data, uint32_t expected_crc) {
    uint32_t crc_value = calculate_crc(data);
    return crc_value == expected_crc;
}

void test_variable_polynomial_lengths() {
    std::vector<uint32_t> data;
    generate_random_data(data, DATA_SIZE);

    std::ofstream out_file("crc_test_results.txt");  // Открываем файл для записи

    if (!out_file) {
        std::cerr << "Ошибка при открытии файла!" << std::endl;
        return;
    }

    out_file << "Polynomial Length, Time (microseconds)\n";  // Записываем заголовок

    std::cout << "Testing variable polynomial lengths:\n";

    for (size_t length = 4; length <= 1000; length += 2) {
        clock_t start = clock();

        uint32_t crc_value = calculate_crc(data);
        bool is_valid = check_data(data, crc_value);

        clock_t end = clock();
        double elapsed_time = ((double)(end - start) / CLOCKS_PER_SEC) * 1e6;

        out_file << length << ", " << elapsed_time << "\n";  // Записываем результат в файл

        std::cout << "Polynomial length: " << length
                  << ", Time: " << elapsed_time << " microseconds, CRC Valid: "
                  << (is_valid ? "Yes" : "No") << std::endl;
    }

    out_file.close();  // Закрываем файл
}

int main() {
    srand(time(nullptr));
    test_variable_polynomial_lengths();
    return 0;
}
