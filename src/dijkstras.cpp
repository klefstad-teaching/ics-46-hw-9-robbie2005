#include "dijkstras.h"


vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int num_nodes = graph.size();
    std::vector<int> shortest_distances(num_nodes, INF);
    std::vector<bool> visited(num_nodes, false);
    
    prev_nodes.assign(num_nodes, -1);
    
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    
    shortest_distances[start_node] = 0;
    pq.push({0, start_node});

    while (!pq.empty()) {
        auto [current_distance, current_node] = pq.top();
        pq.pop();

        if (!visited[current_node]) {
            visited[current_node] = true;

            for (const Edge& edge : graph[current_node]) {
                int neighbor = edge.dst;
                int edge_weight = edge.weight;

                if (!visited[neighbor] && current_distance + edge_weight < shortest_distances[neighbor]) {
                    shortest_distances[neighbor] = current_distance + edge_weight;
                    prev_nodes[neighbor] = current_node;
                    pq.push({shortest_distances[neighbor], neighbor});
                }
            }
        }
    }
    return shortest_distances;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    for (int at = destination; at != -1; at = previous[at]) {
        path.push_back(at);
    }
    std::reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int> & path, int total){
    for(int i = 0; i < path.size(); ++i){cout << path[i] << " ";}
    cout << endl << "Total cost is " << total << endl;
}