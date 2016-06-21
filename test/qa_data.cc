#include <Data.h>
#include <iostream>

int main(void){
    // Try to fill data structure with values
    Data* data = new Data();
    unsigned int numSamples = 10;
    unsigned int numFeatures = 5;
    float counter = 0;
    for(unsigned int i=0; i<numSamples; i++){
        std::vector<float> features(numFeatures);
        float weight;
        float type;
        for(unsigned int j=0; j<numFeatures; j++){
            features[j] = counter;
            counter++;
        }
        weight = features[0]/counter;
        type = (int)features[0]%2;
        data->addSample(features, weight, type);
    }

    // Test the values in the data structure
    if(data->getNumSamples()!=numSamples) return 1;
    if(data->getNumFeatures()!=numFeatures) return 1;
    counter = 0;
    for(unsigned int i=0; i<numSamples; i++){
        for(unsigned int j=0; j<numFeatures; j++){
            if(data->getFeature(i, j)!=counter) return 1;
            counter++;
        }
        if(data->getWeight(i)!=data->getFeature(i,0)/counter) return 1;
        if(data->getType(i)!=(int)data->getFeature(i,0)%2) return 1;
    }

    return 0;
}

