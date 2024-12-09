#include <iostream>
#include <vector>

// Функция для выполнения свертки двух последовательностей
std::vector<double> convolve(const std::vector<double> &signal, const std::vector<double> &kernel)
{
    // Получаем размеры входных последовательностей
    int signalSize = signal.size();
    int kernelSize = kernel.size();

    // Размер результирующей последовательности
    int outputSize = signalSize + kernelSize - 1;
    std::vector<double> result(outputSize, 0.0); // Инициализация результирующего вектора

    // Выполнение свертки
    for (int i = 0; i < outputSize; ++i)
    {
        // Инициализируем текущий элемент результата
        result[i] = 0.0;

        // Перебираем ядро
        for (int j = 0; j < kernelSize; ++j)
        {
            // Индекс для сигнала
            int signalIndex = i - j;

            // Убедимся, что индекс находится в допустимых границах
            if (signalIndex >= 0 && signalIndex < signalSize)
            {
                // Выполняем свертку
                result[i] += signal[signalIndex] * kernel[j];
            }
        }
    }

    return result; // Возвращаем результирующую последовательность
}

int main()
{
    // Пример использования
    std::vector<double> signal = {1, 2, 3};
    std::vector<double> kernel = {4, 5};

    // Выполняем свертку
    std::vector<double> result = convolve(signal, kernel);

    // Выводим результат
    std::cout << "Результат свертки: ";
    for (double val : result)
    {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    return 0;
}
