// Mania de Par
// Complexidade: O((C + V) log C)

#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

struct State {
    int cost, node, parity;
    bool operator>(const State& o) const { return cost > o.cost; }
};

int main() {
    int c, v;
    scanf("%d %d", &c, &v);

    vector<vector<pair<int, int> > > adj(c + 1);
    for (int i = 0; i < v; i++) {
        int c1, c2, g;
        scanf("%d %d %d", &c1, &c2, &g);
        adj[c1].push_back(make_pair(c2, g));
        adj[c2].push_back(make_pair(c1, g));
    }

    const int INF = 1e9;
    vector<vector<int> > dist(c + 1, vector<int>(2, INF));
    priority_queue<State, vector<State>, greater<State> > pq;

    dist[1][0] = 0;
    State init = {0, 1, 0};
    pq.push(init);

    while (!pq.empty()) {
        State cur = pq.top();
        pq.pop();

        if (cur.cost > dist[cur.node][cur.parity]) continue;

        for (size_t i = 0; i < adj[cur.node].size(); i++) {
            int next = adj[cur.node][i].first;
            int w = adj[cur.node][i].second;
            int np = 1 - cur.parity;

            if (dist[cur.node][cur.parity] + w < dist[next][np]) {
                dist[next][np] = dist[cur.node][cur.parity] + w;
                State ns = {dist[next][np], next, np};
                pq.push(ns);
            }
        }
    }

    if (dist[c][0] >= INF) {
        printf("-1\n");
    } else {
        printf("%d\n", dist[c][0]);
    }

    return 0;
}
