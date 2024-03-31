#include <bits/stdc++.h>

#define INF 0x3f3f3f3f

using namespace std;

typedef priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> min_heap;

int dp[5010][5010];
string searchstr, articlestr;

// "opposite" of demogorgon
int getArticleScore(int str1_sz, int str2_sz, int str1_idx, int str2_idx)
{
    // end of one of the strings
    if (str1_sz == str1_idx || str2_sz == str2_idx)
        return 0;
    // letter already checked
    if (dp[str1_idx][str2_idx] != -1)
        return dp[str1_idx][str2_idx];
    // equal letters
    if (searchstr[str1_idx] == articlestr[str2_idx])
    {
        dp[str1_idx][str2_idx] = getArticleScore(str1_sz, str2_sz, str1_idx + 1, str2_idx + 1) + 1;
        return dp[str1_idx][str2_idx];
    }
    // diff letters
    int next_str1_letter = getArticleScore(str1_sz, str2_sz, str1_idx + 1, str2_idx);
    int next_str2_letter = getArticleScore(str1_sz, str2_sz, str1_idx, str2_idx + 1);
    dp[str1_idx][str2_idx] = max(next_str1_letter, next_str2_letter);
    return dp[str1_idx][str2_idx];
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> searchstr >> articlestr;
    memset(dp, -1, sizeof dp);
    int sz1 = searchstr.size(), sz2 = articlestr.size();
    int article_score = getArticleScore(sz1, sz2, 0, 0);
    cout << article_score << "\n";

    return 0;
}