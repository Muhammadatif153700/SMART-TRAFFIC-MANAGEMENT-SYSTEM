#include "HashTable.h"

HashNode::HashNode(string key, int value) : key(key), value(value), next(NULL) {}

HashTable::HashTable() {
    for (int i = 0; i < 101; i++) table[i] = NULL;
}

HashTable::~HashTable() {
    for (int i = 0; i < 101; i++) {
        HashNode* entry = table[i];
        while (entry) {
            HashNode* prevNode = entry;
            entry = entry->next;
            delete prevNode;
        }
    }
}

int HashTable::hashFunc(string key) {
    int hashValue = 0;
    for (int i = 0; i < key.length(); i++)
        hashValue = (hashValue * 31 + key[i]) % 101;
    return hashValue;
}

void HashTable::update(string key, int value) {
    int index = hashFunc(key);
    HashNode* temp = table[index];
    while (temp) {
        if (temp->key == key) {
            temp->value += value;
            return;
        }
        temp = temp->next;
    }
    HashNode* newNode = new HashNode(key, value);
    newNode->next = table[index];
    table[index] = newNode;
}

void HashTable::display() {
    for (int i = 0; i < 101; i++) {
        HashNode* temp = table[i];
        while (temp) {
            cout << temp->key << ":" << temp->value << endl;
            temp = temp->next;
        }
    }
}
