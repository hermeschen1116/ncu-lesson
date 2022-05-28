import threading

import numpy as np


class DataSet:
    def __init__(self, source_path, data_dimension, data_category):
        self.__source_path = source_path  # set the data set source path
        self.__source_size = 0  # initialize the number of images in the data set
        self.__data_dimension = data_dimension  # initialize the data dimension [width, height, channel, ...]
        self.__data_category = data_category  # set the number of categories in the data set
        self.__file_path = []  # initialize the file path
        # self.__file_path = queue.Queue  # initialize the file path
        self.__label_set = []  # initialize the label list
        self.__data_set = np.zeros((data_dimension[0], data_dimension[1])) \
            .reshape(data_dimension[2], data_dimension[0], data_dimension[1])  # initialize the data list
        self.__multi_thread_lock = threading.Lock()  # initialize the multi-thread lock

    def set_source_path(self, source_path):  # set the data set source path
        self.__source_path = source_path

    def get_source_path(self):  # get the data set source path
        return self.__source_path

    def set_source_size(self, source_size):  # set the number of images in the data set
        self.__source_size = source_size

    def get_source_size(self):  # get the number of images in the data set
        return self.__source_size

    def set_data_dimensions(self, data_dimension):  # set the data dimension
        self.__data_dimension = data_dimension

    def get_data_dimensions(self):  # get the data dimension
        return self.__data_dimension

    def set_data_category(self, data_category):  # set the number of categories in the data set
        self.__data_category = data_category

    def get_data_category(self):  # get the number of categories in the data set
        return self.__data_category

    def get_label_set(self):  # get the processed label set
        return self.__label_set

    def get_data_set(self):  # get the processed data set
        return self.__data_set
