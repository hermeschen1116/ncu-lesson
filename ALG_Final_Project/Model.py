import threading
import time

from keras import Sequential
from keras.layers import Conv2D, MaxPooling2D, Dropout, Flatten, Dense
from matplotlib import pyplot as plt


class CNN:
    def __init__(self, label_set, data_set):
        self.model = Sequential()
        self.label_set = label_set
        self.data_set = data_set
        self.num_convolutions = 0
        self.num_pooling = 0
        self.num_dropout = 0
        self.num_flatten = 0
        self.num_dense = 0
        self.train_logs = None
        self.test_logs = []

    def add_convolution_layer(self, filters, kernel_size, activation, input_shape):
        if self.num_convolutions == 0:
            self.model.add(Conv2D(filters, kernel_size, activation=activation, input_shape=input_shape))
        else:
            self.model.add(Conv2D(filters, kernel_size, activation=activation))
        self.num_convolutions += 1

    def add_pooling_layer(self, pool_size):
        self.model.add(MaxPooling2D(pool_size=pool_size))
        self.num_pooling += 1

    def add_dropout_layer(self, dropout_rate):
        self.model.add(Dropout(dropout_rate))
        self.num_dropout += 1

    def add_flatten_layer(self):
        self.model.add(Flatten())
        self.num_flatten += 1

    def add_dense_layer(self, units, activation):
        self.model.add(Dense(units, activation=activation))
        self.num_dense += 1

    def compile_model(self, loss, optimizer, metrics):
        self.model.compile(optimizer=optimizer, loss=loss, metrics=metrics)

    def train_model(self, batch_size, epochs, verbose, validation_split):
        timer_start = time.process_time()
        self.train_logs = self.model.fit(self.data_set, self.label_set,
                                         epochs=epochs, batch_size=batch_size, verbose=verbose,
                                         validation_split=validation_split)
        timer_end = time.process_time()
        print('Training finished. Execution time: {:.2f} s'.format(timer_end - timer_start))

    # def train_model_mt(self, batch_size, epochs, verbose, validation_split, num_threads=1):
    #     threads = []
    #     timer_start = time.time()
    #     for i in range(num_threads):
    #         threads.append(threading.Thread(target=self.train_model,
    #                                         args=(batch_size, epochs, verbose, validation_split)))
    #         threads[i].start()
    #     thread = threading.Thread(target=self.train_model, args=(batch_size, epochs, verbose, validation_split))
    #     thread.start()
    #     thread.join()
    #     for i in range(num_threads):
    #         threads[i].join()
    #     timer_end = time.time()
    #     print('Training finished. Execution time: {:.2f} s'.format(timer_end - timer_start))

    def show_train_logs(self):
        plt.plot(self.train_logs.history['loss'])
        plt.plot(self.train_logs.history['val_loss'])
        plt.title('Training logs')
        plt.ylabel('Loss')
        plt.xlabel('Epoch')
        plt.legend(['loss', 'val_loss'], loc='upper left')
        plt.show()

    def test_model(self, label_set, data_set, verbose):
        timer_start = time.process_time()
        self.test_logs = self.model.evaluate(data_set, label_set, verbose=verbose)
        timer_end = time.process_time()
        print('Testing finished. Execution time: {:.2f} s'.format(timer_end - timer_start))

    def show_test_logs(self):
        print("Total loss: ", self.test_logs[0])
        print("Total accuracy: ", self.test_logs[1])
