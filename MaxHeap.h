#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <string>
using namespace std;

class MaxHeap {
    string vertices[100];
    int counts[100];
    int size;
    void heapifyUp(int index);
    void heapifyDown(int index);
public:
    MaxHeap();
    void push(string vertex, int count);
    string pop();
    bool isEmpty();
};

#endif
