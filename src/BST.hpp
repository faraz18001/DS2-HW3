#pragma once

#include <string>
#include <vector>
#include "FileSystem.hpp"

using namespace std;

struct TreeNode {
    string key;
    vector<int> indices;
    TreeNode *left;
    TreeNode *right;
    int height; // Useful for AVL

    TreeNode(string k, int idx) : key(k), left(nullptr), right(nullptr), height(1) {
        indices.push_back(idx);
    }
};

class BSTIndex {
protected:
    TreeNode *root;

    virtual TreeNode* insert(TreeNode* current, int dataIdx, const string& searchKey);
    TreeNode* search(TreeNode* n, const string& k, int& count) const;
    void clear(TreeNode* n);
    void rangeSearch(TreeNode* n, const string& low, const string& high, vector<int>& out, int& count) const;

public:
    BSTIndex() : root(nullptr) {}
    virtual ~BSTIndex() { clear(root); }

    void CreateIndex(vector<FileSystemEntry> &Data, const string &IndexType);
    virtual void Add(const int i, const string &Key);
    pair<vector<int>, int> Search(const string &Key);
    
    pair<vector<int>, int> RangeSearch(const string& k1, const string& k2);
};