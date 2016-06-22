from Builder import Builder

class Booster:
    def __init__(self, eventSample, numTrees, treeDepth, numCuts):
        self.numTrees = numTrees
        self.eventSample = eventSample
        self.treeDepth = treeDepth
        self.numCuts = numCuts
        self.trees = []

    def train(self):
        builder = Builder();
        for iTree in range(self.numTrees):
            print("Tree:", iTree)
            # Train tree
            tree = builder.build(self.eventSample, self.treeDepth, self.numCuts)
            self.trees.append(tree)
            # Boost the weights of the event
            numTrue = 0
            numFalse = 0
            wrongEvents = []
            for iSample in range(len(self.eventSample)):
                for iTestTree in range(len(self.trees)):
                    out = self.trees[iTestTree].evaluate(self.eventSample[iSample][0])
                    if out==self.eventSample[iSample][2]:
                        numTrue += 1
                    else:
                        numFalse += 1
            print(numTrue/(numTrue+numFalse))

    def evaluate(self):
        pass
