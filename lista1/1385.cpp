#include <bits/stdc++.h>

#define INF 0x3f3f3f3f

using namespace std;

typedef priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> min_heap; 

int offset[11], resp[11][11];

bool format(string *prices, int currPers, int currCol, int sum, int numcols, int lastperson) {
    if (currCol == numcols) {
        int val = 0, acc = 0;
        for (int i = offset[currPers]; i < (int)prices[currPers].size(); i++){
            val = (val * 10) + (prices[currPers][i] - '0');
        }
        for (int i = 0; i < numcols; i++) {
            acc += resp[currPers][i];
        }
        if (acc != val) return false;
        resp[currPers][currCol] = val;
        if (currPers == lastperson + 1) return true;
        return format(prices, currPers+1, currCol, sum, numcols, lastperson);
    }

    int currChar = offset[currPers];
    int numIter = min(offset[currPers]+3, (int)prices[currPers].size());
    if (currPers == lastperson+1) numIter = (int)prices[currPers].size();

    int val = 0;
    for (int i = offset[currPers]; i < numIter; i++) {
        val = (val * 10) + (prices[currPers][i] - '0');
        offset[currPers] = i+1;
        resp[currPers][currCol] = val;
        if (currPers <= lastperson && format(prices, currPers+1, currCol, sum+val, numcols, lastperson)) {
            return true;
        } else if (currPers == lastperson + 1) {
            if (sum == val && format(prices, 1, currCol+1, 0, numcols, lastperson)) return true;
            if (val > sum) {
                offset[currPers] = currChar;
                break;
            }
        }
        offset[currPers] = currChar;

        if (prices[currPers][currChar] == '0') break;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);

    int cases, i;
    cin >> cases;
    for (int j = 0; j < cases; j++) {
        string lines[11], names[11], prices[11];
        int currLine = 0;
        while (cin >> lines[currLine]) {
            if (lines[currLine][0] == 'T' && lines[currLine][1] == 'P') break;
            if (currLine > 0) {
                string name = "";
                for (i = 0; i < lines[currLine].size(); i++){
                    char c = lines[currLine][i];
                    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
                        name.push_back(c);
                    } else {
                        names[currLine] = name;
                        break;
                    }
                }
                while (i < lines[currLine].size()) {
                    prices[currLine].push_back(lines[currLine][i]);
                    i++;
                }
            }
            currLine++;
            prices[currLine] = "";
        }
        for (i = 2; i < lines[currLine].size(); i++) {
            prices[currLine].push_back(lines[currLine][i]);
        }
        int lastperson = currLine-1;
        int numcols = (lines[0].size()-6)/2;

        memset(offset, 0, sizeof(offset));
        memset(resp,0,sizeof(resp));
        format(prices, 1, 0, 0, numcols, lastperson);

        for (int k = 0; k < numcols; k++) cout << "P" << k+1 << " ";
        cout << "Totals\n";
        for (i = 1; i < currLine; i++) {
            cout << names[i].c_str();
            for (int k = 0; k <= numcols; k++){
                cout << " " << resp[i][k];
            }
            cout << "\n"; 
        }
        cout << "TP";
        for (int k = 0; k <= numcols; k++){
            cout << " " << resp[i][k];
        }
        cout << "\n";
    }

    return 0;
}