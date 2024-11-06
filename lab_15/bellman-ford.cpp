#include <iostream>
#include <vector>
#include <string>
#include <limits> // Для numeric_limits

using namespace std;

// Представление бесконечности
const long long INF = numeric_limits<long long>::max();

struct Edge
{
    int to;
    int weight;
};

// Функция для реализации алгоритма Беллмана-Форда
vector<long long> bellmanFord(int numVertices, const vector<vector<Edge>> &graph, int source)
{
    vector<long long> dist(numVertices, INF); // Инициализация расстояний бесконечностью
    dist[source] = 0;                         // Расстояние от источника до самого себя равно 0

    // Релаксация ребер |V| - 1 раз.
    // |V| - число вершин.
    for (int i = 1; i < numVertices; ++i)
    {
        for (int u = 0; u < numVertices; ++u)
        {
            for (const auto &edge : graph[u])
            {
                if (dist[u] != INF && dist[u] + edge.weight < dist[edge.to])
                {
                    dist[edge.to] = dist[u] + edge.weight;
                }
            }
        }
    }

    // Проверка на наличие отрицательных циклов.
    // Если после |V| - 1 итерации можно ещё улучшить, значит есть цикл.
    for (int u = 0; u < numVertices; ++u)
        for (const auto &edge : graph[u])
            if (dist[u] != INF && dist[u] + edge.weight < dist[edge.to])
                // Возвращаем пустой вектор, сигнализирующий о наличии отрицательного цикла
                return vector<long long>();

    return dist;
}

int main()
{
    int numVertices, numEdges;
    cout << "Введите количество вершин: ";
    cin >> numVertices;
    cout << "Введите количество ребер: ";
    cin >> numEdges;

    vector<vector<Edge>> graph(numVertices);

    cout << "Введите ребра в формате (от, до, вес):" << endl;
    for (int i = 0; i < numEdges; ++i)
    {
        int u, v, weight;
        cin >> u >> v >> weight;
        graph[u].push_back({v, weight});
    }

    int source;
    cout << "Введите начальную вершину: ";
    cin >> source;

    vector<long long> shortestDistances = bellmanFord(numVertices, graph, source);

    if (shortestDistances.empty())
    {
        cout << "Обнаружен отрицательный цикл!" << endl;
    }
    else
    {
        cout << "Кратчайшие расстояния от вершины " << source << ":" << endl;
        for (int i = 0; i < numVertices; ++i)
        {
            cout << "К вершине " << i << ": " << (shortestDistances[i] == INF ? "Бесконечность" : to_string(shortestDistances[i])) << endl;
        }
    }

    return 0;
}
