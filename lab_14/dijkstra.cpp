#include <iostream>
#include <vector>
#include <limits> // Для numeric_limits
#include <queue>

using namespace std;

const long long INF = numeric_limits<long long>::max(); // Бесконечность

struct Edge
{
    int to;
    int weight;
};

void dijkstra(int start, const vector<vector<Edge>> &graph, vector<long long> &dist, vector<int> &prev)
{
    int n = graph.size();
    dist.assign(n, INF);
    prev.assign(n, -1);
    dist[start] = 0;

    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq; // Минимальная куча (dist, vertex)
    pq.push({0, start});

    while (!pq.empty())
    {
        long long d = pq.top().first;
        int v = pq.top().second;
        pq.pop();

        if (d > dist[v])
            continue; // Оптимизация: если расстояние больше текущего, пропускаем

        for (const Edge &edge : graph[v])
        {
            long long to = edge.to;
            long long weight = edge.weight;
            if (dist[v] + weight < dist[to])
            {
                dist[to] = dist[v] + weight;
                prev[to] = v;
                pq.push({dist[to], to});
            }
        }
    }
}

int main()
{
    // Пример графа (матрица смежности не используется для большей эффективности)
    vector<vector<Edge>> graph = {
        {{1, 3}, {2, 5}, {3, 1}},
        {{2, 3}},
        {{3, 1}},
        {{2, 6}}};

    int start_node = 0;
    vector<long long> dist;
    vector<int> prev;

    dijkstra(start_node, graph, dist, prev);

    cout << "Кратчайшие расстояния от вершины " << start_node << ":" << endl;
    for (int i = 0; i < dist.size(); ++i)
    {
        if (dist[i] == INF)
        {
            cout << "Вершина " << i << ": недостижима" << endl;
        }
        else
        {
            cout << "Вершина " << i << ": " << dist[i] << endl;
        }
    }

    // Восстановление пути (необязательно, но полезно)
    cout << "\nПути:" << endl;
    for (int i = 0; i < dist.size(); ++i)
    {
        if (dist[i] != INF)
        {
            cout << "Путь до вершины " << i << ": ";
            vector<int> path;
            int curr = i;
            while (curr != -1)
            {
                path.push_back(curr);
                curr = prev[curr];
            }
            for (int j = path.size() - 1; j >= 0; --j)
            {
                cout << path[j] << (j == 0 ? "" : " -> ");
            }
            cout << endl;
        }
    }

    return 0;
}
