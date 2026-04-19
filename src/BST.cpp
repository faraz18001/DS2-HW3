#include "BST.hpp"

void BSTIndex::CreateIndex(vector<FileSystemEntry> &Data, const string &IndexType) {
    int idx = 0;
    for (auto it = Data.begin(); it != Data.end(); ++it) {
        string val = (IndexType == "Filename") ? it->Filename : it->modifiedOn;
        Add(idx, val);
        idx++;
    }
}

void BSTIndex::Add(const int i, const string &Key) {
    root = insert(root, i, Key);
}

TreeNode* BSTIndex::insert(TreeNode* curr, int fileIdx, const string& val) {
    if (!curr) return new TreeNode(val, fileIdx);

    if (curr->key == val) {
        curr->indices.push_back(fileIdx);
    } else {
        if (val < curr->key) {
            curr->left = insert(curr->left, fileIdx, val);
        } else {
            curr->right = insert(curr->right, fileIdx, val);
        }
    }
    return curr;
}

pair<vector<int>, int> BSTIndex::Search(const string &Key) {
    int visits = 0;
    TreeNode* match = search(root, Key, visits);
    vector<int> res;
    if (match) {
        res = match->indices;
    }
    return make_pair(res, visits);
}

TreeNode* BSTIndex::search(TreeNode* n, const string& k, int& count) const {
    if (!n) return nullptr;
    
    count++;
    if (n->key == k) return n;
    
    bool searchLeft = (k < n->key);
    return searchLeft ? search(n->left, k, count) : search(n->right, k, count);
}

void BSTIndex::clear(TreeNode* n) {
    if (n == nullptr) return;
    clear(n->left);
    clear(n->right);
    delete n;
}

pair<vector<int>, int> BSTIndex::RangeSearch(const string& a, const string& b) {
    vector<int> list;
    int steps = 0;
    rangeSearch(root, a, b, list, steps);
    return {list, steps};
}

void BSTIndex::rangeSearch(TreeNode* anchor, const string& minVal, const string& maxVal, vector<int>& list, int& counter) const {
    if (!anchor) return;
    
    counter++;
    bool checkLeft = (anchor->key > minVal);
    bool checkRight = (anchor->key < maxVal);
    
    if (checkLeft) {
        rangeSearch(anchor->left, minVal, maxVal, list, counter);
    }
    
    if (anchor->key >= minVal && anchor->key <= maxVal) {
        for (int item : anchor->indices) {
            list.push_back(item);
        }
    }
    
    if (checkRight) {
        rangeSearch(anchor->right, minVal, maxVal, list, counter);
    }
}