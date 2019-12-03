import _pickle
import gzip
import numpy as np
import joblib
import matplotlib.pyplot as plt
import matplotlib.cm as cm
import random
import json
from neural_network import NeuralNetwork
from mnist_loader import load_data_wrapper
import matplotlib.pyplot as plt


def save_results(model, model_name, model_parameters):
    print('Serializing model...')
    with open(model_name, 'wb') as f:
        joblib.dump(model, f)

    with open('model_parameters.json', 'r') as f:
        params = json.load(f)
    params[model_name] = model_parameters
    with open('model_parameters.json', 'w') as f:
        f.write(json.dumps(params))


def get_saved_results(model_name='model.pkl'):
    print('Deserializing model...')
    with open(model_name, 'rb') as f:
        model = joblib.load(f)
    return model


def show_plots(model, no):
    fig = plt.figure(no*10 + 1)
    fig.canvas.set_window_title(f'{no} - Accuracy')
    plt.plot(model.accuracies["training_data"])
    plt.plot(model.accuracies["test_data"])
    plt.legend(['Training data accuracy', 'Test data accuracy'])
    fig = plt.figure(no * 10 + 2)
    fig.canvas.set_window_title(f'{no} - Cost on training data')
    plt.plot(model.costs)
    plt.show()


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

    parameters = {
        "epochs": 75,
        "mini_batch_size": 32,
        "eta": 0.5,
        "regularization_parameter": 5.0,
        "p_dropout": 0.5,
        "beta_momentum": 0.9,
        "use_maxnorm": False
    }

    # 13 e bun
    # 14 merita lasat la antrenat
    # 15 merita mai mult
    # 16 si mai mult
    # 17 e ce trebuie
    # 18 a depasit 95%
    # la fel si 20

    no = 20
    # model.fit(training_data=train_data, test_data=test_data, **parameters)
    save_results(model, f"model_{no}.pkl", parameters)
    for i in range(1, no + 1):
        model = get_saved_results(f"model_{i}.pkl")
        show_plots(model, i)


if __name__ == '__main__':
    main()
