#include "dijkstras.h"


vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int graph_size = G.size();
    vector<int> distance(graph_size, INF);
    vector<bool> visits(graph_size, 0);
    previous.assign(graph_size, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    distance[source] = 0;
    pq.push({0, source});
    while (!pq.empty()){
        auto [curDis, cur] = pq.top();
        pq.pop();

        if (!visits[cur]){
            visits[cur] = 1;

            for (const Edge & e : G[cur]){
                int adjacent_vertex = e.dst;
                int wgt = e.weight;
                if (!visits[adjacent_vertex] && distance[cur] + wgt < distance[adjacent_vertex]){
                    distance[adjacent_vertex] = distance[cur] + wgt;
                    previous[adjacent_vertex] = cur;
                    pq.push({distance[adjacent_vertex], adjacent_vertex});
                }
            }
        }
    }
    return distance;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    for (int at = destination; at != -1; at = previous[at]) {
        path.push_back(at);
    }
    std::reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& path, int total) {
    if (path.empty()) {
        cout << "No path found" << endl;
        return;
    }
    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i] << " ";
        if (i < path.size() - 1) cout << endl;
    }
    cout << "\nTotal cost is " << total << endl;
}