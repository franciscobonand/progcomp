#include <bits/stdc++.h>

#define INF 0x3f3f3f3f

using namespace std;

typedef priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> min_heap;

// Reference: https://leimao.github.io/article/RSA-Algorithm/

pair<int, int> gcd(int e, int phi)
{
    if (phi == 0)
    {
        return make_pair(1, 0);
    }
    pair<int, int> np = gcd(phi, e % phi);
    int s = np.second;
    int t = np.first - (np.second * (e / phi));
    return make_pair(s, t);
}

int getPhi(int n)
{
    int phi = n;
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        { // not prime
            while (n % i == 0)
            {
                n /= i;
            }
            phi -= phi / i;
        }
    }
    if (n > 1)
        phi -= phi / n;
    return phi;
}

int getModExp(int a, int b, int m)
{
    int modexp = 1;
    while (b > 0)
    {
        if (b % 2)
        {
            modexp = ((long long)modexp * a % m);
        }
        a = ((long long)a * a % m);
        b /= 2;
    }
    return modexp;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, e, c, p, q, d, phi, pre_n_np;
    cin >> n >> e >> c;

    for (int i = 3;; i += 2)
    {
        if (n % i == 0)
        {
            p = i;
            q = n / p;
            pre_n_np = (p - 1) * (q - 1);
            phi = getPhi(pre_n_np);
            d = getModExp(e, phi - 1, pre_n_np);
            break;
        }
    }

    int msg = getModExp(c, d, n);
    cout << msg << "\n";

    return 0;
}