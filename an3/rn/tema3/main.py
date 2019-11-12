import _pickle
import gzip
import numpy as np
import joblib
import matplotlib.pyplot as plt
import matplotlib.cm as cm
import random
from neural_network import NeuralNetwork
from mnist_loader import load_data_wrapper
import matplotlib.pyplot as plt


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
    # good params:
    # model.fit(training_data=train_data, test_data=test_data,
    #           epochs=50, mini_batch_size=10, eta=0.5, regularization_parameter=5.0, p_dropout=0.5, beta_momentum=0.1)

    # also good:
    # model.fit(training_data=train_data, test_data=test_data, epochs=50, mini_batch_size=10,
    #           eta=0.75, regularization_parameter=2.5, p_dropout=0.5, beta_momentum=0.1, use_maxnorm=False)
    
    model.fit(training_data=train_data, test_data=test_data, epochs=50, mini_batch_size=10,
              eta=0.75, regularization_parameter=2.5, p_dropout=0.5, beta_momentum=0.1, use_maxnorm=False)

    save_results(model)
    # model = get_saved_results()

    fig = plt.figure(1)
    fig.canvas.set_window_title('Accuracy')
    plt.plot(model.accuracies["training_data"])
    plt.plot(model.accuracies["test_data"])
    plt.legend(['Training data accuracy', 'Test data accuracy'])
    fig = plt.figure(2)
    fig.canvas.set_window_title('Cost on training data')
    plt.plot(model.costs)
    plt.show()


if __name__ == '__main__':
    main()
