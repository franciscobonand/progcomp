#include <bits/stdc++.h>
#include <utility>
#include <vector>

#define INF 0x3f3f3f3f

using namespace std;

typedef priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> min_heap;

int lin, col;

bool validBounds(int y, int x)
{
    return ((y >= 0 && y < lin) && (x >= 0 && x < col));
}

int findCapturable(vector<vector<int>> &board, vector<vector<bool>> &visited, int y, int x)
{
    vector<int> bounds(4, 0);
    if (validBounds(y - 2, x - 2))
    {
        if ((board[y - 1][x - 1] == 2) && (board[y - 2][x - 2] == 0) && !visited[y - 1][x - 1])
        {
            visited[y - 1][x - 1] = true;
            board[y][x] = 0;
            board[y - 2][x - 2] = 1;
            bounds[0] = findCapturable(board, visited, y - 2, x - 2) + 1;
            visited[y - 1][x - 1] = false;
            board[y][x] = 1;
            board[y - 2][x - 2] = 0;
        }
    }
    if (validBounds(y - 2, x + 2))
    {
        if ((board[y - 1][x + 1] == 2) && (board[y - 2][x + 2] == 0) && !visited[y - 1][x + 1])
        {
            visited[y - 1][x + 1] = true;
            board[y][x] = 0;
            board[y - 2][x + 2] = 1;
            bounds[1] = findCapturable(board, visited, y - 2, x + 2) + 1;
            visited[y - 1][x + 1] = false;
            board[y][x] = 1;
            board[y - 2][x + 2] = 0;
        }
    }
    if (validBounds(y + 2, x - 2))
    {
        if ((board[y + 1][x - 1] == 2) && (board[y + 2][x - 2] == 0) && !visited[y + 1][x - 1])
        {
            visited[y + 1][x - 1] = true;
            board[y][x] = 0;
            board[y + 2][x - 2] = 1;
            bounds[2] = findCapturable(board, visited, y + 2, x - 2) + 1;
            visited[y + 1][x - 1] = false;
            board[y][x] = 1;
            board[y + 2][x - 2] = 0;
        }
    }
    if (validBounds(y + 2, x + 2))
    {
        if ((board[y + 1][x + 1] == 2) && (board[y + 2][x + 2] == 0) && !visited[y + 1][x + 1])
        {
            visited[y + 1][x + 1] = true;
            board[y][x] = 0;
            board[y + 2][x + 2] = 1;
            bounds[3] = findCapturable(board, visited, y + 2, x + 2) + 1;
            visited[y + 1][x + 1] = false;
            board[y][x] = 1;
            board[y + 2][x + 2] = 0;
        }
    }

    int maxval = 0;
    for (int i = 0; i < bounds.size(); i++)
    {
        if (bounds[i] > maxval)
            maxval = bounds[i];
    }
    return maxval;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int qntPieces, piece;
    int cnt = 1;
    while (cin >> lin >> col && (lin || col))
    {
        // vector<int> tests;
        vector<vector<int>> board(lin, vector<int>(col, -1));
        vector<vector<bool>> visited(lin, vector<bool>(col, false));
        vector<pair<int, int>> myPieces;
        int y = lin - 1, x = 0;
        qntPieces = ((lin * col) + 1) / 2;
        for (int i = 0; i < qntPieces; i++)
        {
            cin >> piece;
            // tests.push_back(piece);
            board[y][x] = piece;
            if (piece == 1)
                myPieces.push_back({y, x});
            x++;
            if (x >= col - 1)
            {
                x = board[y][0] == -1 ? 0 : 1;
                y--;
            }
            else
            {
                x++;
            }
        }

        vector<int> bounds(myPieces.size(), 0);
        int val, maxval = 0;
        for (int i = 0; i < myPieces.size(); i++)
        {
            y = myPieces[i].first;
            x = myPieces[i].second;
            val = findCapturable(board, visited, y, x);
            bounds.push_back(val);
        }
        for (int i = 0; i < bounds.size(); i++)
        {
            if (bounds[i] > maxval)
                maxval = bounds[i];
        }
        // if (cnt != 4) {
        cout << maxval << "\n";
        // } else {
        //     cout << lin << "," << col << " ";
        //     for (int i = 0; i < tests.size(); i++) cout << tests[i] << " ";
        //     cout << "\n";
        // }
        // for (int i = 0; i < board.size(); i++) {
        //     for (int j = 0; j < board[0].size(); j++) {
        //         cout << board[i][j] << " ";
        //     }
        //     cout << endl;
        // }
        // cnt++;
    }

    return 0;
}