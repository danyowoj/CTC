#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <chrono> // Для измерения времени выполнения
#include <random> // Для генерации случайных чисел

#define INF INT_MAX

using namespace std;
using namespace chrono; // Для удобства работы с временем

// Размер матрицы
const int N = 10; // Измените это значение для увеличения размера матрицы
int C[N][N];

// Функция для инициализации матрицы случайными значениями
void initialize_matrix()
{
    // Используем текущее время как семя для генератора
    auto now = steady_clock::now().time_since_epoch().count();
    mt19937 gen(static_cast<unsigned int>(now)); // Генератор случайных чисел
    uniform_int_distribution<> dis(1, 100);      // Равномерное распределение от 1 до 100

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (i == j)
            {
                C[i][j] = INF; // Нет пути до самой себя
            }
            else
            {
                C[i][j] = dis(gen); // Случайное значение
            }
        }
    }
}

// Метод полного перебора
long long tsp_brute_force(int start)
{
    vector<int> vertices;
    for (int i = 0; i < N; i++)
    {
        if (i != start)
        {
            vertices.push_back(i);
        }
    }

    long long min_cost = INF;
    do
    {
        long long current_cost = 0;
        int k = start;
        for (int i = 0; i < vertices.size(); i++)
        {
            if (C[k][vertices[i]] == INF)
            {
                current_cost = INF;
                break;
            }
            current_cost += C[k][vertices[i]];
            k = vertices[i];
        }
        if (current_cost != INF && C[k][start] != INF)
        {
            current_cost += C[k][start];
            min_cost = min(min_cost, current_cost);
        }
    } while (next_permutation(vertices.begin(), vertices.end()));

    return min_cost;
}

// Метод ветвей и границ
void tsp_branch_and_bound_util(int level, long long current_cost, long long bound, int current_pos, vector<bool> &visited, long long &min_cost)
{
    if (level == N)
    {
        if (C[current_pos][0] != INF)
        {
            current_cost += C[current_pos][0];
            min_cost = min(min_cost, current_cost);
        }
        return;
    }

    for (int i = 0; i < N; i++)
    {
        if (!visited[i] && C[current_pos][i] != INF)
        {
            visited[i] = true;
            long long temp = bound;

            bound -= (bound + C[current_pos][i]) / 2;
            current_cost += C[current_pos][i];

            if (bound + current_cost < min_cost)
            {
                tsp_branch_and_bound_util(level + 1, current_cost, bound, i, visited, min_cost);
            }

            current_cost -= C[current_pos][i];
            bound = temp;
            visited[i] = false;
        }
    }
}

long long tsp_branch_and_bound()
{
    long long bound = 0;
    for (int i = 0; i < N; i++)
    {
        int min_row = INF;
        for (int j = 0; j < N; j++)
        {
            if (C[i][j] < min_row)
            {
                min_row = C[i][j];
            }
        }
        if (min_row != INF)
        {
            bound += min_row;
        }
    }

    vector<bool> visited(N, false);
    visited[0] = true;

    long long min_cost = INF;
    tsp_branch_and_bound_util(1, 0, bound, 0, visited, min_cost);

    return min_cost;
}

int main()
{
    // Инициализация матрицы случайными значениями
    initialize_matrix();

    // Вывод матрицы
    cout << "Сгенерированная матрица расстояний:" << endl;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (C[i][j] == INF)
            {
                cout << "INF\t";
            }
            else
            {
                cout << C[i][j] << "\t";
            }
        }
        cout << endl;
    }

    // Измерение времени выполнения метода полного перебора
    auto start_brute = steady_clock::now();
    long long min_cost_brute_force = tsp_brute_force(0);
    auto end_brute = steady_clock::now();
    auto duration_brute = duration_cast<microseconds>(end_brute - start_brute).count();

    cout << "\nМетод полного перебора:" << endl;
    if (min_cost_brute_force == INF)
    {
        cout << "Решение не найдено (нет доступного пути)" << endl;
    }
    else
    {
        cout << "Минимальная стоимость пути: " << min_cost_brute_force << endl;
    }
    cout << "Время выполнения: " << duration_brute << " мкс (" << duration_brute / 1000.0 << " мс)" << endl;

    // Измерение времени выполнения метода ветвей и границ
    auto start_branch = steady_clock::now();
    long long min_cost_branch_and_bound = tsp_branch_and_bound();
    auto end_branch = steady_clock::now();
    auto duration_branch = duration_cast<microseconds>(end_branch - start_branch).count();

    cout << "\nМетод ветвей и границ:" << endl;
    if (min_cost_branch_and_bound == INF)
    {
        cout << "Решение не найдено (нет доступного пути)" << endl;
    }
    else
    {
        cout << "Минимальная стоимость пути: " << min_cost_branch_and_bound << endl;
    }
    cout << "Время выполнения: " << duration_branch << " мкс (" << duration_branch / 1000.0 << " мс)" << endl;

    return 0;
}
