#include "BST.hpp"

void BSTIndex::CreateIndex(vector<FileSystemEntry> &Data, const string &IndexType) {
    int total = (int)Data.size();
    for (int idx = 0; idx < total; idx++) {
        if (IndexType == "Filename") {
            Add(idx, Data[idx].Filename);
        } else if (IndexType == "modifiedOn") {
            Add(idx, Data[idx].modifiedOn);
        }
    }
}

void BSTIndex::Add(const int i, const string &Key) {
    root = insert(root, i, Key);
}

TreeNode* BSTIndex::insert(TreeNode* curr, int fileIdx, const string& val) {
    if (curr == nullptr) {
        return new TreeNode(val, fileIdx);
    }

    if (val < curr->key) {
        curr->left = insert(curr->left, fileIdx, val);
    } else if (val > curr->key) {
        curr->right = insert(curr->right, fileIdx, val);
    } else {
        curr->indices.push_back(fileIdx);
    }
    return curr;
}

pair<vector<int>, int> BSTIndex::Search(const string &Key) {
    int totalVisited = 0;
    TreeNode* found = search(root, Key, totalVisited);
    if (found != nullptr) {
        return {found->indices, totalVisited};
    }
    vector<int> empty;
    return {empty, totalVisited};
}

TreeNode* BSTIndex::search(TreeNode* n, const string& k, int& count) const {
    if (n == nullptr) return nullptr;
    
    count = count + 1;
    if (k == n->key) {
        return n;
    }
    
    if (k < n->key) {
        return search(n->left, k, count);
    } else {
        return search(n->right, k, count);
    }
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
    if (anchor == nullptr) return;
    
    counter++;
    
    // go left if there's possibly smaller values in range
    if (!(anchor->key <= minVal)) {
        rangeSearch(anchor->left, minVal, maxVal, list, counter);
    }
    
    // check current
    if (anchor->key >= minVal && anchor->key <= maxVal) {
        int count = (int)anchor->indices.size();
        for (int k = 0; k < count; k++) {
            list.push_back(anchor->indices[k]);
        }
    }
    
    // go right if there's possibly larger values in range
    if (!(anchor->key >= maxVal)) {
        rangeSearch(anchor->right, minVal, maxVal, list, counter);
    }
}