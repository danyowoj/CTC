#include <iostream>
#include <vector>

using namespace std;

int main()
{
    // number of items
    int numItems;
    cout << "Enter the number of items: ";
    cin >> numItems;

    // weight and value for items
    vector<pair<int, int>> items(numItems);
    for (int i = 0; i < numItems; ++i)
    {
        cout << "Enter weight and value for item " << i + 1 << ": ";
        cin >> items[i].first >> items[i].second;
    }

    // knapsack capacity
    int capacity;
    cout << "Enter knapsack capacity: ";
    cin >> capacity;

    // initializing the table
    // the maximum value that can be obtained with weight i
    vector<int> dp(capacity + 1, 0);
    // a vector storing the amount of each item used to achieve dp[i]
    vector<vector<int>> itemsUsed(capacity + 1, vector<int>(numItems, 0));

    // the main cycle
    for (int i = 0; i <= capacity; ++i)
    {
        for (int j = 0; j < numItems; ++j)
        {
            if (i >= items[j].first)
            {
                // checking if we can add another item j
                if (dp[i] < dp[i - items[j].first] + items[j].second)
                {
                    dp[i] = dp[i - items[j].first] + items[j].second;
                    itemsUsed[i] = itemsUsed[i - items[j].first];
                    itemsUsed[i][j]++;
                }
            }
        }
    }

    // output of the result
    cout << "\nMaximum value: " << dp[capacity] << endl;
    cout << "\nItems used:" << endl;
    for (int i = 0; i < numItems; ++i)
    {
        if (itemsUsed[capacity][i] > 0)
        {
            cout << "Item " << i + 1 << ": " << itemsUsed[capacity][i] << " units" << endl;
        }
    }

    return 0;
}
