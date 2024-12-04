#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

std::string multiply_large_numbers(const std::string &num1, const std::string &num2)
{
    int len1 = num1.size();
    int len2 = num2.size();
    std::vector<int> result(len1 + len2, 0);

    // Умножаем каждую цифру первого числа на каждую цифру второго числа
    for (int i = len1 - 1; i >= 0; --i)
    {
        for (int j = len2 - 1; j >= 0; --j)
        {
            int mul = (num1[i] - '0') * (num2[j] - '0');
            int sum = mul + result[i + j + 1];

            result[i + j + 1] = sum % 10; // сохраняем последнюю цифру
            result[i + j] += sum / 10;    // добавляем десятки к следующему разряду
        }
    }

    // Преобразуем результат в строку
    std::string result_str;
    for (int num : result)
    {
        if (!(result_str.empty() && num == 0))
        { // избегаем ведущих нулей
            result_str.push_back(num + '0');
        }
    }

    return result_str.empty() ? "0" : result_str;
}

void print_multiplication_process(const std::string &num1, const std::string &num2)
{
    std::cout << "Умножение столбиком:\n";
    std::cout << " " << std::string(std::max(num1.size(), num2.size()) + 2, '-') << "\n";
    std::cout << "| " << num1 << "\n";
    std::cout << "|× " << num2 << "\n";
    std::cout << " " << std::string(std::max(num1.size(), num2.size()) + 2, '-') << "\n";

    std::vector<std::string> intermediate_results;

    for (int j = num2.size() - 1; j >= 0; --j)
    {
        int digit = num2[j] - '0';
        if (digit == 0)
        {
            intermediate_results.push_back("0");
            continue;
        }

        std::string current_result;
        int carry = 0;

        // Умножаем текущую цифру второго числа на первое число
        for (int i = num1.size() - 1; i >= 0; --i)
        {
            int mul = digit * (num1[i] - '0') + carry;
            current_result.insert(current_result.begin(), (mul % 10) + '0');
            carry = mul / 10;
        }

        // Добавляем остаток от деления, если он есть
        if (carry > 0)
        {
            current_result.insert(current_result.begin(), carry + '0');
        }

        // Добавляем нули в конец текущего результата
        current_result.append(num2.size() - 1 - j, '0');
        intermediate_results.push_back(current_result);
    }

    // Выравниваем промежуточные результаты и выводим их
    size_t max_width = std::max(num1.size() + num2.size(), intermediate_results.back().size());
    for (size_t i = 0; i < intermediate_results.size(); ++i)
    {
        std::cout << std::setw(max_width) << intermediate_results[i] << "\n";
    }

    // Суммируем результаты и отображаем итог
    std::cout << "+" << std::string(max_width - 1, '-') << "\n";
}

int main()
{
    std::string num1, num2;

    std::cout << "Введите первое число (до 20 знаков): ";
    std::cin >> num1;
    std::cout << "Введите второе число (до 20 знаков): ";
    std::cin >> num2;

    // Проверка на наличие знака
    bool negative_result = (num1[0] == '-' && num2[0] != '-') || (num1[0] != '-' && num2[0] == '-');
    if (num1[0] == '-' || num2[0] == '-')
    {
        num1 = num1[0] == '-' ? num1.substr(1) : num1;
        num2 = num2[0] == '-' ? num2.substr(1) : num2;
    }

    // Печатаем процесс умножения
    print_multiplication_process(num1, num2);

    std::string result = multiply_large_numbers(num1, num2);

    if (negative_result && result != "0")
    {
        result = "-" + result;
    }

    std::cout << "Результат: " << result << "\n";
    return 0;
}
