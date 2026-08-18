#include <iostream>
#include <iomanip>
#include "campusgraph.h"
#include "unsortedtype.cpp"
#include "stacktype.cpp"
#include "queuetype.cpp"
using namespace std;

CampusGraph::CampusGraph() {
    numLocations = 0;

    for (int i = 0; i < MAX_LOCATIONS; i++)
        marks[i] = false;
}

CampusGraph::~CampusGraph() {
}

bool CampusGraph::ValidLocation(int id) {
    return (id >= 0 && id < numLocations);
}

void CampusGraph::AddLocation(string name) {
    if (numLocations < MAX_LOCATIONS) {
        locations[numLocations] = name;
        numLocations++;
    }
}

void CampusGraph::AddRoad(int location1, int location2) {
    if (!ValidLocation(location1) || !ValidLocation(location2)) {
        cout << "\n[ERROR] Invalid location ID.\n";
        return;
    }

    bool found;
    adjacencyList[location1].Search(location2, found);

    if (found) {
        cout << "\n[INFO] That road already exists.\n";
        return;
    }

    adjacencyList[location1].Insert(location2);
    adjacencyList[location2].Insert(location1);
}

void CampusGraph::RemoveRoad(int location1, int location2) {
    if (!ValidLocation(location1) || !ValidLocation(location2)) {
        cout << "\n[ERROR] Invalid location ID.\n";
        return;
    }

    bool found;
    adjacencyList[location1].Search(location2, found);

    if (!found) {
        cout << "\n[INFO] That road does not exist.\n";
        return;
    }

    adjacencyList[location1].Delete(location2);
    adjacencyList[location2].Delete(location1);
}

void CampusGraph::DisplayLocations() {
    cout << "\n+----+--------------------------------+" << endl;
    cout << "| ID | CAMPUS LOCATION                |" << endl;
    cout << "+----+--------------------------------+" << endl;

    for (int i = 0; i < numLocations; i++) {
        cout << "| " << right << setw(2) << i << " | "
             << left << setw(30) << locations[i] << " |" << endl;
    }

    cout << "+----+--------------------------------+" << endl;
    cout << right;
}

void CampusGraph::DisplayGraph() {
    cout << "\n==================================================" << endl;
    cout << "              CAMPUS CONNECTIONS" << endl;
    cout << "==================================================" << endl;

    for (int i = 0; i < numLocations; i++) {
        cout << "\n[" << setw(2) << i << "] " << locations[i] << endl;

        adjacencyList[i].Reset();
        int length = adjacencyList[i].Length();

        for (int j = 0; j < length; j++) {
            int neighbor;
            adjacencyList[i].GetNext(neighbor);
            cout << "     -> [" << setw(2) << neighbor << "] "
                 << locations[neighbor] << endl;
        }
    }

    cout << "\n==================================================" << endl;
}

void CampusGraph::GetToVertices(int vertex, QueueType<int> &adjVertices) {
    adjacencyList[vertex].Reset();
    int length = adjacencyList[vertex].Length();

    for (int i = 0; i < length; i++) {
        int neighbor;
        adjacencyList[vertex].GetNext(neighbor);
        adjVertices.Enqueue(neighbor);
    }
}

void CampusGraph::ClearMarks() {
    for (int i = 0; i < numLocations; i++)
        marks[i] = false;
}

void CampusGraph::MarkVertex(int vertex) {
    marks[vertex] = true;
}

bool CampusGraph::IsMarked(int vertex) {
    return marks[vertex];
}

void CampusGraph::BFS(int startVertex) {
    if (!ValidLocation(startVertex)) {
        cout << "\n[ERROR] Invalid location ID.\n";
        return;
    }

    QueueType<int> queue;
    ClearMarks();
    queue.Enqueue(startVertex);

    cout << "\n==================================================" << endl;
    cout << "               BFS TRAVERSAL" << endl;
    cout << "==================================================" << endl;
    cout << "Start : [" << startVertex << "] " << locations[startVertex] << endl;
    cout << "\nVisit order:" << endl;

    while (!queue.IsEmpty()) {
        int vertex;
        queue.Dequeue(vertex);

        if (!IsMarked(vertex)) {
            MarkVertex(vertex);
            cout << "  -> [" << setw(2) << vertex << "] " << locations[vertex] << endl;

            QueueType<int> adj;
            GetToVertices(vertex, adj);

            while (!adj.IsEmpty()) {
                int item;
                adj.Dequeue(item);

                if (!IsMarked(item))
                    queue.Enqueue(item);
            }
        }
    }

    cout << "==================================================" << endl;
}

void CampusGraph::DFS(int startVertex) {
    if (!ValidLocation(startVertex)) {
        cout << "\n[ERROR] Invalid location ID.\n";
        return;
    }

    StackType<int> stack;
    ClearMarks();
    stack.Push(startVertex);

    cout << "\n==================================================" << endl;
    cout << "               DFS TRAVERSAL" << endl;
    cout << "==================================================" << endl;
    cout << "Start : [" << startVertex << "] " << locations[startVertex] << endl;
    cout << "\nVisit order:" << endl;

    while (!stack.IsEmpty()) {
        int vertex = stack.Top();
        stack.Pop();

        if (!IsMarked(vertex)) {
            MarkVertex(vertex);
            cout << "  -> [" << setw(2) << vertex << "] " << locations[vertex] << endl;

            QueueType<int> adj;
            GetToVertices(vertex, adj);

            while (!adj.IsEmpty()) {
                int item;
                adj.Dequeue(item);

                if (!IsMarked(item))
                    stack.Push(item);
            }
        }
    }

    cout << "==================================================" << endl;
}

void CampusGraph::ShortestPath(int startVertex, int endVertex) {
    if (!ValidLocation(startVertex) || !ValidLocation(endVertex)) {
        cout << "\n[ERROR] Invalid location ID.\n";
        return;
    }

    if (startVertex == endVertex) {
        cout << "\n==================================================" << endl;
        cout << "               SHORTEST PATH" << endl;
        cout << "==================================================" << endl;
        cout << "From  : [" << startVertex << "] " << locations[startVertex] << endl;
        cout << "To    : [" << endVertex << "] " << locations[endVertex] << endl;
        cout << "\nRoute : " << locations[startVertex] << endl;
        cout << "Hops  : 0" << endl;
        cout << "==================================================" << endl;
        return;
    }

    int distance[MAX_LOCATIONS];
    int parent[MAX_LOCATIONS];

    for (int i = 0; i < numLocations; i++) {
        distance[i] = -1;
        parent[i] = -1;
    }

    QueueType<int> queue;
    queue.Enqueue(startVertex);
    distance[startVertex] = 0;

    while (!queue.IsEmpty()) {
        int vertex;
        queue.Dequeue(vertex);

        QueueType<int> adj;
        GetToVertices(vertex, adj);

        while (!adj.IsEmpty()) {
            int item;
            adj.Dequeue(item);

            if (distance[item] == -1) {
                distance[item] = distance[vertex] + 1;
                parent[item] = vertex;
                queue.Enqueue(item);
            }
        }
    }

    if (distance[endVertex] == -1) {
        cout << "\n==================================================" << endl;
        cout << "               SHORTEST PATH" << endl;
        cout << "==================================================" << endl;
        cout << "From  : [" << startVertex << "] " << locations[startVertex] << endl;
        cout << "To    : [" << endVertex << "] " << locations[endVertex] << endl;
        cout << "\n[INFO] No path found between these locations." << endl;
        cout << "==================================================" << endl;
        return;
    }

    StackType<int> path;
    int current = endVertex;

    while (current != -1) {
        path.Push(current);
        current = parent[current];
    }

    cout << "\n==================================================" << endl;
    cout << "               SHORTEST PATH" << endl;
    cout << "==================================================" << endl;
    cout << "From  : [" << startVertex << "] " << locations[startVertex] << endl;
    cout << "To    : [" << endVertex << "] " << locations[endVertex] << endl;
    cout << "\nRoute : ";

    while (!path.IsEmpty()) {
        int vertex = path.Top();
        path.Pop();

        cout << locations[vertex];
        if (!path.IsEmpty())
            cout << " -> ";
    }

    cout << endl;
    cout << "Hops  : " << distance[endVertex] << endl;
    cout << "==================================================" << endl;
}

void CampusGraph::SearchByID(int id) {
    cout << "\n---------------- LOCATION SEARCH ----------------" << endl;

    if (ValidLocation(id))
        cout << "[FOUND] [" << id << "] " << locations[id] << endl;
    else
        cout << "[NOT FOUND] No location exists with ID " << id << "." << endl;

    cout << "-------------------------------------------------" << endl;
}

void CampusGraph::SearchByName(string name) {
    cout << "\n---------------- LOCATION SEARCH ----------------" << endl;

    for (int i = 0; i < numLocations; i++) {
        if (locations[i] == name) {
            cout << "[FOUND] [" << i << "] " << locations[i] << endl;
            cout << "-------------------------------------------------" << endl;
            return;
        }
    }

    cout << "[NOT FOUND] No location named \"" << name << "\"." << endl;
    cout << "-------------------------------------------------" << endl;
}


void CampusGraph::CheckDirectConnection(int location1, int location2) {
    if (!ValidLocation(location1) || !ValidLocation(location2)) {
        cout << "\n[ERROR] Invalid location ID.\n";
        return;
    }

    bool found;
    adjacencyList[location1].Search(location2, found);

    cout << "\n==================================================" << endl;
    cout << "           DIRECT CONNECTION CHECK" << endl;
    cout << "==================================================" << endl;
    cout << "From   : [" << location1 << "] " << locations[location1] << endl;
    cout << "To     : [" << location2 << "] " << locations[location2] << endl;
    cout << "\nStatus : ";

    if (found)
        cout << "Directly connected" << endl;
    else
        cout << "No direct connection" << endl;

    cout << "==================================================" << endl;
}

void CampusGraph::DisplayNeighbors(int id) {
    if (!ValidLocation(id)) {
        cout << "\n[ERROR] Invalid location ID.\n";
        return;
    }

    cout << "\n==================================================" << endl;
    cout << "             DIRECT NEIGHBORS" << endl;
    cout << "==================================================" << endl;
    cout << "Location : [" << id << "] " << locations[id] << endl;

    adjacencyList[id].Reset();
    int length = adjacencyList[id].Length();

    if (length == 0) {
        cout << "\n[INFO] This location has no direct connections." << endl;
    } else {
        cout << "\nDirectly connected locations:" << endl;

        for (int i = 0; i < length; i++) {
            int neighbor;
            adjacencyList[id].GetNext(neighbor);
            cout << "  -> [" << setw(2) << neighbor << "] "
                 << locations[neighbor] << endl;
        }
    }

    cout << "\nTotal direct connections : " << length << endl;
    cout << "==================================================" << endl;
}

void CampusGraph::DisplayDegree(int id) {
    if (!ValidLocation(id)) {
        cout << "\n[ERROR] Invalid location ID.\n";
        return;
    }

    cout << "\n==================================================" << endl;
    cout << "              LOCATION DEGREE" << endl;
    cout << "==================================================" << endl;
    cout << "Location           : [" << id << "] " << locations[id] << endl;
    cout << "Direct connections : " << adjacencyList[id].Length() << endl;
    cout << "==================================================" << endl;
}

void CampusGraph::DisplayStatistics() {
    int totalDegree = 0;
    int maxDegree = -1;
    int maxVertex = -1;

    for (int i = 0; i < numLocations; i++) {
        int degree = adjacencyList[i].Length();
        totalDegree += degree;

        if (degree > maxDegree) {
            maxDegree = degree;
            maxVertex = i;
        }
    }

    cout << "\n==================================================" << endl;
    cout << "              CAMPUS STATISTICS" << endl;
    cout << "==================================================" << endl;
    cout << "Total locations       : " << numLocations << endl;
    cout << "Total roads           : " << totalDegree / 2 << endl;

    if (maxVertex != -1) {
        cout << "Most connected        : [" << maxVertex << "] "
             << locations[maxVertex] << endl;
        cout << "Direct connections    : " << maxDegree << endl;
    }

    cout << "==================================================" << endl;
}

void CampusGraph::Reachable(int startVertex, int endVertex) {
    if (!ValidLocation(startVertex) || !ValidLocation(endVertex)) {
        cout << "\n[ERROR] Invalid location ID.\n";
        return;
    }

    QueueType<int> queue;
    ClearMarks();
    queue.Enqueue(startVertex);
    bool found = false;

    while (!queue.IsEmpty() && !found) {
        int vertex;
        queue.Dequeue(vertex);

        if (!IsMarked(vertex)) {
            MarkVertex(vertex);

            if (vertex == endVertex) {
                found = true;
            } else {
                QueueType<int> adj;
                GetToVertices(vertex, adj);

                while (!adj.IsEmpty()) {
                    int item;
                    adj.Dequeue(item);

                    if (!IsMarked(item))
                        queue.Enqueue(item);
                }
            }
        }
    }

    cout << "\n==================================================" << endl;
    cout << "              REACHABILITY CHECK" << endl;
    cout << "==================================================" << endl;
    cout << "From   : [" << startVertex << "] " << locations[startVertex] << endl;
    cout << "To     : [" << endVertex << "] " << locations[endVertex] << endl;
    cout << "\nStatus : ";

    if (found)
        cout << "Reachable" << endl;
    else
        cout << "Not reachable" << endl;

    cout << "==================================================" << endl;
}

void CampusGraph::LocationsWithinHops(int startVertex, int maxHops) {
    if (!ValidLocation(startVertex)) {
        cout << "\n[ERROR] Invalid location ID.\n";
        return;
    }

    if (maxHops < 0) {
        cout << "\n[ERROR] Maximum hops cannot be negative.\n";
        return;
    }

    int distance[MAX_LOCATIONS];

    for (int i = 0; i < numLocations; i++)
        distance[i] = -1;

    QueueType<int> queue;
    queue.Enqueue(startVertex);
    distance[startVertex] = 0;
    int count = 0;

    cout << "\n==================================================" << endl;
    cout << "            LOCATIONS WITHIN HOPS" << endl;
    cout << "==================================================" << endl;
    cout << "Start      : [" << startVertex << "] " << locations[startVertex] << endl;
    cout << "Maximum hops: " << maxHops << endl;
    cout << "\nNearby locations:" << endl;

    while (!queue.IsEmpty()) {
        int vertex;
        queue.Dequeue(vertex);

        if (distance[vertex] >= maxHops)
            continue;

        QueueType<int> adj;
        GetToVertices(vertex, adj);

        while (!adj.IsEmpty()) {
            int item;
            adj.Dequeue(item);

            if (distance[item] == -1) {
                distance[item] = distance[vertex] + 1;

                if (distance[item] <= maxHops) {
                    cout << "  -> [" << setw(2) << item << "] "
                         << left << setw(30) << locations[item]
                         << right << "  (" << distance[item] << " hop";

                    if (distance[item] != 1)
                        cout << "s";

                    cout << ")" << endl;
                    count++;
                }

                if (distance[item] < maxHops)
                    queue.Enqueue(item);
            }
        }
    }

    if (count == 0)
        cout << "  [INFO] No other locations fall within this hop limit." << endl;

    cout << "\nTotal nearby locations : " << count << endl;
    cout << "==================================================" << endl;
}
