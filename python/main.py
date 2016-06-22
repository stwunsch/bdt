from Booster import Booster
import numpy.random as rand

""" Generate data and setup event sample"""

numEventsSig = 10000
numEventsBkg = 10000
eventSample = []
for i in range(numEventsSig):
    features = [rand.normal(0, 1)]
    eventSample.append([features, 1, 1])
for i in range(numEventsBkg):
    features = [rand.normal(2.5, 1)]
    eventSample.append([features, 1, -1])

""" Build boosted forest """

booster = Booster(eventSample, numTrees=10, treeDepth=2, numCuts=10)
booster.train()

