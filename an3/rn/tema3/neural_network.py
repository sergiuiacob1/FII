import numpy as np
import random


def sigmoid(z):
    return 1.0/(1.0+np.exp(-z))


def sigmoid_prime(z):
    """Derivative of the sigmoid function."""
    return sigmoid(z)*(1-sigmoid(z))


class NeuralNetwork:
    def __init__(self, layerDims, learningRate=3.0):
        self.noLayers = len(layerDims)
        self.layerDims = layerDims
        self.learningRate = learningRate
        # TODO initialize weights with custom mu and sigma
        self.biases = [np.random.randn(y, 1) for y in layerDims[1:]]
        self.weights = [np.random.randn(y, x)
                        for x, y in zip(layerDims[:-1], layerDims[1:])]

    def fit(self, X, y, epochs=10, miniBatchSize=10, eta=0.01, testData=None):
        bestWeights = None
        bestBiases = None
        bestCost = None
        noOfMiniBatches = len(X)//miniBatchSize

        for i in range(epochs):
            # shuffle
            print(f'Starting epoch {i}/{epochs}...')
            p = np.random.permutation(len(X))
            X, y = X[p], y[p]

            for j in range(noOfMiniBatches):
                batchX = X[j * miniBatchSize:(j + 1) * miniBatchSize]
                batchY = y[j * miniBatchSize:(j + 1) * miniBatchSize]
                self.updateMiniBatch(batchX, batchY, eta)
                # if testData is not None:
                #     nailedCases = self.evaluate(test_data)
                #     cost = n_test - nailedCases
                #     print("Epoch {0}: {1}/{2}".format(j, nailedCases, n_test))

                # if bestCost is None or (bestCost is not None and bestCost > cost):
                #     bestCost = cost
                #     bestBiases = self.biases
                #     bestWeights = self.weights

            # this epoch is done, evaluate
            print(f"Epoch {i} complete")
            cost = self.evaluate(X, y)
            if bestCost is None or (bestCost is not None and bestCost > cost):
                bestCost = cost
                bestBiases = self.biases
                bestWeights = self.weights

        self.weights = bestWeights
        self.biases = bestBiases

    def updateMiniBatch(self, X, y, eta):
        nabla_b = [np.zeros(b.shape) for b in self.biases]
        nabla_w = [np.zeros(w.shape) for w in self.weights]
        n = len(X)
        for x, t in zip(X, y):
            delta_nabla_b, delta_nabla_w = self.backPropagation(x, t)
            # TODO nu e echivalent cu nabla_b += delta_nabla_b?
            nabla_b = [nb + dnb for nb, dnb in zip(nabla_b, delta_nabla_b)]
            nabla_w = [nw + dnw for nw, dnw in zip(nabla_w, delta_nabla_w)]
        # TODO la fel aici, nu poate fi simplificat?
        self.weights = [w - (eta/n)*nw
                        for w, nw in zip(self.weights, nabla_w)]
        self.biases = [b - (eta/n)*nb
                       for b, nb in zip(self.biases, nabla_b)]

    def evaluate(self, X, y):
        return 0

    def predict(self, X):
        return ...

    def feedForward(self, a):
        """Returns the output of the network if `a` is input"""
        for b, w in zip(self.biases, self.weights):
            a = sigmoid(np.dot(w, a)+b)
        return a

    def backPropagation(self, x, y):
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
        delta = self.cost_derivative(activations[-1], y) * \
            sigmoid_prime(zs[-1])
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
            nabla_w[-l] = np.dot(delta, activations[-l - 1].transpose())
        return (nabla_b, nabla_w)

    def cost_derivative(self, output_activations, y):
        """Return the vector of partial derivatives partial C_x /
        partial a for the output activations."""
        return (output_activations-y)
