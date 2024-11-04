#include <iostream>
#include <vector>
#include <complex> // для использования комплексных чисел
#include <cmath>   // для использования M_PI, sin, cos

using namespace std;

// счетчик комплексных умножений
int counter = 0;

/*
Функция для вычисления Дискретного Преобразования Фурье
Принимает вектор вещественных чисел.
Создает вектор комплексных чисел для хранения преобразованного сигнала.
Реализует два вложенных цикла: внешний проходит по элементам результата, а внутренний рассчитывает сумму.
*/
vector<complex<double>> DFT(const vector<double> &x)
{
    int N = x.size();             // Количество отсчетов
    vector<complex<double>> X(N); // Вектор, хранящий результат

    // Проходим по каждому выходному значению k
    for (int k = 0; k < N; k++)
    {
        complex<double> sum(0.0, 0.0); // Инициализация суммы для k
        // Считаем сумму для данного k
        for (int n = 0; n < N; n++)
        {
            // Вычисление комплексной экспоненты
            double angle = -2 * M_PI * k * n / N;
            complex<double> w(cos(angle), sin(angle));
            // Обновляем сумму
            sum += x[n] * w;
            // увеличиваем счетчик
            counter++;
        }
        X[k] = sum; // Сохраняем результат преобразования для k
    }

    return X; // Возвращаем вектор с результатами
}

/*
Основная функция.
Инициализирует входные данные.
Вызывает функцию ДПФ и выводит результаты в консоль.
*/
int main()
{
    vector<double> input = {1.0, .0, .0, .0, .0, .0, .0, .0, .0, .0}; // Пример входных данных

    // Вычисляем ДПФ
    vector<complex<double>> output = DFT(input);

    // Выводим результаты
    // cout << "DFT Result:" << endl;
    // for (const auto &value : output)
    // {
    //     cout << value << endl; // Каждый комплексный результат
    // }

    // Выводим количество комплексных умножений
    cout << "\nSize = 10" << endl;
    cout << "Complex multiplication counter: " << counter << endl;

    input = {1.0, .0, .0, .0, .0, .0, .0, .0, .0, .0, 1.0, .0, .0, .0, .0, .0, .0, .0, .0, .0};

    counter = 0;

    // Вычисляем ДПФ
    output = DFT(input);

    cout << "\nSize = 20" << endl;
    cout << "Complex multiplication counter: " << counter << endl;

    input = {1.0, .0, .0, .0, .0, .0, .0, .0, .0, .0, 1.0, .0, .0, .0, .0, .0, .0, .0, .0, .0, 1.0, .0, .0, .0, .0, .0, .0, .0, .0, .0, 1.0, .0, .0, .0, .0, .0, .0, .0, .0, .0};

    counter = 0;

    // Вычисляем ДПФ
    output = DFT(input);

    cout << "\nSize = 40" << endl;
    cout << "Complex multiplication counter: " << counter << endl;

    return 0;
}
