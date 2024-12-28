// BELLMAN-FORD ALGORITHM

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>
using namespace std;

string fileName = "graph1.txt";

// Define a structure for a node in the graph
struct Node {
    int index, predecessor, cost;
};

// Define a structure for the graph
struct Graph {
    int numNodes = 0;                   // Number of nodes in the graph
    vector<Node> nodes;                 // List of nodes
    int** edges = new int* [numNodes];  // Adjacency matrix for edges
};


void menu() {
    cout << endl;
    cout << "Bellman-Ford Algorithm - Options:" << endl;
    cout << "1) Read graph from file" << endl;
    cout << "2) Generate random graph" << endl;
    cout << "3) Run algorithm" << endl;
    cout << "4) Display shortest path" << endl;
    cout << "5) Exit" << endl;
    cout << endl;
    cout << "Choice: ";
}

void readGraph(Graph& G) {
    int numNodes;

    ifstream file(fileName);

    // Check if the file opened successfully
    if (!file.is_open()) {
        cout << "Error: Could not open file '" << fileName << "'. Please check if the file exists and is accessible." << endl;
        return;
    }

    // Read the number of nodes from the file
    if (!(file >> numNodes)) {
        cout << "Error: Failed to read the number of nodes from the file." << endl;
        return;
    }

    G.nodes.clear();        // in case we already read/generated graph before
    G.numNodes = numNodes;
    G.edges = new int* [numNodes];
    for (int i = 0; i < numNodes; i++) {
        G.edges[i] = new int[numNodes];
    }

    int edgeCost;
    for (int i = 0; i < numNodes; i++) {
        for (int j = 0; j < numNodes; j++) {
            if (!(file >> edgeCost)) {
                cout << "Error: Failed to read edge cost for node " << i << " to node " << j << "." << endl;
                return;
            }

            G.edges[i][j] = (edgeCost == 9999) ? NULL : edgeCost;
        }
    }

    cout << "Graph successfully read from file." << endl;
    cout << endl;
}

void generateGraph(Graph& G, int numNodes) {
    G.nodes.clear();        // in case we already read/generated graph before
    G.numNodes = numNodes;

    G.edges = new int* [numNodes];
    for (int i = 0; i < numNodes; i++) {
        G.edges[i] = new int[numNodes];
    }

    // Randomly assign weights to edges
    for (int i = 0; i < numNodes; i++) {
        for (int j = 0; j < numNodes; j++) {
            G.edges[i][j] = rand() % numNodes + 1;
        }
    }
}

void bellmanFord(Graph& G, int startNode) {
    if (startNode > G.numNodes) {
        cout << "Node " << startNode << " does not exist!" << endl;
        return;
    }

    // Initialize nodes
    for (int i = 0; i < G.numNodes; i++) {
        Node n;
        n.index = i;
        G.nodes.push_back(n);
    }

    // Start the timer for execution time measurement
    auto start = std::chrono::steady_clock::now();

    // Initialize the starting node
    G.nodes[startNode].cost = 0;
    G.nodes[startNode].predecessor = -1;

    // Set cost to infinity and predecessor to -1 for all other nodes
    for (int i = 0; i < G.numNodes; i++) {
        if (G.nodes[i].index == startNode) continue;
        G.nodes[i].cost = INT16_MAX;
        G.nodes[i].predecessor = -1;
    }

    // Relax edges repeatedly for (numNodes - 1) iterations
    for (int k = 0; k < G.numNodes - 1; k++) {
        for (int u = 0; u < G.nodes.size(); u++) {
            for (int v = 0; v < G.nodes.size(); v++) {
                if (G.nodes[v].index == u) continue;

                if ((G.nodes[u].cost + G.edges[u][v]) < G.nodes[v].cost) {
                    G.nodes[v].cost = G.nodes[u].cost + G.edges[u][v];
                    G.nodes[v].predecessor = G.nodes[u].index;
                }
            }
        }
    }

    // Check for negative-weight cycles
    for (int u = 0; u < G.nodes.size(); u++) {
        for (int v = 0; v < G.nodes.size(); v++) {
            if (G.nodes[v].index == u) continue;

            if (G.nodes[u].cost + G.edges[u][v] < G.nodes[v].cost) {
                cout << "Error: Negative-weight cycle detected!" << endl;
                return;
            }
        }
    }

    // End the timer
    auto end = std::chrono::steady_clock::now();
    cout << "Execution time of Bellman-Ford algorithm: "
        << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "μs." << endl;
}

// Recursive function to display the shortest path
void displayPath(Graph G, Node source, Node destination) {
    if (source.index == destination.index) {
        cout << "Path: " << destination.index << " ";
    }
    else {
        if (destination.predecessor == -1) {
            cout << "No path exists between " << source.index << " and " << destination.index << "!" << endl;
        }
        else {
            displayPath(G, source, G.nodes[destination.predecessor]);
            cout << destination.index << " ";
        }
    }
}

// Print the adjacency matrix of the graph
void printGraph(Graph G) {
    for (int i = 0; i < G.numNodes; i++) {
        for (int j = 0; j < G.numNodes; j++) {
            cout << G.edges[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    int selection;
    bool running = true;

    Graph G;
    int numNodes;

    int startNode = -1;
    int endNode;

    do {
        menu();
        cin >> selection;
        system("cls");
        switch (selection) {
        case 1:
            readGraph(G);
            printGraph(G);
            break;
        case 2:
            cout << "Enter the number of nodes: ";
            cin >> numNodes;
            generateGraph(G, numNodes);
            printGraph(G);
            break;
        case 3:
            cout << "Enter the starting node: ";
            cin >> startNode;
            bellmanFord(G, startNode);
            cout << endl;
            break;
        case 4:
            cout << "Enter the destination node: ";
            cin >> endNode;
            cout << endl;
            if (endNode > G.numNodes) {
                cout << "Destinantion node must be between 1 and (including) " << G.numNodes - 1 << endl;
                break;
            }
            if (startNode >= 0 && startNode < G.numNodes) {
                displayPath(G, G.nodes[startNode], G.nodes[endNode]);
                cout << "\nPath cost: " << G.nodes[endNode].cost << endl;
            }
            else {
                cout << "Starting node not initialized!" << endl;
            }
            cout << endl;
            break;
        case 5:
            running = false;
            break;
        default:
            cout << "ERROR: Invalid option!" << endl;
            break;
        }
    } while (running);

    return 0;
}
