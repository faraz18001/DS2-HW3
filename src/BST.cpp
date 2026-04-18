#include "BST.hpp"

void BSTIndex::CreateIndex(vector<FileSystemEntry> &Data, const string &IndexType) {
    for (int i = 0; i < (int)Data.size(); ++i) {
        if (IndexType == "Filename") {
            Add(i, Data[i].Filename);
        } else if (IndexType == "modifiedOn") {
            Add(i, Data[i].modifiedOn);
        }
    }
}

void BSTIndex::Add(const int i, const string &Key) {
    root = insert(root, i, Key);
}

TreeNode* BSTIndex::insert(TreeNode* node, int idx, const string& key) {
    if (!node) return new TreeNode(key, idx);
    if (key == node->key) {
        node->indices.push_back(idx);
    } else if (key < node->key) {
        node->left = insert(node->left, idx, key);
    } else {
        node->right = insert(node->right, idx, key);
    }
    return node;
}

pair<vector<int>, int> BSTIndex::Search(const string &Key) {
    int visited = 0;
    TreeNode* node = search(root, Key, visited);
    if (node) return {node->indices, visited};
    return {{}, visited};
}

TreeNode* BSTIndex::search(TreeNode* node, const string& key, int& visited) const {
    if (!node) return nullptr;
    visited++;
    if (key == node->key) return node;
    if (key < node->key) return search(node->left, key, visited);
    return search(node->right, key, visited);
}

void BSTIndex::clear(TreeNode* node) {
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

pair<vector<int>, int> BSTIndex::RangeSearch(const string& k1, const string& k2) {
    vector<int> results;
    int visited = 0;
    rangeSearch(root, k1, k2, results, visited);
    return {results, visited};
}

void BSTIndex::rangeSearch(TreeNode* node, const string& k1, const string& k2, vector<int>& results, int& visited) const {
    if (!node) return;
    visited++;

    if (node->key > k1) rangeSearch(node->left, k1, k2, results, visited);
    if (node->key >= k1 && node->key <= k2) {
        results.insert(results.end(), node->indices.begin(), node->indices.end());
    }
    if (node->key < k2) rangeSearch(node->right, k1, k2, results, visited);
}