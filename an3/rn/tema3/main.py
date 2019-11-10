import _pickle
import gzip
import numpy as np
import joblib
import matplotlib.pyplot as plt
import matplotlib.cm as cm
import random
from neural_network import NeuralNetwork


def getTrainAndTestData():
    with gzip.open('mnist.pkl.gz', 'rb') as f:
        # use encoding for python2
        trainSet, validSet, testSet = _pickle.load(f, encoding='iso-8859-1')

    # concatenez trainSet cu validSet
    trainSet = (np.array(list(trainSet[0]) + list(validSet[0])),
                np.array(list(trainSet[1]) + list(validSet[1])))
    return trainSet, testSet


def saveResults(model):
    print('Serializing model...')
    with open('model.pkl', 'wb') as f:
        joblib.dump(model, f)


def getSavedResults():
    print('Deserializing model...')
    with open('model.pkl', 'rb') as f:
        model = joblib.load(f)
    return model


def main():
    print('Getting train, validation and test data...')
    trainData, testData = getTrainAndTestData()
    model = NeuralNetwork((784, 100, 10))
    model.fit(X=trainData[0], y=trainData[1],
              epochs=10, miniBatchSize=10, eta=0.01)
    accuracy = model.predict(testData)
    print(f'Model has an accuracy of {accuracy}')

    saveResults(model)


if __name__ == '__main__':
    main()
