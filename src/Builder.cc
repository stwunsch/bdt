#include <Builder.h>
#include <limits>
#include <iostream> // FIXME

Builder::Builder(Data* data_){
    data = data_;
    typeSignal = 0;
}

void Builder::build(Tree* tree){
    // Create the root node of the tree and attach all data to it
    tree->setRoot(new Node(0));
    for(unsigned int iSample=0; iSample<data->getNumSamples(); iSample++){
        tree->getRoot()->addSampleIndex(iSample);
    }

    // Start splitting from the root and proceed recursively until reaching
    // the desired depth of the tree
    split(tree, tree->getRoot());
}

void Builder::split(Tree* tree, Node* node){
    // Get histograms of features
    std::vector<std::vector<float> > hSig(data->getNumFeatures());
    std::vector<std::vector<float> > hBkg(data->getNumFeatures());
    for(unsigned int iFeature=0; iFeature<data->getNumFeatures(); iFeature++){
        hSig[iFeature].resize(data->getNumBins());
        hBkg[iFeature].resize(data->getNumBins());
    }
    std::vector<unsigned int>* sampleIndexes = node->getSampleIndexes();
    unsigned int iSample;
    for(unsigned int iSampleIndex=0; iSampleIndex<sampleIndexes->size(); iSampleIndex++){
        iSample = sampleIndexes->at(iSampleIndex);
        for(unsigned int iFeature=0; iFeature<data->getNumFeatures(); iFeature++){
            if(data->getType(iSample)==typeSignal) hSig[iFeature][data->getFeatureBin(iSample, iFeature)] += data->getWeight(iSample);
            else hBkg[iFeature][data->getFeatureBin(iSample, iFeature)] += data->getWeight(iSample);
        }
    }

    // Turn the histograms into cumulative histograms
    for(unsigned int iFeature=0; iFeature<data->getNumFeatures(); iFeature++){
        for(unsigned int iBin=1; iBin<data->getNumBins(); iBin++){
            hSig[iFeature][iBin] += hSig[iFeature][iBin-1];
            hBkg[iFeature][iBin] += hBkg[iFeature][iBin-1];
        }
    }

    // Calculate the separation gain for each bin and feature
    float maxGain = -std::numeric_limits<float>::max();
    unsigned int maxBin, maxFeature;
    float gain, purity;
    for(unsigned int iFeature=0; iFeature<data->getNumFeatures(); iFeature++){
        for(unsigned int iBin=0; iBin<data->getNumBins(); iBin++){
            purity = hSig[iFeature][iBin]/(hSig[iFeature][iBin]+hBkg[iFeature][iBin]);
            gain = separationGain(purity);
            std::cout << iFeature << " " << iBin << " " << gain << std::endl;
            if(gain>maxGain){
                maxGain = gain;
                maxBin = iBin;
                maxFeature = iFeature;
            }
        }
    }

    // Find the best separation and and therefore the best cut

    // Create two new nodes if the depth of the tree is not reached
    // and attach data samples (indexes) to the nodes. Then split
    // recursively on them.
}
