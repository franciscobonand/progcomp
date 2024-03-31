#include <bits/stdc++.h>

#define INF 0x3f3f3f3f

using namespace std;

typedef priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> min_heap;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int rooms, mana;
    double dmg;
    while (cin >> rooms >> mana >> dmg)
    {
        double m_lifes[rooms], dmg_incr[rooms];
        for (int room = 0; room < rooms; room++)
        {
            cin >> m_lifes[room] >> dmg_incr[room];
        }

        if (mana == 0)
        {
            double time = 0;
            for (int room = 0; room < rooms; room++)
            {
                time += m_lifes[room] / dmg;
            }
            cout << fixed << setprecision(4) << time << "\n";
            continue;
        }
        // dp
        double mana_per_room[rooms + 1][mana + 1];
        for (int i = 0; i <= mana; i++)
        {
            mana_per_room[0][i] = 0;
        }
        // base case - without mana usage
        for (int room = 1; room <= rooms; room++)
        {
            mana_per_room[room][0] = mana_per_room[room - 1][0] + m_lifes[room - 1] / dmg;
        }
        for (int room = 1; room <= rooms; room++)
        {
            for (int mana_qnt = 1; mana_qnt <= mana; mana_qnt++)
            {
                double time_w_dmg_incr = mana_per_room[room - 1][mana_qnt - 1] + (m_lifes[room - 1] / (dmg + dmg_incr[room - 1]));
                double time_w_curr_dmg = mana_per_room[room - 1][mana_qnt] + (m_lifes[room - 1] / dmg);
                mana_per_room[room][mana_qnt] = min(time_w_dmg_incr, time_w_curr_dmg);
            }
        }
        cout << fixed << setprecision(4) << mana_per_room[rooms][mana] << "\n";
    }

    return 0;
}