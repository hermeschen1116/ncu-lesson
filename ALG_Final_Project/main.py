import Preprocess
import Model

train_set_source_path = "data_set/train_image/"
data_dimension = [1, 28, 28]
data_category = 10

train_set = Preprocess.DataSet(train_set_source_path, data_dimension, data_category)
