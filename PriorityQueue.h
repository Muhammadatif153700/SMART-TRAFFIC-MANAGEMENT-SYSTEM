#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

using namespace std;

class priorityQueue {
    int costs[100];
    int vertices[100];
    int size;
    void heapifyUp(int index);
    void heapifyDown(int index);
public:
    priorityQueue();
    void push(int cost, int vertex);
    int pop();
    bool isEmpty();
};

#endif
