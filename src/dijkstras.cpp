#include "dijkstras.h"


vector<int> dijkstra_shortest_path(const Graph& graph, int start, vector<int>& prev_nodes) {
    int num_nodes = graph.size();
    vector<int> distances(num_nodes, INF);
    vector<bool> visited(num_nodes, false);
    
    prev_nodes.assign(num_nodes, -1);
    
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    distances[start] = 0;  
    pq.push({0, start});   

    while (!pq.empty()) {
        auto [current_dist, current_node] = pq.top();
        pq.pop();

        if (!visited[current_node]) {
            visited[current_node] = true;  

            for (const Edge& edge : graph[current_node]) {
                int neighbor = edge.dst;
                int edge_weight = edge.weight;

                if (!visited[neighbor] && current_dist + edge_weight < distances[neighbor]) {
                    distances[neighbor] = current_dist + edge_weight;
                    prev_nodes[neighbor] = current_node;  
                    pq.push({distances[neighbor], neighbor}); 
                }
            }
        }
    }

    return distances;  
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