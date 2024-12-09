#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

struct Edge
{
    int u, v, weight;
};

class DisjointSet
{
public:
    DisjointSet(int n) : parent(n), rank(n, 0)
    {
        for (int i = 0; i < n; ++i)
        {
            parent[i] = i;
        }
    }

    int find(int u)
    {
        if (parent[u] != u)
        {
            parent[u] = find(parent[u]); // Path compression
        }
        return parent[u];
    }

    void unionSets(int u, int v)
    {
        int rootU = find(u);
        int rootV = find(v);
        if (rootU != rootV)
        {
            if (rank[rootU] < rank[rootV])
            {
                parent[rootU] = rootV;
            }
            else if (rank[rootU] > rank[rootV])
            {
                parent[rootV] = rootU;
            }
            else
            {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }
    }

private:
    vector<int> parent;
    vector<int> rank;
};

vector<Edge> kruskal(int graph[][7], int n)
{
    vector<Edge> edges;

    // 1. Сначала упорядочиваем все ребра по возрастанию весов.
    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            if (graph[i][j] != 0)
            { // 0 означает отсутствие ребра
                edges.push_back({i, j, graph[i][j]});
            }
        }
    }

    // Сортируем ребра по весу
    sort(edges.begin(), edges.end(), [](Edge a, Edge b)
         { return a.weight < b.weight; });

    DisjointSet ds(n);
    vector<Edge> result;

    // 4. Берем ребра и строим остовное дерево
    for (const auto &edge : edges)
    {
        if (ds.find(edge.u) != ds.find(edge.v))
        {
            ds.unionSets(edge.u, edge.v);
            result.push_back(edge);
        }
    }

    return result;
}

void printMST(const vector<Edge> &mst)
{
    cout << "Минимальное остовное дерево:" << endl;
    for (const auto &edge : mst)
    {
        cout << "Ребро: " << edge.u + 1 << " - " << edge.v + 1 << ", вес: " << edge.weight << endl;
    }
}

int main()
{
    const int n = 7; // Количество вершин
    int graph[7][7] = {
        {0, 20, 0, 0, 0, 23, 1},
        {20, 0, 5, 0, 0, 0, 4},
        {0, 5, 0, 3, 0, 0, 9},
        {0, 0, 3, 0, 17, 0, 16},
        {0, 0, 0, 17, 0, 28, 25},
        {23, 0, 0, 0, 28, 0, 36},
        {1, 4, 9, 16, 25, 36, 0}};

    vector<Edge> mst = kruskal(graph, n);
    printMST(mst);

    return 0;
}
