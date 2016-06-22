import numpy as np
import csv

from Booster import Booster

""" Import data """

variables = np.zeros((150,4))
targets = np.zeros(variables.shape[0])
with open('iris.data', 'r') as f:
    reader = csv.reader(f)
    your_list = list(reader)
    for i in range(len(your_list)):
        for j in range(variables.shape[1]):
            variables[i][j] = float(your_list[i][j])
        targets[i] = float(your_list[i][-1])

""" Train classifier """

booster = Booster()
booster.boost(variables, targets, possibleTargets=[0, 1, 2], numCuts=5, numBoosts=100)

""" Test classifier """

numTrue = 0
numFalse = 0
for iSample in range(variables.shape[0]):
    cla = booster.classify(variables[iSample])
    if np.argmax(cla)==targets[iSample]:
        numTrue += 1
    else:
        numFalse +=1
print("Efficiency:", numTrue/(numTrue+numFalse))
