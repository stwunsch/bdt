from Builder import Builder
import numpy as np

class Booster:
    def __init__(self, eventSample, numTrees, treeDepth, numCuts, minNodeSize):
        self.minNodeSize = minNodeSize
        self.numTrees = numTrees
        self.eventSample = eventSample
        self.treeDepth = treeDepth
        self.numCuts = numCuts
        self.trees = []
        self.treeWeights = []

    def train(self):
        # Normalize the weights of the event sample
        sumWeights = 0
        for iSample in range(len(self.eventSample)):
            sumWeights += self.eventSample[iSample][1]
        for iSample in range(len(self.eventSample)):
            self.eventSample[iSample][1] /= sumWeights
        builder = Builder();
        # Build the forest
        for iTree in range(self.numTrees):
            print("Tree:", iTree)
            # Boost the event weights
            if iTree!=0:
                for iSample in range(len(self.eventSample)):
                    out = self.trees[iTree-1].evaluate(self.eventSample[iSample][0])
                    self.eventSample[iSample][1] *= np.exp(-out*self.treeWeights[iTree-1]*self.eventSample[iSample][2])
            # Train tree
            tree = builder.build(self.eventSample, self.treeDepth, self.numCuts, self.minNodeSize)
            self.trees.append(tree)
            # Set tree weight
            if iTree==0:
                self.treeWeights.append(1)
            else:
                err = 0
                for iSample in range(len(self.eventSample)):
                    out = self.trees[iTree].evaluate(self.eventSample[iSample][0])
                    if out!=self.eventSample[iSample][2]:
                        err += self.eventSample[iSample][1]
                self.treeWeights.append(0.5*np.log((1.0-err)/err))

            # Test trained trees
            numTrue = 0
            numFalse = 0
            for iSample in range(len(self.eventSample)):
                out = self.evaluate(self.eventSample[iSample][0])
                if out==self.eventSample[iSample][2]:
                    numTrue += 1
                else:
                    numFalse += 1
            print("Eff:", numTrue/(numTrue+numFalse))


    def evaluate(self, features):
        sumOut = 0
        for iTree in range(len(self.trees)):
            out = self.trees[iTree].evaluate(features)
            sumOut += out*self.treeWeights[iTree]
        if sumOut>0:
            return 1
        else:
            return -1
