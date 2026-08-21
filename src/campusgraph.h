#ifndef CAMPUSGRAPH_H
#define CAMPUSGRAPH_H

#include <string>
#include "unsortedtype.h"
#include "stacktype.h"
#include "queuetype.h"
using namespace std;

const int MAX_LOCATIONS = 25;

class CampusGraph {
private:
    string locations[MAX_LOCATIONS];
    UnsortedType<int> adjacencyList[MAX_LOCATIONS];
    bool marks[MAX_LOCATIONS];
    int numLocations;

    // Member 2 (Jaima) - Location validation for road operations
    bool ValidLocation(int id);
    // Member 3 (Risha) - BFS helper and traversal support
    void GetToVertices(int vertex, QueueType<int> &adjVertices);
    // Member 3 (Risha) - Traversal marks helper
    void ClearMarks();
    // Member 3 (Risha) - Traversal marks helper
    void MarkVertex(int vertex);
    // Member 3 (Risha) - Traversal marks helper
    bool IsMarked(int vertex);

public:
    // Member 1 (Hasib) - Graph initialization and overall structure
    CampusGraph();
    // Member 1 (Hasib) - Graph cleanup / overall structure
    ~CampusGraph();

    // Member 1 (Hasib) - Add locations / graph setup
    void AddLocation(string name);
    // Member 2 (Jaima) - Dynamic road addition
    void AddRoad(int location1, int location2);
    // Member 2 (Jaima) - Dynamic road removal
    void RemoveRoad(int location1, int location2);

    // Member 4 (Fabiha) - Display locations
    void DisplayLocations();
    // Member 4 (Fabiha) - Display graph connections
    void DisplayGraph();

    // Member 3 (Risha) - Breadth First Search
    void BFS(int startVertex);
    // Member 5 (Safwan) - Depth First Search
    void DFS(int startVertex);
    // Member 1 (Hasib) - BFS-based shortest path
    void ShortestPath(int startVertex, int endVertex);

    // Member 4 (Fabiha) - Search location by ID
    void SearchByID(int id);
    // Member 4 (Fabiha) - Search location by name
    void SearchByName(string name);
};

#endif
