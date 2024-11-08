Объяснение работы алгоритма:
    - Входные параметры: Функция convolve принимает два вектора: signal - это
    последовательность, которую мы анализируем, и kernel - это ядро свертки,
    которое определяет как будет происходить свертка.

    - Размеры последовательностей: Мы определяем размеры входных последовательностей
    для дальнейших расчетов. Размер выходного вектора равен size(signal) + size(kernel) - 1,
    так как во время свертки на крайних участках добавляются дополнительные элементы.

    - Результирующий вектор: Инициализируем выходной вектор result размером outputSize,
    заполненный нулями.

    - Двойной цикл:

        - Внешний цикл проходит по каждому индексу выходного вектора.
        - Внутренний цикл проходит по элементам ядра. На каждой итерации для текущего
        элемента выходного вектора, мы умножаем соответствующий элемент сигнала на элемент
        ядра и добавляем результат к текущему значению в result.

    - Проверка индексов: Проверяем, подходит ли текущий индекс сигнала (вычисленный как i - j)
    для текущей итерации. Это необходимо, чтобы избежать выхода за границы массива.

    - Возврат результата: Функция возвращает заполненный вектор с результатами свертки.