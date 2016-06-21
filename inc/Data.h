#pragma once

#include <vector>
#include <string>

class Data{
public:
    // Getter
    unsigned int getNumSamples(){return values.size();}
    unsigned int getNumFeatures(){return values[0].size();}
    std::vector<float>* getFeatureValues(unsigned int index){return &values[index];}
    std::vector<unsigned int>* getFeatureBins(unsigned int index){return &bins[index];}
    float getFeatureValue(unsigned int iSample, unsigned int iFeature);
    unsigned int getFeatureBin(unsigned int iSample, unsigned int iFeature);
    float getWeight(unsigned int index){return weights[index];}
    unsigned int getType(unsigned int index){return types[index];}
    unsigned int getNumBins(){return mapping[0].size();}

    // Add samples to the dataset
    void addSample(std::vector<float> features, float weight, unsigned int type);

    // Map bins to values
    void mapValuesToBins(unsigned int numBins);
    float getValueFromBin(unsigned int iFeature, unsigned int iBin){return mapping[iFeature][iBin];}

private:
    std::vector<std::vector<float> > values;
    std::vector<std::vector<unsigned int> > bins;
    std::vector<std::vector<float> > mapping;
    std::vector<float> weights;
    std::vector<unsigned int> types;
};
