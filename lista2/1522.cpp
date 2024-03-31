#include <bits/stdc++.h>

#define INF 0x3f3f3f3f

using namespace std;

typedef priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> min_heap;

bool isWinnable(int card_qnt, int piles[3][110], int cp1, int cp2, int cp3, map<string, int> *m);

bool singleCardWin(int card_qnt, int piles[3][110], int chosen_pile, int card1, int card2, int card3, map<string, int> *m)
{
    if (chosen_pile == 0)
    {
        bool card_in_bounds = card1 < card_qnt;
        bool mult_of_3 = piles[chosen_pile][card1] % 3 == 0;
        return card_in_bounds && mult_of_3 && isWinnable(card_qnt, piles, card1 + 1, card2, card3, m);
    }
    else if (chosen_pile == 1)
    {
        bool card_in_bounds = card2 < card_qnt;
        bool mult_of_3 = piles[chosen_pile][card2] % 3 == 0;
        return card_in_bounds && mult_of_3 && isWinnable(card_qnt, piles, card1, card2 + 1, card3, m);
    }
    else
    {
        bool card_in_bounds = card3 < card_qnt;
        bool mult_of_3 = piles[chosen_pile][card3] % 3 == 0;
        return card_in_bounds && mult_of_3 && isWinnable(card_qnt, piles, card1, card2, card3 + 1, m);
    }
}

bool doubleCardWin(int card_qnt, int piles[3][110], int cp1, int cp2, int card1, int card2, int card3, map<string, int> *m)
{
    if (cp1 == 0 && cp2 == 1)
    {
        bool cards_in_bounds = card1 < card_qnt && card2 < card_qnt;
        bool sum_mult_of_3 = (piles[cp1][card1] + piles[cp2][card2]) % 3 == 0;
        return cards_in_bounds && sum_mult_of_3 && isWinnable(card_qnt, piles, card1 + 1, card2 + 1, card3, m);
    }
    else if (cp1 == 0 && cp2 == 2)
    {
        bool cards_in_bounds = card1 < card_qnt && card3 < card_qnt;
        bool sum_mult_of_3 = (piles[cp1][card1] + piles[cp2][card3]) % 3 == 0;
        return cards_in_bounds && sum_mult_of_3 && isWinnable(card_qnt, piles, card1 + 1, card2, card3 + 1, m);
    }
    else
    {
        bool cards_in_bounds = card2 < card_qnt && card3 < card_qnt;
        bool sum_mult_of_3 = (piles[cp1][card2] + piles[cp2][card3]) % 3 == 0;
        return cards_in_bounds && sum_mult_of_3 && isWinnable(card_qnt, piles, card1, card2 + 1, card3 + 1, m);
    }
}

bool threeCardWin(int card_qnt, int piles[3][110], int card1, int card2, int card3, map<string, int> *m)
{
    bool cards_in_bounds = card1 < card_qnt && card2 < card_qnt && card3 < card_qnt;
    bool sum_mult_of_3 = (piles[0][card1] + piles[1][card2] + piles[2][card3]) % 3 == 0;
    return cards_in_bounds && sum_mult_of_3 && isWinnable(card_qnt, piles, card1 + 1, card2 + 1, card3 + 1, m);
}

bool isWinnable(int card_qnt, int piles[3][110], int cp1, int cp2, int cp3, map<string, int> *m)
{
    string s = to_string(cp1) + to_string(cp2) + to_string(cp3);

    if (cp1 == card_qnt && cp2 == card_qnt && cp3 == card_qnt)
    {
        (*m)[s] = 1;
        return true;
    }

    if ((*m)[s] > 0)
    {
        if ((*m)[s] == 1)
            return true;
        return false;
    }

    bool win = singleCardWin(card_qnt, piles, 0, cp1, cp2, cp3, m) ||
               singleCardWin(card_qnt, piles, 1, cp1, cp2, cp3, m) ||
               singleCardWin(card_qnt, piles, 2, cp1, cp2, cp3, m) ||
               doubleCardWin(card_qnt, piles, 0, 1, cp1, cp2, cp3, m) ||
               doubleCardWin(card_qnt, piles, 0, 2, cp1, cp2, cp3, m) ||
               doubleCardWin(card_qnt, piles, 1, 2, cp1, cp2, cp3, m) ||
               threeCardWin(card_qnt, piles, cp1, cp2, cp3, m);

    if (win)
    {
        (*m)[s] = 1;
        return true;
    }

    (*m)[s] = 2;
    return false;
}

int main()
{
    int card_qnt;
    while (cin >> card_qnt && card_qnt != 0)
    {
        int card_piles[3][110];
        map<string, int> m;
        for (int card = 0; card < card_qnt; card++)
        {
            for (int pile = 0; pile < 3; pile++)
            {
                cin >> card_piles[pile][card];
            }
        }

        if (isWinnable(card_qnt, card_piles, 0, 0, 0, &m))
        {
            cout << "1\n";
            continue;
        }
        cout << "0\n";
    }

    return 0;
}