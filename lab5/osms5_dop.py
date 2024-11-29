import random
import time
import matplotlib.pyplot as plt

def calculate_crc(data, generator):
    """Вычисление CRC для данных с заданным полиномом."""
    augmented_data = data + [0] * (len(generator) - 1)
    remainder = augmented_data[:]
    for i in range(len(data)):
        if remainder[i] == 1:
            for j in range(len(generator)):
                remainder[i + j] ^= generator[j]
    return remainder[-(len(generator) - 1):]

def check_data(data_with_crc, generator):
    """Проверка корректности данных с CRC."""
    remainder = data_with_crc[:]
    for i in range(len(data_with_crc) - len(generator) + 1):
        if remainder[i] == 1:
            for j in range(len(generator)):
                remainder[i + j] ^= generator[j]
    return all(bit == 0 for bit in remainder[-(len(generator) - 1):])

def generate_random_data(size):
    """Генерация случайных данных заданного размера."""
    return [random.randint(0, 1) for _ in range(size)]

def read_cpp_results(filename):
    """Чтение данных из файла, созданного C++ программой."""
    lengths = []
    times = []
    with open(filename, "r") as f:
        next(f)  # Пропускаем заголовок
        for line in f:
            length, time_value = line.strip().split(", ")
            lengths.append(int(length))
            times.append(float(time_value))
    return lengths, times

def test_variable_polynomial_lengths():
    """Тестирование времени вычисления CRC для полиномов разной длины."""
    py_times = []
    py_lengths = []
    data = generate_random_data(250)

    print("Тестирование полиномов разной длины:")
    for length in range(4, 1001, 2):
        generator = [1] * length

        start_time = time.time()
        crc = calculate_crc(data, generator)
        data_with_crc = data + crc
        check_data(data_with_crc, generator)
        end_time = time.time()

        elapsed_time = (end_time - start_time) * 1e6
        py_times.append(elapsed_time)
        py_lengths.append(length)
        print(f"Длина полинома: {length}, Время: {elapsed_time:.2f} мкс")

    # Чтение данных из C++ файла
    cpp_lengths, cpp_times = read_cpp_results("crc_test_results.txt")

    # Построение графиков
    plt.plot(py_lengths, py_times, marker='o', label="Python")
    plt.plot(cpp_lengths, cpp_times, marker='x', label="C++")
    plt.xlabel("Длина полинома")
    plt.ylabel("Время вычислений (мкс)")
    plt.title("Сравнение времени вычислений CRC")
    plt.legend()
    plt.grid()
    plt.show()

if __name__ == "__main__":
    print("Запуск теста:")
    test_variable_polynomial_lengths()
