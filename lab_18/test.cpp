#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include <iomanip>
#include <algorithm>

const int INF = std::numeric_limits<int>::max();

struct Node
{
    std::vector<std::vector<int>> reducedMatrix;
    int cost;
    int vertex;
    int level;
    std::vector<int> path;
};

void printMatrix(const std::vector<std::vector<int>> &matrix)
{
    for (const auto &row : matrix)
    {
        for (const auto &elem : row)
        {
            if (elem == INF)
                std::cout << "INF ";
            else
                std::cout << std::setw(3) << elem << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int reduceMatrix(std::vector<std::vector<int>> &matrix)
{
    int reductionCost = 0;

    // Row reduction
    for (auto &row : matrix)
    {
        int rowMin = INF;
        for (int value : row)
        {
            rowMin = std::min(rowMin, value);
        }
        if (rowMin != INF && rowMin > 0)
        {
            reductionCost += rowMin;
            for (auto &value : row)
            {
                if (value != INF)
                    value -= rowMin;
            }
        }
    }

    // Column reduction
    for (size_t j = 0; j < matrix.size(); ++j)
    {
        int colMin = INF;
        for (size_t i = 0; i < matrix.size(); ++i)
        {
            colMin = std::min(colMin, matrix[i][j]);
        }
        if (colMin != INF && colMin > 0)
        {
            reductionCost += colMin;
            for (size_t i = 0; i < matrix.size(); ++i)
            {
                if (matrix[i][j] != INF)
                    matrix[i][j] -= colMin;
            }
        }
    }

    return reductionCost;
}

Node createNode(const std::vector<std::vector<int>> &parentMatrix, int level, int i, int j, const std::vector<int> &path)
{
    Node node;
    node.reducedMatrix = parentMatrix;

    // Invalidate row and column of the current edge
    for (size_t k = 0; k < parentMatrix.size(); ++k)
    {
        node.reducedMatrix[i][k] = INF;
        node.reducedMatrix[k][j] = INF;
    }
    node.reducedMatrix[j][0] = INF; // Prevent return to the starting node prematurely

    node.cost = reduceMatrix(node.reducedMatrix);
    node.vertex = j;
    node.level = level;
    node.path = path;
    node.path.push_back(j);

    return node;
}

struct Compare
{
    bool operator()(const Node &lhs, const Node &rhs) const
    {
        return (lhs.cost > rhs.cost);
    }
};

void solveTSP(const std::vector<std::vector<int>> &costMatrix)
{
    std::priority_queue<Node, std::vector<Node>, Compare> pq;

    Node root;
    root.reducedMatrix = costMatrix;
    root.cost = reduceMatrix(root.reducedMatrix);
    root.vertex = 0;
    root.level = 0;
    root.path.push_back(0);

    pq.push(root);

    int minCost = INF;
    std::vector<int> bestPath;

    while (!pq.empty())
    {
        Node current = pq.top();
        pq.pop();

        if (current.level == costMatrix.size() - 1)
        {
            int lastToFirst = costMatrix[current.vertex][0];
            if (lastToFirst != INF)
            {
                int totalCost = current.cost + lastToFirst;
                if (totalCost < minCost)
                {
                    minCost = totalCost;
                    bestPath = current.path;
                    bestPath.push_back(0);
                }
            }
            continue;
        }

        for (size_t j = 0; j < costMatrix.size(); ++j)
        {
            if (costMatrix[current.vertex][j] != INF && std::find(current.path.begin(), current.path.end(), j) == current.path.end())
            {
                Node child = createNode(current.reducedMatrix, current.level + 1, current.vertex, j, current.path);
                child.cost += current.cost + costMatrix[current.vertex][j];

                std::cout << "Exploring path: ";
                for (int p : child.path)
                    std::cout << p << " -> ";
                std::cout << "[Cost: " << child.cost << ", Potential: " << child.cost + (costMatrix[child.vertex][0] == INF ? 0 : costMatrix[child.vertex][0]) << "]" << std::endl;

                pq.push(child);
            }
        }
    }

    std::cout << "\nSolution tour: ";
    for (int v : bestPath)
    {
        std::cout << v << " ";
    }
    std::cout << "\nTour length: " << minCost << std::endl;
}

int main()
{
    std::vector<std::vector<int>> costMatrix = {
        {3, 6, 7, INF},
        {INF, 7, 4, 3},
        {8, 4, INF, 6},
        {2, 4, 8, INF}};

    solveTSP(costMatrix);

    return 0;
}
