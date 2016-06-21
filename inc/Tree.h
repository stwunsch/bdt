#pragma once

#include <Node.h>

class Tree{
public:
    // Constructors & destructors
    Tree(unsigned int depth);

    // Getter
    unsigned int getDepth(){return depth;}
    Node* getRoot(){return root;}

    // Setter
    void setDepth(unsigned int x){depth = x;}
    void setRoot(Node* x){root = x;}

private:
    unsigned int depth; // number of layers of the tree
    Node* root; // root node of the tree
};
