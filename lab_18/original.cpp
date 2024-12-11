#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <chrono> // Для измерения времени выполнения

#define INF INT_MAX

using namespace std;
using namespace chrono; // Для удобства работы с временем

// Матрица расстояний
const int N = 6;
int C[N][N] = {
    {INF, 13, 7, 5, 2, 9},
    {8, INF, 4, 6, 5, INF},
    {8, 4, INF, 3, 6, 2},
    {5, 6, 1, INF, 0, 1},
    {INF, 6, 1, 4, INF, 9},
    {10, 0, 8, 3, 7, INF}};

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
    // Измерение времени выполнения метода полного перебора
    auto start_brute = high_resolution_clock::now();
    long long min_cost_brute_force = tsp_brute_force(0);
    auto end_brute = high_resolution_clock::now();
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
    cout << "Время выполнения: " << duration_brute << " мкс" << endl;

    // Измерение времени выполнения метода ветвей и границ
    auto start_branch = high_resolution_clock::now();
    long long min_cost_branch_and_bound = tsp_branch_and_bound();
    auto end_branch = high_resolution_clock::now();
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
    cout << "Время выполнения: " << duration_branch << " мкс" << endl;

    return 0;
}
