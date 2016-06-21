from Booster import Booster
import numpy.random as rand

""" Generate data and setup event sample"""

numEventsSig = 10000
numEventsBkg = 10000
eventSample = []
for i in range(numEventsSig):
    features = [rand.normal(0, 1)]
    eventSample.append([features, 1, 0])
for i in range(numEventsBkg):
    features = [rand.normal(3, 1)]
    eventSample.append([features, 1, 1])

""" Build boosted forest """

#builder = Builder()
#tree = builder.build(eventSample, 2, 20)
booster = Booster(eventSample, 100)

