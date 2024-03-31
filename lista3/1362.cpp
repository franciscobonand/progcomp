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

    map<string, int> shirt_szs;
    int tcases, shirt_qnt = 6;
    int shirts, vols;
    cin >> tcases;
    for (int test = 0; test < tcases; test++)
    {
        cin >> shirts >> vols;
        int vertices = vols + shirt_qnt + 2;
        int src = vols + shirt_qnt, tgt = vols + shirt_qnt + 1;
        Graph graph(vertices, src, tgt);

        shirt_szs["XXL"] = vols;
        shirt_szs["XL"] = vols + 1;
        shirt_szs["L"] = vols + 2;
        shirt_szs["M"] = vols + 3;
        shirt_szs["S"] = vols + 4;
        shirt_szs["XS"] = vols + 5;

        int cap = shirts / 6;
        // shirts to terminals
        for (int i = 0; i < 6; i++)
        {
            graph.add_edge(vols + i, tgt, cap);
        }

        // source to voluntaries
        for (int i = 0; i < vols; i++)
        {
            graph.add_edge(src, i, 1);
        }

        string shirt1, shirt2;
        // voluntaries to shirts
        for (int i = 0; i < vols; i++)
        {
            cin >> shirt1 >> shirt2;
            graph.add_edge(i, shirt_szs[shirt1], 1);
            graph.add_edge(i, shirt_szs[shirt2], 1);
        }
        int mf = graph.get_max_flow();
        if (mf >= vols)
        {
            cout << "YES\n";
            continue;
        }
        cout << "NO\n";
    }

    return 0;
}