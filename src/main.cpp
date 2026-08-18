#include <iostream>
#include <string>
#include <cstdlib>
#include "campusgraph.h"
using namespace std;

void ClearConsole() {
    system("cls");
}

void PauseConsole() {
    cout << endl;
    system("pause");
}

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

    int choice;

    do {
        ClearConsole();

        cout << "+==========================================================+" << endl;
        cout << "|               CAMPUS NAVIGATION SYSTEM                   |" << endl;
        cout << "+==========================================================+" << endl;
        cout << "|  1. Display all locations                                |" << endl;
        cout << "|  2. Display campus connections                           |" << endl;
        cout << "|  3. Add a road                                           |" << endl;
        cout << "|  4. Remove a road                                        |" << endl;
        cout << "|  5. BFS traversal                                        |" << endl;
        cout << "|  6. DFS traversal                                        |" << endl;
        cout << "|  7. Find shortest path                                   |" << endl;
        cout << "|  8. Search location by ID                                |" << endl;
        cout << "|  9. Search location by name                              |" << endl;
        cout << "| 10. Check direct connection                              |" << endl;
        cout << "| 11. Show direct neighbors                                |" << endl;
        cout << "| 12. Show location degree                                 |" << endl;
        cout << "| 13. Campus statistics                                    |" << endl;
        cout << "| 14. Check reachability                                   |" << endl;
        cout << "| 15. Find locations within N hops                         |" << endl;
        cout << "|  0. Exit                                                 |" << endl;
        cout << "+----------------------------------------------------------+" << endl;
        cout << "  Select an option: ";
        cin >> choice;

        if (choice == 0)
            break;

        ClearConsole();

        if (choice == 1) {
            campus.DisplayLocations();
        } else if (choice == 2) {
            campus.DisplayGraph();
        } else if (choice == 3) {
            int a, b;
            campus.DisplayLocations();
            cout << "\n  First location ID  : ";
            cin >> a;
            cout << "  Second location ID : ";
            cin >> b;
            campus.AddRoad(a, b);
        } else if (choice == 4) {
            int a, b;
            campus.DisplayLocations();
            cout << "\n  First location ID  : ";
            cin >> a;
            cout << "  Second location ID : ";
            cin >> b;
            campus.RemoveRoad(a, b);
        } else if (choice == 5) {
            int start;
            campus.DisplayLocations();
            cout << "\n  Starting location ID: ";
            cin >> start;
            campus.BFS(start);
        } else if (choice == 6) {
            int start;
            campus.DisplayLocations();
            cout << "\n  Starting location ID: ";
            cin >> start;
            campus.DFS(start);
        } else if (choice == 7) {
            int start, end;
            campus.DisplayLocations();
            cout << "\n  Starting location ID : ";
            cin >> start;
            cout << "  Destination ID       : ";
            cin >> end;
            campus.ShortestPath(start, end);
        } else if (choice == 8) {
            int id;
            cout << "\n  Enter location ID: ";
            cin >> id;
            campus.SearchByID(id);
        } else if (choice == 9) {
            string name;
            cin.ignore(1000, '\n');
            cout << "\n  Enter location name: ";
            getline(cin, name);
            campus.SearchByName(name);
        } else if (choice == 10) {
            int a, b;
            campus.DisplayLocations();
            cout << "\n  First location ID  : ";
            cin >> a;
            cout << "  Second location ID : ";
            cin >> b;
            campus.CheckDirectConnection(a, b);
        } else if (choice == 11) {
            int id;
            campus.DisplayLocations();
            cout << "\n  Location ID: ";
            cin >> id;
            campus.DisplayNeighbors(id);
        } else if (choice == 12) {
            int id;
            campus.DisplayLocations();
            cout << "\n  Location ID: ";
            cin >> id;
            campus.DisplayDegree(id);
        } else if (choice == 13) {
            campus.DisplayStatistics();
        } else if (choice == 14) {
            int start, end;
            campus.DisplayLocations();
            cout << "\n  Starting location ID : ";
            cin >> start;
            cout << "  Destination ID       : ";
            cin >> end;
            campus.Reachable(start, end);
        } else if (choice == 15) {
            int start, hops;
            campus.DisplayLocations();
            cout << "\n  Starting location ID : ";
            cin >> start;
            cout << "  Maximum hops         : ";
            cin >> hops;
            campus.LocationsWithinHops(start, hops);
        } else {
            cout << "\n[ERROR] Invalid menu option. Please choose 0-15.\n";
        }

        PauseConsole();

    } while (choice != 0);

    ClearConsole();
    cout << "==========================================================" << endl;
    cout << "  Campus Navigation System closed." << endl;
    cout << "==========================================================" << endl;

    return 0;
}
