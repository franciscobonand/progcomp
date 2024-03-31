#include <bits/stdc++.h>

#define INF 0x3f3f3f3f

using namespace std;

typedef priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> min_heap;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int ncols;
    int cols[50010];
    cin >> ncols;
    for (int i = 0; i < ncols; i++)
    {
        cin >> cols[i];
    }

    int left[50010];
    left[0] = 1;
    for (int i = 1; i < ncols; i++)
    {
        left[i] = min(left[i - 1] + 1, cols[i]);
    }

    int right[50010];
    right[ncols - 1] = 1;
    for (int i = ncols - 2; i >= 0; i--)
    {
        right[i] = min(right[i + 1] + 1, cols[i]);
    }

    int mincol, maxheight = 0;
    for (int i = 0; i < ncols; i++)
    {
        mincol = min(left[i], right[i]);
        maxheight = max(maxheight, mincol);
    }

    cout << maxheight << "\n";
    return 0;
}