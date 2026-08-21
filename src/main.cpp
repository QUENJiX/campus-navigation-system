#include <iostream>
#include <string>
#include "campusgraph.h"
using namespace std;

int main() {
    // Member 1 (Hasib) - Create the campus graph
    CampusGraph campus;

    // Member 1 (Hasib) - Initialize campus locations
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

    // Member 1 (Hasib) - Initialize campus road connections
    campus.AddRoad(0, 4);
    campus.AddRoad(1, 3);
    campus.AddRoad(1, 12);
    campus.AddRoad(2, 5);
    campus.AddRoad(2, 9);
    campus.AddRoad(3, 5);
    campus.AddRoad(5, 7);
    campus.AddRoad(3, 11);
    campus.AddRoad(3, 16);
    campus.AddRoad(4, 5);
    campus.AddRoad(5, 8);
    campus.AddRoad(4, 10);
    campus.AddRoad(5, 6);
    campus.AddRoad(5, 9);
    campus.AddRoad(5, 12);
    campus.AddRoad(3, 12);
    campus.AddRoad(4, 12);
    campus.AddRoad(6, 13);
    campus.AddRoad(6, 14);
    campus.AddRoad(6, 15);
    campus.AddRoad(6, 17);
    campus.AddRoad(15, 17);
    campus.AddRoad(4, 15);

    // Member 4 (Fabiha) - Menu and user input handling
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

        // Member 4 (Fabiha) - Display and search menu operations
        if (choice == 1) {
            campus.DisplayLocations();
        } else if (choice == 2) {
            campus.DisplayGraph();
        // Member 2 (Jaima) - Dynamic road add/remove menu operations
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
        // Member 3 (Risha) - BFS menu operation
        } else if (choice == 5) {
            int start;
            campus.DisplayLocations();
            cout << "Enter starting location ID: ";
            cin >> start;
            campus.BFS(start);
        // Member 5 (Safwan) - DFS menu operation
        } else if (choice == 6) {
            int start;
            campus.DisplayLocations();
            cout << "Enter starting location ID: ";
            cin >> start;
            campus.DFS(start);
        // Member 1 (Hasib) - Shortest path menu operation
        } else if (choice == 7) {
            int start, end;
            campus.DisplayLocations();
            cout << "Enter starting location ID: ";
            cin >> start;
            cout << "Enter destination ID: ";
            cin >> end;
            campus.ShortestPath(start, end);
        // Member 4 (Fabiha) - Search menu operations
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
