#include <Node.h>

Node::Node(){
    right = 0;
    left = 0;
}

Node* Node::evaluateValues(std::vector<float>* features){
    if(features->at(cutFeature)>cutValue) return right;
    else return left;
}

Node* Node::evaluateBins(std::vector<unsigned int>* bins){
    if(bins->at(cutFeature)>cutBin) return right;
    else return left;
}
