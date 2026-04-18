#pragma once

#include "BST.hpp"

class AVLIndex : public BSTIndex {
private:
    int getHeight(TreeNode* n);
    int getBalance(TreeNode* n);

    TreeNode* rotateRight(TreeNode* parent);
    TreeNode* rotateLeft(TreeNode* parent);
    TreeNode* insert(TreeNode* current, int dataIdx, const string& searchKey) override;

public:
    void Add(const int i, const string &Key) override;
};