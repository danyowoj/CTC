#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

// Функция для умножения столбиком двух целых чисел
long long multiply_column(long long num1, long long num2)
{
    // Обработка знака.  Используем побитовое XOR для определения знака результата.
    // Если одно из чисел отрицательное, а другое положительное, результат будет отрицательным.
    bool negative = (num1 < 0) ^ (num2 < 0);
    // Берем абсолютные значения для упрощения вычислений
    num1 = abs(num1);
    num2 = abs(num2);

    // Преобразуем числа в строки для удобства работы с отдельными цифрами
    string s1 = to_string(num1);
    string s2 = to_string(num2);

    // Вектор для хранения промежуточных произведений (частных произведений)
    vector<long long> partial_products(s2.length(), 0);
    // Вектор для хранения промежуточных произведений в виде строк (для вывода на экран)
    vector<string> partial_product_strings(s2.length());

    // Цикл по цифрам второго числа (умножаемого)
    for (int i = s2.length() - 1; i >= 0; --i)
    {
        long long digit2 = s2[i] - '0'; // Извлекаем цифру из строки
        long long carry = 0;            // Перенос
        string partial_product;         // Строка для хранения промежуточного произведения

        // Цикл по цифрам первого числа (множителя)
        for (int j = s1.length() - 1; j >= 0; --j)
        {
            long long digit1 = s1[j] - '0';                              // Извлекаем цифру из строки
            long long product = digit1 * digit2 + carry;                 // Умножаем цифры и добавляем перенос
            carry = product / 10;                                        // Новый перенос
            partial_product = to_string(product % 10) + partial_product; // Добавляем последнюю цифру к строке
        }
        // Если после обработки всех цифр первого числа остаётся перенос, добавляем его к строке
        if (carry > 0)
            partial_product = to_string(carry) + partial_product;

        partial_product += string(s2.length() - 1 - i, '0'); // Добавляем нули в конец промежуточного произведения в зависимости от позиции цифры во втором числе
        partial_product_strings[i] = partial_product;        // Сохраняем строку промежуточного произведения
        partial_products[i] = stoll(partial_product);        // Преобразуем строку в long long и сохраняем в векторе
    }

    // Суммируем все промежуточные произведения
    long long result = 0;
    for (long long pp : partial_products)
        result += pp;

    // Вывод промежуточных результатов для наглядности
    cout << "-------------------------" << endl;
    cout << "Промежуточные результаты:" << endl;
    for (const string &str : partial_product_strings)
    {
        cout << str << endl;
    }
    cout << "-------------------------" << endl;

    // Возвращаем результат с учетом знака
    return negative ? -result : result;
}

int main()
{
    long long num1, num2;
    cout << "Введите первое число: ";
    cin >> num1;
    cout << "Введите второе число: ";
    cin >> num2;
    long long product = multiply_column(num1, num2);
    cout << "Результат: " << product << endl;

    return 0;
}
