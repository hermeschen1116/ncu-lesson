import os
import threading
import time

import numpy as np
from PIL import Image
from keras.utils import np_utils


class ImagePreprocessor:
    def __init__(self, image_path, data_dimensions, color_range):
        self.image_path = image_path  # [path, filename]
        self.data_dimensions = data_dimensions  # [width, height, channels, ...]
        self.color_mode = color_range  # how many color

    def get_label(self):  # get label
        return int(self.image_path[0].split('/')[-1])

    def get_image_data(self):  # get processed image data
        full_path = os.path.join(self.image_path[0], self.image_path[1])
        image_data = Image.open(full_path)

        return (np.array(image_data) / self.color_mode) \
            .reshape(self.data_dimensions[2], self.data_dimensions[0], self.data_dimensions[1])


class DataSet:
    def __init__(self, source_path, data_dimension, data_category):
        self.source_path = source_path  # set the data set source path
        self.source_size = 0  # initialize the number of images in the data set
        self.data_dimension = data_dimension  # initialize the data dimension [width, height, channel, ...]
        self.data_category = data_category  # set the number of categories in the data set
        self.file_path = []  # initialize the file path
        self.label_set = []  # initialize the label list
        self.data_set = np.zeros((data_dimension[0], data_dimension[1])) \
            .reshape(data_dimension[2], data_dimension[0], data_dimension[1])  # initialize the data list

    def set_source_path(self, source_path):  # set the data set source path
        self.source_path = source_path

    def get_source_path(self):  # get the data set source path
        return self.source_path

    def set_source_size(self, source_size):  # set the number of images in the data set
        self.source_size = source_size

    def get_source_size(self):  # get the number of images in the data set
        return self.source_size

    def set_data_dimensions(self, data_dimension):  # set the data dimension
        self.data_dimension = data_dimension

    def get_data_dimensions(self):  # get the data dimension
        return self.data_dimension

    def set_data_category(self, data_category):  # set the number of categories in the data set
        self.data_category = data_category

    def get_data_category(self):  # get the number of categories in the data set
        return self.data_category

    def load_data_set(self):  # load the data set
        timer_start = time.process_time()
        for root, dirs, files in os.walk(self.source_path):
            for file in files:
                if file == '.DS_Store' or file == 'desktop.ini':
                    continue
                self.file_path.append([root, file])
                self.source_size += 1
        timer_end = time.process_time()
        print('Data set loaded. Execution time: {:.2f} s'.format(timer_end - timer_start))

    # def load_data_set_mt(self, num_threads=1):  # load the data set with multi-threading
    #     threads = []
    #     timer_start = time.process_time()
    #     for i in range(num_threads):
    #         threads.append(threading.Thread(target=self.load_data_set))
    #         threads[i].start()
    #     thread = threading.Thread(target=self.load_data_set)
    #     thread.start()
    #     thread.join()
    #     for i in range(num_threads):
    #         threads[i].join()
    #     timer_end = time.process_time()
    #     print('Data set loaded. Execution time: {:.2f} s'.format(timer_end - timer_start))

    def preprocess(self):  # preprocess the data set
        timer_start = time.process_time()
        for path in self.file_path:
            processor = ImagePreprocessor(path, self.data_dimension, 225)
            self.label_set.append(processor.get_label())
            self.data_set = np.vstack((self.data_set, processor.get_image_data()))
        self.data_set = np.delete(self.data_set, [0], 0)
        self.data_set = self.data_set.reshape(self.source_size,
                                              self.data_dimension[0], self.data_dimension[1], self.data_dimension[2])
        self.label_set = np_utils.to_categorical(self.label_set, self.data_category)
        timer_end = time.process_time()
        print('Data set preprocessed. Execution time: {:.2f} s'.format(timer_end - timer_start))

    # def preprocess_mt(self, num_threads=1):  # preprocess the data set with multi-threading
    #     threads = []
    #     timer_start = time.process_time()
    #     for i in range(num_threads):
    #         threads.append(threading.Thread(target=self.preprocess))
    #         threads[i].start()
    #     thread = threading.Thread(target=self.preprocess)
    #     thread.start()
    #     thread.join()
    #     for i in range(num_threads):
    #         threads[i].join()
    #     timer_end = time.process_time()
    #     print('Data set preprocessed. Execution time: {:.2f} s'.format(timer_end - timer_start))

    def get_label_set(self):  # get the processed label set
        return self.label_set

    def get_data_set(self):  # get the processed data set
        return self.data_set
