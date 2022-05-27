import os

import numpy as np
from PIL import Image
from keras.utils import np_utils


class ImagePreprocessor:
    def __init__(self, image_path, target_dimensions, color_mode):
        self.image_path = image_path  # (path, filename)
        self.target_dimensions = target_dimensions  # (channel, width, height)
        self.color_mode = color_mode  # how many color

    def get_label(self):  # get label
        return int(self.image_path[0].split('//')[2])

    def get_image_data(self):  # get processed image data
        full_path = os.path.join(self.image_path[0], self.image_path[1])
        image_data = Image.open(full_path)

        return np.array(image_data / self.color_mode).reshape(self.target_dimensions)


class DataSet:
    def __init__(self, source_path, data_dimension, data_category):
        self.source_path = source_path  # set the data set source path
        self.source_size = 0  # initialize the number of images in the data set
        self.data_category = data_category  # set the number of categories in the data set
        self.data_dimension = data_dimension  # set the dimension of the data set (channel, width, height, ...)
        self.label_set = []  # initialize the label list
        self.data_set = np.zeros(self.data_dimension[1], self.data_dimension[2]).reshape(self.data_dimension)
        # initialize the data list

    def set_source_path(self, source_path):  # set the data set source path
        self.source_path = source_path

    def get_source_path(self):  # get the data set source path
        return self.source_path

    def set_source_size(self, source_size):  # set the number of images in the data set
        self.source_size = source_size

    def get_source_size(self):  # get the number of images in the data set
        return self.source_size

    def set_data_category(self, data_category):  # set the number of categories in the data set
        self.data_category = data_category

    def get_data_category(self):  # get the number of categories in the data set
        return self.data_category

    def set_data_dimension(self, data_dimension):  # set the dimension of the data set (channel, width, height, ...)
        self.data_dimension = data_dimension

    def get_data_dimension(self):  # get the dimension of the data set (channel, width, height, ...)
        return self.data_dimension

    def preprocess(self):  # preprocess the data set
        for root, dirs, files in os.walk(self.source_path):
            for file in files:
                processor = ImagePreprocessor([root, file], self.data_dimension, 225)
                self.label_set.append(processor.get_label())
                self.data_set = np.vstack((self.data_set, processor.get_image_data()))
                self.source_size += 1
        self.data_set = np.delete(self.data_set, [0], 0)
        self.data_set = self.data_set.reshape(self.source_size, self.data_dimension)
        self.label_set = np_utils.to_categorical(self.label_set, self.data_category)

    def get_label_set(self):  # get the processed label set
        return self.label_set

    def get_data_set(self):  # get the processed data set
        return self.data_set
