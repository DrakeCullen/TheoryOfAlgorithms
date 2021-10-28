#include <iostream>
#include <vector>
#include <map>
#include <list>

using namespace std;

class Edge {
    public:
    int from, to;
    Edge* residual;
    long flow;
    long capacity;

    /**
     * Default constructor that inititializes an edge.
     * @param newFrom -> The index of the node we are coming from
     * @param newTo -> The index of the node we are going to
     * @param newCapacity -> The maximum capacity of the edge
     */
    Edge(int newFrom = 0, int newTo = 0, long newCapacity = 0) {
        from = newFrom;
        to = newTo;
        capacity = newCapacity;
    }

    /**
     * Determines whether an edge is residual. Used for printing forward edges.
     * @return bool -> Return true if the edge is residual.
     */
    bool isResidual() {
        return capacity == 0;
    }

    /**
     * Determines the remaining capacity of an edge.
     * @return long -> The remaining capacity.
     */
    long remainingCapacity() {
        return capacity - flow;
    }

    /**
     * Update the flow and residual flow of an edge based on the bottleneck value.
     * @param bottleNeck -> The lowest value on an augmenting path
     */
    void augment(long bottleNeck) {
        flow += bottleNeck;
        residual->flow -= bottleNeck;
    }
};

class NetworkFlow {
    private:
    // Inputs: n = number of nodes, s = source, t = sink
    int n, s, t;

    // 'visited' and 'visitedToken' are variables used in graph sub-routines to
    // track whether a node has been visited or not. In particular, node 'i' was
    // recently visited if visited[i] == visitedToken is true. This is handy
    // because to mark all nodes as unvisited simply increment the visitedToken.
    int visitedToken;
    vector<int> visited;

    long maxFlow;

    // The adjacency list representing the flow graph.
    map<int, list<Edge*>> graph;

    public:
    /**
     * Default constructor that inititializes an instance of Network Flow.
     * @param newN -> The total number of nodes
     * @param newS -> The index of the source node
     * @param newT -> The index of the sink node
     */
    NetworkFlow(int newN, int newS, int newT) {
        maxFlow = 0;
        visitedToken = 1;
        n = newN;
        s = newS;
        t = newT;
        visited.resize(n);
    }

    /**
     * Create a forward and residual edge between two nodes.
     * @param from -> The index of the node we are coming from
     * @param to -> The index of the node we are going to
     * @param capacity -> The maximum capacity of the edge
     */
    void addEdge(int from, int to, long capacity) {
        Edge* e1 = new Edge(from, to, capacity);
        Edge* e2 = new Edge(to, from, 0);
        e1->residual = e2;
        e2->residual = e1;
        graph[from].push_back(e1);
        graph[to].push_back(e2);
    }

    /**
     * Find the maximum flow in a network and update the flow from the sink to the source.
     * Use DFS to augment the flow.
     * @return maxFlow -> the total amount of flow through the network.
     */
    long getMaxFlow() {
        // Run dfs until the augmenting flow is 0
        for (long f = dfs(s, 1e9); f != 0; f = dfs(s, 1e9)) {
            visitedToken++;
            maxFlow += f;
        }
        for (auto edge:graph[6])
            if (edge->to == 5)
                edge->flow = maxFlow;
        return maxFlow;
    }

    /**
     * Performs DFS to augment the flow.
     * @param node -> The index of the last node you were at
     * @param flow -> The bottleneck of the augmenting path
     * @param newCapacity -> The maximum capacity of the edge
     * @return flow -> The bottleneck of the augmenting path
     */
    long dfs(int node, long flow) {
        if (node == t) return flow;

        visited[node] = visitedToken;

        list<Edge*> edges = graph[node];
        for (Edge* edge : edges) {
            if (edge->remainingCapacity() > 0 && visited[edge->to] != visitedToken) {
                long bottleNeck = dfs(edge->to, min(flow, edge->remainingCapacity()));
                if (bottleNeck > 0) {
                edge->augment(bottleNeck);
                return bottleNeck;
                }
            }
        }
        return 0;
    }

    /**
     * Verify that all the survey conditions are met.
     * @param customers -> A vector containing the customer minimum and maximum requirements
     * @param products -> A vector containing the product minimum and maximum requirements
     * @param source -> The index of the source
     * @param sink -> The index of the sink
     * @param n -> The number of node
     * @return bool -> Return true if all conditions are met.
     */
    bool checkSolution(vector<pair<int, int>> &customers, vector<pair<int, int>> &products, int source, int sink, int n) {
         for (const auto &pair : graph ){
            for (auto edge: pair.second) {
                if (!edge->isResidual()){
                    if (edge->from == source) {
                        if (edge->flow < customers[edge->to].first || edge->flow > customers[edge->to].second)
                            return false;
                    } else if (edge->to == sink) {
                        if (edge->flow < products[edge->from - n].first || edge->flow > products[edge->from - n].second)
                            return false;
                    }
                }
            }
         } 
         return true;
    }

    /**
     * Print the results for all forward edges
     */
    void printResults() {
        for (const auto &pair : graph ) {
            for (auto edge: pair.second)
                if (!edge->isResidual())
                    cout<<"From "<<edge->from<<" to "<<edge->to<<" the flow is "<<edge->flow<<endl;
        }
        cout<<endl;
    }
  };


void initializeMinMaxVectors(vector<pair<int, int>> &customers, vector<pair<int, int>> &products, int inputSize);
void connectSourceAndCustomers(NetworkFlow &networkFlow, vector<pair<int, int>> &customers, int n, int source);
void connectSinkAndProducts(NetworkFlow &networkFlow, vector<pair<int, int>> &products, int n, int k, int sink);
void connectCustomersAndProducts(NetworkFlow &networkFlow);

int main(int argc, char *argv[]) {
    int source = 5, sink = 6, size = 7, n = 3, k = 2;
    NetworkFlow networkFlow(size, source, sink);
    vector<pair<int, int>> customers;
    vector<pair<int, int>> products;
    
    initializeMinMaxVectors(customers, products, argc);
    connectSourceAndCustomers(networkFlow, customers, n, source);
    connectSinkAndProducts(networkFlow, products, n, k, sink);
    connectCustomersAndProducts(networkFlow);
    
    networkFlow.getMaxFlow();
    networkFlow.printResults();
    if (networkFlow.checkSolution(customers, products, source, sink, n))
        cout<<"The survey can be conducted!"<<endl;
    else
        cout<<"The survey can't be conducted!"<<endl;
}

// Add the corresponding ci,c'i values to the customers vector and the pj,p'j values to the products vector.
void initializeMinMaxVectors(vector<pair<int, int>> &customers, vector<pair<int, int>> &products, int inputSize) {
    customers.push_back(make_pair(1, 3));
    customers.push_back(make_pair(0, 1));
    customers.push_back(make_pair(2, 5));
    if (inputSize > 1)
        products.push_back(make_pair(3, 5));
    else
        products.push_back(make_pair(2, 5));
    products.push_back(make_pair(1, 3));
}

// Add edges between customers and products.
void connectCustomersAndProducts(NetworkFlow &networkFlow) {
    networkFlow.addEdge(0, 3, 1);
    networkFlow.addEdge(2, 3, 1);
    networkFlow.addEdge(2, 4, 1);
    networkFlow.addEdge(6, 5, 9);
}

// Create edges from the source node to each customer.
void connectSourceAndCustomers(NetworkFlow &networkFlow, vector<pair<int, int>> &customers, int n, int source) {
    for (int i = 0; i < n; i++)
        networkFlow.addEdge(source, i, customers[i].second);
}

// Create edges from each product to the sink.
void connectSinkAndProducts(NetworkFlow &networkFlow, vector<pair<int, int>> &products, int n, int k, int sink) {
    for (int i = 0; i < k; i++)
        networkFlow.addEdge(n+i, sink, products[i].second);
}
