#include <Builder.h>
#include <limits>
#include <iostream>
#include <cmath>

Builder::Builder(Data* data_){
    data = data_;
    typeSignal = 0;
    typeBackground = 1;
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
    std::cout << "Layer: " << node->getLayer() << std::endl;
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

    // Make this node a leaf node if the cutting failed.
    // As well, make this node a leaf node if the depth of the tree
    // is reached.
    // Determine to node type by choosing the greater number of signal or
    // background.
    if(node->getLayer()==tree->getDepth()){
        node->setLeaf(true);
        unsigned int sumSig = 0;
        unsigned int sumBkg = 0;
        for(unsigned int iSampleIndex=0; iSampleIndex<sampleIndexes->size(); iSampleIndex++){
            iSample = sampleIndexes->at(iSampleIndex);
            if(data->getType(iSample)==typeSignal) sumSig++;
            else sumBkg++;
        }
        if(sumSig>sumBkg) node->setType(typeSignal);
        else node->setType(typeBackground);
        return;
    }

    std::cout << "Best feature/bin: " << bestFeature << " " << bestBin << std::endl;

    // Otherwise, set the cut values and split into two new nodes in the next
    // layer and append the appropriate data to them.
    // A node on the right contains all values which are greater than the cut.
    node->setCutFeature(bestFeature);
    node->setCutBin(bestBin);
    node->setCutValue(data->getValueFromBin(bestFeature, bestBin));

    Node* right = new Node(node->getLayer()+1);
    Node* left = new Node(node->getLayer()+1);
    node->setRight(right);
    node->setLeft(left);
    for(unsigned int iSampleIndex=0; iSampleIndex<sampleIndexes->size(); iSampleIndex++){
        iSample = sampleIndexes->at(iSampleIndex);
        if(data->getFeatureBin(iSample, bestFeature)>bestBin) right->addSampleIndex(iSample);
        else left->addSampleIndex(iSample);
    }

    std::vector<unsigned int>* x = right->getSampleIndexes();
    std::vector<unsigned int>* y = left->getSampleIndexes();
    std::cout << "Right/left: " << x->size() << " " << y->size() << std::endl;

    split(tree, right);
    split(tree, left);
}
