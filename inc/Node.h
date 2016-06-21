#pragma once

#include <vector>

class Node{
public:
    // Constructors & destructors
    Node();

    // Getter
    unsigned int getCutFeature(){return cutFeature;}
    float getCutBin(){return cutBin;}
    float getCutValue(){return cutValue;}

    // Setter
    void setCutFeature(unsigned int x){cutFeature = x;}
    void setCutBin(unsigned int x){cutBin = x;}
    void setCutValue(float x){cutValue = x;}

    // Evaluate features
    Node* evaluateValues(std::vector<float>* features);
    Node* evaluateBins(std::vector<unsigned int>* bins);

private:
    unsigned int cutFeature; // feature which is used for the cut
    unsigned int cutBin; // bin which is mapped to value on which is cut
    float cutValue; // value on which is cut (mapped on bins during training)
    Node* right; // next node on the right
    Node* left; // next node on the left
};
