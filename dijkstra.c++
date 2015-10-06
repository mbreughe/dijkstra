#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <utility>
#include <string>
#include <sstream>
#include <climits> 
using namespace std;

typedef unsigned int Node;
typedef unsigned int Distance;
#define INVALID UINT_MAX
#define MAX_DIST UINT_MAX

class CompareDist
{
public:
    bool operator()(pair<Node, Distance> n1,pair<Node, Distance> n2) {
        return n1.second>n2.second;
    }
};

typedef priority_queue<pair<Node, Distance>, vector<pair<Node, Distance>>, CompareDist> PQ_NodeWeights;

void dijkstra_initialize_edge(const string& s, map<Node, map<Node, Distance>> & edges){
    istringstream iss(s);

    // Extract the source node, destination node and length of their path    
    unsigned int src, dst, length;
    iss >> src;
    iss >> dst;
    iss >> length;

    edges[src][dst]= length; 
}

string dijkstra_get_path(Node dest, PQ_NodeWeights & unvisited, map<Node, Node> & previous){
    return "-1";
}

void dijkstra_eval(map<Node, map<Node, Distance>> & edges, PQ_NodeWeights & unvisited, map<Node, Node> & previous, map<Node, Distance> distances, Node dest){
    while (! unvisited.empty()){
        // Get node with shortest distance
        pair<Node, Distance> curr_node = unvisited.top();
        // Mark this node as visited
        unvisited.pop();

        // Exit if their are no reachable nodes anymore
        if (curr_node.second == MAX_DIST){
            cout << "No reachable nodes" << endl;
            return;
        }

        // Process this node
        map<Node, Distance> neighbours = edges[curr_node.first];
        for (auto it = neighbours.begin(); it != neighbours.end(); ++it){
            Distance new_dist = curr_node.second + it->second;
            Node neighbour_node = it->first;
            // If this is the smallest distance we can find to neighbour node
            if (new_dist < distances[neighbour_node]){
                // update neighbour nodes' smallest distance
                distances[neighbour_node] = new_dist;
                // Push neighbour_node with this distance on the priority stack
                unvisited.emplace(neighbour_node, new_dist);  
                // Update neighbour_nodes' link towards the origin
                previous[neighbour_node] = curr_node.first;
            }

        }

        // If the processed node was the destination, stop processing!
        if (curr_node.first == dest){
            cout << "Found it!" << endl;
            return;
        }

    }
} 

string dijkstra_solve(istream& in_stream){
    // Lines that are read will first be stored in a string
    string s;

    // Get number of nodes and edges 
    getline(in_stream, s);
    istringstream iss(s);
    unsigned num_nodes = 0;
    unsigned num_edges = 0;
    iss >> num_nodes; 
    iss >> num_edges;
 
    // set up data structures for our algorithm  
    map<Node, map<Node, Distance>> edges;   // Weight of the edges Node
    PQ_NodeWeights unvisited;               // Set of unvisited nodes, prioritized by distance
    map<Node, Node> previous;               // Neighbour node on the path to the origin
    map<Node, Distance> distances;          // Shortest distance to reach this node

    // Initialize the edges of the graph
    for (int i=0; i< num_edges; ++i){
        getline(in_stream, s);
        dijkstra_initialize_edge(s, edges);
    }

    // Initialize the nodes of the graph
    for (Node n=1; n <= num_nodes; ++n){
        if (n == 1){
            unvisited.emplace(n, 0);
            distances[n] = 0;
        }
        else{
            unvisited.emplace(n, MAX_DIST);
            distances[n] = MAX_DIST;
        }
        previous[n] = INVALID;
    }

    dijkstra_eval(edges, unvisited, previous, distances, num_nodes);

    string path = dijkstra_get_path(num_nodes, unvisited, previous); 
    
    return path;
}
int main(){
    std::cout << dijkstra_solve(cin) << endl;
}
