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

    Edge(int newFrom = 0, int newTo = 0, long newCapacity = 0) {
      from = newFrom;
      to = newTo;
      capacity = newCapacity;
    }

    bool isResidual() {
      return capacity == 0;
    }

    long remainingCapacity() {
      return capacity - flow;
    }

    void augment(long bottleNeck) {
      flow += bottleNeck;
      residual->flow -= bottleNeck;
    }
};

class NetworkFlow {
    private:
    int n, s, t;
    int visitedToken;
    vector<int> visited;

    long maxFlow;
    map<int, list<Edge*>> graph;

    public:
    NetworkFlow(int newN, int newS, int newT) {
        maxFlow = 0;
        visitedToken = 1;
        n = newN;
        s = newS;
        t = newT;
        visited.resize(n);
    }

    void addEdge(int from, int to, long capacity) {
        Edge* e1 = new Edge(from, to, capacity);
        Edge* e2 = new Edge(to, from, 0);
        e1->residual = e2;
        e2->residual = e1;
        graph[from].push_back(e1);
        graph[to].push_back(e2);
    }

    map<int, list<Edge*>> getGraph() {
        return graph;
    }

    long getMaxFlow() {
        for (long f = dfs(s, 1e9); f != 0; f = dfs(s, 1e9)) {
        visitedToken++;
        maxFlow += f;
        }
        return maxFlow;
    }

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

    void printResults() {
        for (const auto &pair : graph ) {
            for (auto edge: pair.second)
                if (!edge->isResidual())
                    cout<<"From "<<edge->from<<" to "<<edge->to<<" the flow is "<<edge->flow<<endl;
        }
        cout<<endl;
    }
  };

void connectSourceAndCustomers(NetworkFlow &networkFlow, vector<pair<int, int>> &customers, int n, int source);
void connectSinkAndProducts(NetworkFlow &networkFlow, vector<pair<int, int>> &products, int n, int k, int sink);

int main() {
    int source = 5, sink = 6, size = 7, n = 3, k = 2;
    NetworkFlow networkFlow(size, source, sink);
    vector<pair<int, int>> customers;
    vector<pair<int, int>> products;
    customers.push_back(make_pair(1, 3));
    customers.push_back(make_pair(0, 1));
    customers.push_back(make_pair(2, 5));
    products.push_back(make_pair(2, 5));
    products.push_back(make_pair(1, 3));
    connectSourceAndCustomers(networkFlow, customers, n, source);
    connectSinkAndProducts(networkFlow, products, n, k, sink);
    networkFlow.addEdge(0, 3, 1);
    networkFlow.addEdge(2, 3, 1);
    networkFlow.addEdge(2, 4, 1);
    networkFlow.getMaxFlow();
    networkFlow.printResults();
    if (networkFlow.checkSolution(customers, products, source, sink, n))
        cout<<"The survey can be conducted!"<<endl;
    else
        cout<<"The survey can't be conducted!"<<endl;
}

void connectSourceAndCustomers(NetworkFlow &networkFlow, vector<pair<int, int>> &customers, int n, int source) {
    for (int i = 0; i < n; i++)
        networkFlow.addEdge(source, i, customers[i].second);
}

void connectSinkAndProducts(NetworkFlow &networkFlow, vector<pair<int, int>> &products, int n, int k, int sink) {
    for (int i = 0; i < k; i++)
        networkFlow.addEdge(n+i, sink, products[i].second);
}
