#include "campusGraph.h"
#include <iostream>
#include <queue>
#include <stack>
CampusGraph::CampusGraph(){

}
void CampusGraph::addBuilding(const string& buildingName){
    for(const string& building : buildings){
        if (building == buildingName) {
            cout << "Warning: Duplicate building name found: " << buildingName << endl;
            return;
        }
    }
    buildings.push_back(buildingName);
    adjacencyList.push_back(vector<int>());
}
int CampusGraph::findBuildingIndex(const string& buildingName) const{
    for(int i = 0; i < buildings.size(); i++){
        if (buildings[i] == buildingName) {
            return i;
        }
    }
    return -1;
}
void CampusGraph::addConnection(const string& fromBuilding, const string& toBuilding){

   int toIndex = findBuildingIndex(toBuilding);
   int fromIndex = findBuildingIndex(fromBuilding);

   if (toIndex == -1 || fromIndex == -1) {
        cout << "Warning: One or both buildings not found for connection: " << fromBuilding << " - " << toBuilding << endl;
        return;
    }

    if (toIndex == fromIndex) {
        cout << "Warning: Connection between the same building: " << fromBuilding << endl;
        return;
    }

    for(int neighbor : adjacencyList[fromIndex]) {
        if (neighbor == toIndex) {
            cout << "Warning: Duplicate connection found: " << fromBuilding << " - " << toBuilding << endl;
            return;
        }
    }

    adjacencyList[fromIndex].push_back(toIndex);
    adjacencyList[toIndex].push_back(fromIndex);
}
void CampusGraph::displayGraph(const vector<string>& buildings, const vector<vector<int>>& adjacencyList) const{
    cout << "Campus Graph:" << endl;
    for(int i = 0; i < buildings.size(); ++i) {
        cout << "Building: " << buildings[i] << " is connected to: ";
        for(int neighbor : adjacencyList[i]) {
            cout << buildings[neighbor] << " ";
        }
        cout << endl;
    }
}
void CampusGraph::graphCountsAndDegrees(const vector<string>& buildings, const vector<vector<int>>& adjacencyList) const{
    cout << "Total number of buildings: " << buildings.size() << endl;
    for(int i = 0; i < buildings.size(); ++i) {
        cout << "Building: " << buildings[i] << " has degree: " << adjacencyList[i].size() << endl;
    }
}
void CampusGraph::bfsSearch(const string& startBuilding, const vector<string>& buildings, const vector<vector<int>>& adjacencyList) const{
    int startIndex = -1;
    for (int i = 0; i < buildings.size(); ++i) {
        if (buildings[i] == startBuilding) {
            startIndex = i;
            break;
        }
    }
    if (startIndex == -1) {
        cout << "Warning: Start building not found for BFS search: " << startBuilding << endl;
        return;
    }
    cout << "From: " << startBuilding << endl;
    queue<int> bfsQueue;
    vector<bool> visited(buildings.size(), false);
    vector<int> distances(buildings.size(), -1);

    bfsQueue.push(startIndex);
    visited[startIndex] = true;
    distances[startIndex] = 0;
    
    while (!bfsQueue.empty()) {
        int currentIndex = bfsQueue.front();
        bfsQueue.pop();
        cout << buildings[currentIndex] << " (Distance: " << distances[currentIndex] << ")" << endl;

        for (int neighbor : adjacencyList[currentIndex]) {
            if (!visited[neighbor]) {
                bfsQueue.push(neighbor);
                visited[neighbor] = true;
                distances[neighbor] = distances[currentIndex] + 1;
                
            }
        }
    }
    for(int i = 0; i < buildings.size(); ++i) {
        if(!visited[i]) {
            cout << buildings[i] << " not connected." << endl;
        }
    }
}
