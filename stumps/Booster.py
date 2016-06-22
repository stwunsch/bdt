from Stump import Stump
import numpy as np

class Booster:
    def __init__(self):
        self.stumps = []
        self.stumpWeights = []
        self.possibleTargets = None

    def boost(self, variables, targets, possibleTargets, numCuts, numBoosts):
        weights = np.zeros(variables.shape[0])
        self.possibleTargets = possibleTargets
        for iBoost in range(numBoosts):
            # Setup weights for first boost
            if iBoost==0:
                for iWeight in range(weights.shape[0]):
                    weights[iWeight] = 1.0/variables.shape[0]
            # Otherwise, set the new weights
            else:
                for iSample in range(variables.shape[0]):
                    cla = self.stumps[iBoost-1].classify(variables[iSample])
                    if cla==targets[iSample]:
                        weights[iSample] *= np.exp(-self.stumpWeights[iBoost-1])
                    else:
                        weights[iSample] *= np.exp(self.stumpWeights[iBoost-1])
            # Train new stump
            stump = Stump()
            stump.train(variables, targets, possibleTargets, numCuts, weights)
            self.stumps.append(stump)
            print("Left:", stump.targetsLeft)
            print("Right:", stump.targetsRight)
            # Set classifier weights
            if iBoost==0:
                self.stumpWeights.append(1)
            else:
                err = 0
                for iSample in range(variables.shape[0]):
                    cla = self.stumps[iBoost].classify(variables[iSample])
                    if cla!=targets[iSample]:
                        err += weights[iSample]
                self.stumpWeights.append(0.5*np.log((1-err)/err))

    def classify(self, variables):
        votes = np.zeros(len(self.possibleTargets))
        for iStump in range(len(self.stumps)):
            cla = self.stumps[iStump].classify(variables)
            votes[self.possibleTargets.index(cla)] += 1
        return votes/len(self.stumps)
