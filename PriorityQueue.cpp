#include "PriorityQueue.h"
#include <algorithm>

priorityQueue::priorityQueue() : size(0) {}

void priorityQueue::heapifyUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (costs[parent] > costs[index]) {
            swap(costs[parent], costs[index]);
            swap(vertices[parent], vertices[index]);
        }
        index = parent;
    }
}

void priorityQueue::heapifyDown(int index) {
    while (true) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;
        if (left < size && costs[left] < costs[smallest]) smallest = left;
        if (right < size && costs[right] < costs[smallest]) smallest = right;
        if (smallest != index) {
            swap(costs[index], costs[smallest]);
            swap(vertices[index], vertices[smallest]);
            index = smallest;
        }
        else break;
    }
}

void priorityQueue::push(int cost, int vertex) {
    costs[size] = cost;
    vertices[size] = vertex;
    heapifyUp(size++);
}

int priorityQueue::pop() {
    if (size == 0) return -1;
    int topVertex = vertices[0];
    costs[0] = costs[--size];
    vertices[0] = vertices[size];
    heapifyDown(0);
    return topVertex;
}

bool priorityQueue::isEmpty() {
    return size == 0;
}
