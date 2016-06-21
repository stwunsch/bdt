#include <Builder.h>
#include <random>
#include <iostream>

int main(void){
    // Create dataset of 2D Gaussian distributions
    unsigned int numSamplesSig = 1000;
    unsigned int numSamplesBkg = 1000;
    Data* data = new Data();
    std::vector<float> features(2);
    std::default_random_engine de(time(0));
    std::normal_distribution<float> ndSig(0, 1);
    std::normal_distribution<float> ndBkg(2, 1);
    for(unsigned int iSample=0; iSample<numSamplesSig; iSample++){
        features[0] = ndSig(de);
        features[1] = ndSig(de);
        data->addSample(features, 1, 0);
    }
    for(unsigned int iSample=0; iSample<numSamplesSig; iSample++){
        features[0] = ndBkg(de);
        features[1] = ndBkg(de);
        data->addSample(features, 1, 1);
    }
    unsigned int numBins = 20;
    data->mapValuesToBins(numBins);

    // Build a tree from this data
    unsigned int depth = 2;
    Tree* tree = new Tree(depth);
    Builder builder(data);
    builder.build(tree);

    return 0;
}
