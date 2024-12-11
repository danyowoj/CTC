#include <iostream>
#include <vector>
#include <limits>
#include <functional> // Для std::function

// Функция для вычисления минимальной стоимости умножения матриц
void matrixChainOrder(const std::vector<int> &dimensions)
{
    int n = dimensions.size() - 1; // Количество матриц

    // Таблица для хранения минимальных затрат на умножение
    std::vector<std::vector<int>> dp(n, std::vector<int>(n, 0));

    // Таблица для хранения индексов, где оптимально ставить скобки
    std::vector<std::vector<int>> split(n, std::vector<int>(n, 0));

    // Заполняем таблицу dp по длинам цепочек
    for (int chainLength = 2; chainLength <= n; ++chainLength)
    {
        for (int i = 0; i < n - chainLength + 1; ++i)
        {
            int j = i + chainLength - 1;
            dp[i][j] = std::numeric_limits<int>::max();

            for (int k = i; k < j; ++k)
            {
                int cost = dp[i][k] + dp[k + 1][j] + dimensions[i] * dimensions[k + 1] * dimensions[j + 1];
                if (cost < dp[i][j])
                {
                    dp[i][j] = cost;
                    split[i][j] = k;
                }
            }
        }
    }

    // Вывод минимальной стоимости
    std::cout << "Минимальная стоимость умножения матриц: " << dp[0][n - 1] << std::endl;

    // Функция для построения оптимального порядка скобок
    std::function<void(int, int)> printOptimalParenthesis = [&](int i, int j)
    {
        if (i == j)
        {
            std::cout << "A" << i + 1;
        }
        else
        {
            std::cout << "(";
            printOptimalParenthesis(i, split[i][j]);
            printOptimalParenthesis(split[i][j] + 1, j);
            std::cout << ")";
        }
    };

    // Вывод оптимального порядка расстановки скобок
    std::cout << "Оптимальный порядок умножения: ";
    printOptimalParenthesis(0, n - 1);
    std::cout << std::endl;
}

int main()
{
    // Пример использования
    // Матрицы с размерами 2x3, 3x4, 4x5
    std::vector<int> dimensions = {2, 3, 4, 5};

    // Вызываем функцию для расчета
    matrixChainOrder(dimensions);

    return 0;
}
