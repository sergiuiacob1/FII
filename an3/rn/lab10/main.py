import gzip
import pickle
import numpy as np
from keras.datasets import mnist

data = mnist.load_data()
print(len(data))
# data = pickle.load(gzip.open('mnist.pkl.gz'), encoding='latin')
# (x_train, y_train), (x_val, y_val), (x_test, y_test) = data

# targets = np.eye(10)
# x_train, y_val, y_test = [targets[y] for y in [y_train, y_val, y_test]]

import this