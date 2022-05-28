def preprocess(self):  # preprocess the data set
    timer_start = time.process_time()
    for path in self.__file_path:
        processor = ImagePreprocessor(path, self.__data_dimension, 225)
        self.__label_set.append(processor.get_label())
        self.__data_set = np.vstack((self.__data_set, processor.get_image_data()))
    self.__data_set = np.delete(self.__data_set, [0], 0)
    self.__data_set = self.__data_set.reshape(self.__source_size, self.__data_dimension[0],
                                              self.__data_dimension[1], self.__data_dimension[2])
    self.__label_set = np_utils.to_categorical(self.__label_set, self.__data_category)
    timer_end = time.process_time()
    print('Data set preprocessed. Execution time: {:.2f} s'.format(timer_end - timer_start))

# def __preprocess(self):  # preprocess the data set
#     for path in self.__file_path:
#         processor = ImagePreprocessor(path, self.__data_dimension, 225)
#         self.__label_set.append(processor.get_label())
#         self.__data_set = np.vstack((self.__data_set, processor.get_image_data()))
#
#
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
#     self.__data_set = np.delete(self.__data_set, [0], 0)
#     self.__data_set = self.__data_set.reshape(self.__source_size, self.__data_dimension[0],
#                                               self.__data_dimension[1], self.__data_dimension[2])
#     self.__label_set = np_utils.to_categorical(self.__label_set, self.__data_category)
#     timer_end = time.process_time()
#     print('Data set preprocessed. Execution time: {:.2f} s'.format(timer_end - timer_start))