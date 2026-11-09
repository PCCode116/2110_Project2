#include <iostream>
#include <fstream>
#include <string>    
#include <vector>
#include <campusGraph.h>
using namespace std;
//g++ -I include src/main.cpp src/campusGraph.cpp -o program
bool sameName(const string& name1, const string& name2) {
    if(name1.size() != name2.size()) {
        return false;
    }
    for(size_t i = 0; i < name1.size(); ++i) {
        if(tolower(name1[i]) != tolower(name2[i])) {
            return false;
        }
    }
    return true;
}
string trim(const string& str) {
    size_t start = str.find_first_not_of(" \t\n\r");
    if (start == string::npos){
        return "";
    }
    size_t end = str.find_last_not_of(" \t\n\r");
    return str.substr(start, end - start + 1);
}
void loadBuildingName(const string& filename, vector<string>& buildings) {
    ifstream buildingNamesFile(filename);

    int accepted = 0;
    int rejected = 0;
    int line = 0;

    if (!buildingNamesFile) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }
    string buildingName;

    while(getline(buildingNamesFile, buildingName)){
        ++line;
        buildingName = trim(buildingName);

        if (buildingName.empty()) {
            continue;
        }
        if (buildingName[0] == '#') {
            continue;
        }
        bool duplicate = false;
        for(const string& building : buildings){
            if (sameName(building, buildingName)) {
                duplicate = true;
                break;
            }
        }
        if (duplicate) {
            cout << "Warning: Duplicate building name found in file name: " << filename << ", building name: " << buildingName << endl;
            rejected++;
            continue;
        }

        buildings.push_back(buildingName);
        accepted++;
    }
  
    buildingNamesFile.close();
    cout << "Building names loaded: " << accepted << " accepted, " << rejected << " rejected." << endl;
}
int findBuilding(const vector<string>& buildings, const string& buildingName) {
    for(int i = 0; i < buildings.size(); i++){
        if (buildings[i] == buildingName) {
            return i;
        }
    }
    return -1;
}
void loadConnections(const string& filename, vector<string>& buildings, vector<vector<int>>& adjacencyList){
    ifstream connectionFile(filename);
    int accepted = 0;
    int rejected = 0;
    int line = 0;

    if (!connectionFile) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }
    string connection;
    while(getline(connectionFile, connection)) {
        line++;
        connection = trim(connection);
        if (connection.empty() || connection[0] == '#') {
            continue;
        }
        size_t position = connection.find('|');
        if(position == string::npos || connection.find('|', position + 1) != string::npos) {
            cout << "Warning: Invalid connection format in file name: " << filename << ", line: " << line << endl;
            rejected++;
            continue;
        }
        string buildingA = trim(connection.substr(0, position));
        string buildingB = trim(connection.substr(position + 1));

        if (buildingA.empty() || buildingB.empty()) {
            cout << "Warning: Invalid connection format in file name: " << filename << ", line: " << line << endl;
            rejected++;
            continue;
        }

        int indexA = findBuilding(buildings, buildingA);
        int indexB = findBuilding(buildings, buildingB);
        
        if (indexA == -1 || indexB == -1) {
            cout << "Warning: Building not found in file name: " << filename << ", line: " << line << endl;
            rejected++;
            continue;
        }

        if (indexA == indexB) {
            cout << "Warning: Connection between the same building in file name: " << filename << ", line: " << line << endl;
            rejected++;
            continue;
        }
        bool duplicate = false;
        for(int neighbor : adjacencyList[indexA]) {
            if (neighbor == indexB) {
                duplicate = true;
                break;
            }
        }

        if (duplicate) {
            cout << "Warning: Duplicate connection found in file name: " << filename << ", line: " << line << endl;
            rejected++;
            continue;
        }

        adjacencyList[indexA].push_back(indexB);
        adjacencyList[indexB].push_back(indexA);
        accepted++;
    
    
    }
    connectionFile.close();
    cout << "Connections loaded: " << accepted << " accepted, " << rejected << " rejected." << endl;

}
void loadFacilities(const string& filename, const vector<string>& buildings) {
    ifstream facilityFile(filename);
    int accepted = 0;
    int rejected = 0;
    int line = 0;

    if(!facilityFile.is_open()) {
        cout << "Error: Unable to open facility file: " << filename << endl;
        return;
    }
    string facility;
    while(getline(facilityFile, facility)) {
        line++;
        facility = trim(facility);
        
        if(facility.empty() || facility[0] == '#') {
            continue;
        }
        size_t first = facility.find('|');
        if(first == string::npos) {
            cout << "Warning: Invalid facility format in file name: " << filename << ", line: " << line << endl;
            rejected++;
            continue;
        }
        size_t second = facility.find('|', first + 1);
        if(second == string::npos) {
            cout << "Warning: Invalid facility format in file name: " << filename << ", line: " << line << endl;
            rejected++;
            continue;
        }
        size_t third = facility.find('|', second + 1);
        if(third == string::npos) {
            cout << "Warning: Invalid facility format in file name: " << filename << ", line: " << line << endl;
            rejected++;
            continue;
        }
        string facilityID = trim(facility.substr(0, first));
        string facilityName = trim(facility.substr(first + 1, second - first - 1));
        string buildingName = trim(facility.substr(second + 1, third - second - 1));
        string facilityCategory = trim(facility.substr(third + 1));

        if(facilityID.empty() || facilityName.empty() || buildingName.empty() || facilityCategory.empty()) {
            cout << "Warning: Invalid facility entry in file name: " << filename << ", line: " << line << endl;
            rejected++;
            continue;
        }
        for (char c : facilityID) {
            c = static_cast<char>(toupper(c));
        }
        if(facilityID.length() != 4 || facilityID[0] != 'F' || !isdigit(facilityID[1]) || !isdigit(facilityID[2]) || !isdigit(facilityID[3])) {
            cout << "Warning: Invalid facility ID length in file name: " << filename << ", line: " << line << endl;
            rejected++;
            continue;
        }

        int buildingIndex = findBuilding(buildings, buildingName);
        if(buildingIndex == -1) {
            cout << "Warning: Building not found for facility in file name: " << filename << ", line: " << line << endl;
            rejected++;
            continue;
        }
        /*
        check if the id already exists in the facilities hashtable
        if duplicate facility ID is found, print a warning and reject the entry.
        insert the valid facility into the facilities hashtable
        */
        accepted++;
    }
    facilityFile.close();
    cout << "Facilities loaded: " << accepted << " accepted, " << rejected << " rejected." << endl;
}
void loadDepartments(const string& filename) {
    ifstream departmentFile(filename);
    int accepted = 0;
    int rejected = 0;
    int line = 0;

    if(!departmentFile.is_open()) {
        cout << "Error: Unable to open department file: " << filename << endl;
        return;
    }
    string department;
    while(getline(departmentFile, department)) {
        line++;
        department = trim(department);
        
        if(department.empty()) {
            continue;
        }
        if(department[0] == '#') {
            continue;
        }
        size_t pos = department.find('|');
        if(pos == string::npos || department.find('|', pos + 1) != string::npos) {
            cout << "Warning: Invalid department format in file name: " << filename << ", line: " << line << endl;
            rejected++;
            continue;
        }

        string departmentName = trim(department.substr(0, pos));
        string parentName = trim(department.substr(pos + 1));

        if(departmentName.empty() || parentName.empty()) {
            cout << "Warning: Invalid department entry in file name: " << filename << ", line: " << line << endl;
            rejected++;
            continue;
        }


        // check if department name already exists
        // seatch the deparment tree for duplicate department names
        //handle the dfirst deparment

        if(accepted == 0) {
            if(parentName != "NONE") {
                cout << "Warning: First department must have parent as NONE in file name: " << filename << ", line: " << line << endl;
                rejected++;
                continue;
            }
            // Insert this as the root department
        }
        else {
            // search the department tree for the parent department
            // if the parent department does not exist, reject this entry
            // insert this department under the parent department1
        }

        accepted++;
    }
    departmentFile.close();
    cout << "Departments loaded: " << accepted << " accepted, " << rejected << " rejected." << endl;
}
int main(){
    vector<string> buildings;
    vector<vector<int>> adjacencyList;
    loadBuildingName("data/BuildingName.txt", buildings);
    adjacencyList.resize(buildings.size());
    loadConnections("data/connections.txt", buildings, adjacencyList);
    loadFacilities("data/Facilities.txt", buildings);
    loadDepartments("data/Departments.txt");

    CampusGraph campusGraph;
    int choice;
    string startingBuilding;

    while (choice != 10){
        cout << "==== Campus Navigation and Facilities System ====" << endl;
        cout << "1. Visit all facilities: " << endl;
        cout << "2. Search Facilities by ID" << endl;
        cout << "3. View campus Graph" << endl; // me
        cout << "4. Display graph counts and degrees" << endl; // me
        cout << "5. Find reachable buildings" << endl; //me
        cout << "6. Add departments" << endl;
        cout << "7. Search departments" << endl;
        cout << "8. Display departments hierarchy" << endl;
        cout << "9. Run preorder traversal" << endl;
        cout << "10. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch(choice) {
            case 1:
                // Navigate Campus
                break;
            case 2:
                // View Facilities
                break;
            case 3:
                campusGraph.displayGraph(buildings, adjacencyList);
                break;
            case 4:
                campusGraph.graphCountsAndDegrees(buildings, adjacencyList);
                break;
            case 5:
                
                cout << "Enter the starting building: ";
                cin >> startingBuilding;
                campusGraph.bfsSearch(startingBuilding, buildings, adjacencyList);
                break;
            case 6:
                // Add Departmentsg
                break;  
            case 7:
                // Search Departments
                break;
            case 8:
                // Display Departments Hierarchy    
                break;
            case 9:
                // Run Preorder Traversal
                break;
            case 10:
                cout << "Thank you for using the Campus Navigation and Facilities System." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }
    return 0;
}
