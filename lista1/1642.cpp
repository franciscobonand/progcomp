#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int keys;
    while (cin >> keys && (keys != 0))
    {
        string phrase;
        cin >> ws;
        getline(cin, phrase);

        int maxLen = phrase.length();
        int left = 0, maxReps = 0;
        unordered_map<char, int> reps;
        for (int right = 0; right < maxLen; right++)
        {
            char chr = phrase[right];
            reps[chr]++;

            while (reps.size() > keys)
            {
                char d = phrase[left];
                reps[d]--;
                if (reps[d] == 0)
                {
                    reps.erase(d);
                }
                left++;
            }

            maxReps = max(maxReps, right - left + 1);
        }
        cout << maxReps << "\n";
    }
    return 0;
}