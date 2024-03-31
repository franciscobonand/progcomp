#include <bits/stdc++.h>

#define INF 0x3f3f3f3f

using namespace std;

typedef priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> min_heap;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int tests, balls, capacity, c_health;
    cin >> tests;
    for (int test = 0; test < tests; test++)
    {
        cin >> balls;
        int d_pow[balls], p_wg[balls];
        for (int ball = 0; ball < balls; ball++)
        {
            cin >> d_pow[ball] >> p_wg[ball];
        }
        cin >> capacity >> c_health;

        // dp
        int proj_per_cap[balls + 1][capacity + 1];
        for (int ball = 0; ball <= balls; ball++)
        {
            for (int c = 0; c <= capacity; c++)
            {
                if (ball == 0 || c == 0)
                {
                    proj_per_cap[ball][c] = 0;
                    continue;
                }
                if (c < p_wg[ball - 1])
                {
                    proj_per_cap[ball][c] = proj_per_cap[ball - 1][c];
                    continue;
                }
                int prev_proj = proj_per_cap[ball - 1][c];
                int this_proj = proj_per_cap[ball - 1][c - p_wg[ball - 1]] + d_pow[ball - 1];
                proj_per_cap[ball][c] = max(prev_proj, this_proj);
            }
        }
        if (c_health <= proj_per_cap[balls][capacity])
        {
            cout << "Missao completada com sucesso\n";
            continue;
        }
        cout << "Falha na missao\n";
    }

    return 0;
}