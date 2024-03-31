#include <bits/stdc++.h>

#define INF 0x3f3f3f3f

using namespace std;

typedef priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> min_heap;

bool canBalance(int *weights, int wg_size, int diff, int curr_wg)
{
    // base cases
    if (wg_size == 0)
        return true;
    if (wg_size == 1)
    {
        if (weights[0] <= 5)
            return true;
        return false;
    }

    int wg_diff = abs(diff - weights[curr_wg]);
    // last gift
    if (curr_wg == wg_size - 1)
    {
        if ((weights[curr_wg] + diff <= 5) || (wg_diff <= 5))
            return true;
        return false;
    }
    // gift can be added to curr stack
    else if (
        weights[curr_wg] + diff <= 5 &&
        canBalance(weights, wg_size, weights[curr_wg] + diff, curr_wg + 1))
    {
        return true;
    }
    else if (
        wg_diff <= 5 &&
        canBalance(weights, wg_size, wg_diff, curr_wg + 1))
    {
        return true;
    }

    return false;
}

int main()
{
    int tests, gifts;
    cin >> tests;
    for (int test = 0; test < tests; test++)
    {
        cin >> gifts;
        int weights[gifts];
        for (int i = 0; i < gifts; i++)
        {
            cin >> weights[i];
        }

        int wg_size = sizeof(weights) / sizeof(int);
        if (canBalance(weights, wg_size, 0, 0))
        {
            cout << "Feliz Natal!\n";
            continue;
        }
        cout << "Ho Ho Ho!\n";
    }
    return 0;
}