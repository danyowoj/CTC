#include <iostream>
#include <vector>
#include <complex>
#include <algorithm>
#include <cmath>

// Определяем комплексный тип дляРаботы с числами
typedef std::complex<double> Complex;

// Функция для выполнения FFT (быстрое преобразование Фурье)
void fft(std::vector<Complex> &x)
{
    int n = x.size();
    if (n <= 1)
        return;

    // Разделяем на четные и нечетные
    std::vector<Complex> even(n / 2), odd(n / 2);
    for (int i = 0; i < n / 2; ++i)
    {
        even[i] = x[i * 2];
        odd[i] = x[i * 2 + 1];
    }

    // Рекурсивно вызываем FFT для четных и нечетных
    fft(even);
    fft(odd);

    // Объединяем результаты
    for (int k = 0; k < n / 2; ++k)
    {
        Complex t = std::polar(1.0, -2 * 3.14 * k / n) * odd[k];
        x[k] = even[k] + t;
        x[k + n / 2] = even[k] - t;
    }
}

// Функция для получения обратного FFT
void ifft(std::vector<Complex> &x)
{
    // Конъюгируем элементы
    for (auto &value : x)
    {
        value = std::conj(value);
    }

    // Выполняем FFT
    fft(x);

    // Конъюгируем обратно и нормируем
    for (auto &value : x)
    {
        value = std::conj(value) / (double)x.size();
    }
}

// Функция свертки двух последовательностей
std::vector<double> convolution(const std::vector<double> &a, const std::vector<double> &b)
{
    // Размер результата соответствует сумме размерностей входных последовательностей
    int n = 1;
    while (n < a.size() + b.size())
        n <<= 1; // Увеличиваем n до следующей степени двойки

    // Создаем векторы, заполняем их данными
    std::vector<Complex> fa(n), fb(n);
    for (size_t i = 0; i < a.size(); ++i)
        fa[i] = a[i];
    for (size_t i = 0; i < b.size(); ++i)
        fb[i] = b[i];

    // Применяем FFT к обеим последовательностям
    fft(fa);
    fft(fb);

    // Умножаем результаты поэлементно
    for (int i = 0; i < n; ++i)
    {
        fa[i] *= fb[i];
    }

    // Выполняем обратное FFT
    ifft(fa);

    // Извлекаем только действительные части
    std::vector<double> result(a.size() + b.size() - 1);
    for (size_t i = 0; i < result.size(); ++i)
    {
        result[i] = fa[i].real();
    }

    return result;
}

// Пример использования
int main()
{
    std::vector<double> a = {1, 2, 3};
    std::vector<double> b = {4, 5};

    std::vector<double> result = convolution(a, b);

    // Выводим результат свертки
    std::cout << "Свертка: ";
    std::cout << std::fixed;
    std::cout.precision(2);
    for (const auto &value : result)
    {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    return 0;
}
