class Tree:
    def __init__(self, depth):
        self.depth = depth
        self.root = None

    def evaluate(self, features):
        self.propagate(self.root, features)
        return self.result

    def propagate(self, node, features):
        if node.isLeaf==True:
            self.result = node.class_
        else:
            self.propagate(node.cut(features), features);
