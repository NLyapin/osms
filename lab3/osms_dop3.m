% Входные данные
dataA = [0.03, 0.02, 1, 4.2, -2, 1.5, 0]; % Данные для автокорреляции A
dataB = [0.009, 400, -20, 1006, 10, 0.001, 20]; % Данные для автокорреляции B

% Инициализация массивов для хранения значений автокорреляции
autoCorrA = zeros(1, length(dataA)); % Автокорреляция для данных A
normAutoCorrA = zeros(1, length(dataA)); % Нормированная автокорреляция для данных A
normAutoCorrB = zeros(1, length(dataB)); % Нормированная автокорреляция для данных B

% Расчет автокорреляции для dataA
for i = 1:length(dataA)
    shiftedDataA = circshift(dataA, i - 1); % Сдвиг данных A
    autoCorrA(i) = sum(dataA .* shiftedDataA); % Вычисление автокорреляции
    sumDataA = sum(dataA .* dataA); % Сумма квадратов данных A
    sumShiftedA = sum(shiftedDataA .* shiftedDataA); % Сумма квадратов сдвинутых данных A
    normAutoCorrA(i) = autoCorrA(i) / sqrt(sumDataA * sumShiftedA); % Нормировка автокорреляции
end

% Инициализация массива для хранения значений автокорреляции для dataB
autoCorrB = zeros(1, length(dataB));

% Расчет автокорреляции для dataB
for i = 1:length(dataB)
    shiftedDataB = circshift(dataB, i - 1); % Сдвиг данных B
    autoCorrB(i) = sum(dataB .* shiftedDataB); % Вычисление автокорреляции
    sumDataB = sum(dataB .* dataB); % Сумма квадратов данных B
    sumShiftedB = sum(shiftedDataB .* shiftedDataB); % Сумма квадратов сдвинутых данных B
    normAutoCorrB(i) = autoCorrB(i) / sqrt(sumDataB * sumShiftedB); % Нормировка автокорреляции
end

% Вывод нормированных автокорреляций
fprintf('Нормированная автокорреляция для данных A:\n');
for i = 1:length(normAutoCorrA)
    fprintf('Сдвиг %d: %.4f\n', i-1, normAutoCorrA(i));
end

fprintf('\nНормированная автокорреляция для данных B:\n');
for i = 1:length(normAutoCorrB)
    fprintf('Сдвиг %d: %.4f\n', i-1, normAutoCorrB(i));
end

% Временные оси
t1 = 0:length(dataA) - 1; % Временная ось для данных A
t2 = 0:length(dataB) - 1; % Временная ось для данных B


figure;
plot(t1, normAutoCorrA, 'b-', 'LineWidth', 2); 
hold on; 
plot(t2, normAutoCorrB, 'r-', 'LineWidth', 2); 
title('Нормированная автокорреляция для данных A и B');
xlabel('Сдвиг');
ylabel('Нормированная автокорреляция');
grid on;
hold off;
