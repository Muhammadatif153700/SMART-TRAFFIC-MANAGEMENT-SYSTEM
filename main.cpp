#include "Graph.h"

int main() {
    Graph* g = new Graph();

    g->readNetworkCSV();
    g->readVehicles();

    while (true) {
        cout << "\t\t------------------------------------\n";
        cout << "\t\t      SMART TRAFFIC MANAGEMENT SYSTEM\n";
        cout << "\t\t------------------------------------\n";
        cout << "\n1. NETWORK & INFRASTRUCTURE";
        cout << "\n2. TRAFFIC OPERATIONS";
        cout << "\n3. EMERGENCY & ANALYTICS";
        cout << "\n4. SYSTEM LOGS & SETTINGS";
        cout << "\n0. EXIT PROGRAM";
        cout << "\n------------------------------------------";
        cout << "\nSelect Category: ";

        int mainChoice;
        if (!(cin >> mainChoice)) break;

        if (mainChoice == 0) {
            g->saveNetworkToFile();
            break;
        }

        switch (mainChoice) {
        case 1: {
            cout << "\n1. Display Road Network";
            cout << "\n2. Display Blocked Roads";
            cout << "\n3. Insert or Block Road";
            cout << "\n4. Return";
            cout << "\nChoice: ";
            int c1; cin >> c1;

            if (c1 == 1) {
                g->displayNetwork();
            }
            else if (c1 == 2) {
                g->displayBlocked();
            }
            else if (c1 == 3) {
                string t, s, e; int w;
                cout << "Action (insert/block): "; cin >> t;
                cout << "Start: "; cin >> s; cout << "End: "; cin >> e;
                if (t == "insert") {
                    cout << "Weight: "; cin >> w;
                    g->insertEdge(s, e, w);
                }
                else {
                    g->blockRoad(s, e);
                }
            }
            break;
        }

        case 2: {
            cout << "\n1. Run Traffic Simulation";
            cout << "\n2. View Signal Status";
            cout << "\n3. Return";
            cout << "\nChoice: ";
            int c2; cin >> c2;

            if (c2 == 1) {
                g->readClosures();
                g->simulateTraffic();
            }
            else if (c2 == 2) {
                g->readTrafficSignals();
                g->displaySignals();
            }
            break;
        }

        case 3: {
            cout << "\n1. Route Emergency (CSV)";
            cout << "\n2. Manual Emergency Route";
            cout << "\n3. Congestion Analytics";
            cout << "\n4. Return";
            cout << "\nChoice: ";
            int c3; cin >> c3;

            if (c3 == 1) {
                g->readEmergencyVehicles();
            }
            else if (c3 == 2) {
                string s, e;
                cout << "Start: "; cin >> s;
                cout << "End: "; cin >> e;
                g->emergencyVehicleRouting(s, e);
            }
            else if (c3 == 3) {
                g->displayCongestion();
            }
            break;
        }

        case 4: {
            cout << "\n1. View Activity History";
            cout << "\n2. Force Save Data";
            cout << "\n3. Return";
            cout << "\nChoice: ";
            int c4; cin >> c4;

            if (c4 == 1) {
                g->showHistory();
            }
            else if (c4 == 2) {
                g->saveNetworkToFile();
            }
            break;
        }

        default:
            cout << "\nInvalid Selection. Please try again.\n";
        }
    }

    delete g;
    return 0;
}