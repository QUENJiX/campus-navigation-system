#include <iostream>
#include "campusgraph.h"
#include "unsortedtype.cpp"
#include "stacktype.cpp"
#include "queuetype.cpp"
using namespace std;

// Member 1 (Hasib) - Graph initialization and overall structure
CampusGraph::CampusGraph() {
    numLocations = 0;

    for (int i = 0; i < MAX_LOCATIONS; i++)
        marks[i] = false;
}

// Member 1 (Hasib) - Graph cleanup / overall structure
CampusGraph::~CampusGraph() {
}

// Member 2 (Jaima) - Location validation for road operations
bool CampusGraph::ValidLocation(int id) {
    return (id >= 0 && id < numLocations);
}

// Member 1 (Hasib) - Add locations / graph setup
void CampusGraph::AddLocation(string name) {
    if (numLocations < MAX_LOCATIONS) {
        locations[numLocations] = name;
        numLocations++;
    }
}

// Member 2 (Jaima) - Add roads using the adjacency list
void CampusGraph::AddRoad(int location1, int location2) {
    if (!ValidLocation(location1) || !ValidLocation(location2)) {
        cout << "Invalid location ID." << endl;
        return;
    }

    bool found;
    adjacencyList[location1].Search(location2, found);

    if (found) {
        cout << "Road already exists." << endl;
        return;
    }

    if(location1 == location2){
        cout << "Can't form road between the same vertex" << endl;
        return;
    }

    adjacencyList[location1].Insert(location2);
    adjacencyList[location2].Insert(location1);
}

// Member 2 (Jaima) - Remove roads using the adjacency list
void CampusGraph::RemoveRoad(int location1, int location2) {
    if (!ValidLocation(location1) || !ValidLocation(location2)) {
        cout << "Invalid location ID." << endl;
        return;
    }

    bool found;
    adjacencyList[location1].Search(location2, found);

    if (!found) {
        cout << "Road does not exist." << endl;
        return;
    }

    adjacencyList[location1].Delete(location2);
    adjacencyList[location2].Delete(location1);
}

// Member 4 (Fabiha) - Display locations
void CampusGraph::DisplayLocations() {
    cout << "\n===== CAMPUS LOCATIONS =====" << endl;

    for (int i = 0; i < numLocations; i++)
        cout << i << ". " << locations[i] << endl;
}

// Member 4 (Fabiha) - Display graph connections
void CampusGraph::DisplayGraph() {
    cout << "\n===== CAMPUS CONNECTIONS =====" << endl;

    for (int i = 0; i < numLocations; i++) {
        cout << locations[i] << " -> ";

        adjacencyList[i].Reset();
        int length = adjacencyList[i].Length();

        for (int j = 0; j < length; j++) {
            int neighbor;
            adjacencyList[i].GetNext(neighbor);
            cout << locations[neighbor];

            if (j < length - 1)
                cout << ", ";
        }

        cout << endl;
    }
}

// Member 3 (Risha) - Get adjacent vertices for BFS / traversal
void CampusGraph::GetToVertices(int vertex, QueueType<int> &adjVertices) {
    adjacencyList[vertex].Reset();
    int length = adjacencyList[vertex].Length();

    for (int i = 0; i < length; i++) {
        int neighbor;
        adjacencyList[vertex].GetNext(neighbor);
        adjVertices.Enqueue(neighbor);
    }
}

// Member 3 (Risha) - Clear traversal marks
void CampusGraph::ClearMarks() {
    for (int i = 0; i < numLocations; i++)
        marks[i] = false;
}

// Member 3 (Risha) - Mark a vertex as visited
void CampusGraph::MarkVertex(int vertex) {
    marks[vertex] = true;
}

// Member 3 (Risha) - Check whether a vertex is visited
bool CampusGraph::IsMarked(int vertex) {
    return marks[vertex];
}

// Member 3 (Risha) - Breadth First Search using Queue
void CampusGraph::BFS(int startVertex) {
    if (!ValidLocation(startVertex)) {
        cout << "Invalid location ID." << endl;
        return;
    }

    QueueType<int> queue;
    ClearMarks();
    queue.Enqueue(startVertex);

    cout << "BFS: ";

    while (!queue.IsEmpty()) {
        int vertex;
        queue.Dequeue(vertex);

        if (!IsMarked(vertex)) {
            MarkVertex(vertex);
            cout << locations[vertex] << " ";

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

    cout << endl;
}

// Member 5 (Safwan) - Depth First Search using Stack
void CampusGraph::DFS(int startVertex) {
    if (!ValidLocation(startVertex)) {
        cout << "Invalid location ID." << endl;
        return;
    }

    StackType<int> stack;
    ClearMarks();
    stack.Push(startVertex);

    cout << "DFS: ";

    while (!stack.IsEmpty()) {
        int vertex = stack.Top();
        stack.Pop();

        if (!IsMarked(vertex)) {
            MarkVertex(vertex);
            cout << locations[vertex] << " ";

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
    cout << endl;
}

// Member 1 (Hasib) - BFS-based shortest path and route reconstruction
void CampusGraph::ShortestPath(int startVertex, int endVertex) {
    if (!ValidLocation(startVertex) || !ValidLocation(endVertex)) {
        cout << "Invalid location ID." << endl;
        return;
    }

    if (startVertex == endVertex) {
        cout << "Shortest path: " << locations[startVertex] << endl;
        cout << "Path length: 0" << endl;
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
        cout << "No path found." << endl;
        return;
    }

    StackType<int> path;
    int current = endVertex;

    while (current != -1) {
        path.Push(current);
        current = parent[current];
    }

    cout << "Shortest path: ";

    while (!path.IsEmpty()) {
        int vertex = path.Top();
        path.Pop();

        cout << locations[vertex];
        if (!path.IsEmpty())
            cout << " -> ";
    }

    cout << endl;
    cout << "Path length: " << distance[endVertex] << endl;
}

// Member 4 (Fabiha) - Search location by ID
void CampusGraph::SearchByID(int id) {
    if (ValidLocation(id))
        cout << "Location found: " << locations[id] << endl;
    else
        cout << "Location not found." << endl;
}

// Member 4 (Fabiha) - Search location by name
void CampusGraph::SearchByName(string name) {
    for (int i = 0; i < numLocations; i++) {
        if (locations[i] == name) {
            cout << "Location found. ID: " << i << endl;
            return;
        }
    }

    cout << "Location not found." << endl;
}
