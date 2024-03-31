#include <algorithm>
#include <bits/stdc++.h>
#include <string>
#include <vector>

using namespace std;

int sum(vector<int> vec)
{
    int total = 0;
    for (int i = 0; i < vec.size(); i++)
    {
        total += vec[i];
    }
    return total;
}

bool fold(vector<int> input, vector<int> output, int offset, bool isRev)
{
    vector<int> newv = input;
    while (newv.size() > output.size())
    {
        vector<int> aux;
        int j = offset - 1, i = offset;
        while (j >= 0)
        {
            aux.push_back(newv[j] + newv[i]);
            i++;
            j--;
        }

        for (int k = i; k < newv.size(); k++)
        {
            aux.push_back(newv[k]);
        }
        newv.clear();
        newv = aux;
        if (newv.size() > output.size() && offset > output.size())
            break;
    }

    bool resp = newv == output;
    reverse(newv.begin(), newv.end());
    resp = resp || newv == output;
    return resp;
}

// offset min = 1, max = input/2
bool compareVecs(vector<int> inp, vector<int> oup)
{
    bool resp = false;
    int si = inp.size() / 2;

    for (int k = 1; k <= si; k++)
    {
        resp = fold(inp, oup, k, false);
        if (resp)
            return resp;
    }

    reverse(inp.begin(), inp.end());
    for (int k = 1; k <= si; k++)
    {
        resp = fold(inp, oup, k, true);
        if (resp)
            return resp;
    }

    return false;
}

int main()
{
    int vecLen, val;
    while (cin >> vecLen)
    {
        vector<int> input, output;
        for (int i = 0; i < vecLen; i++)
        {
            cin >> val;
            input.push_back(val);
        }
        cin >> vecLen;
        for (int i = 0; i < vecLen; i++)
        {
            cin >> val;
            output.push_back(val);
        }

        int lenDif = input.size() - output.size();

        if (lenDif < 0 || (sum(input) != sum(output)))
        {
            cout << "N\n";
            continue;
        }

        if (lenDif == 0)
        {
            if (input == output)
            {
                cout << "S\n";
                continue;
            }
            bool r = true;
            for (int i = 0; i < vecLen; i++)
            {
                if (input[i] != output[vecLen - 1 - i])
                    r = false;
            }
            if (r)
                cout << "S\n";
            else
                cout << "N\n";
            continue;
        }
        bool resp = compareVecs(input, output);

        if (resp)
            cout << "S\n";
        else
            cout << "N\n";
    }
    return 0;
}