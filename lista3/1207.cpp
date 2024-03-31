#include <algorithm>
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

    int vdk_types, vdk_categs;
    while (cin >> vdk_types >> vdk_categs)
    {
        int cost, categ;
        int vertices = vdk_types + vdk_categs;
        Graph graph(vertices + 2, vertices + 1, 0);

        for (int i = 1; i <= vdk_types; i++)
        {
            cin >> cost;
            graph.add_edge(i, 0, cost);
        }

        vector<int> cat_sz;
        for (int i = 0; i < vdk_categs; i++)
        {
            cin >> categ;
            cat_sz.push_back(categ);
        }

        int benefit, vdks, total_benefit = 0;
        for (int i = 0; i < vdk_categs; i++)
        {
            cin >> benefit;
            total_benefit += benefit;
            for (int j = 0; j < cat_sz[i]; j++)
            {
                cin >> vdks;
                graph.add_edge(i + vdk_types + 1, vdks, INF);
            }
            graph.add_edge(vertices + 1, i + vdk_types + 1, benefit);
        }

        cout << abs(total_benefit - graph.get_max_flow()) << "\n";
    }

    return 0;
}