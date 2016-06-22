import numpy as np

def lossFunction(purity):
    return purity*(1.0-purity)

class Stump:
    def __init__(self):
        self.cutVariable = None
        self.cutValue = None
        self.cutTargetRight = None
        self.cutTargetLeft = None

    def train(self, variables, targets, possibleTargets, numCuts, weights):
        # Get value range for each feature
        mins = np.amin(variables, axis=0)
        maxs = np.amax(variables, axis=0)
        cuts = []
        for iVar in range(variables.shape[1]):
            cuts.append(np.linspace(mins[iVar], maxs[iVar], numCuts+2)[1:-1])
        # Go through cuts and calculate loss for each cut
        minLoss = float("inf");
        for iVar in range(variables.shape[1]):
            for iCut in range(numCuts):
                # Calculate which targets go right or left
                targetsRight = np.zeros(len(possibleTargets))
                targetsLeft = np.zeros(len(possibleTargets))
                for iSample in range(variables.shape[0]):
                    if variables[iSample][iVar]>cuts[iVar][iCut]:
                        targetsRight[possibleTargets.index(targets[iSample])] += weights[iSample]
                    else:
                        targetsLeft[possibleTargets.index(targets[iSample])] += weights[iSample]
                # Get the purities for the counted targets on each side
                purityRight = np.zeros(len(possibleTargets))
                purityLeft = np.zeros(len(possibleTargets))
                for iTarget in range(len(possibleTargets)):
                    purityRight[iTarget] = targetsRight[iTarget]/sum(targetsRight)
                    purityLeft[iTarget] = targetsLeft[iTarget]/sum(targetsLeft)
                    # Get the loss for each cut
                    loss = sum(targetsRight)*lossFunction(purityRight[iTarget]) + sum(targetsLeft)*lossFunction(purityLeft[iTarget])
                    if loss<minLoss:
                        minLoss = loss
                        self.cutValue = cuts[iVar][iCut]
                        self.cutVariable = iVar
                        self.cutTargetRight = possibleTargets[np.argmax(targetsRight)]
                        self.cutTargetLeft = possibleTargets[np.argmax(targetsLeft)]
                        self.targetsRight = targetsRight
                        self.targetsLeft = targetsLeft

    def classify(self, variables):
        if variables[self.cutVariable]>self.cutValue:
            return self.cutTargetRight
        else:
            return self.cutTargetLeft
