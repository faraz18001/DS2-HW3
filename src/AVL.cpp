#include "AVL.hpp"

int getHigherVal(int v1, int v2) {
    if (v1 > v2) {
        return v1;
    }
    return v2;
}

int AVLIndex::getHeight(TreeNode* n) {
    return n != nullptr ? n->height : 0;
}

int AVLIndex::getBalance(TreeNode* n) {
    if (!n) return 0;
    int leftH = getHeight(n->left);
    int rightH = getHeight(n->right);
    return leftH - rightH;
}

TreeNode* AVLIndex::rotateRight(TreeNode* top) {
    TreeNode* pivot = top->left;
    top->left = pivot->right;
    pivot->right = top;

    int lh = getHeight(top->left);
    int rh = getHeight(top->right);
    top->height = (lh > rh ? lh : rh) + 1;

    int plh = getHeight(pivot->left);
    int prh = getHeight(pivot->right);
    pivot->height = (plh > prh ? plh : prh) + 1;

    return pivot;
}

TreeNode* AVLIndex::rotateLeft(TreeNode* top) {
    TreeNode* pivot = top->right;
    top->right = pivot->left;
    pivot->left = top;

    int lh = getHeight(top->left);
    int rh = getHeight(top->right);
    top->height = (lh > rh ? lh : rh) + 1;

    int plh = getHeight(pivot->left);
    int prh = getHeight(pivot->right);
    pivot->height = (plh > prh ? plh : prh) + 1;

    return pivot;
}


TreeNode* AVLIndex::insert(TreeNode* node, int index, const string& keyVal) {
    if (!node) {
        TreeNode* fresh = new TreeNode(keyVal, index);
        return fresh;
    }

    bool isLess = keyVal < node->key;
    bool isGreater = keyVal > node->key;

    if (isLess) {
        node->left = insert(node->left, index, keyVal);
    } else if (isGreater) {
        node->right = insert(node->right, index, keyVal);
    } else {
        node->indices.push_back(index);
        return node;
    }

    int hl = getHeight(node->left);
    int hr = getHeight(node->right);
    node->height = 1 + (hl > hr ? hl : hr);
    
    int balanceFactor = getBalance(node);

    bool leftHeavy = balanceFactor > 1;
    bool rightHeavy = balanceFactor < -1;

    if (leftHeavy) {
        if (keyVal >= node->left->key) {
            node->left = rotateLeft(node->left);
        }
        return rotateRight(node);
    }

    if (rightHeavy) {
        if (keyVal <= node->right->key) {
            node->right = rotateRight(node->right);
        }
        return rotateLeft(node);
    }

    return node;
}

void AVLIndex::Add(const int i, const string &Key) {
    root = insert(root, i, Key);
}
