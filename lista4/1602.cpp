#include <bits/stdc++.h>

#define INF 0x3f3f3f3f

using namespace std;

typedef priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> min_heap;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    // Preprocesses the quantity of divisors for all possible inputs.
    // It iterates up to 2000001 so that the divisors of numbers which
    // multiplied by 2 are greater than 10^6 are accounted for
    int qnt_fac, aux;
    vector<int> divisors(2000001, 0);
    vector<bool> primes(2000001, 1);
    vector<int> prime_div_count(2000001, 0);
    primes[0] = primes[1] = 0;

    for (int i = 2; i <= 2000001; i++)
    {
        if (primes[i])
        {
            divisors[i] = 2; // 1 and the number itself
            for (int j = i * 2; j <= 2000001; j += i)
            {
                primes[j] = 0; // multiple of i isnt prime
                qnt_fac = 0, aux = j;
                // gets exponential val for current prime
                while (aux % i == 0)
                {
                    qnt_fac++;
                    aux /= i;
                }
                // if the number still has other prime factors to be divided by,
                // multiply the current prime factor by 2 to account for
                // all possible exponent combinations
                if (aux != 1)
                    qnt_fac *= 2;
                if (divisors[j] == 0)
                {
                    divisors[j] += qnt_fac + 1;
                    continue;
                }
                divisors[j] *= (qnt_fac + 1); // combination of existing divisors
            }
        }
    }
    for (int i = 2; i <= 2000001; i++)
    {
        prime_div_count[i] = prime_div_count[i - 1];
        if (primes[divisors[i]])
            prime_div_count[i]++;
    }

    // reads in the number and uses the preprocessed divisor quantity list
    int number;
    while (cin >> number)
    {
        cout << prime_div_count[number] << "\n";
    }

    return 0;
}