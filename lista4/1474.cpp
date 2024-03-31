#include <bits/stdc++.h>

#define INF 0x3f3f3f3f

using namespace std;

typedef priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> min_heap;
typedef vector<vector<unsigned long long>> matrix;

matrix matrix_mult(matrix x, matrix y)
{
    matrix result(x.size(), vector<unsigned long long>(y[0].size(), 0));
    for (int i = 0; i < x.size(); i++)
    {
        for (int j = 0; j < y[0].size(); j++)
        {
            for (int k = 0; k < y.size(); k++)
            {
                result[i][j] += (x[i][k] % 1000000) * (y[k][j] % 1000000);
                result[i][j] = result[i][j] % 1000000;
            }
        }
    }
    return result;
}

matrix matrix_pow(matrix x, unsigned long long exp)
{
    // base case
    if (exp == 0)
        return matrix{{1, 0}, {0, 1}};

    matrix result = matrix_pow(x, exp / 2);
    result = matrix_mult(result, result);

    if (exp % 2 == 1)
    {
        result = matrix_mult(result, x);
    }
    return result;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    unsigned long long meters, micro_bus, bus;
    while (cin >> meters >> micro_bus >> bus)
    {
        meters /= 5;
        matrix mb_mx = {{1, micro_bus}};
        matrix allb_mx = {{0, bus}, {1, micro_bus}};

        matrix allb_pow_meters = matrix_pow(allb_mx, meters);
        matrix resp = matrix_mult(mb_mx, allb_pow_meters);

        cout << setw(6) << setfill('0');
        cout << resp[0][0] % 1000000 << endl;
    }

    return 0;
}