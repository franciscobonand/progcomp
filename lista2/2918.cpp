#include <bits/stdc++.h>

#define INF 0x3f3f3f3f

using namespace std;

typedef priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> min_heap;

const int mod = 1e9 + 7;

long long digitSumInRange(long long n)
{
    // 1 digit number
    if (n < 10)
        return n * (n + 1) / 2;

    long long digits = log10(n);
    long long sums[digits + 1];
    sums[1] = 45;

    // sums[i] = sum of digits from 1 to 10^(i-1) = a[i-1] * 10 + 45*10^(i-1)
    for (long long i = 2; i <= digits; i++)
    {
        sums[i] = (sums[i - 1] * 10) + (45 * pow(10, i - 1));
    }

    // power of 10 the digit is in
    long long pow_10 = pow(10, digits);
    long long most_sig_dig = n / pow_10;
    // sums from 1 up to (most_sig_dig * pow_10) - 1
    // example: if n = 420, dig_up_to_msd_sum is the sum from 1 to 399,
    // which is calculated by: (900 * 4) + (6 * 100)
    long long dig_up_to_msd_sum = (sums[digits] * most_sig_dig) + ((most_sig_dig * (most_sig_dig - 1)) / 2) * pow_10;
    long long msd_sum = (n % pow_10 + 1) * most_sig_dig;
    long long remainder_sum = digitSumInRange(n % pow_10);
    return (dig_up_to_msd_sum + msd_sum + remainder_sum) % mod;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    long long start, end;
    while (cin >> start >> end)
    {
        long long total = digitSumInRange(end) - digitSumInRange(start - 1);
        cout << total << "\n";
    }
    return 0;
}