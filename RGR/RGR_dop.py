import matplotlib.pyplot as plt
import numpy as np


def string_to_bits(s):
    return [int(bit) for char in s for bit in bin(ord(char))[2:].zfill(8)]


def add_noise(signal, sigma):
    noise = np.random.normal(0, sigma, len(signal))
    return (signal + noise).tolist()


def decode_signal(signal, threshold=0.5):
    return [1 if sample > threshold else 0 for sample in signal]


def calculate_ber(payload_bits, sigma, samples_per_bit=10):
    payload_signal = np.repeat(payload_bits, samples_per_bit)
    noisy_signal = add_noise(payload_signal, sigma)
    
    decoded_signal = decode_signal(noisy_signal, threshold=0.5)
    decoded_bits = decoded_signal[::samples_per_bit]

    errors = sum(b1 != b2 for b1, b2 in zip(payload_bits, decoded_bits))
    ber = errors / len(payload_bits)
    return errors, ber


name = "NikitaLapin"
payload_bits = string_to_bits(name)
sigmas = np.linspace(0.1, 2.0, 10)
num_simulations = 100


average_bers = []

print("Результаты симуляций:\n")
for sigma in sigmas:
    total_errors = 0
    total_ber = 0.0

    for _ in range(num_simulations):
        errors, ber = calculate_ber(payload_bits, sigma)
        total_errors += errors
        total_ber += ber

    avg_errors = total_errors / num_simulations
    avg_ber = total_ber / num_simulations
    average_bers.append(avg_ber)

    print(f"Sigma: {sigma:.2f}, Ошибок: {avg_errors:.0f}, BER: {avg_ber:.4f}")


plt.figure(figsize=(10, 6))
plt.plot(sigmas, average_bers, marker='o', linestyle='-', color='b', label="Средний BER")
plt.title("Зависимость BER от сигмы шума (логарифмический масштаб)")
plt.xlabel("Сигма (уровень шума)")
plt.ylabel("BER (битовая ошибка)")
plt.yscale("log")  
plt.grid(True, which="both", linestyle="--", linewidth=0.5)
plt.legend()
plt.show()
