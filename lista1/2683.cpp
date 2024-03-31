#include <algorithm>
#include <bits/stdc++.h>
#include <cstdlib>

using namespace std;

struct UFNode
{
    int parent, height;
};

struct Edge
{
    int init, end, weight;
};

struct Graph
{
    int nVert, nEdge;
    Edge *edges;
};

int Find(int idx, UFNode nodes[])
{
    if (nodes[idx].parent != idx)
    {
        nodes[idx].parent = Find(nodes[idx].parent, nodes);
    }

    return nodes[idx].parent;
}

void Union(int x, int y, UFNode nodes[])
{
    int rootX = Find(x, nodes);
    int rootY = Find(y, nodes);

    if (nodes[rootX].height > nodes[rootY].height)
    {
        nodes[rootY].parent = rootX;
    }
    else if (nodes[rootX].height < nodes[rootY].height)
    {
        nodes[rootX].parent = rootY;
    }
    else
    {
        nodes[rootY].parent = rootX;
        nodes[rootX].height++;
    }
}

int Kruskal(Graph *graph)
{
    Edge mst[graph->nVert];
    UFNode *nodes = new UFNode[sizeof(UFNode) * graph->nVert];

    for (int v = 0; v < graph->nVert; v++)
    {
        nodes[v].parent = v;
        nodes[v].height = 0;
    }

    int currEdge = 0, i = 0;
    while (currEdge < graph->nVert - 1 && i < graph->nEdge)
    {
        Edge next_edge = graph->edges[i];
        i++;
        int rootX = Find(next_edge.init, nodes);
        int rootY = Find(next_edge.end, nodes);

        if (rootX != rootY)
        {
            mst[currEdge] = next_edge;
            currEdge++;
            Union(rootX, rootY, nodes);
        }
    }

    int totalWeight = 0;
    for (int j = 0; j < currEdge; j++)
    {
        totalWeight += mst[j].weight;
    }

    return totalWeight;
}

int Ascending(const void *a, const void *b)
{
    Edge *e1 = (Edge *)a;
    Edge *e2 = (Edge *)b;
    return e1->weight > e2->weight;
}

int Descending(const void *a, const void *b)
{
    Edge *e1 = (Edge *)a;
    Edge *e2 = (Edge *)b;
    return e1->weight < e2->weight;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int nGaleries;
    cin >> nGaleries;

    Graph *graph = new Graph;
    graph->nEdge = nGaleries;
    graph->nVert = nGaleries;
    graph->edges = new Edge[nGaleries];

    for (int i = 0; i < nGaleries; i++)
    {
        int in, out, w;
        cin >> in >> out >> w;
        graph->edges[i].init = in;
        graph->edges[i].end = out;
        graph->edges[i].weight = w;
    }

    qsort(graph->edges, graph->nEdge, sizeof(graph->edges[0]), Descending);
    int max = Kruskal(graph);
    qsort(graph->edges, graph->nEdge, sizeof(graph->edges[0]), Ascending);
    int min = Kruskal(graph);

    cout << max << "\n"
         << min << "\n";

    return 0;
}