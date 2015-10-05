#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <utility>
#include <string>
#include <sstream>
using namespace std;

typedef unsigned int Node;
typedef unsigned int Distance;

class CompareDist
{
public:
    bool operator()(pair<Node, Distance> n1,pair<Node, Distance> n2) {
        return n1.second>n2.second;
    }
};

typedef priority_queue<pair<Node, Distance>, vector<pair<Node, Distance>>, CompareDist> PQ_NodeWeights;

void dijkstra_initialize_node(const string& s, map<Node, map<Node, Distance>> & edges, PQ_NodeWeights & unvisited, map<Node, Node> & previous){
    istringstream iss(s);

    // Extract the source node, destination node and length of their path    
    unsigned int src, dst, length;
    iss >> src;
    iss >> dst;
    iss >> length;

    edges[src][dst]= length; 
    (void) unvisited;
    (void) previous;
}

string dijkstra_get_path(Node dest, PQ_NodeWeights & unvisited, map<Node, Node> & previous){
    return "-1";
}

void dijkstra_eval(map<Node, map<Node, Distance>> & edges, PQ_NodeWeights & unvisited, map<Node, Node> & previous){
;
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
    map<Node, map<Node, Distance>> edges;
    PQ_NodeWeights unvisited;
    map<Node, Node> previous;

    // Initialize the graph
    for (int i=0; i< num_edges; ++i){
        std::cout << "First node: ";
        getline(in_stream, s);
        dijkstra_initialize_node(s, edges, unvisited, previous);
        cout << endl;
    }

    dijkstra_eval(edges, unvisited, previous);

    string path = dijkstra_get_path(num_nodes, unvisited, previous); 
    
    return path;
}
int main(){
    std::cout << dijkstra_solve(cin) << endl;
}
