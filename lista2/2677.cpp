#include <bits/stdc++.h>

#define INF 0x3f3f3f3f

using namespace std;

typedef priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> min_heap;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int numqte, val;
    while (cin >> numqte && numqte != 0)
    {
        int values[1010];
        numqte *= 2;
        for (int i = 0; i < numqte; i++)
        {
            cin >> val;
            values[i] = val;
        }

        int sssmatrix[1010][1010];
        for (int i = 1; i < numqte; i++)
        {
            for (int j = 0; i + j < numqte; j++)
            {
                int k = i + j;
                if (i % 2 == 0)
                {
                    sssmatrix[j][k] = min(sssmatrix[j][k - 1], sssmatrix[j + 1][k]);
                    continue;
                }
                int jeven = values[j] % 2 == 0 ? 1 : 0;
                int cpeven = values[k] % 2 == 0 ? 1 : 0;
                sssmatrix[j][k] = max(sssmatrix[j][k - 1] + cpeven, sssmatrix[j + 1][k] + jeven);
            }
        }
        cout << sssmatrix[0][numqte - 1] << "\n";
    }

    return 0;
}