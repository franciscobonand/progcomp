#include <bits/stdc++.h>

#define INF 0x3f3f3f3f

using namespace std;

typedef priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> min_heap;

// explodes if declared inside of function?
int subgrids[310][310][310];
char room[310][310];

int main()
{
    int rows, seats, friends;
    while (cin >> rows >> seats >> friends && (rows != 0 && seats != 0 && friends != 0))
    {
        for (int i = 0; i < rows; i++)
        {
            cin >> room[i];
        }
        // dinamic prog to evaluate available seats in all possible subgrids
        for (int row = rows - 1; row >= 0; row--)
        {
            for (int seat = seats - 1; seat >= 0; seat--)
            {
                // iterate through subgrids with different sizes
                for (int size = 1; size <= seats - seat; size++)
                {
                    int available = room[row][seat] == '.' ? 1 : 0;
                    if (size == 1)
                    {
                        subgrids[row][seat][size] = available;
                        continue;
                    }
                    subgrids[row][seat][size] = subgrids[row][seat + 1][size - 1] + available;
                }
            }
        }

        int sg_start, height, acc_available, min_area = INF;
        for (int seat = 0; seat < seats; seat++)
        {
            for (int size = 1; size <= seats - seat; size++)
            {
                sg_start = 0;
                acc_available = 0;
                for (int row = 0; row < rows; row++)
                {
                    acc_available += subgrids[row][seat][size];
                    while (acc_available >= friends)
                    {
                        height = row - sg_start + 1;
                        if (size * height < min_area)
                        {
                            min_area = size * height;
                        }
                        acc_available -= subgrids[sg_start][seat][size];
                        sg_start++;
                    }
                }
            }
        }
        cout << min_area << "\n";
    }
}