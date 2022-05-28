import os

import numpy as np
from PIL import Image


class ImagePreprocessor:
    def __init__(self, image_path, data_dimensions, color_range):
        self.__image_path = image_path  # [path, filename]
        self.__data_dimensions = data_dimensions  # [width, height, channels, ...]
        self.__color_mode = color_range  # how many color

    def get_label(self):  # get label
        return int(self.__image_path[0].split('/')[-1])

    def get_image_data(self):  # get processed image data
        full_path = os.path.join(self.__image_path[0], self.__image_path[1])
        image_data = Image.open(full_path)

        return (np.array(image_data) / self.__color_mode) \
            .reshape(self.__data_dimensions[2], self.__data_dimensions[0], self.__data_dimensions[1])
