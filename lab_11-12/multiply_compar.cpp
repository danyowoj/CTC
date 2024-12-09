#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <string>
#include <algorithm>

// Комплексное число для FFT
using Complex = std::complex<double>;
const double PI = acos(-1);

// Быстрое преобразование Фурье
void fft(std::vector<Complex> &a, bool invert)
{
    int n = a.size();
    if (n == 1)
        return;

    std::vector<Complex> a0(n / 2), a1(n / 2);
    for (int i = 0; 2 * i < n; i++)
    {
        a0[i] = a[2 * i];
        a1[i] = a[2 * i + 1];
    }

    fft(a0, invert);
    fft(a1, invert);

    double angle = 2 * PI / n * (invert ? -1 : 1);
    Complex w(1), wn(cos(angle), sin(angle));
    for (int i = 0; 2 * i < n; i++)
    {
        a[i] = a0[i] + w * a1[i];
        a[i + n / 2] = a0[i] - w * a1[i];
        if (invert)
        {
            a[i] /= 2;
            a[i + n / 2] /= 2;
        }
        w *= wn;
    }
}

// Умножение двух больших чисел через FFT
std::string multiplyFFT(const std::string &num1, const std::string &num2)
{
    std::vector<int> a, b;
    for (int i = num1.size() - 1; i >= 0; --i)
        a.push_back(num1[i] - '0');
    for (int i = num2.size() - 1; i >= 0; --i)
        b.push_back(num2[i] - '0');

    int n = 1;
    while (n < a.size() + b.size())
        n <<= 1;
    std::vector<Complex> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; ++i)
        fa[i] *= fb[i];
    fft(fa, true);

    std::vector<int> result(n);
    int carry = 0;
    for (int i = 0; i < n; ++i)
    {
        result[i] = int(fa[i].real() + 0.5) + carry;
        carry = result[i] / 10;
        result[i] %= 10;
    }

    std::string product;
    while (!result.empty() && result.back() == 0)
        result.pop_back();
    for (int i = result.size() - 1; i >= 0; --i)
        product.push_back(result[i] + '0');
    return product.empty() ? "0" : product;
}

// Умножение столбиком для сравнения
std::string multiplyColumn(const std::string &num1, const std::string &num2)
{
    int n = num1.size(), m = num2.size();
    std::vector<int> result(n + m, 0);

    for (int i = n - 1; i >= 0; --i)
    {
        for (int j = m - 1; j >= 0; --j)
        {
            int mul = (num1[i] - '0') * (num2[j] - '0');
            int sum = result[i + j + 1] + mul;
            result[i + j + 1] = sum % 10;
            result[i + j] += sum / 10;
        }
    }

    std::string product;
    for (int num : result)
    {
        if (!(product.empty() && num == 0))
            product.push_back(num + '0');
    }
    return product.empty() ? "0" : product;
}

// Генерация случайного числа заданной длины
std::string generateRandomNumber(int length)
{
    std::string number;
    number.push_back('1' + rand() % 9); // Первая цифра не может быть 0
    for (int i = 1; i < length; ++i)
    {
        number.push_back('0' + rand() % 10);
    }
    return number;
}

// Измерение времени выполнения
double measureTime(const std::string &num1, const std::string &num2, std::string (*multiplyFunc)(const std::string &, const std::string &))
{
    clock_t start = clock();
    std::string result = multiplyFunc(num1, num2);
    clock_t end = clock();
    return double(end - start) / CLOCKS_PER_SEC;
}

int main()
{
    srand(static_cast<unsigned>(time(0)));

    int length = 10000; // Длина случайных чисел
    std::string num1 = generateRandomNumber(length);
    std::string num2 = generateRandomNumber(length);

    std::cout << "Длина перемножаемых чисел: " << length << std::endl;

    // FFT умножение
    double timeFFT = measureTime(num1, num2, multiplyFFT);
    std::cout << "Время умножения через FFT: " << timeFFT << " секунд." << std::endl;

    // Умножение столбиком
    double timeColumn = measureTime(num1, num2, multiplyColumn);
    std::cout << "Время умножения столбиком: " << timeColumn << " секунд." << std::endl;

    // // Просто FFT умножение с вводом с клавиатуры
    // std::string num1, num2;
    // std::cout << "Введите первое число: ";
    // std::cin >> num1;

    // std::cout << "Введите второе число: ";
    // std::cin >> num2;

    // std::cout << "Результат умножения через FFT: " << multiplyFFT(num1, num2) << std::endl;

    return 0;
}
