#include "dijkstras.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;

int main(){
    Graph test_graph;
    file_to_graph("medium.txt", test_graph);
    int src = 3;
    vector<int> prev;
    vector<int> dijkstra_path = dijkstra_shortest_path(test_graph, src, prev);
    int destination = 1;
    vector<int> short_path = extract_shortest_path(dijkstra_path, prev, destination);
    print_path(short_path, short_path.size());
    return 0;
}