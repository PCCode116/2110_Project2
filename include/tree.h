// tree.h

#ifndef TREE_H
#define TREE_H
#include <string>
#include <vector>
using namespace std;

struct DepartmentNode {
    string name;
    DepartmentNode* parent;                 // NULL for the root
    vector<DepartmentNode*> children;       
    int depth;                              
};

class DepartmentTree {
    private:
        DepartmentNode* root;
        vector<DepartmentNode*> nodes;      // owns every node (

        vector<const DepartmentNode*> preorder() const;
        vector<const DepartmentNode*> postorder() const;
        vector<const DepartmentNode*> levelOrder() const;
        static void printSequence(const char* title, const vector<const DepartmentNode*>& seq);

        DepartmentTree(const DepartmentTree&);              // not copyable
        DepartmentTree& operator=(const DepartmentTree&);

    public:
        DepartmentTree();
        ~DepartmentTree();

        bool isEmpty() const;
        size_t getSize() const;
        bool addRoot(const string& name, string& error);
        bool addChild(const string& name, const string& parentName, string& error);
        DepartmentNode* find(const string& name) const;

        void displaySearch(const string& name) const;     // TREE 4
        void displayHierarchy() const;                    // TREE 5
        void displayPreorder() const;                     // TREE 6
        void displayPostorder() const;                    // TREE 7
        void displayLevelOrder() const;                   // TREE 7
        void displayStatistics() const;                   // TREE 8
};

#endif
