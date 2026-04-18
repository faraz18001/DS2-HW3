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

    virtual TreeNode* insert(TreeNode* node, int idx, const string& key);
    TreeNode* search(TreeNode* node, const string& key, int& visited) const;
    void clear(TreeNode* node);
    void rangeSearch(TreeNode* node, const string& k1, const string& k2, vector<int>& results, int& visited) const;

public:
    BSTIndex() : root(nullptr) {}
    virtual ~BSTIndex() { clear(root); }

    void CreateIndex(vector<FileSystemEntry> &Data, const string &IndexType);
    virtual void Add(const int i, const string &Key);
    pair<vector<int>, int> Search(const string &Key);
    
    pair<vector<int>, int> RangeSearch(const string& k1, const string& k2);
};