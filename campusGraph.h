#ifndef CAMPUSGRAPH_H
#define CAMPUSGRAPH_H
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class CampusGraph {
    private:
        vector<string> buildings;
        vector<vector<int> > adjacencyList;
        

    public:
        CampusGraph();

        void addBuilding(const string& buildingName);
        int findBuildingIndex(const string& buildingName) const;
        void addConnection(const string& fromBuilding, const string& toBuilding);
        void displayGraph(const vector<string>& buildings, const vector<vector<int>>& adjacencyList) const;
        void graphCountsAndDegrees(const vector<string>& buildings, const vector<vector<int>>& adjacencyList) const;
        void bfsSearch(const string& startBuilding, const vector<string>& buildings, const vector<vector<int>>& adjacencyList) const;
        void shortestPath(const string& startBuilding, const string& endBuilding) const;
        void connectivityReport() const;
};
#endif