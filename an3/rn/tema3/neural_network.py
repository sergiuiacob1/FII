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
            test_data=None, regularization_parameter=0.1, p_dropout=0.2, beta_momentum=0.9):
        self.accuracies = {}
        self.accuracies["test_data"] = []
        self.accuracies["training_data"] = []
        self.costs = []
        for j in range(epochs):
            # shuffle
            random.shuffle(training_data)
            mini_batches = [training_data[k:k + mini_batch_size]
                            for k in range(0, len(training_data), mini_batch_size)]
            for mini_batch in mini_batches:
                self.update_mini_batch(
                    mini_batch, eta, len(training_data), regularization_parameter, p_dropout, beta_momentum)
            if test_data:
                accuracy = self.get_nailed_cases(test_data)/len(test_data)
                self.accuracies["test_data"].append(accuracy)
                print(
                    f'Test data accuracy on epoch {j}/{epochs}: {accuracy * 100}')

                accuracy = self.get_nailed_cases(
                    training_data, True)/len(training_data)
                self.accuracies["training_data"].append(accuracy)
                print(
                    f'Training data accuracy on epoch {j}/{epochs}: {accuracy * 100}')

                self.costs.append(self.calculate_cost(training_data))
                print(
                    f'Training data cost on epoch {j}/{epochs}: {self.costs[-1]}')
            else:
                print(f"Epoch {j} complete")
            print ("\n")

    def calculate_cost(self, data):
        cost = 0
        for x, t in data:
            # t is the truth, y are my activations
            y = self.feedforward(x)
            cost += sum(np.multiply(t, np.log(y))) + \
                sum(np.multiply(np.subtract(1, t), np.log(np.subtract(1, y))))
        cost *= -1/len(data)
        return cost

    def get_predictions(self, X):
        return [np.argmax(self.feedforward(x)) for x in X]

    def update_mini_batch(self, mini_batch, eta, training_data_length, regularization_parameter, p_dropout, beta_momentum):
        """
        Update the network's weights and biases by applying gradient descent using backpropagation
        to a single mini batch. The "mini_batch" is a list of tuples "(x,y)" and "eta" is the learning
        rate.
        """
        nabla_b = [np.zeros(b.shape) for b in self.biases]
        nabla_w = [np.zeros(w.shape) for w in self.weights]
        momentum_nabla_b = [np.zeros(b.shape) for b in self.biases]
        momentum_nabla_w = [np.zeros(w.shape) for w in self.weights]
        for x, y in mini_batch:
            delta_nabla_b, delta_nabla_w = self.back_propagation(
                x, y, p_dropout)
            nabla_b = [nb+dnb for nb, dnb in zip(nabla_b, delta_nabla_b)]
            nabla_w = [nw+dnw for nw, dnw in zip(nabla_w, delta_nabla_w)]
        # Applying momentum
        momentum_nabla_b = np.multiply(
            momentum_nabla_b, beta_momentum) + np.multiply(nabla_b, 1 - beta_momentum)
        momentum_nabla_w = np.multiply(
            momentum_nabla_w, beta_momentum) + np.multiply(nabla_w, 1 - beta_momentum)

        # Applying L2 Regularization
        # update weights and biases
        self.weights = [(1 - eta * regularization_parameter / training_data_length)*w-(eta/len(mini_batch))*nw
                        for w, nw in zip(self.weights, momentum_nabla_w)]
        self.biases = [b-(eta/len(mini_batch))*nb
                       for b, nb in zip(self.biases, momentum_nabla_b)]

        # self.apply_maxnorm()

    def apply_maxnorm(self):
        c = 5
        epsilon = 10 ** (-8)
        # for each hidden layer
        for l in range(1, self.no_of_layers - 1):
            # for each neuron in this layer, update the weights that determine his value
            for i in range(0, self.layer_dimensions[l]):
                w_neuron = self.weights[l-1][i]
                value = np.sqrt(sum([w**2 for w in w_neuron]))
                if value > c:
                    w_neuron = np.multiply(w_neuron, c/(value + epsilon))
                    self.weights[l-1][i] = w_neuron

    def back_propagation(self, x, y, p_dropout):
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
            # Using dropout on activations
            dropout = np.array(np.random.binomial(
                size=len(activation), n=1, p=p_dropout)).reshape((len(activation), 1))
            activation = np.multiply(activation, dropout)
            activation = np.multiply(activation, 1.0/(1.0-p_dropout))

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

    def get_nailed_cases(self, test_data, y_is_vectorized=False):
        """Returns how many cases it nailed from the test_data"""
        test_results = [(np.argmax(self.feedforward(x)), y if y_is_vectorized==False else np.argmax(y))
                        for (x, y) in test_data]
        return sum(int(x == y) for (x, y) in test_results)


def sigmoid(z):
    """The sigmoid function."""
    return 1.0/(1.0+np.exp(-z))


def sigmoid_prime(z):
    """Derivative of the sigmoid function."""
    return sigmoid(z)*(1-sigmoid(z))
