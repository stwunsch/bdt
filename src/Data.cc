#include <Data.h>

void Data::addSample(std::vector<float> features, float weight, unsigned int type){
    values.push_back(features);
    weights.push_back(weight);
    types.push_back(type);
}

float Data::getFeature(unsigned int iSample, unsigned int iFeature){
    return values[iSample][iFeature];
}
