#ifndef FACILITIES_HASH_H
#define FACILITIES_HASH_H
#include <string>
using namespace std;
struct facility {
    string id;
    string name;
    string buildingName;
    string category;
    
    facility* next;

    facility(const string& i, const string& n, const string& b, const string& c) : id(i), name(n), buildingName(b), category(c), next(nullptr) {}
};
class FacilitiesHash {
    private:
        static const int INITIAL_TABLE_SIZE = 100;
        int tableSize;
        facility** table;
        int emptySlots;
        int collisionCount;

    public:
        FacilitiesHash();
        ~FacilitiesHash();
        
        int hashFunction(const string& id) const;
        void insert(const string& id, const string& name, const string& buildingName, const string& category);
        facility* search(const string& id) const;
        void displayFacilities() const;
        void displayStats() const;
};


#endif 
