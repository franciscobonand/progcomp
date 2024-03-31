#include <bits/stdc++.h>
#include <cmath>

#define INF 0x3f3f3f3f

using namespace std;

typedef priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> min_heap;
typedef vector<vector<double>> matrix;

double getEuclideanDistance(pair<int, int> p1, pair<int, int> p2)
{
    double diff1 = pow(p1.first - p2.first, 2.0);
    double diff2 = pow(p1.second - p2.second, 2.0);
    return sqrt(diff1 + diff2);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n_points;
    while (cin >> n_points && n_points != 0)
    {
        int x, y;
        vector<pair<int, int>> points;
        double euc_distances[n_points + 1][n_points + 1];
        for (int i = 0; i < n_points; i++)
        {
            cin >> x >> y;
            points.push_back(make_pair(x, y));
        }

        memset(euc_distances, 0, (n_points + 1) * (n_points + 1) * sizeof(double));
        int isosceles_count = 0;
        double dist;
        for (int i = 0; i < n_points; i++)
        {
            // get euclidean distance from 1 point to all of the others
            for (int j = 0; j < n_points; j++)
            {
                if (euc_distances[i][j] == 0)
                {
                    dist = getEuclideanDistance(points[i], points[j]);
                    euc_distances[i][j] = dist;
                    euc_distances[j][i] = dist;
                }
            }

            sort(euc_distances[i], euc_distances[i] + n_points);
            int eq_dist_points = 1;
            double curr_dist = euc_distances[i][0];
            for (int j = 1; j < n_points; j++)
            {
                if (euc_distances[i][j] != curr_dist)
                {
                    isosceles_count += eq_dist_points * (eq_dist_points - 1) / 2; // combination of points
                    curr_dist = euc_distances[i][j];
                    eq_dist_points = 0;
                }
                eq_dist_points++;
            }
            // check once more, in case the last point in the for loop has equal distance
            if (eq_dist_points > 1)
            {
                isosceles_count += eq_dist_points * (eq_dist_points - 1) / 2;
            }
        }
        cout << isosceles_count << "\n";
    }

    return 0;
}