import time

from keras import Sequential
from keras.layers import Conv2D, MaxPooling2D, Dropout, Flatten, Dense
from matplotlib import pyplot as plt


class CNN:
    def __init__(self, label_set, data_set):
        self.__model = Sequential()
        self.__label_set = label_set
        self.__data_set = data_set
        self.__num_convolutions = 0
        self.__num_pooling = 0
        self.__num_dropout = 0
        self.__num_flatten = 0
        self.__num_dense = 0
        self.__train_logs = None
        self.__test_logs = []

    def add_convolution_layer(self, filters, kernel_size, activation, input_shape):
        if self.__num_convolutions == 0:
            self.__model.add(Conv2D(filters, kernel_size, activation=activation, input_shape=input_shape))
        else:
            self.__model.add(Conv2D(filters, kernel_size, activation=activation))
        self.__num_convolutions += 1

    def add_pooling_layer(self, pool_size):
        self.__model.add(MaxPooling2D(pool_size=pool_size))
        self.__num_pooling += 1

    def add_dropout_layer(self, dropout_rate):
        self.__model.add(Dropout(dropout_rate))
        self.__num_dropout += 1

    def add_flatten_layer(self):
        self.__model.add(Flatten())
        self.__num_flatten += 1

    def add_dense_layer(self, units, activation):
        self.__model.add(Dense(units, activation=activation))
        self.__num_dense += 1

    def compile_model(self, loss, optimizer, metrics):
        self.__model.compile(optimizer=optimizer, loss=loss, metrics=metrics)

    def train_model(self, batch_size, epochs, verbose, validation_split):
        timer_start = time.process_time()
        self.__train_logs = self.__model.fit(self.__data_set, self.__label_set,
                                             epochs=epochs, batch_size=batch_size, verbose=verbose,
                                             validation_split=validation_split)
        timer_end = time.process_time()
        print('Training finished. Execution time: {:.2f} s'.format(timer_end - timer_start))

    def show_train_logs(self):
        plt.plot(self.__train_logs.history['loss'])
        plt.plot(self.__train_logs.history['val_loss'])
        plt.title('Training logs')
        plt.ylabel('Loss')
        plt.xlabel('Epoch')
        plt.legend(['loss', 'val_loss'], loc='upper left')
        plt.show()

    def test_model(self, label_set, data_set, verbose):
        timer_start = time.process_time()
        self.__test_logs = self.__model.evaluate(data_set, label_set, verbose=verbose)
        timer_end = time.process_time()
        print('Testing finished. Execution time: {:.2f} s'.format(timer_end - timer_start))

    def show_test_logs(self):
        print("Total loss: ", self.__test_logs[0])
        print("Total accuracy: ", self.__test_logs[1])
