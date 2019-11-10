import numpy as np
import random


class CrossEntropyCost(object):

    @staticmethod
    def fn(a, y):
        """Return the cost associated with an output ``a`` and desired output
        ``y``.  Note that np.nan_to_num is used to ensure numerical
        stability.  In particular, if both ``a`` and ``y`` have a 1.0
        in the same slot, then the expression (1-y)*np.log(1-a)
        returns nan.  The np.nan_to_num ensures that that is converted
        to the correct value (0.0).

        """
        return np.sum(np.nan_to_num(-y*np.log(a)-(1-y)*np.log(1-a)))

    @staticmethod
    def delta(z, a, y):
        """Return the error delta from the output layer.  Note that the
        parameter ``z`` is not used by the method.  It is included in
        the method's parameters in order to make the interface
        consistent with the delta method for other cost classes.

        """
        return (a-y)


def sigmoid(z):
    """The sigmoid function."""
    return 1.0/(1.0+np.exp(-z))


def sigmoid_prime(z):
    """Derivative of the sigmoid function."""
    return sigmoid(z)*(1-sigmoid(z))


class NeuralNetwork:
    def __init__(self, layerDims):
        self.noLayers = len(layerDims)
        self.layerDims = layerDims
        # Custom weights initializations (course 4)
        # TODO
        self.biases = [np.random.randn(y, 1) for y in layerDims[1:]]
        self.weights = [np.random.randn(y, x)
                        for x, y in zip(layerDims[:-1], layerDims[1:])]

    def fit(self, trainData, epochs=10, miniBatchSize=10, eta=0.5, regularizationValue=5, testData=None):
        """Fits the Neural Network using Stochastic Gradient Descent"""
        bestWeights = None
        bestBiases = None
        bestCost = None
        noOfMiniBatches = len(trainData)//miniBatchSize
        if len(trainData) % miniBatchSize > 0:
            noOfMiniBatches += 1

        for i in range(epochs):
            print(f'Starting epoch {i}/{epochs}...')
            # shuffle
            random.shuffle(trainData)
            # p = np.random.permutation(n)
            # X, y = X[p], y[p]

            # update per batch
            for j in range(noOfMiniBatches):
                batch = trainData[j * miniBatchSize:(j + 1) * miniBatchSize]
                self.updateMiniBatch(
                    batch, eta, regularizationValue, len(trainData))

            # this epoch is done, evaluate
            if testData is not None:
                nailedCases = self.evaluate(testData)
                cost = len(testData) - nailedCases
                print(f'Epoch {i}: {nailedCases}/{len(testData)}')

                if bestCost is None or (bestCost is not None and bestCost > cost):
                    bestCost = cost
                    bestBiases = self.biases
                    bestWeights = self.weights

        if bestWeights is not None and bestBiases is not None:
            self.weights = bestWeights
            self.biases = bestBiases

    def updateMiniBatch(self, data, eta, regularizationValue, n):
        nabla_b = [np.zeros(b.shape) for b in self.biases]
        nabla_w = [np.zeros(w.shape) for w in self.weights]
        m = len(data)
        for x, y in data:
            delta_nabla_b, delta_nabla_w = self.backPropagation(x, y)
            nabla_b = [nb+dnb for nb, dnb in zip(nabla_b, delta_nabla_b)]
            nabla_w = [nw+dnw for nw, dnw in zip(nabla_w, delta_nabla_w)]
        self.weights = [(1-eta*(regularizationValue/n))*w-(eta/m)*nw
                        for w, nw in zip(self.weights, nabla_w)]
        self.biases = [b-(eta/m)*nb
                       for b, nb in zip(self.biases, nabla_b)]

    def evaluate(self, data):
        test_results = [(np.argmax(self.feedForward(x)), t)
                        for (x, t) in data]
        return sum([int(x == y) for (x, y) in test_results])

    def predict(self, X):
        return [np.argmax(self.feedForward(x)) for x in X]

    def feedForward(self, a):
        """Returns the output of the network if `a` is input"""
        for b, w in zip(self.biases, self.weights):
            a = sigmoid(np.dot(w, a)+b)
        return a

    def backPropagation(self, x, y):
        """Backpropagates the error and returns, for each neuron in the Neural Network, how much of the error comes from that neuron"""
        # """Return a tuple ``(nabla_b, nabla_w)`` representing the
        # gradient for the cost function C_x.  ``nabla_b`` and
        # ``nabla_w`` are layer-by-layer lists of numpy arrays, similar
        # to ``self.biases`` and ``self.weights``."""
        nabla_b = [np.zeros(b.shape) for b in self.biases]
        nabla_w = [np.zeros(w.shape) for w in self.weights]
        # feedforward
        activation = x
        activations = [x]  # list to store all the activations, layer by layer
        zs = []  # list to store all the z vectors, layer by layer
        for b, w in zip(self.biases, self.weights):
            z = np.dot(w, activation)+b
            zs.append(z)
            activation = sigmoid(z)
            activations.append(activation)
        # backward pass
        delta = (CrossEntropyCost).delta(zs[-1], activations[-1], y)
        nabla_b[-1] = delta
        nabla_w[-1] = np.dot(delta, activations[-2].transpose())
        # Note that the variable l in the loop below is used a little
        # differently to the notation in Chapter 2 of the book.  Here,
        # l = 1 means the last layer of neurons, l = 2 is the
        # second-last layer, and so on.  It's a renumbering of the
        # scheme in the book, used here to take advantage of the fact
        # that Python can use negative indices in lists.
        for l in range(2, len(self.layerDims)):
            z = zs[-l]
            sp = sigmoid_prime(z)
            delta = np.dot(self.weights[-l+1].transpose(), delta) * sp
            nabla_b[-l] = delta
            nabla_w[-l] = np.dot(delta, activations[-l-1].transpose())
        return (nabla_b, nabla_w)
