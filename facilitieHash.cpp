#include "facilitieHash.h"
#include <iostream>
#include <string>
using namespace std;

FacilitiesHash::FacilitiesHash() {
    tableSize = INITIAL_TABLE_SIZE;
    table = new facility*[tableSize];
    for (int i = 0; i < tableSize; i++) {
        table[i] = nullptr;
    }
    emptySlots = 0;
    collisionCount = 0;
}

FacilitiesHash::~FacilitiesHash() {
    for (int i = 0; i < tableSize; i++) {
        facility* current = table[i];
        while (current != nullptr) {
            facility* next = current->next;
            delete current;
            current = next;
        }
    }
    delete[] table;
}
int FacilitiesHash :: hashFunction(const string& id) const{
    int hash = 0;
    for (int i = 0; i < id.length(); i++) {
        hash += static_cast<int>(id[i]);
    }
    return hash % tableSize;
}
void FacilitiesHash::insert(const string& id, const string& name, const string& buildingName, const string& category){
    string lowID = id;
    for (char& c : lowID) {
        c = static_cast<char>(toupper(c));
    }

    if (search(lowID) != nullptr) {
        cout << "Warning: Facility with ID " << lowID << " already exists." << endl;
        return;
    }

    int index = hashFunction(lowID);
    if(table[index] != nullptr) {
        collisionCount++;
    }

    facility* newNode = new facility(lowID, name, buildingName, category);
    newNode->next = table[index];
    table[index] = newNode;
    emptySlots++;
}

facility* FacilitiesHash::search(const string& id) const{
    string lowID = id;
    for (char& c : lowID) {
        c = static_cast<char>(toupper(c));
    }
    int index = hashFunction(lowID);
    facility* current = table[index];

    while (current != nullptr) {
        if (current->id == lowID) {
            return current;
        }
        current = current->next;
    }
    return nullptr;

}

void FacilitiesHash::displayFacilities() const {
    for (int i = 0; i < tableSize; i++) {
        facility* current = table[i];
        while (current != nullptr) {
            cout << "Facility ID: " << current->id << "| Name: " << current->name << "| Building: " << current->buildingName << "| Category: " << current->category << endl;
            current = current->next;
        }
    }
}
void FacilitiesHash::displayStats() const {
    cout << "Facilities Hash Table Statistics:" << endl;
    cout << "Table Size: " << tableSize << endl;
    cout << "Total Facilities: " << emptySlots << endl;
    cout << "Collisions: " << collisionCount << endl;
}
