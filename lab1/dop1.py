import numpy as np
import matplotlib.pyplot as plt

def fft_builtin(data):
    return np.fft.fft(data)

def manual_fourier_transform(data):
    N = len(data)
    result = []
    for k in range(N):
        s = 0
        for n in range(N):
            s += data[n] * np.exp(-2j * np.pi * k * n / N)
        result.append(s)
    return np.array(result)

data = np.random.random(10)
print(data)

fft_result = fft_builtin(data)
manual_fft_result = manual_fourier_transform(data)
print(manual_fft_result)
print(np.fft.fft(data))

plt.figure(figsize=(12, 6))

plt.subplot(2, 1, 1)
plt.plot(np.abs(fft_result), label="FFT встроенная")
plt.title("Сравнение")
plt.ylabel("Амплитуда")
plt.legend()

plt.subplot(2, 1, 2)
plt.plot(np.abs(manual_fft_result), label="FFT ручная", color='r')
plt.xlabel("Частота")
plt.ylabel("Амплитуда")
plt.legend()

plt.show()
