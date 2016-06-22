from Booster import Booster
import numpy.random as rand

""" Generate data and setup event sample"""

numEventsSig = 10000
numEventsBkg = 10000
numEvents = numEventsSig+numEventsBkg
eventSample = []
for i in range(numEventsSig):
    features = rand.multivariate_normal([0, 0], [[1,0.1],[0.2,1]], 1)[0]
    eventSample.append([features, 1, 1])
for i in range(numEventsBkg):
    features = rand.multivariate_normal([3, 3], [[1,0.2],[0.3,1]], 1)[0]
    eventSample.append([features, 1, -1])

""" Build boosted forest """

booster = Booster(eventSample, numTrees=10, treeDepth=1, numCuts=10, minNodeSize=50)
booster.train()

