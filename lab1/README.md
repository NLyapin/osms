# Практическая работа №1 — Временная и частотная формы сигналов. Преобразования Фурье. Дискретизация сигналов

## Описание 

В данной работе рассматривается генерация периодических сигналов, их дискретизация, прореживание аудиосигналов, спектральный анализ и оценка влияния разрядности аналого-цифрового преобразования (АЦП).

### Основные шаги работы: 
 
1. **Генерация периодического сигнала** 
Генерируется сигнал вида $$y(t) = 2 \cdot \cos(2 \pi f t + \pi/3)$$, где $$f = 4$$ Гц. Визуализируются временная и частотная области сигнала.
 
2. **Оцифровка сигнала** 
Осуществляется оцифровка исходного сигнала на заданной частоте дискретизации. Построение временной и частотной областей сигнала после оцифровки.
 
3. **Прореживание аудиофайла** 
Загружается аудиофайл и прореживается с понижением частоты дискретизации. Проводится сравнение спектров исходного и прореженного сигналов.
 
4. **Оценка влияния разрядности АЦП** 
Исследуется влияние разрядности АЦП на квантование сигнала с различными разрядностями (3, 4, 5 и 6 бит). Визуализируются временные и частотные области квантованных сигналов.

## Установка зависимостей 

Для выполнения работы требуются следующие библиотеки:
 
- `numpy`
 
- `matplotlib`
 
- `scipy`
 
- `soundfile`

Установить зависимости можно командой:


```bash
pip install numpy matplotlib scipy soundfile
```

## Запуск 

Для запуска программы выполните:


```bash
python <название_скрипта>.py
```

### Входные данные: 
 
- `audio.wav`: аудиофайл для прореживания.

## Описание функций 
 
- `generate_signal(frequency, duration, sampling_rate)`: Генерирует периодический сигнал.
 
- `plot_signal_and_spectrum(t, y, Fs, title)`: Строит график сигнала и его спектра.
 
- `sample_signal(y, Fs, num_samples)`: Осуществляет оцифровку сигнала.
 
- `downsample_audio(filename, factor)`: Прореживает аудиофайл с указанным фактором.
 
- `plot_audio_spectra(audio_data, Fs, audio_data_downsampled, new_Fs)`: Сравнивает спектры исходного и прореженного аудиосигналов.
 
- `quantize_signal(signal, bit_depth)`: Квантует сигнал с заданной разрядностью.

## Выводы 

В работе изучены основные аспекты дискретизации сигналов, прореживания аудиофайлов и влияния разрядности АЦП на сигнал.