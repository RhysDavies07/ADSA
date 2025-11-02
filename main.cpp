#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <sstream>
using namespace std;

struct Edge {
    int cost;
    int from;
    int to;

    bool operator>(const Edge &other) const {
        return cost > other.cost;
    }
};

int charToCost(char c) {
    if (c >= 'A' && c <= 'Z') return c - 'A';
    return c - 'a' + 26;
}

vector<vector<int>> parseMatrix(const string &str) {
    vector<vector<int>> matrix;
    stringstream ss(str);
    string row;
    
    while (getline(ss, row, ',')) {
        vector<int> rowVals;
        for (char c : row) {
            if (c == '0' || c == '1') rowVals.push_back(c - '0'); 
            else rowVals.push_back(charToCost(c));
        }
        matrix.push_back(rowVals);
    }
    return matrix;
}

int main() {
    string countryStr, buildStr, destroyStr;
    cin >> countryStr >> buildStr >> destroyStr;

    vector<vector<int>> country = parseMatrix(countryStr);
    vector<vector<int>> build = parseMatrix(buildStr);
    vector<vector<int>> destroy = parseMatrix(destroyStr);

    int n = country.size();

    // 1. Compute the total destroy cost if all existing roads are removed
    int totalDestroy = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (country[i][j] == 1) {
                totalDestroy += destroy[i][j];
            }
        }
    }

    // 2. Prim’s MST using savings (negative cost for keeping existing roads)
    vector<bool> visited(n, false);
    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
    int mstCost = 0;

    // Start with node 0
    visited[0] = true;
    for (int j = 1; j < n; j++) {
        int cost = (country[0][j] == 1) ? -destroy[0][j] : build[0][j];
        pq.push({cost, 0, j});
    }

    int visitedCount = 1;
    while (visitedCount < n) {
        auto [cost, from, to] = pq.top();
        pq.pop();
        if (visited[to]) continue;

        visited[to] = true;
        visitedCount++;
        mstCost += cost;

        for (int nxt = 0; nxt < n; nxt++) {
            if (!visited[nxt] && nxt != to) {
                int edgeCost = (country[to][nxt] == 1) ? -destroy[to][nxt] : build[to][nxt];
                pq.push({edgeCost, to, nxt});
            }
        }
    }

    int totalCost = totalDestroy + mstCost;
    cout << totalCost << endl;

    return 0;
}