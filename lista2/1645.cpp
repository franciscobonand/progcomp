#include <bits/stdc++.h>

#define INF 0x3f3f3f3f

using namespace std;

typedef priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> min_heap;

long long countAscendingSequences(const vector<int> &nums, int k)
{
    int n = nums.size();
    vector<vector<long long>> dp(n, vector<long long>(k, 0));
    long long count = 0;
    for (int i = 0; i < n; i++)
    {
        dp[i][0] = 1;
    }

    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j <= i && j < k; j++)
        {
            for (int l = 0; l < i; l++)
            {
                if (nums[l] < nums[i])
                {
                    dp[i][j] += dp[l][j - 1];
                }
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        count += dp[i][k - 1];
    }

    return count;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int seq_size, des_size;
    while (cin >> seq_size >> des_size && seq_size != 0)
    {
        vector<int> values(seq_size);
        for (int i = 0; i < seq_size; i++)
        {
            cin >> values[i];
        }
        long long count = countAscendingSequences(values, des_size);
        cout << count << endl;
    }

    return 0;
}