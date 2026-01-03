#include "ActivityStack.h"

ActivityStack::ActivityStack() : top(NULL) {}

void ActivityStack::push(string action) {
    LogNode* newNode = new LogNode;
    newNode->log = action;
    newNode->next = top;
    top = newNode;
}

void ActivityStack::displayHistory() {
    cout << "\n- Recent Activity Log -" << endl;
    LogNode* temp = top;
    if (!temp) cout << "No activity recorded." << endl;
    while (temp) {
        cout << temp->log << endl;


        temp = temp->next;
    }
}

ActivityStack::~ActivityStack() {
    while (top) {
        LogNode* temp = top;
        top = top->next;
        delete temp;
    }
}
