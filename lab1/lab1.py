import numpy as np
import matplotlib.pyplot as plt
from scipy.fft import fft, ifft, fftfreq
from scipy.io import wavfile
from scipy.signal import resample
import soundfile as sf


# Генерация периодического сигнала y(t) = 2 * cos(2 * pi * f * t + pi/3), f = 4 Гц
def generate_signal(frequency, duration, sampling_rate):
    t = np.linspace(0, duration, int(sampling_rate * duration), endpoint=False)
    y = 2 * np.cos(2 * np.pi * frequency * t + np.pi / 3)
    return t, y


# Оцифровка сигнала и построение его спектра
def plot_signal_and_spectrum(t, y, Fs, title):
    plt.figure(figsize=(12, 6))

    # Временная область
    plt.subplot(211)
    plt.plot(t, y, label='Сигнал')
    plt.title(f'{title}: Временная область')
    plt.xlabel('Время (с)')
    plt.ylabel('Амплитуда')
    plt.grid(True)

    # Частотная область (спектр)
    plt.subplot(212)
    spectrum = fft(y)
    frequencies = fftfreq(len(y), 1 / Fs)
    plt.plot(frequencies[:len(frequencies) // 2], np.abs(spectrum[:len(frequencies) // 2]))
    plt.title(f'{title}: Частотная область')
    plt.xlabel('Частота (Гц)')
    plt.ylabel('Амплитуда')
    plt.grid(True)
    plt.tight_layout()
    plt.show()


# Оцифровка сигнала
def sample_signal(y, Fs, num_samples):
    sampled_signal = resample(y, num_samples)
    return sampled_signal


# Прореживание аудиофайла
def downsample_audio(filename, factor):
    Fs, audio_data = wavfile.read(filename)
    print(f"\nЧастота дискретизации: {Fs} Гц")
    print(f"Размер массива данных: {audio_data.size}")

    duration_audio = len(audio_data) / Fs
    print(f"Длительность звукозаписи: {duration_audio} секунд")

    # Прореживание
    new_Fs = Fs // factor
    num_samples_new = int(len(audio_data) * (new_Fs / Fs))
    audio_data_downsampled = resample(audio_data, num_samples_new)
    output_filename = "audio_downsampled.wav"
    wavfile.write(output_filename, int(new_Fs), audio_data_downsampled.astype(np.int16))
    print(f"Прореженный сигнал сохранен в файл: {output_filename}\n")

    # Построение спектров
    plot_audio_spectra(audio_data, Fs, audio_data_downsampled, new_Fs)


# Построение спектров оригинального и прореженного сигналов
def plot_audio_spectra(audio_data, Fs, audio_data_downsampled, new_Fs):
    num_channels = audio_data.shape[1] if len(audio_data.shape) > 1 else 1
    plt.figure(figsize=(12, 6))

    # Спектр оригинального сигнала
    plt.subplot(211)
    for channel in range(num_channels):
        spectrum_original = fft(audio_data[:, channel] if num_channels > 1 else audio_data)
        amplitudes_original = np.abs(spectrum_original)
        frequencies_original = fftfreq(audio_data.shape[0], 1 / Fs)
        plt.plot(frequencies_original[:len(frequencies_original) // 2],
                 amplitudes_original[:len(frequencies_original) // 2], label=f"Канал {channel + 1}")

    plt.title('Амплитудный спектр оригинального сигнала')
    plt.xlabel('Частота (Гц)')
    plt.ylabel('Амплитуда')
    plt.xlim(0, Fs / 2)  # Ограничиваем ось частот до Fs/2
    plt.legend()
    plt.grid(True)

    # Спектр прореженного сигнала
    plt.subplot(212)
    num_channels_downsampled = audio_data_downsampled.shape[1] if len(audio_data_downsampled.shape) > 1 else 1
    for channel in range(num_channels_downsampled):
        spectrum_downsampled = fft(
            audio_data_downsampled[:, channel] if num_channels_downsampled > 1 else audio_data_downsampled)
        amplitudes_downsampled = np.abs(spectrum_downsampled)
        frequencies_downsampled = fftfreq(audio_data_downsampled.shape[0], 1 / new_Fs)

        # Пропорционально масштабируем частоты для отображения в тех же пределах, что и оригинал
        plt.plot(frequencies_downsampled[:len(frequencies_downsampled) // 2] * (new_Fs / Fs),
                 amplitudes_downsampled[:len(frequencies_downsampled) // 2], label=f"Канал {channel + 1}")

    plt.title('Амплитудный спектр прореженного сигнала')
    plt.xlabel('Частота (Гц)')
    plt.ylabel('Амплитуда')
    plt.xlim(0, Fs / 2)  # Устанавливаем такой же лимит оси частот
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.show()


# Оценка влияния разрядности АЦП
def quantize_signal(signal, bit_depth):
    max_level = 2 ** bit_depth - 1
    min_value = np.min(signal)
    max_value = np.max(signal)
    signal_normalized = (signal - min_value) / (max_value - min_value) * max_level
    quantized_signal = np.round(signal_normalized) / max_level * (max_value - min_value) + min_value
    return quantized_signal


if __name__ == "__main__":
    # Параметры сигнала
    frequency = 4  # Гц
    duration = 1  # секунда
    Fs = 100  # Частота дискретизации

    # Генерация и визуализация сигнала
    t, y = generate_signal(frequency, duration, Fs)
    plot_signal_and_spectrum(t, y, Fs, 'Оригинальный сигнал')

    # Минимальная частота дискретизации (теорема Котельникова)
    min_Fs = 2 * frequency
    print(f"Минимальная частота дискретизации по теореме Котельникова: {min_Fs} Гц")

    # Оцифровка сигнала
    num_samples = int(Fs * duration)
    sampled_signal = sample_signal(y, Fs, num_samples)
    plot_signal_and_spectrum(t, sampled_signal, Fs, 'Оцифрованный сигнал')

    # Работа с аудиофайлом: прореживание
    downsample_audio('audio.wav', 10)

    # Оценка влияния разрядности АЦП
    bit_depths = [3, 4, 5, 6]
    for bits in bit_depths:
        quantized_signal = quantize_signal(y, bits)
        plot_signal_and_spectrum(t, quantized_signal, Fs, f'Квантованный сигнал с {bits}-разрядным АЦП')
