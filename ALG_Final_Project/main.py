import Model  # Import model
import Preprocess  # Import preprocess

train_set_source_path = "data_set/train_image/"  # train_set_source_path
data_dimensions = [28, 28, 1]  # data_dimensions
data_category = 10  # data_category

train_set = Preprocess.DataSet(train_set_source_path, data_dimensions, data_category)  # train_set
train_set.load_data_set()  # load_data_set
train_set.preprocess()  # preprocess
print('Training Set Size:', train_set.get_source_size())  # Training Set Size: 2450

classifier = Model.CNN(train_set.get_label_set(), train_set.get_data_set())  # classifier
classifier.add_convolution_layer(32, (3, 3), 'relu', (28, 28, 1))  # add_convolution_layer
classifier.add_pooling_layer((2, 2))  # add_pooling_layer
classifier.add_convolution_layer(64, (3, 3), 'relu', ())  # add_convolution_layer
classifier.add_pooling_layer((2, 2))  # add_pooling_layer
classifier.add_dropout_layer(0.1)  # add_dropout_layer
classifier.add_flatten_layer()  # add_flatten_layer
classifier.add_dropout_layer(0.1)  # add_dropout_layer
classifier.add_dense_layer(128, 'relu')  # add_dense_layer
classifier.add_dropout_layer(0.25)  # add_dropout_layer
classifier.add_dense_layer(10, 'softmax')  # add_dense_layer
classifier.compile_model('categorical_crossentropy', 'adam', ['accuracy'])  # compile_model
classifier.train_model(32, 100, 1, 0.1)  # train_model
classifier.show_train_logs()  # show_train_logs

test_set_source_path = "data_set/test_image/"  # test_set_source_path

test_set = Preprocess.DataSet(test_set_source_path, data_dimensions, data_category)  # test_set
test_set.load_data_set()  # load_data_set
test_set.preprocess()  # preprocess
print('Testing Set Size:', test_set.get_source_size())  # Testing Set Size: 1700

classifier.test_model(test_set.get_label_set(), test_set.get_data_set(), 1)  # test_model
classifier.show_test_logs()  # show_test_logs
