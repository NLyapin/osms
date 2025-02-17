# Практическая работа №5 

## Описание программы 

Программа предназначена для вычисления контрольной суммы (CRC) пакета данных, проверки корректности передачи данных по каналу связи и анализа обнаружения ошибок при искажении битов.

## Основные этапы работы программы 
 
1. **Генерация данных:**  
  - Формируется случайный пакет длиной $$N = 25$$ или $$N = 250$$ бит.
 
2. **Вычисление CRC:**  
  - Остаток от деления пакета данных на порождающий полином $$G = x^7 + x^5 + x^3 + x^2 + x + 1$$ используется как CRC.
 
3. **Передача данных:** 
  - CRC добавляется к исходным данным для формирования полного пакета.
 
4. **Проверка на приемной стороне:** 
  - Пакет с CRC делится на порождающий полином. Если остаток равен нулю, ошибок нет.
 
5. **Тестирование с искажениями:** 
  - Все биты пакета поочередно инвертируются. Программа проверяет, обнаружены ли ошибки.
 
6. **Вывод результатов:** 
  - Показывает, сколько ошибок было обнаружено и сколько пропущено.

## Использование 
 
1. Скомпилируйте программу:


```bash
g++ crc_program.cpp -o crc_program
```
 
2. Запустите программу:


```bash
./crc_program
```

## Результат работы 

Программа выведет:

- Сгенерированные данные и CRC.

- Пакет данных с CRC.

- Отчет об ошибках в принятом пакете.

- Результаты тестирования искажений (количество обнаруженных и пропущенных ошибок).

## Пример вывода 


```yaml
---- N = 25 ----  
Data: [1 0 1 0 ...]  
CRC: [1 1 0 1 0 1 1]  
Data with CRC: [1 0 1 0 ...]  
No errors detected.  

---- N = 250 ----  
Data: [0 1 1 0 ...]  
CRC: [1 1 0 1 0 1 1]  
Data with CRC: [0 1 1 0 ...]  
No errors detected.  

---- Data with errors ----  
Error detection results, N = 250  
Errors Detected: 255  
Errors Missed: 0
```

## Контрольные вопросы 
 
1. Для чего используются CRC-проверки?
CRC проверяет целостность данных, помогая обнаружить ошибки при передаче.
 
2. Что такое порождающий полином?
Это фиксированный полином, который используется для вычисления остатка (CRC) при делении данных.
 
3. Как вычисляется CRC?
Остаток от деления данных на порождающий полином добавляется в конец пакета. На приемной стороне этот остаток проверяется повторно.
