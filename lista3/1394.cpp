#include <bits/stdc++.h>

#define INF 0x3f3f3f3f

using namespace std;

typedef priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> min_heap;

struct Edge
{
    int from, to, cap, flow = 0;
    Edge(int v, int u, int cap) : from(v), to(u), cap(cap) {}
};

struct Graph
{
    vector<Edge> edges;
    vector<vector<int>> adjacency_list;
    int n_vert;
    int curr_vert = 0;
    int source, target;
    vector<int> level; // distance to source
    queue<int> q;

    Graph(int sz, int src, int tgt) : n_vert(sz), source(src), target(tgt)
    {
        adjacency_list.resize(sz);
        level.resize(sz);
    }

    void add_edge(int from, int to, int cap)
    {
        edges.push_back(Edge(from, to, cap));
        edges.push_back(Edge(to, from, 0));
        adjacency_list[from].push_back(curr_vert);
        adjacency_list[to].push_back(curr_vert + 1);
        curr_vert += 2;
    }

    // bfs
    bool has_path_to_target()
    {
        fill(level.begin(), level.end(), -1);
        level[source] = 0;
        q.push(source);
        while (!q.empty())
        {
            int vert = q.front();
            q.pop();
            for (int i = 0; i < adjacency_list[vert].size(); i++)
            {
                int curr_edge = adjacency_list[vert][i];
                bool not_seen = level[edges[curr_edge].to] == -1;
                bool has_cap = (edges[curr_edge].cap - edges[curr_edge].flow) > 0;
                if (not_seen && has_cap)
                {
                    level[edges[curr_edge].to] = level[vert] + 1;
                    q.push(edges[curr_edge].to);
                }
            }
        }
        return level[target] != -1;
    }

    int dfs(int from, int rec_flow)
    {
        if (rec_flow == 0)
            return 0;
        if (from == target)
            return rec_flow;

        for (int ed = 0; ed < adjacency_list[from].size(); ed++)
        {
            int curr_edge = adjacency_list[from][ed];
            int to = edges[curr_edge].to;
            bool steps_forward = level[from] + 1 == level[to];
            bool has_cap = (edges[curr_edge].cap - edges[curr_edge].flow) > 0;
            if (steps_forward && has_cap)
            {
                int temp_flow = dfs(to, min(rec_flow, edges[curr_edge].cap - edges[curr_edge].flow));
                if (temp_flow != 0)
                {
                    edges[curr_edge].flow += temp_flow;
                    edges[curr_edge ^ 1].flow -= temp_flow; // reverse edge
                    return temp_flow;
                }
            }
        }
        return 0;
    }

    int get_max_flow()
    {
        int max_flow = 0;
        while (has_path_to_target())
        {
            while (int pushed_flow = dfs(source, INF))
            {
                max_flow += pushed_flow;
            }
        }
        return max_flow;
    }
};

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int teams, corr, g_played, max_corr = 4;
    while (cin >> teams >> corr >> g_played && teams != 0)
    {
        vector<vector<int>> games(teams + max_corr + 1, vector<int>(teams + max_corr + 1, 0));
        vector<int> points(teams + max_corr + 1, 0);
        int t1, t2, my_t_games_played = 0;
        char outcome;
        for (int i = 0; i < g_played; i++)
        {
            cin >> t1 >> outcome >> t2;
            games[t1][t2]++;
            games[t2][t1]++;
            if (t1 == 0 || t2 == 0)
                my_t_games_played++;
            if (outcome == '>')
            {
                points[t1] += 2;
                continue;
            }
            else if (outcome == '<')
            {
                points[t2] += 2;
                continue;
            }
            points[t1]++;
            points[t2]++;
        }

        int games_to_be_played = (teams - 1) * corr;
        int total_viable_points = points[0] + ((games_to_be_played - my_t_games_played) * 2) - 1;
        bool is_winnable = true;
        // if there's a team with more points that my team can ever make, RIP
        for (int i = 1; i < teams; i++)
        {
            if (total_viable_points < points[i])
            {
                is_winnable = false;
                break;
            }
        }
        if (!is_winnable)
        {
            cout << "N\n";
            continue;
        }

        map<pair<int, int>, int> matches_played; // used to group other teams by matchups
        int required_points = 0;
        int intermed_node = teams;
        for (int i = 1; i < teams; i++)
        {
            for (int j = i + 1; j < teams; j++)
            {
                required_points += (corr - games[i][j]) * 2;
                matches_played[{i, j}] = intermed_node;
                intermed_node++;
            }
        }

        int src = 0, tgt = intermed_node + 1;
        Graph graph(intermed_node + 2, src, tgt);
        // links my team to all other teams, with cap equals to the
        // points my team can make subtracted by the points the other team has made
        for (int i = 1; i < teams; i++)
        {
            graph.add_edge(src, i, total_viable_points - points[i]);
        }
        // links all other teams, pairwise, to an intermediary node with infinite capacity,
        // then links this intermediary node to the target node with a capacity equals
        // to the most points that can be made from the matchup between the paired teams
        for (int i = 1; i < teams; i++)
        {
            for (int j = i + 1; j < teams; j++)
            {
                graph.add_edge(i, matches_played[{i, j}], INF);
                graph.add_edge(j, matches_played[{i, j}], INF);
                graph.add_edge(matches_played[{i, j}], tgt, (corr - games[i][j]) * 2);
            }
        }

        int mf = graph.get_max_flow();
        if (mf == required_points)
        {
            cout << "Y\n";
            continue;
        }
        cout << "N\n";
    }
    return 0;
}