#include <iostream>
#include <string>
#include "campusgraph.h"
using namespace std;

int main() {
    CampusGraph campus;

    campus.AddLocation("Gate 1");
    campus.AddLocation("Gate 8");
    campus.AddLocation("Administrative Building");
    campus.AddLocation("NAC");
    campus.AddLocation("SAC");
    campus.AddLocation("Ground Floor");
    campus.AddLocation("Upper Plaza");
    campus.AddLocation("Female Lounge");
    campus.AddLocation("Male Lounge");
    campus.AddLocation("Book Shop & Stationery");
    campus.AddLocation("Medical Center");
    campus.AddLocation("City Bank ATM");
    campus.AddLocation("Cafeteria");
    campus.AddLocation("Student Affairs");
    campus.AddLocation("Auditorium");
    campus.AddLocation("Central Library");
    campus.AddLocation("Playground");
    campus.AddLocation("Gallery");

    campus.AddRoad(0, 4);
    campus.AddRoad(1, 3);
    campus.AddRoad(1, 12);
    campus.AddRoad(2, 5);
    campus.AddRoad(2, 9);
    campus.AddRoad(3, 5);
    campus.AddRoad(3, 7);
    campus.AddRoad(3, 11);
    campus.AddRoad(3, 16);
    campus.AddRoad(4, 5);
    campus.AddRoad(4, 8);
    campus.AddRoad(4, 10);
    campus.AddRoad(5, 6);
    campus.AddRoad(5, 9);
    campus.AddRoad(5, 12);
    campus.AddRoad(6, 13);
    campus.AddRoad(6, 14);
    campus.AddRoad(6, 15);
    campus.AddRoad(6, 17);

    int choice;

    do {
        cout << "\n===== CAMPUS NAVIGATION SYSTEM =====" << endl;
        cout << "1. Display locations" << endl;
        cout << "2. Display connections" << endl;
        cout << "3. Add road" << endl;
        cout << "4. Remove road" << endl;
        cout << "5. BFS traversal" << endl;
        cout << "6. DFS traversal" << endl;
        cout << "7. Shortest path" << endl;
        cout << "8. Search location by ID" << endl;
        cout << "9. Search location by name" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            campus.DisplayLocations();
        } else if (choice == 2) {
            campus.DisplayGraph();
        } else if (choice == 3) {
            int a, b;
            campus.DisplayLocations();
            cout << "Enter first location ID: ";
            cin >> a;
            cout << "Enter second location ID: ";
            cin >> b;
            campus.AddRoad(a, b);
        } else if (choice == 4) {
            int a, b;
            campus.DisplayLocations();
            cout << "Enter first location ID: ";
            cin >> a;
            cout << "Enter second location ID: ";
            cin >> b;
            campus.RemoveRoad(a, b);
        } else if (choice == 5) {
            int start;
            campus.DisplayLocations();
            cout << "Enter starting location ID: ";
            cin >> start;
            campus.BFS(start);
        } else if (choice == 6) {
            int start;
            campus.DisplayLocations();
            cout << "Enter starting location ID: ";
            cin >> start;
            campus.DFS(start);
        } else if (choice == 7) {
            int start, end;
            campus.DisplayLocations();
            cout << "Enter starting location ID: ";
            cin >> start;
            cout << "Enter destination ID: ";
            cin >> end;
            campus.ShortestPath(start, end);
        } else if (choice == 8) {
            int id;
            cout << "Enter location ID: ";
            cin >> id;
            campus.SearchByID(id);
        } else if (choice == 9) {
            string name;
            cin.ignore(1000, '\n');
            cout << "Enter location name: ";
            getline(cin, name);
            campus.SearchByName(name);
        } else if (choice != 0) {
            cout << "Invalid choice." << endl;
        }

    } while (choice != 0);

    return 0;
}
