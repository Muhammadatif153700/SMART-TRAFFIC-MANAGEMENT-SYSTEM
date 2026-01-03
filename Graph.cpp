#include "Graph.h"
#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
using namespace std;
void List::insert(string vertex, int weight) {
    Node* newNode = new Node(weight, vertex);

    if (!head)
        head = newNode;
    else {
        Node* temp = head;
        while (temp->next)
            temp = temp->next;
        temp->next = newNode;
    }
}

void List::display(string vertex) {
    if (!head)
        return;

    cout << vertex << "->";
    Node* temp = head->next;
    while (temp) {
        cout << "(" << temp->vertex << "," << temp->weight << ") ";
        temp = temp->next;
    }
    cout << endl;
}
Graph::Graph() : count(0), vehicleCountTotal(0), blockedCount(0) {}


int Graph::findVertex(string vertex) {
    for (int i = 0; i < count; i++) {
        if (adjList[i].head && adjList[i].head->vertex == vertex)
            return i;
    }
    return -1;
}

void Graph::reversePath(int path[], int pathSize) {
    for (int i = 0; i < pathSize / 2; i++)
        swap(path[i], path[pathSize - 1 - i]);
}

int Graph::heuristic(int start, int end) {
    return abs(start - end);
}

int Graph::mapPriority(string priority) {
    if (priority == "High")
        return 2;
    if (priority == "Medium")
        return 1;
    return 0;
}

void Graph::insertEdge(string start, string end, int weight) {
    int startIndex = findVertex(start);

    if (startIndex == -1) {
        adjList[count].insert(start, 0);
        vertices[count] = start;
        startIndex = count++;
    }

    adjList[startIndex].insert(end, weight);
    history.push("Added road from " + start + " to " + end);
}

void Graph::removeEdge(string start, string end) {
    int startIndex = findVertex(start);
    if (startIndex == -1)
        return;

    Node* temp = adjList[startIndex].head;
    Node* localPrev = nullptr;

    while (temp) {
        if (temp->vertex == end) {
            if (!localPrev)
                adjList[startIndex].head = temp->next;
            else
                localPrev->next = temp->next;

            delete temp;
            return;
        }
        localPrev = temp;
        temp = temp->next;
    }
}

void Graph::blockRoad(string start, string end) {
    removeEdge(start, end);
    removeEdge(end, start);

    blocked[blockedCount][0] = start;
    blocked[blockedCount][1] = end;
    blockedCount++;

    history.push("Blocked road: " + start + " <-> " + end);
}

void Graph::saveNetworkToFile() {
    ofstream outFile("road_network.csv");
    outFile << "Source,Destination,Weight" << endl;

    for (int i = 0; i < count; i++) {
        Node* temp = adjList[i].head->next;
        while (temp) {
            outFile << vertices[i] << "," << temp->vertex << "," << temp->weight << endl;
            temp = temp->next;
        }
    }

    outFile.close();
    cout << "Network changes saved." << endl;
}


void Graph::readNetworkCSV() {
    ifstream file("road_network.csv");
    string s, e, w, line;

    getline(file, line); 

    while (getline(file, s, ',')) {
        getline(file, e, ',');
        getline(file, w);

        if (s != "") {
            insertEdge(s, e, stoi(w));
            insertEdge(e, s, stoi(w));
        }
    }
}

void Graph::readTrafficSignals() {
    ifstream file("traffic_signals.csv");
    string v, t;

    while (getline(file, v, ',')) {
        getline(file, t);
        int idx = findVertex(v);

        if (idx != -1)
            adjList[idx].head->greenTime = stoi(t);
    }
}

void Graph::readVehicles() {
    ifstream file("vehicles.csv");
    string id, s, e;

    getline(file, id); 

    while (getline(file, id, ',')) {
        getline(file, s, ',');
        getline(file, e);

        vehicles[vehicleCountTotal][0] = s;
        vehicles[vehicleCountTotal][1] = e;
        vehicleCountTotal++;
    }
}

void Graph::readClosures() {
    ifstream file("road_closures.csv");
    string s, e, st;

    while (getline(file, s, ',')) {
        getline(file, e, ',');
        getline(file, st);

        if (st == "Blocked")
            blockRoad(s, e);
    }
}

void Graph::readEmergencyVehicles() {
    MaxHeap emergency;
    ifstream file("emergency_vehicles.csv");
    string id, s, e, p;

    getline(file, id); 

    while (getline(file, id, ',')) {
        getline(file, s, ',');
        getline(file, e, ',');
        getline(file, p);

        emergency.push(s + e, mapPriority(p));
    }

    while (!emergency.isEmpty()) {
        string full = emergency.pop();
        string s_node = string(1, full[0]);
        string e_node = string(1, full[1]);

        cout << "\nEmergency vehicle: " << s_node << " to " << e_node << endl;
        emergencyVehicleRouting(s_node, e_node);
    }
}


void Graph::dijkstra(int start, int end, int*& path, int& pathSize) {
    int* distances = new int[100];
    int* parent = new int[100];
    bool* visited = new bool[100];

    for (int i = 0; i < 100; i++) {
        distances[i] = 30000;
        visited[i] = false;
        parent[i] = -1;
    }

    distances[start] = 0;

    for (int i = 0; i < count; i++) {
        int minDist = 30000, curr = -1;

        for (int j = 0; j < count; j++) {
            if (!visited[j] && distances[j] < minDist) {
                minDist = distances[j];
                curr = j;
            }
        }

        if (curr == -1)
            break;

        visited[curr] = true;

        Node* t = adjList[curr].head->next;
        while (t) {
            int nIdx = findVertex(t->vertex);
            if (!visited[nIdx] && distances[nIdx] > distances[curr] + t->weight) {
                distances[nIdx] = distances[curr] + t->weight;
                parent[nIdx] = curr;
            }
            t = t->next;
        }
    }

    pathSize = 0;
    int currPath = end;
    while (currPath != -1) {
        path[pathSize++] = currPath;
        currPath = parent[currPath];
    }
    reversePath(path, pathSize);

    delete[] distances;
    delete[] parent;
    delete[] visited;
}


void Graph::simulateTraffic() {
    int** paths = new int* [vehicleCountTotal];
    int* pSizes = new int[vehicleCountTotal];

    for (int i = 0; i < vehicleCountTotal; i++)
        paths[i] = new int[100];

    MaxHeap cong;

    for (int i = 0; i < vehicleCountTotal; i++)
        dijkstra(findVertex(vehicles[i][0]), findVertex(vehicles[i][1]), paths[i], pSizes[i]);

    bool running = true;
    while (running) {
        running = false;

        for (int i = 0; i < vehicleCountTotal; i++) {
            if (pSizes[i] > 1) {
                running = true;
                string road = vertices[paths[i][0]] + "->" + vertices[paths[i][1]];
                roadCongestion.update(road, 1);
                cong.push(vertices[paths[i][1]], 1);

                cout << "Vehicle " << i + 1 << " moving: " << vertices[paths[i][0]]
                    << " to " << vertices[paths[i][1]] << endl;

                for (int j = 0; j < pSizes[i] - 1; j++)
                    paths[i][j] = paths[i][j + 1];

                pSizes[i]--;
            }
        }

        while (!cong.isEmpty())
            cout << "Signal Green at: " << cong.pop() << endl;

        cout << "----------------------------------" << endl;
    }

    for (int i = 0; i < vehicleCountTotal; i++)
        delete[] paths[i];

    delete[] paths;
    delete[] pSizes;
}
void Graph::emergencyVehicleRouting(string start, string end) {
    int sIdx = findVertex(start);
    int eIdx = findVertex(end);

    priorityQueue pq;

    int* g = new int[100];
    int* f = new int[100];
    int* par = new int[100];
    bool* vis = new bool[100];

    for (int i = 0; i < count; i++) {
        g[i] = 30000;
        f[i] = 30000;
        par[i] = -1;
        vis[i] = false;
    }

    g[sIdx] = 0;
    f[sIdx] = heuristic(sIdx, eIdx);
    pq.push(f[sIdx], sIdx);

    while (!pq.isEmpty()) {
        int curr = pq.pop();
        if (curr == eIdx)
            break;

        if (vis[curr])
            continue;

        vis[curr] = true;

        Node* t = adjList[curr].head->next;
        while (t) {
            int nIdx = findVertex(t->vertex);
            if (!vis[nIdx] && g[nIdx] > g[curr] + t->weight) {
                g[nIdx] = g[curr] + t->weight;
                f[nIdx] = g[nIdx] + heuristic(nIdx, eIdx);
                par[nIdx] = curr;
                pq.push(f[nIdx], nIdx);
            }
            t = t->next;
        }
    }

    int* p = new int[100];
    int ps = 0;
    int c = eIdx;

    while (c != -1) {
        p[ps++] = c;
        c = par[c];
    }
    reversePath(p, ps);

    cout << "Path: ";
    for (int i = 0; i < ps; i++)
        cout << vertices[p[i]] << (i == ps - 1 ? "" : " -> ");

    cout << "\nEmergency destination reached!\n";

    delete[] g;
    delete[] f;
    delete[] par;
    delete[] vis;
    delete[] p;
}

void Graph::displayCongestion() {
    roadCongestion.display(); 
}
void Graph::showHistory() {
    history.displayHistory();
}
void Graph::displayNetwork() {
    for (int i = 0; i < count; i++)
        adjList[i].display(vertices[i]);
}
void Graph::displayBlocked() {
    for (int i = 0; i < blockedCount; i++)
        cout << blocked[i][0] << " to " << blocked[i][1] << " BLOCKED\n";
}
void Graph::displaySignals() {
    for (int i = 0; i < count; i++)
        cout << vertices[i] << " Green: " << adjList[i].head->greenTime << "s\n";
}
