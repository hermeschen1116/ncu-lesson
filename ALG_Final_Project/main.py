import Preprocess
import Model

train_set_source_path = "data_set/train_image/"
data_dimensions = [28, 28, 1]
data_category = 10

train_set = Preprocess.DataSet(train_set_source_path, data_dimensions, data_category)
train_set.load_data_set()
train_set.preprocess()
print('Training Set Size:', train_set.get_source_size())

classifier = Model.CNN(train_set.get_label_set(), train_set.get_data_set())
classifier.add_convolution_layer(32, (3, 3), 'relu', (28, 28, 1))
classifier.add_pooling_layer((2, 2))
classifier.add_convolution_layer(64, (3, 3), 'relu', ())
classifier.add_pooling_layer((2, 2))
classifier.add_dropout_layer(0.1)
classifier.add_flatten_layer()
classifier.add_dropout_layer(0.1)
classifier.add_dense_layer(128, 'relu')
classifier.add_dropout_layer(0.25)
classifier.add_dense_layer(10, 'softmax')
classifier.compile_model('categorical_crossentropy', 'adam', ['accuracy'])
classifier.train_model(32, 100, 1, 0.1)
classifier.show_train_logs()

test_set_source_path = "data_set/test_image/"

test_set = Preprocess.DataSet(test_set_source_path, data_dimensions, data_category)
test_set.load_data_set()
test_set.preprocess()
print('Testing Set Size:', test_set.get_source_size())

classifier.test_model(test_set.get_label_set(), test_set.get_data_set(), 1)
classifier.show_test_logs()
