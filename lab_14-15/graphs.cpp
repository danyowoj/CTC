#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include <string>

const int INF = std::numeric_limits<int>::max(); // Значение "бесконечность"

// Функция для восстановления пути
void printPath(int vertex, const std::vector<int> &predecessor)
{
    if (vertex == -1)
    {
        return;
    }
    printPath(predecessor[vertex], predecessor);
    std::cout << vertex << " ";
}

// Алгоритм Форда-Беллмана
void bellmanFord(const std::vector<std::vector<int>> &graph, int src)
{
    int V = graph.size();
    std::vector<int> dist(V, INF);
    std::vector<int> predecessor(V, -1); // Хранит предшественников
    dist[src] = 0;

    // Алгоритм Форда-Беллмана
    for (int i = 0; i < V - 1; ++i)
    {
        for (int u = 0; u < V; ++u)
        {
            for (int v = 0; v < V; ++v)
            {
                if (graph[u][v] != 0 && dist[u] != INF && dist[u] + graph[u][v] < dist[v])
                {
                    dist[v] = dist[u] + graph[u][v];
                    predecessor[v] = u; // Запоминаем, откуда пришли
                }
            }
        }
    }

    // Проверка на наличие отрицательных циклов
    for (int u = 0; u < V; ++u)
    {
        for (int v = 0; v < V; ++v)
        {
            if (graph[u][v] != 0 && dist[u] != INF && dist[u] + graph[u][v] < dist[v])
            {
                std::cout << "Граф содержит отрицательный цикл." << std::endl;
                return;
            }
        }
    }

    // Вывод кратчайших расстояний и путей
    std::cout << "Кратчайшие расстояния и пути от вершины " << src << " (Форд-Беллман):" << std::endl;
    for (int i = 0; i < V; ++i)
    {
        if (dist[i] == INF)
        {
            std::cout << "Вершина " << i << ": недостижима" << std::endl;
        }
        else
        {
            std::cout << "Вершина " << i << ": расстояние = " << dist[i] << ", путь = ";
            printPath(i, predecessor);
            std::cout << std::endl;
        }
    }
}

// Алгоритм Дейкстры
void dijkstra(const std::vector<std::vector<int>> &graph, int src)
{
    int V = graph.size();
    std::vector<int> dist(V, INF);
    std::vector<int> predecessor(V, -1); // Хранит предшественников
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        for (int v = 0; v < V; ++v)
        {
            if (graph[u][v] != 0 && dist[u] != INF && dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
                predecessor[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    // Вывод кратчайших расстояний и путей
    std::cout << "Кратчайшие расстояния и пути от вершины " << src << " (Дейкстра):" << std::endl;
    for (int i = 0; i < V; ++i)
    {
        if (dist[i] == INF)
        {
            std::cout << "Вершина " << i << ": недостижима" << std::endl;
        }
        else
        {
            std::cout << "Вершина " << i << ": расстояние = " << dist[i] << ", путь = ";
            printPath(i, predecessor);
            std::cout << std::endl;
        }
    }
}

int main()
{
    // Матрица смежности
    std::vector<std::vector<int>> graph = {
        {0, 25, 15, 7, 2},
        {25, 0, 6, 0, 0},
        {15, 6, 0, 4, 0},
        {7, 0, 4, 0, 3},
        {2, 0, 0, 3, 0}};

    int src = 0; // Начальная вершина
    std::cout << "Выберите алгоритм для поиска кратчайшего пути:\n";
    std::cout << "1. Форд-Беллман\n";
    std::cout << "2. Дейкстра\n";
    std::cout << "Введите номер алгоритма: ";
    int choice;
    std::cin >> choice;

    if (choice == 1)
    {
        bellmanFord(graph, src);
    }
    else if (choice == 2)
    {
        dijkstra(graph, src);
    }
    else
    {
        std::cout << "Неверный выбор. Завершение программы." << std::endl;
    }

    return 0;
}
