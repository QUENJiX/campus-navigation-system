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

    bool ValidLocation(int id);
    void GetToVertices(int vertex, QueueType<int> &adjVertices);
    void ClearMarks();
    void MarkVertex(int vertex);
    bool IsMarked(int vertex);

public:
    CampusGraph();
    ~CampusGraph();

    void AddLocation(string name);
    void AddRoad(int location1, int location2);
    void RemoveRoad(int location1, int location2);

    void DisplayLocations();
    void DisplayGraph();

    void BFS(int startVertex);
    void DFS(int startVertex);
    void ShortestPath(int startVertex, int endVertex);

    void SearchByID(int id);
    void SearchByName(string name);
};

#endif
