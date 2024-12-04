#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <chrono>
#include <math.h>

using namespace std;

using Complex = complex<double>;
using Vector = vector<Complex>;

// O(n^2) Discrete Fourier Transform (DFT)
void DFT(const Vector &input, Vector &output)
{
    int n = input.size();
    output.resize(n);
    for (int k = 0; k < n; ++k)
    {
        output[k] = 0;
        for (int j = 0; j < n; ++j)
        {
            double angle = -2.0 * M_PI * k * j / n;
            output[k] += input[j] * polar(1.0, angle);
        }
    }
}

// O(n^{3/2}) Discrete Fourier Transform (Cooley-Lewis)
void FFT_n32(Vector &a)
{
    int n = a.size();
    int m = static_cast<int>(sqrt(n) + 0.5); // Округляем sqrt(n) до ближайшего целого
    int k = n / m;
    Vector sub_result(m);

    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < k; ++j)
        {
            sub_result[i] += a[j * m + i] * polar(1.0, -2 * M_PI * i * j / n);
        }
    }

    Vector result(n);
    for (int i = 0; i < k; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            result[i * m + j] = sub_result[j] * polar(1.0, -2 * M_PI * i * j / n);
        }
    }
    a = move(result);
}

// O(n log n) FFT (Cooley-Tukey Recursive)
void FFT_recursive(Vector &a)
{
    int n = a.size();
    if (n <= 1)
        return;

    Vector even(n / 2), odd(n / 2);
    for (int i = 0; i < n / 2; ++i)
    {
        even[i] = a[i * 2];
        odd[i] = a[i * 2 + 1];
    }

    FFT_recursive(even);
    FFT_recursive(odd);

    for (int k = 0; k < n / 2; ++k)
    {
        Complex t = polar(1.0, -2 * M_PI * k / n) * odd[k];
        a[k] = even[k] + t;
        a[k + n / 2] = even[k] - t;
    }
}

// Функция для замера времени выполнения
template <typename Func, typename... Args>
double measure_time(Func func, Args &&...args)
{
    int repeats = 10; // Повторяем несколько раз для повышения точности
    double total_time = 0;
    for (int i = 0; i < repeats; ++i)
    {
        auto start = chrono::high_resolution_clock::now();
        func(forward<Args>(args)...);
        auto end = chrono::high_resolution_clock::now();
        total_time += chrono::duration<double>(end - start).count();
    }
    return total_time / repeats;
}

// Генерация тестовых данных
Vector generate_data(int n)
{
    Vector data(n);
    for (int i = 0; i < n; ++i)
    {
        data[i] = Complex(rand() % 100, rand() % 100);
    }
    return data;
}

int main()
{
    vector<int> sizes = {(int)pow(2, 15), (int)pow(2, 16), (int)pow(2, 17), (int)pow(2, 18), (int)pow(2, 19), (int)pow(2, 20)}; // Размеры для тестов

    for (int n : sizes)
    {
        cout << "Размер данных: " << n << endl;

        auto data = generate_data(n);

        // Замер для O(n^2)
        // Vector output_n2;
        // double time_n2 = measure_time([&]()
        //                               { DFT(data, output_n2); });
        // cout << "DFT (O(n^2)): " << time_n2 << " сек." << endl;

        // Замер для O(n^{3/2})
        auto data_n32 = data;
        double time_n32 = measure_time([&]()
                                       { FFT_n32(data_n32); });
        cout << "FFT (O(n^{3/2})): " << time_n32 << " сек." << endl;

        // Замер для O(n log n)
        auto data_fft = data;
        double time_fft = measure_time([&]()
                                       { FFT_recursive(data_fft); });
        cout << "FFT (O(n log n)): " << time_fft << " сек." << endl;

        cout << "----------------------------------" << endl;
    }

    return 0;
}
