#include <bits/stdc++.h>
#include <string>

#define INF 0x3f3f3f3f

using namespace std;

typedef priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> min_heap;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    double pop_sec;
    int bags, comp_per_team, max_pop = 0;
    cin >> bags >> comp_per_team >> pop_sec;
    vector<double> pop_bags(bags);
    for (int i = 0; i < bags; i++)
    {
        cin >> pop_bags[i];
        max_pop = max_pop > pop_bags[i] ? max_pop : pop_bags[i];
    }

    int upperb = max_pop / pop_sec;
    int lowerb = upperb / 2;
    int ss = 1, min_secs;
    bool sol_found = false;
    while (ss != 0)
    {
        double currBag = 0;
        int currComp = 0;
        for (int i = 0; i < bags; i++)
        {
            if ((pop_bags[i] / pop_sec) > upperb || currComp == comp_per_team)
            {
                currComp = comp_per_team + 1;
                break;
            }
            if ((currBag + pop_bags[i]) / pop_sec <= upperb)
            {
                currBag += pop_bags[i];
                continue;
            }
            currComp++;
            currBag = pop_bags[i];
        }
        ss = (upperb - lowerb) / 2;
        currComp++;
        if (currComp <= comp_per_team)
        {
            min_secs = upperb;
            upperb -= ss;
            sol_found = true;
            continue;
        }
        if (sol_found)
        {
            lowerb = upperb;
            upperb += ss;
            continue;
        }
        ss = 1;
        lowerb = upperb;
        upperb = upperb * 2;
    }
    cout << min_secs << "\n";

    return 0;
}