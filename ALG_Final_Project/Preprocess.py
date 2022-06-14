import os
import time

import numpy as np
from PIL import Image
from keras.utils import np_utils


class ImagePreprocessor:
    def __init__(self, image_path, data_dimensions, color_range):  # init
        self.__image_path = image_path  # [path, filename]
        self.__data_dimensions = data_dimensions  # [width, height, channels, ...]
        self.__color_mode = color_range  # how many color

    def get_label(self):  # get label
        return int(self.__image_path[0].split('/')[-1])  # get label

    def get_image_data(self):  # get processed image data
        full_path = os.path.join(self.__image_path[0], self.__image_path[1])  # get full path
        image_data = Image.open(full_path)  # open image

        return (np.array(image_data) / self.__color_mode) \
            .reshape(self.__data_dimensions[2], self.__data_dimensions[0], self.__data_dimensions[1])  # reshape


class DataSet:
    def __init__(self, source_path, data_dimension, data_category):
        self.__source_path = source_path  # set the data set source path
        self.__source_size = 0  # initialize the number of images in the data set
        self.__data_dimension = data_dimension  # initialize the data dimension [width, height, channel, ...]
        self.__data_category = data_category  # set the number of categories in the data set
        self.__file_path = []  # initialize the file path
        self.__label_set = []  # initialize the label list
        self.__data_set = np.zeros((data_dimension[0], data_dimension[1])) \
            .reshape(data_dimension[2], data_dimension[0], data_dimension[1])  # initialize the data list

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

    def load_data_set(self):  # load the data set
        timer_start = time.process_time()  # start timer
        for root, dirs, files in os.walk(self.__source_path):  # walk through the data set
            for file in files:  # get the file path
                if file == '.DS_Store' or file == 'desktop.ini':  # skip the .DS_Store and the desktop.ini file
                    continue
                self.__file_path.append([root, file])  # add the file path to the list
                self.__source_size += 1  # increase the number of images
        timer_end = time.process_time()  # end timer
        print('Data set loaded. Execution time: {:.2f} s'.format(timer_end - timer_start))  # print execution time

    def preprocess(self):  # preprocess the data set
        timer_start = time.process_time()  # start timer
        for path in self.__file_path:  # walk through the data set
            processor = ImagePreprocessor(path, self.__data_dimension, 225)  # create image processor
            self.__label_set.append(processor.get_label())  # add the label to the list
            self.__data_set = np.vstack((self.__data_set, processor.get_image_data()))  # add the image data to the list
        self.__data_set = np.delete(self.__data_set, [0], 0)  # delete the first row
        self.__data_set = self.__data_set.reshape(self.__source_size, self.__data_dimension[0],
                                                  self.__data_dimension[1], self.__data_dimension[2])  # reshape
        self.__label_set = np_utils.to_categorical(self.__label_set, self.__data_category)  # convert to categorical
        timer_end = time.process_time()  # end timer
        print('Data set preprocessed. Execution time: {:.2f} s'.format(timer_end - timer_start))  # print execution time

    def get_label_set(self):  # get the processed label set
        return self.__label_set

    def get_data_set(self):  # get the processed data set
        return self.__data_set
