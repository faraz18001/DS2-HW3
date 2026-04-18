#pragma once

#include "BST.hpp"

class AVLIndex : public BSTIndex {
private:
    int getHeight(TreeNode* node);
    int getBalance(TreeNode* node);

    TreeNode* rotateRight(TreeNode* y);
    TreeNode* rotateLeft(TreeNode* x);
    TreeNode* insert(TreeNode* node, int idx, const string& key) override;

public:
    void Add(const int i, const string &Key) override;
};