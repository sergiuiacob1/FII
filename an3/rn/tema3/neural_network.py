import sys
import mnist_loader
import random
import numpy as np


class NeuralNetwork(object):
    def __init__(self, layer_dimensions):
        # the number of the layers in NeuralNetwork
        self.no_of_layers = len(layer_dimensions)
        self.layer_dimensions = layer_dimensions
        # Custom weight initialization (course 4) with mu=0 and std = 1/sqrt(number of connections for that neuron)
        self.biases = [np.random.randn(y, 1) for y in layer_dimensions[1:]]
        self.weights = [np.random.randn(y, x) / np.sqrt(x)
                        for x, y in zip(layer_dimensions[:-1], layer_dimensions[1:])]

    def feedforward(self, a):
        """This function is only used to get activations for evaluation.

        It does NOT use dropout"""
        for b, w in zip(self.biases, self.weights):
            a = sigmoid(np.dot(w, a) + b)
        return a

    def fit(self, training_data, epochs, mini_batch_size, eta,
            test_data=None, regularization_parameter=0.1):
        if test_data:
            n_test = len(test_data)
        n = len(training_data)
        for j in range(epochs):
            # rearrange the training_data randomly
            random.shuffle(training_data)
            mini_batches = [training_data[k:k + mini_batch_size]
                            for k in range(0, n, mini_batch_size)]
            for mini_batch in mini_batches:
                self.update_mini_batch(
                    mini_batch, eta, n, regularization_parameter)
            if test_data:
                print("Epoch {0}: {1} / {2}".format(j,
                                                    self.evaluate(test_data), n_test))
            else:
                print("Epoch {0} complete".format(j))

    def update_mini_batch(self, mini_batch, eta, training_data_length, regularization_parameter):
        """
        Update the network's weights and biases by applying gradient descent using backpropagation
        to a single mini batch. The "mini_batch" is a list of tuples "(x,y)" and "eta" is the learning
        rate.
        """
        nabla_b = [np.zeros(b.shape) for b in self.biases]
        nabla_w = [np.zeros(w.shape) for w in self.weights]
        for x, y in mini_batch:
            delta_nabla_b, delta_nabla_w = self.backprop(x, y)
            nabla_b = [nb+dnb for nb, dnb in zip(nabla_b, delta_nabla_b)]
            nabla_w = [nw+dnw for nw, dnw in zip(nabla_w, delta_nabla_w)]
        # Applying L2 Regularization
        self.weights = [(1 - eta * regularization_parameter / training_data_length)*w-(eta/len(mini_batch))*nw
                        for w, nw in zip(self.weights, nabla_w)]
        self.biases = [b-(eta/len(mini_batch))*nb
                       for b, nb in zip(self.biases, nabla_b)]

    def backprop(self, x, y):
        """Return a tuple ``(nabla_b, nabla_w)`` representing the
        gradient for the cost function C_x.  ``nabla_b`` and
        ``nabla_w`` are layer-by-layer lists of numpy arrays, similar
        to ``self.biases`` and ``self.weights``."""
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
        # Using softmax for the last layer
        # Course 4, slide 27
        sum_of_values = sum([np.exp(z) for z in zs[-1]])
        activations[-1] = [np.exp(z)/sum_of_values for z in zs[-1]]

        # Using the derivative of Cross Entropy here
        delta = activations[-1] - y
        nabla_b[-1] = delta
        nabla_w[-1] = np.dot(delta, activations[-2].transpose())

        for l in range(2, self.no_of_layers):
            z = zs[-l]
            sp = sigmoid_prime(z)
            delta = np.dot(self.weights[-l+1].transpose(), delta) * sp
            nabla_b[-l] = delta
            nabla_w[-l] = np.dot(delta, activations[-l-1].transpose())
        return (nabla_b, nabla_w)

    def evaluate(self, test_data):
        """Return the number of test inputs for which the neural
        network outputs the correct result. Note that the neural
        network's output is assumed to be the index of whichever
        neuron in the final layer has the highest activation."""
        test_results = [(np.argmax(self.feedforward(x)), y)
                        for (x, y) in test_data]
        return sum(int(x == y) for (x, y) in test_results)


def sigmoid(z):
    """The sigmoid function."""
    return 1.0/(1.0+np.exp(-z))


def sigmoid_prime(z):
    """Derivative of the sigmoid function."""
    return sigmoid(z)*(1-sigmoid(z))
