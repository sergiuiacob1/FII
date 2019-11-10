import _pickle
import gzip
import numpy as np
import joblib
import matplotlib.pyplot as plt
import matplotlib.cm as cm
import random
from neural_network import NeuralNetwork
from mnist_loader import load_data_wrapper


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
    # trainData, testData = getTrainAndTestData()
    trainData, validationData, testData = load_data_wrapper()
    trainData += validationData
    model = NeuralNetwork((784, 30, 10))
    model.fit(trainData=trainData, testData=testData,
              epochs=10, miniBatchSize=10, eta=0.5, regularizationValue=5.0)
    predictions = model.predict([item[0] for item in testData])
    accuracy = sum([int(prediction == truth) for prediction, truth in zip(predictions, [item[1] for item in testData])]) / len(testData) * 100
    print(f'Model has an accuracy of {accuracy}')

    saveResults(model)


if __name__ == '__main__':
    main()
