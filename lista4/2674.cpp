#include <bits/stdc++.h>
#include <cmath>

#define INF 0x3f3f3f3f

using namespace std;

typedef priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> min_heap;

bool isPrime(int number)
{
    if (number <= 1)
    {
        return false;
    }
    int max_iter = ceil(sqrt(number));
    for (int i = 2; i <= max_iter; i++)
    {
        if (number != i && number % i == 0)
            return false;
    }
    return true;
}

bool isSuper(int number)
{
    int dec_mov;
    while (number >= 1)
    {
        // shifts each digit
        dec_mov = number % 10;
        if (!isPrime(dec_mov))
            return false;
        number /= 10;
    }
    return true;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int number;
    while (cin >> number)
    {
        bool is_prime = isPrime(number);
        if (!is_prime)
        {
            cout << "Nada\n";
            continue;
        }
        bool is_super = isSuper(number);
        if (is_super)
        {
            cout << "Super\n";
            continue;
        }
        cout << "Primo\n";
    }

    return 0;
}