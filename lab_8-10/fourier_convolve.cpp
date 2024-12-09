#include <iostream>
#include <vector>
#include <complex>
#include <cmath>

using namespace std;

using Vector = vector<complex<double>>;

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
        complex<double> t = polar(1.0, -2 * M_PI * k / n) * odd[k];
        a[k] = even[k] + t;
        a[k + n / 2] = even[k] - t;
    }
}

// Функция свертки с использованием DFT
Vector convolutionDFT(const Vector &a, const Vector &b)
{
    int n = a.size();
    int m = b.size();
    int size = n + m - 1;

    Vector A(size), B(size), C(size);

    // Заполняем A и B нулями
    for (int i = 0; i < n; ++i)
        A[i] = a[i];
    for (int i = 0; i < m; ++i)
        B[i] = b[i];

    // Применяем DFT
    Vector dftA(size), dftB(size);
    DFT(A, dftA);
    DFT(B, dftB);

    // Умножаем DFT
    for (int i = 0; i < size; ++i)
    {
        C[i] = dftA[i] * dftB[i];
    }

    // Применяем обратное DFT
    Vector result(size);
    DFT(C, result); // Здесь можно использовать обратное DFT (необходимо реализовать)

    // Нормируем результат
    for (auto &value : result)
    {
        value /= size; // Делим на размер
    }

    return result;
}

// Функция свертки с использованием FFT (Cooley-Tukey)
Vector convolutionFFT(const Vector &a, const Vector &b)
{
    int n = a.size();
    int m = b.size();
    int size = n + m - 1;

    Vector A(size), B(size);

    // Заполняем A и B нулями
    for (int i = 0; i < n; ++i)
        A[i] = a[i];
    for (int i = 0; i < m; ++i)
        B[i] = b[i];

    // Применяем FFT
    FFT_recursive(A);
    FFT_recursive(B);

    // Умножаем FFT
    for (int i = 0; i < size; ++i)
    {
        A[i] *= B[i];
    }

    // Применяем обратное FFT
    // Здесь также можно использовать другой алгоритм FFT, чтобы получить нормализованный результат
    FFT_recursive(A);

    // Нормируем результат
    for (auto &value : A)
    {
        value /= size; // Делим на размер
    }

    return A;
}

// Функция свертки с использованием FFT Cooley-Lewis
Vector convolutionFFT_n32(const Vector &a, const Vector &b)
{
    int n = a.size();
    int m = b.size();
    int size = n + m - 1;

    Vector A(size), B(size);

    // Заполняем A и B нулями
    for (int i = 0; i < n; ++i)
        A[i] = a[i];
    for (int i = 0; i < m; ++i)
        B[i] = b[i];

    // Применяем Cooley-Lewis FFT
    FFT_n32(A);
    FFT_n32(B);

    // Умножаем FFT
    for (int i = 0; i < size; ++i)
    {
        A[i] *= B[i];
    }

    // Применяем обратное Cooley-Lewis FFT
    FFT_n32(A);

    // Нормируем результат
    for (auto &value : A)
    {
        value /= size; // Делим на размер
    }

    return A;
}

// Функция для демонстрации работы свертки
int main()
{
    Vector a = {1, 2, 3};
    Vector b = {0, 1, 0.5};

    Vector resultDFT = convolutionDFT(a, b);
    cout << "Свертка с использованием DFT (O(n^2)):" << endl;
    for (const auto &value : resultDFT)
    {
        cout << value.real() << "; ";
    }
    cout << endl
         << endl;

    Vector resultFFT = convolutionFFT(a, b);
    cout << "Свертка с использованием FFT (O(n log n)):" << endl;
    for (const auto &value : resultFFT)
    {
        cout << value.real() << "; ";
    }
    cout << endl
         << endl;

    Vector resultFFT_n32 = convolutionFFT_n32(a, b);
    cout << "Свертка с использованием FFT (O(n^{3/2})):" << endl;
    for (const auto &value : resultFFT_n32)
    {
        cout << value.real() << "; ";
    }
    cout << endl
         << endl;

    return 0;
}
