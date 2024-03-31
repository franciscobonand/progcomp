#include <bits/stdc++.h>

#define INF 0x3f3f3f3f

using namespace std;

typedef priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> min_heap;
typedef vector<vector<unsigned long long>> matrix;

map<string, int> note_dist = {
    {"Ab", 12},
    {"A", 1},
    {"A#", 2},
    {"Bb", 2},
    {"B", 3},
    {"B#", 4},
    {"Cb", 3},
    {"C", 4},
    {"C#", 5},
    {"Db", 5},
    {"D", 6},
    {"D#", 7},
    {"Eb", 7},
    {"E", 8},
    {"E#", 9},
    {"Fb", 8},
    {"F", 9},
    {"F#", 10},
    {"Gb", 10},
    {"G", 11},
    {"G#", 12}};

string getNoteDistance(vector<string> notes)
{
    string nt_dists = "";
    int dist_diff;
    for (int i = 0; i < notes.size() - 1; i++)
    {
        dist_diff = note_dist[notes[i]] - note_dist[notes[i + 1]];
        if (dist_diff < 0)
            dist_diff += 12;
        nt_dists += " " + to_string(dist_diff);
    }
    return nt_dists;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int m, t;
    while (cin >> m >> t && m != 0)
    {
        vector<string> song(m);
        vector<string> snippet(t);

        for (int i = 0; i < m; i++)
        {
            cin >> song[i];
        }
        for (int i = 0; i < t; i++)
        {
            cin >> snippet[i];
        }

        string song_notes_dist = getNoteDistance(song);
        string snippet_notes_dist = getNoteDistance(snippet);

        auto snip_in_song = song_notes_dist.find(snippet_notes_dist);
        if (snip_in_song == string::npos)
        {
            cout << "N\n";
            continue;
        }
        cout << "S\n";
    }

    return 0;
}