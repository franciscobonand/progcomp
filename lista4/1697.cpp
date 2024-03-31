#include <bits/stdc++.h>

#define INF 0x3f3f3f3f

using namespace std;

typedef priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> min_heap;
typedef vector<vector<unsigned long long>> matrix;

bool isPrime(unsigned int number)
{
    if (number == 2)
        return true;
    if (number <= 1 || number % 2 == 0)
    {
        return false;
    }
    int max_iter = sqrt(number);
    for (int i = 3; i <= max_iter; i += 2)
    {
        if (number % i == 0)
            return false;
    }
    return true;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    unsigned int max_n = 1000000000;
    int tcases;
    cin >> tcases;
    for (int tc = 0; tc < tcases; tc++)
    {
        unsigned int n_qnt;
        cin >> n_qnt;

        vector<unsigned int> numbers(n_qnt, 0);
        for (unsigned int i = 0; i < n_qnt; i++)
        {
            cin >> numbers[i];
        }

        // sort ascending
        sort(numbers.begin(), numbers.end());
        // remove repeated
        numbers.erase(unique(numbers.begin(), numbers.end()), numbers.end());
        if (numbers[0] != 1)
        { // doesnt begin with 1
            cout << "0\n";
            continue;
        }

        unsigned int last_prime_found, i = 0, order = 1;
        while (order <= max_n)
        {
            bool next_in_list = numbers[i] == order;
            // found prime that isnt in the number list
            if (!next_in_list && isPrime(order))
            {
                last_prime_found = order;
                break;
            }
            // number not on the list, but can be made from multiplying other numbers
            if (!next_in_list)
            {
                order++;
                continue;
            }
            // number on the list
            order++;
            i++;
        }
        cout << last_prime_found - 1 << "\n";
    }

    return 0;
}