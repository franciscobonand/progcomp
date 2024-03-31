#include <bits/stdc++.h>

#define INF 0x3f3f3f3f

using namespace std;

typedef priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> min_heap;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string msg;
    cin >> msg;

    transform(msg.begin(), msg.end(), msg.begin(), ::tolower);
    auto found = msg.find("zelda");
    if (found != string::npos)
    {
        cout << "Link Bolado\n";
        return 0;
    }
    cout << "Link Tranquilo\n";

    return 0;
}