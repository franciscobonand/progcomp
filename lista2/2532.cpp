#include <bits/stdc++.h>

#define INF 0x3f3f3f3f

using namespace std;

typedef priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> min_heap;

int dp[2001][1001];

int getMinManaSpent(int *sd, int *sc, int curr_idx, int last_idx, int m_hp)
{
    // monster is killed
    if (m_hp <= 0)
        return 0;
    // all spells checked
    if (curr_idx == last_idx)
        return INF;
    // spell not cast yet
    if (dp[m_hp][curr_idx] != -1)
        return dp[m_hp][curr_idx];

    int spell_used = getMinManaSpent(sd, sc, curr_idx + 1, last_idx, m_hp - sd[curr_idx]) + sc[curr_idx];
    int spell_skipped = getMinManaSpent(sd, sc, curr_idx + 1, last_idx, m_hp);
    dp[m_hp][curr_idx] = min(spell_used, spell_skipped);
    return dp[m_hp][curr_idx];
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int avail_spells, m_hp;
    while (cin >> avail_spells >> m_hp)
    {
        int spell_dmgs[avail_spells], spell_cost[avail_spells];
        int dmg_sum = 0;
        for (int i = 0; i < avail_spells; i++)
        {
            cin >> spell_dmgs[i] >> spell_cost[i];
            dmg_sum += spell_dmgs[i];
        }
        // impossible to defeat monster
        if (dmg_sum < m_hp)
        {
            cout << "-1\n";
            continue;
        }

        memset(dp, -1, sizeof dp);
        int mana_spent = getMinManaSpent(spell_dmgs, spell_cost, 0, avail_spells, m_hp);
        if (mana_spent != INF)
        {
            cout << mana_spent << "\n";
            continue;
        }
        cout << "-1\n";
    }

    return 0;
}