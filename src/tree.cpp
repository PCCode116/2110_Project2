// tree.cpp
#include "tree.h"
#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
using namespace std;

namespace {
//removes undesirable characters 
string trim(const string& s) {
    const char* ws = " \t\r\n\f\v";
    size_t start = s.find_first_not_of(ws);
    if (start == string::npos) return "";
    size_t end = s.find_last_not_of(ws);
    return s.substr(start, end - start + 1);
}

// ASCII lowercase copy
string toLowerStr(const string& s) {
    string r = s;
    for (size_t i = 0; i < r.size(); ++i)
        if (r[i] >= 'A' && r[i] <= 'Z') r[i] = static_cast<char>(r[i] - 'A' + 'a');
    return r;
}

}

DepartmentTree::DepartmentTree() : root(NULL) {
}

// Every node is spawned by the nodes vector, so deleting that list frees the whole tree.
DepartmentTree::~DepartmentTree() {
    for (size_t i = 0; i < nodes.size(); ++i) delete nodes[i];
}

bool DepartmentTree::isEmpty() const { return root == NULL; }

size_t DepartmentTree::getSize() const { return nodes.size(); }

// The first department becomes the root.
bool DepartmentTree::addRoot(const string& rawName, string& error) {
    string name = trim(rawName);
    if (name.empty()) { error = "department name is empty"; return false; }
    if (root) { error = "tree already has a root"; return false; }
    DepartmentNode* n = new DepartmentNode;
    n->name = name;
    n->parent = NULL;
    n->depth = 0;
    root = n;
    nodes.push_back(n);
    return true;
}

// Attaches a new node under an existing parent 
bool DepartmentTree::addChild(const string& rawName, const string& parentName, string& error) {
    string name = trim(rawName);
    if (name.empty()) { error = "department name is empty"; return false; }
    if (find(name)) { error = "duplicate department name \"" + name + "\""; return false; }
    DepartmentNode* p = find(parentName);
    if (!p) { error = "unknown parent \"" + trim(parentName) + "\""; return false; }
    DepartmentNode* n = new DepartmentNode;
    n->name = name;
    n->parent = p;
    n->depth = p->depth + 1;
    p->children.push_back(n);
    nodes.push_back(n);
    return true;
}

// Linear search
DepartmentNode* DepartmentTree::find(const string& name) const {
    string key = toLowerStr(trim(name));
    for (size_t i = 0; i < nodes.size(); ++i)
        if (toLowerStr(nodes[i]->name) == key) return nodes[i];
    return NULL;
}

// Shows name, parent, direct-child count and depth.
void DepartmentTree::displaySearch(const string& name) const {
    DepartmentNode* n = find(name);
    if (!n) { cout << "Department not found: \"" << trim(name) << "\"." << endl; return; }
    cout << "Name: " << n->name << endl;
    cout << "Parent: " << (n->parent ? n->parent->name : string("None")) << endl;
    cout << "Direct children: " << n->children.size() << endl;
    cout << "Depth: " << n->depth << endl;
}

// preorder with an explicit stack 
vector<const DepartmentNode*> DepartmentTree::preorder() const {
    vector<const DepartmentNode*> out;
    if (!root) return out;
    stack<const DepartmentNode*> st;
    st.push(root);
    while (!st.empty()) {
        const DepartmentNode* cur = st.top();
        st.pop();
        out.push_back(cur);
        for (size_t i = cur->children.size(); i > 0; --i) st.push(cur->children[i - 1]);
    }
    return out;
}

// Iterative postorder
vector<const DepartmentNode*> DepartmentTree::postorder() const {
    vector<const DepartmentNode*> out;
    if (!root) return out;
    stack<const DepartmentNode*> st;
    st.push(root);
    while (!st.empty()) {
        const DepartmentNode* cur = st.top();
        st.pop();
        out.push_back(cur);
        for (size_t i = 0; i < cur->children.size(); ++i) st.push(cur->children[i]);
    }
    reverse(out.begin(), out.end());
    return out;
}

// Level-order traversal
vector<const DepartmentNode*> DepartmentTree::levelOrder() const {
    vector<const DepartmentNode*> out;
    if (!root) return out;
    queue<const DepartmentNode*> q;
    q.push(root);
    while (!q.empty()) {
        const DepartmentNode* cur = q.front();
        q.pop();
        out.push_back(cur);
        for (size_t i = 0; i < cur->children.size(); ++i) q.push(cur->children[i]);
    }
    return out;
}

// Prints a traversal as one line of names.
void DepartmentTree::printSequence(const char* title, const vector<const DepartmentNode*>& seq) {
    if (seq.empty()) { cout << "No departments are loaded." << endl; return; }
    cout << title << ": ";
    for (size_t i = 0; i < seq.size(); ++i) cout << (i ? " -> " : "") << seq[i]->name;
    cout << endl;
}

// Preorder listing
void DepartmentTree::displayHierarchy() const {
    vector<const DepartmentNode*> seq = preorder();
    if (seq.empty()) { cout << "No departments are loaded." << endl; return; }
    for (size_t i = 0; i < seq.size(); ++i)
        cout << string(static_cast<size_t>(seq[i]->depth) * 4, ' ') << seq[i]->name << endl;
}

void DepartmentTree::displayPreorder() const   { printSequence("Preorder", preorder()); }
void DepartmentTree::displayPostorder() const  { printSequence("Postorder", postorder()); }
void DepartmentTree::displayLevelOrder() const { printSequence("Level-order", levelOrder()); }

// Total, leaves and height
void DepartmentTree::displayStatistics() const {
    if (!root) {
        cout << "No departments are loaded." << endl;
        cout << "Total departments: 0" << endl;
        cout << "Leaf departments: 0" << endl;
        cout << "Tree height: N/A" << endl;
        return;
    }
    size_t leaves = 0;
    int height = 0;
    for (size_t i = 0; i < nodes.size(); ++i) {
        if (nodes[i]->children.empty()) ++leaves;
        height = max(height, nodes[i]->depth);
    }
    cout << "Total departments: " << nodes.size() << endl;
    cout << "Leaf departments: " << leaves << endl;
    cout << "Tree height: " << height << endl;
}
