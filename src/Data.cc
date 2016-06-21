#include <Data.h>
#include <limits>
#include <cmath>

void Data::addSample(std::vector<float> features, float weight, unsigned int type){
    values.push_back(features);
    weights.push_back(weight);
    types.push_back(type);
}

float Data::getFeatureValue(unsigned int iSample, unsigned int iFeature){
    return values[iSample][iFeature];
}

unsigned int Data::getFeatureBin(unsigned int iSample, unsigned int iFeature){
    return bins[iSample][iFeature];
}

void Data::mapValuesToBins(unsigned int numBins){
    // Get min and max of the features
    std::vector<float> min(getNumFeatures());
    std::vector<float> max(getNumFeatures());
    for(unsigned int i=0; i<getNumFeatures(); i++){
        min[i] = -std::numeric_limits<float>::max();
        max[i] = std::numeric_limits<float>::max();
    }
    for(unsigned int iSample=0; iSample<getNumSamples(); iSample++){
        for(unsigned int iFeature=0; iFeature<getNumFeatures(); iFeature++){
            if(max[iFeature]<values[iSample][iFeature]) max[iFeature] = values[iSample][iFeature];
            if(min[iFeature]>values[iSample][iFeature]) min[iFeature] = values[iSample][iFeature];
        }
    }

    // Calculate the middle of the bins
    mapping.resize(getNumFeatures());
    for(unsigned int iFeature=0; iFeature<getNumFeatures(); iFeature++){
        mapping[iFeature].resize(numBins);
        for(unsigned int iBin=0; iBin<numBins; iBin++){
            mapping[iFeature][iBin] = min[iFeature]+(iBin+0.5)*(max[iFeature]-min[iFeature]);
        }
    }

    // Map the values to the bins
    float diff, tmp;
    unsigned int bin;
    for(unsigned int iSample=0; iSample<getNumSamples(); iSample++){
        bin = std::numeric_limits<unsigned int>::max();
        diff = std::numeric_limits<float>::max();
        for(unsigned int iFeature=0; iFeature<getNumFeatures(); iFeature++){
            for(unsigned int iBin=0; iBin<numBins; iBin++){
                tmp = std::fabs(values[iSample][iFeature]-mapping[iFeature][iBin]);
                if(tmp<diff){
                    diff = tmp;
                    bin = iBin;
                }
            }
            if(bin!=std::numeric_limits<unsigned int>::max()) bins[iSample][iFeature] = bin;
            else throw "Mapping of bins to values failed.";
        }
    }
}
