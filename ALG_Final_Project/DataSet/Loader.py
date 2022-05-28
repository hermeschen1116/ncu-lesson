import os
import queue
import threading
import time


class Loader(threading.Thread):
    def __init__(self, source_path, loader_lock):
        threading.Thread.__init__(self)
        self.__source_path = source_path
        self.__file_queue = queue.Queue()
        self.__source_size = 0
        self.__loader_lock = loader_lock

    def loader(self):
        for root, dirs, files in os.walk(self.__source_path):
            self.__loader_lock.acquire()
            for file in files:
                if file == '.DS_Store' or file == 'desktop.ini':
                    continue
                self.__file_queue.put([root, file])
                self.__source_size += 1
            self.__loader_lock.release()

    def load_data_set(self, num_threads):
        thread_pool = []
        timer_start = time.process_time()
        for i in range(num_threads):
            thread_pool.append(Loader(self.__source_path, self.__loader_lock))
            thread_pool[i].start()
        for i in range(num_threads):
            thread_pool[i].join()
        timer_end = time.process_time()
        print('Data set loaded. Execution time: {:.2f} s'.format(timer_end - timer_start))
