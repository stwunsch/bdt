#pragma once

class Node{
public:
    // Constructors & destructors
    Node();

    // Getter
    unsigned int getCutVariable(){return cutVariable;}
    float getCutValue(){return cutVariable;}
    float getCutBin(){return cutBin;}

    // Setter
    void setCutVariable(unsigned int x){cutVariable = x;}
    void setCutValue(float x){cutValue = x;}
    void setCutBin(unsigned int x){cutValue = x;}

private:
    unsigned int cutVariable; // variable which is used for the cut
    float cutValue; // cut value for the cut variable
    unsigned int cutBin; // bin which is mapped to the cutVariable during training
    Node* parent; // parent node
    Node* right; // next node on the right
    Node* left; // next node on the left
};
