#pragma once

#include <vector>

class Data{
public:
    // Getter
    unsigned int getNumSamples(){return values.size();}
    unsigned int getNumFeatures(){return values[0].size();}
    std::vector<float>* getFeatures(unsigned int index){return &values[index];}
    float getFeature(unsigned int iSample, unsigned int iFeature);
    float getWeight(unsigned int index){return weights[index];}
    unsigned int getType(unsigned int index){return types[index];}

    // Setter
    void addSample(std::vector<float> features, float weight, unsigned int type);

private:
    std::vector<std::vector<float> > values;
    std::vector<float> weights;
    std::vector<unsigned int> types;
};
