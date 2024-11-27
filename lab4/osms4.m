% Параметры последовательностей Голда
SIZE = 5;
length_seq = 2^SIZE - 1;

% Начальные состояния регистров для последовательностей
regs = {
    [0, 1, 0, 0, 1], [1, 0, 0, 0, 0];  %9 9+7
    [0, 1, 0, 1, 0], [0, 1, 0, 1, 1]   %9+1 9+2
};

% Генерация последовательностей Голда
[gold_seq1, reg1_final] = generate_sequence(regs{1,1}, regs{1,2}, length_seq);
[gold_seq2, reg2_final] = generate_sequence(regs{2,1}, regs{2,2}, length_seq);

% Вывод последовательностей
disp_gold_sequence('Первая последовательность Голда (x = 12, y = 19)', gold_seq1);
disp_gold_sequence('Вторая последовательность Голда (x = 13, y = 14)', gold_seq2);

% Вычисление и отображение корреляций
plot_correlations(gold_seq1, gold_seq2);

% Функция для генерации последовательности Голда
function [seq, reg_final] = generate_sequence(reg_x, reg_y, length)
    seq = zeros(1, length);
    for i = 1:length
        seq(i) = mod(reg_x(end) + reg_y(end), 2);
        [reg_x, reg_y] = shift_registers(reg_x, reg_y);
    end
    reg_final = {reg_x, reg_y};
end

% Функция сдвига регистров
function [reg_x, reg_y] = shift_registers(reg_x, reg_y)
    reg_x = [mod(reg_x(4) + reg_x(5), 2), reg_x(1:end-1)];
    reg_y = [mod(reg_y(3) + reg_y(5), 2), reg_y(1:end-1)];
end

% Функция для вывода последовательности Голда
function disp_gold_sequence(title_str, gold_seq)
    fprintf('%s:\n', title_str);
    fprintf('Последовательность Голда: %s\n\n', num2str(gold_seq));
end

% Функция для вычисления и отображения корреляций
function plot_correlations(seq1, seq2)
    [cor1, lag1] = xcorr(seq1, 'normalized');
    [cor2, lag2] = xcorr(seq2, 'normalized');
    [cross_cor, lag_cross] = xcorr(seq1, seq2, 'normalized');

    positive_lag_idx = lag1 >= 0 & lag1 <= 31;

    figure('Name', 'Корреляции последовательностей Голда');

    subplot(3,1,1);
    stem(lag1(positive_lag_idx), cor1(positive_lag_idx));
    title('Автокорреляция первой последовательности');
    xlabel('Задержка (лаг)');
    ylabel('Значение автокорреляции');
    xlim([0, 30]); 

    subplot(3,1,2);
    stem(lag2(positive_lag_idx), cor2(positive_lag_idx));
    title('Автокорреляция второй последовательности');
    xlabel('Задержка (лаг)');
    ylabel('Значение автокорреляции');
    xlim([0, 30]);

    subplot(3,1,3);
    stem(lag_cross(positive_lag_idx), cross_cor(positive_lag_idx));
    title('Взаимная корреляция последовательностей');
    xlabel('Задержка (лаг)');
    ylabel('Значение взаимной корреляции');
    xlim([0, 30]);

    display_correlation_values(lag1, cor1, 'Автокорреляция первой последовательности');
    display_correlation_values(lag2, cor2, 'Автокорреляция второй последовательности');
    display_correlation_values(lag_cross, cross_cor, 'Взаимная корреляция');
end

% Функция для вывода значений корреляции
function display_correlation_values(lag, cor, title_str)
    fprintf('\n--- Значения %s ---\n', title_str);
    positive_lag_idx = lag >= 0 & lag <= 31;
    for i = find(positive_lag_idx)
        fprintf('Задержка %d: %.3f\n', lag(i), cor(i));
    end
end
