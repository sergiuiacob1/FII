import _pickle
import gzip
import numpy as np
import joblib
import matplotlib.pyplot as plt
import matplotlib.cm as cm
import random


noOfIterations = 50
noOfMiniBatches = 5
learningRate = 0.01


def getTrainAndTestData():
    with gzip.open('mnist.pkl.gz', 'rb') as f:
        # use encoding for python2
        trainSet, validSet, testSet = _pickle.load(f, encoding='iso-8859-1')

    # concatenez trainSet cu validSet
    trainSet = (np.array(list(trainSet[0]) + list(validSet[0])),
                np.array(list(trainSet[1]) + list(validSet[1])))
    return trainSet, testSet


def activationFunction(z):
    return 0 if z < 0 else 1

def trainPerceptrons(trainData):
    """
    Trains all of the perceptrons simutaneously
    """
    X, y = trainData
    perceptronWeights, perceptronBiases = [None] * 10, [None] * 10
    weights = np.random.rand(10, len(X[0]))
    bias = np.random.rand(10)
    miniBatchSize = len(X)//noOfMiniBatches

    for i in range(0, noOfIterations):
        # learningRate = 1/(i + 1)
        print(f'    --- Iteration {i + 1} ---')
        # shuffle the dataset
        print('    Shuffling the data set...')
        p = np.random.permutation(len(X))
        X = X[p]
        y = y[p]
        # mini batch training
        print('    Performing mini batch training...')
        for j in range(0, noOfMiniBatches):
            print(f'    Batch {j+1}/{noOfMiniBatches}')
            batchX = X[j * miniBatchSize:(j + 1) * miniBatchSize]
            batchY = y[j * miniBatchSize:(j + 1) * miniBatchSize]
            weightsDelta = [0] * 10
            for i in range (0, 10):
                weightsDelta[i] = [0] * len(weights[0])
            biasDelta = [0] * 10

            for x, yVal in zip(batchX, batchY):
                t = [1 if index == yVal else 0 for index in range (0, 10)]
                z = np.dot(weights, x) + bias
                predictions = list(map(lambda x: activationFunction(x), z))

                for i in range (0, 10):
                    weightsDelta[i] += (t[i] - predictions[i]) * x * learningRate
                    biasDelta[i] += (t[i] - predictions[i]) * learningRate
                # weightsDelta[:] += (t - predictions) * x * learningRate
                # biasDelta[:] += (t - predictions) * learningRate

            # update weights and biases
            print('    Updating weights and bias...')
            weights += weightsDelta
            bias += biasDelta
    return weights, bias


def getPredictions(X, perceptronWeights, perceptronBiases):
    predictions = []
    for x in X:
        # Let's see what each perceptron has to say about x
        perceptronPredictions = [sum(x * weights) + bias
                                 for weights, bias in zip(perceptronWeights, perceptronBiases)]
        predictions.append(perceptronPredictions.index(
            max(perceptronPredictions)))
    return predictions


def saveResults(weights, biases):
    print('Saving weights and biases...')
    with open('weights.pkl', 'wb') as f:
        joblib.dump(weights, f)
    with open('biases.pkl', 'wb') as f:
        joblib.dump(biases, f)


def getSavedResults():
    print('Loading weights and biases...')
    weights, biases = None, None
    with open('weights.pkl', 'rb') as f:
        weights = joblib.load(f)
    with open('biases.pkl', 'rb') as f:
        biases = joblib.load(f)

    return weights, biases


def main():
    trainData, testData = getTrainAndTestData()
    perceptronWeights, perceptronBiases = [None] * 10, [None] * 10
    # perceptronWeights, perceptronBiases = getSavedResults()

    # for i in range(0, 10):
    #     perceptronWeights[i], perceptronBiases[i] = trainPerceptron(
    #         trainData, i)
    perceptronWeights, perceptronBiases = trainPerceptrons(trainData)
    saveResults(perceptronWeights, perceptronBiases)

    print('Predicting on the test set...')
    predictions = getPredictions(
        testData[0], perceptronWeights, perceptronBiases)
    accuracy = sum([prediction == truth for prediction,
                    truth in zip(predictions, testData[1])])/len(testData[0])
    print(f'I have an accuracy of {accuracy * 100}%')

    for i in range(0, 5):
        randomIndex = np.random.randint(0, len(testData[0]) - 1)
        sample = testData[0][randomIndex]
        prediction = predictions[randomIndex]
        plt.imshow(np.array(sample).reshape(28, 28))
        print(f'I think this is {prediction} but it is actually an {testData[1][randomIndex]}')
        plt.show()
    input('Press Enter to continue...')


if __name__ == '__main__':
    main()
