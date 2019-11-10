import _pickle
import gzip
import numpy as np
import joblib
import matplotlib.pyplot as plt
import matplotlib.cm as cm
import random
from neural_network import NeuralNetwork
from mnist_loader import load_data_wrapper


def save_results(model):
    print('Serializing model...')
    with open('model.pkl', 'wb') as f:
        joblib.dump(model, f)


def get_saved_results():
    print('Deserializing model...')
    with open('model.pkl', 'rb') as f:
        model = joblib.load(f)
    return model


def main():
    print('Getting train, validation and test data...')
    train_data, _, test_data = load_data_wrapper()
    model = NeuralNetwork((784, 100, 10))
    model.fit(training_data=train_data, test_data=test_data,
              epochs=10, mini_batch_size=10, eta=0.5, regularization_parameter=5.0, p_dropout=0.5)
    # predictions = model.predict([item[0] for item in testData])
    # accuracy = sum([int(prediction == truth) for prediction, truth in zip(predictions, [item[1] for item in testData])]) / len(testData) * 100
    # print(f'Model has an accuracy of {accuracy}')

    save_results(model)


if __name__ == '__main__':
    main()
