#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <string>
#include "ActivityStack.h"
#include "HashTable.h"
#include "MaxHeap.h"
#include "PriorityQueue.h"

using namespace std;

// Node for adjacency list 
class Node {
public:
    Node* next;
    string vertex;
    int weight, greenTime;
    Node(int weight, string vertex) : weight(weight), vertex(vertex), next(NULL), greenTime(0) {}
};


class List {
public:
    Node* head;
    List() : head(NULL) {}
    void insert(string vertex, int weight);
    void display(string vertex);
};

class Graph {
private:
    List adjList[100];
    string vertices[100];
    int count;
    string vehicles[100][2];
    string blocked[100][2];
    int blockedCount, vehicleCountTotal;
    HashTable roadCongestion;
    ActivityStack history;

    int findVertex(string vertex);
    void reversePath(int path[], int pathSize);
    int heuristic(int start, int end);
    int mapPriority(string priority);

public:
    Graph();
    ~Graph() {}

    void insertEdge(string start, string end, int weight);
    void removeEdge(string start, string end);
    void blockRoad(string start, string end);
    void saveNetworkToFile();
    void readNetworkCSV();
    void readTrafficSignals();
    void readVehicles();
    void readClosures();
    void readEmergencyVehicles();
    void dijkstra(int start, int end, int*& path, int& pathSize);
    void simulateTraffic();
    void emergencyVehicleRouting(string start, string end);

    void displayCongestion();
    void showHistory();
    void displayNetwork();
    void displayBlocked();
    void displaySignals();
};

#endif
