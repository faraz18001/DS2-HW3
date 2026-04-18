#include "AVL.hpp"

int getMax(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}


int AVLIndex::getHeight(TreeNode* node) {
    if (node != nullptr) {
        return node->height;
    } else {
        return 0;
    }
}

int AVLIndex::getBalance(TreeNode* node) {
    if (node != nullptr) {
        return getHeight(node->left) - getHeight(node->right);
    } else {
        return 0;
    }
}

TreeNode* AVLIndex::rotateRight(TreeNode* y) {
    TreeNode* x = y->left;
    TreeNode* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = getMax(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = getMax(getHeight(x->left), getHeight(x->right)) + 1;
    return x;
}

TreeNode* AVLIndex::rotateLeft(TreeNode* x) {
    TreeNode* y = x->right;
    TreeNode* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = getMax(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = getMax(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}

TreeNode* AVLIndex::insert(TreeNode* node, int idx, const string& key) {
    if (!node) return new TreeNode(key, idx);

    if (key == node->key) {
        node->indices.push_back(idx);
        return node;
    } else if (key < node->key) {
        node->left = insert(node->left, idx, key);
    } else {
        node->right = insert(node->right, idx, key);
    }

    node->height = 1 + getMax(getHeight(node->left), getHeight(node->right));
    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key) return rotateRight(node);
    if (balance < -1 && key > node->right->key) return rotateLeft(node);
    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

void AVLIndex::Add(const int i, const string &Key) {
    root = insert(root, i, Key);
}
