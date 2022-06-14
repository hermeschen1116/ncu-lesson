import time

from keras import Sequential
from keras.layers import Conv2D, MaxPooling2D, Dropout, Flatten, Dense
from matplotlib import pyplot as plt


class CNN:
    def __init__(self, label_set, data_set):  # init
        self.__model = Sequential()  # init model
        self.__label_set = label_set  # init label set
        self.__data_set = data_set  # init data set
        self.__num_convolutions = 0  # init number of convolutions
        self.__num_pooling = 0  # init number of pooling
        self.__num_dropout = 0  # init number of dropout
        self.__num_flatten = 0  # init number of flatten
        self.__num_dense = 0  # init number of dense
        self.__train_logs = None  # init train logs
        self.__test_logs = []  # init test logs

    def add_convolution_layer(self, filters, kernel_size, activation, input_shape):  # add convolution layer
        if self.__num_convolutions == 0:  # if first convolution layer
            self.__model.add(
                Conv2D(filters, kernel_size, activation=activation, input_shape=input_shape))  # add convolution layer
        else:  # if not first convolution layer
            self.__model.add(Conv2D(filters, kernel_size, activation=activation))  # add convolution layer
        self.__num_convolutions += 1  # increment number of convolutions layers

    def add_pooling_layer(self, pool_size):  # add pooling layer
        self.__model.add(MaxPooling2D(pool_size=pool_size))  # add pooling layer
        self.__num_pooling += 1  # increment number of pooling layers

    def add_dropout_layer(self, dropout_rate):  # add dropout layer
        self.__model.add(Dropout(dropout_rate))  # add dropout layer
        self.__num_dropout += 1  # increment number of dropout layers

    def add_flatten_layer(self):  # add flatten layer
        self.__model.add(Flatten())  # add flatten layer
        self.__num_flatten += 1  # increment number of flatten layers

    def add_dense_layer(self, units, activation):  # add dense layer
        self.__model.add(Dense(units, activation=activation))  # add dense layer
        self.__num_dense += 1  # increment number of dense layers

    def compile_model(self, loss, optimizer, metrics):  # compile model
        self.__model.compile(optimizer=optimizer, loss=loss, metrics=metrics)  # compile model

    def train_model(self, batch_size, epochs, verbose, validation_split):  # train model
        timer_start = time.process_time()  # start timer
        self.__train_logs = self.__model.fit(self.__data_set, self.__label_set,
                                             epochs=epochs, batch_size=batch_size, verbose=verbose,
                                             validation_split=validation_split)  # model training settings
        timer_end = time.process_time()  # end timer
        print('Training finished. Execution time: {:.2f} s'.format(timer_end - timer_start))  # print execution time

    def show_train_logs(self):  # show train logs
        plt.plot(self.__train_logs.history['loss'])  # plot loss
        plt.plot(self.__train_logs.history['val_loss'])  # plot validation loss
        plt.title('Training logs')  # plot title
        plt.ylabel('Loss')  # plot y label
        plt.xlabel('Epoch')  # plot x label
        plt.legend(['loss', 'val_loss'], loc='upper left')  # plot legend
        plt.show()  # show plot

    def test_model(self, label_set, data_set, verbose):  # test model
        timer_start = time.process_time()  # start timer
        self.__test_logs = self.__model.evaluate(data_set, label_set, verbose=verbose)  # test model
        timer_end = time.process_time()  # end timer
        print('Testing finished. Execution time: {:.2f} s'.format(timer_end - timer_start))  # print execution time

    def show_test_logs(self):
        print("Total loss: ", self.__test_logs[0])  # print total loss
        print("Total accuracy: ", self.__test_logs[1])  # print total accuracy
