#include <Builder.h>
#include <limits>
#include <iostream>
#include <cmath>

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

    // Calculate the separation gain for each bin and feature by finding the minimal loss.
    // This gives the best cut on the features for the given binning.
    float minLoss = std::numeric_limits<float>::max();
    unsigned int bestBin, bestFeature;
    float purityLeft, purityRight, loss;
    for(unsigned int iFeature=0; iFeature<data->getNumFeatures(); iFeature++){
        for(unsigned int iBin=0; iBin<data->getNumBins(); iBin++){
            purityLeft = hSig[iFeature][iBin]/(hSig[iFeature][iBin]+hBkg[iFeature][iBin]);
            purityRight = (hSig[iFeature].back()-hSig[iFeature][iBin])/(hSig[iFeature].back()-hSig[iFeature][iBin]+hBkg[iFeature].back()-hBkg[iFeature][iBin]);
            loss = purityLeft*(1.0-purityLeft) + purityRight*(1-purityRight);
            if(std::isnan(loss)) loss = std::numeric_limits<float>::max();
            if(loss<minLoss){
                minLoss = loss;
                bestBin = iBin;
                bestFeature = iFeature;
            }
        }
    }

    if(bestBin==0 || bestBin==data->getNumBins()-1) std::cout << "[ERROR] Cutting failed." << std::endl;

    // Create two new nodes if the depth of the tree is not reached
    // and attach data samples (indexes) to the nodes. Then split
    // recursively on them.
}
