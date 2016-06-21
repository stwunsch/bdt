#pragma once

#include <vector>

class Node{
public:
    // Constructors & destructors
    Node(unsigned int layer);

    // Getter
    unsigned int getCutFeature(){return cutFeature;}
    float getCutBin(){return cutBin;}
    float getCutValue(){return cutValue;}
    bool isLeaf(){return leaf;}
    unsigned int getType(){return type;}
    unsigned int getLayer(){return layer;}

    // Setter
    void setCutFeature(unsigned int x){cutFeature = x;}
    void setCutBin(unsigned int x){cutBin = x;}
    void setCutValue(float x){cutValue = x;}
    void setLeaf(bool x){leaf = x;}
    void setType(unsigned int x){type = x;}
    void setLayer(unsigned int x){layer = x;}

    // Attach data to the node
    void addSampleIndex(unsigned int index){sampleIndexes.push_back(index);}
    std::vector<unsigned int>* getSampleIndexes(){return &sampleIndexes;}

    // Evaluate features
    Node* evaluateValues(std::vector<float>* features);
    Node* evaluateBins(std::vector<unsigned int>* bins);

private:
    unsigned int cutFeature; // feature which is used for the cut
    unsigned int cutBin; // bin which is mapped to value on which is cut
    float cutValue; // value on which is cut (mapped on bins during training)
    Node* right; // next node on the right
    Node* left; // next node on the left
    bool leaf; // tag the node as leaf
    unsigned int type; // type of the node if it is a leaf
    unsigned int layer; // layer of the node, 0 equals root node
    std::vector<unsigned int> sampleIndexes;
};
