from Tree import Tree
from Node import Node
import numpy as np

def getMin(eventSample):
    mins = []
    for iFeature in range(len(eventSample[0][0])):
        mins.append(1000)
        for event in eventSample:
            if event[0][iFeature]<mins[iFeature]:
                mins[iFeature] = event[0][iFeature]
    return mins

def getMax(eventSample):
    maxs = []
    for iFeature in range(len(eventSample[0][0])):
        maxs.append(-1000)
        for event in eventSample:
            if event[0][iFeature]>maxs[iFeature]:
                maxs[iFeature] = event[0][iFeature]
    return maxs

class Builder:
    def __init__(self):
        self.eventSample = None

    def build(self, eventSample, treeDepth, numCuts):
        self.treeDepth = treeDepth
        self.numCuts = numCuts
        # Get tree
        tree = Tree(treeDepth)
        # Set root node of tree
        tree.root = Node(0, eventSample)
        # Split the node recursively
        self.split(tree.root)
        return tree

    def split(self, node):
        # Make this node a leaf if depth of tree is reached
        if node.layer==self.treeDepth:
            node.setLeafClass()
            return
        # Get the cut values of the features
        cuts = []
        mins = getMin(node.eventSample)
        maxs = getMax(node.eventSample)
        for i in range(len(mins)):
            cuts.append(np.linspace(mins[i], maxs[i], self.numCuts))
        # Find the best cut
        minLoss = 1000
        bestCut = None
        bestFeature = None
        for iFeature in range(len(cuts)):
            for iCut in range(len(cuts[0])):
                numSigLeft = 0
                numBkgLeft = 0
                numSigRight = 0
                numBkgRight = 0
                for iSample in range(len(node.eventSample)):
                    features = node.eventSample[iSample][0]
                    weight = node.eventSample[iSample][1]
                    class_ = node.eventSample[iSample][2]
                    if features[iFeature]>cuts[iFeature][iCut]:
                        if class_ == 1:
                            numSigRight += weight
                        else:
                            numBkgRight += weight
                    else:
                        if class_ == 1:
                            numSigLeft += weight
                        else:
                            numBkgLeft += weight
                purityLeft = None
                if numSigLeft+numBkgLeft>0:
                    purityLeft = numSigLeft/(numSigLeft+numBkgLeft)
                purityRight = None
                if numSigRight+numBkgRight>0:
                    purityRight = numSigRight/(numSigRight+numBkgRight)
                loss = None
                if purityLeft!=None and purityRight!=None:
                    loss = purityLeft*(1.0-purityLeft) + purityRight*(1.0-purityRight)
                    #print("%i\t%.2f\t%.2f" % (iFeature, cuts[iFeature][iCut], loss))
                if loss!=None:
                    if loss<minLoss:
                        minLoss = loss
                        bestCut = cuts[iFeature][iCut]
                        bestFeature = iFeature
        # Set cut value for this node
        node.cutValue = bestCut
        node.cutFeature = bestFeature
        #print("Feature:", bestFeature)
        #print("Cut:", bestCut)
        # Split the node
        eventSampleRight = []
        eventSampleLeft = []
        for sample in node.eventSample:
            if sample[0][bestFeature]>bestCut:
                eventSampleRight.append(sample)
            else:
                eventSampleLeft.append(sample)
        node.right = Node(node.layer+1, eventSampleRight)
        node.left = Node(node.layer+1, eventSampleLeft)
        # Split the left and right nodes again
        self.split(node.right)
        self.split(node.left)
