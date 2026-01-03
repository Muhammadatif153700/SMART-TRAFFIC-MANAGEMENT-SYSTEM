#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <string>
using namespace std;

class HashNode {
public:
    string key;
    int value;
    HashNode* next;
    HashNode(string key, int value);
};

class HashTable {
    HashNode* table[101];
    int hashFunc(string key);
public:
    HashTable();
    ~HashTable();
    void update(string key, int value);
    void display();
};

#endif
