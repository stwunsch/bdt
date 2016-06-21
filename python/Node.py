class Node:
    def __init__(self, layer, eventSample):
        self.layer = layer
        self.eventSample = eventSample
        self.right = None
        self.left = None
        self.cutValue = None
        self.cutFeature = None
        self.isLeaf = False
        self.class_ = None

    def setLeafClass(self):
        self.isLeaf = True
        numSig = 0
        numBkg = 0
        for sample in self.eventSample:
            if sample[2]==0:
                numSig += 1
            else:
                numBkg += 1
        if numSig>numBkg:
            self.class_ = 0
        else:
            self.class_ = 1

    def cut(self, features):
        if features[self.cutFeature]>self.cutValue:
            return self.right
        else:
            return self.left
