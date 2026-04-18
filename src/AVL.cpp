#include "AVL.hpp"

int getHigherVal(int v1, int v2) {
    if (v1 > v2) {
        return v1;
    }
    return v2;
}

int AVLIndex::getHeight(TreeNode* n) {
    if (n == nullptr) {
        return 0;
    }
    return n->height;
}

int AVLIndex::getBalance(TreeNode* n) {
    if (n == nullptr) {
        return 0;
    }
    return getHeight(n->left) - getHeight(n->right);
}

TreeNode* AVLIndex::rotateRight(TreeNode* top) {
    TreeNode* pivot = top->left;
    TreeNode* orphan = pivot->right;

    pivot->right = top;
    top->left = orphan;

    top->height = getHigherVal(getHeight(top->left), getHeight(top->right)) + 1;
    pivot->height = getHigherVal(getHeight(pivot->left), getHeight(pivot->right)) + 1;

    return pivot;
}

TreeNode* AVLIndex::rotateLeft(TreeNode* top) {
    TreeNode* pivot = top->right;
    TreeNode* orphan = pivot->left;

    pivot->left = top;
    top->right = orphan;

    top->height = getHigherVal(getHeight(top->left), getHeight(top->right)) + 1;
    pivot->height = getHigherVal(getHeight(pivot->left), getHeight(pivot->right)) + 1;

    return pivot;
}

TreeNode* AVLIndex::insert(TreeNode* node, int index, const string& keyVal) {
    if (node == nullptr) {
        return new TreeNode(keyVal, index);
    }

    if (keyVal == node->key) {
        node->indices.push_back(index);
        return node;
    } 
    
    if (keyVal < node->key) {
        node->left = insert(node->left, index, keyVal);
    } else {
        node->right = insert(node->right, index, keyVal);
    }

    node->height = 1 + getHigherVal(getHeight(node->left), getHeight(node->right));
    int diff = getBalance(node);

    if (diff > 1) {
        if (keyVal < node->left->key) {
            return rotateRight(node);
        } else {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
    }

    if (diff < -1) {
        if (keyVal > node->right->key) {
            return rotateLeft(node);
        } else {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
    }

    return node;
}

void AVLIndex::Add(const int i, const string &Key) {
    root = insert(root, i, Key);
}
