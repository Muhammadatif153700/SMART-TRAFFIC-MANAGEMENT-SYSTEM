#include "MaxHeap.h"
#include <algorithm>

MaxHeap::MaxHeap() : size(0) {}

void MaxHeap::heapifyUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (counts[parent] < counts[index]) {
            swap(vertices[parent], vertices[index]);
            swap(counts[parent], counts[index]);
        }
        index = parent;
    }
}

void MaxHeap::heapifyDown(int index) {
    while (true) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int largest = index;
        if (left < size && counts[left] > counts[largest]) largest = left;
        if (right < size && counts[right] > counts[largest]) largest = right;
        if (largest != index) {
            swap(vertices[index], vertices[largest]);
            swap(counts[index], counts[largest]);
            index = largest;
        }
        else break;
    }
}

void MaxHeap::push(string vertex, int count) {
    for (int i = 0; i < size; i++) {
        if (vertices[i] == vertex) {
            counts[i] += count;
            heapifyUp(i);
            return;
        }
    }
    vertices[size] = vertex;
    counts[size] = count;
    heapifyUp(size++);
}

string MaxHeap::pop() {
    if (size == 0) return "";
    string topVertex = vertices[0];
    vertices[0] = vertices[--size];
    counts[0] = counts[size];
    heapifyDown(0);
    return topVertex;
}

bool MaxHeap::isEmpty() {
    return size == 0;
}
