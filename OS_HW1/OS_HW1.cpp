#include <iostream>
#include <vector>
#include <pthread.h>
using namespace std;

typedef struct mParameter_t {
    vector<int> _src_;
    int _lb_;
    int _rb_;
    pthread_mutex_t _rLock_;
} parameter;

parameter *setInput(vector<int> &_src_, int _lb_, int _rb_);
bool isSorted(vector<int> _src_);
void swap(int &n1, int &n2);
void *quickSort(void *_input);
void print_array(vector<int> _src_) {
    cout << _src_[0];
    for (int i = 1; i < _src_.size(); i++) cout << ", " << _src_[i];
    cout << '#' << endl;
}

class Array {
private :
    vector<int> src;
public:
    void add(int input);
    void sort(int _lb_, int _rb_);
    void sort();
    void show(int _lb_, int _rb_);
    void show();
    int size();
    bool isEmpty();
};

int main(void) {
    vector<int> src;
    int tmp;
    parameter *data;

    for (int i = 0; i < 8; i++) {
        cin >> tmp;
        src.push_back(tmp);
    }
    data = setInput(src, 0, src.size()-1);
    quickSort(data);
    print_array(src);

    pthread_exit(NULL);
}

parameter *setInput(vector<int> &_src_, int _lb_, int _rb_) {
    parameter *newInput = new parameter;
    newInput->_src_ = ref(_src_);
    newInput->_lb_ = _lb_;
    newInput->_rb_ = _rb_;
    pthread_mutex_init(&newInput->_rLock_, NULL);
    return newInput;
}

bool isSorted(vector<int> _src_) {
    int length = _src_.size();
    if (length > 0) {
        for (int i = 0; i < length-1; i++) {
            if (_src_[i] > _src_[i+1]) return false;
        }
    }
    return true;
}

void swap(int &n1, int &n2) {
    int temp = n1;

    n1 = n2;
    n2 = temp;
}

void *quickSort(void *_input_) {
    parameter *data = (parameter *)_input_;
    int pivot, l, r;
    parameter *input[2];
    pthread_t pool[2];

    if (data->_lb_ < data->_rb_ && !isSorted(data->_src_)) {
        pthread_mutex_lock(&data->_rLock_);
        pivot = data->_rb_, l = data->_lb_, r = data->_rb_-1;
        while (true) {
            while (l < data->_rb_ and data->_src_[l] < data->_src_[pivot]) ++l;
            while (r > data->_lb_ and data->_src_[r] > data->_src_[pivot]) --r;
            if (l >= r) break;
            swap(data->_src_[l], data->_src_[r]);
            if (l != r) print_array(data->_src_);
        }
        swap(data->_src_[pivot], data->_src_[l]);
        swap(pivot, l);
        if (pivot != l) print_array(data->_src_);
        pthread_mutex_unlock(&data->_rLock_);

        input[0] = setInput(data->_src_, data->_lb_, pivot-1);
        input[1] = setInput(data->_src_, pivot+1, data->_rb_);
        for (int i = 0; i < 2; i++) {
            pthread_create(&pool[i], NULL, quickSort, (void *)input[i]);
            pthread_join(pool[i], NULL);
        }
        pthread_mutex_destroy(&data->_rLock_);
    }
    return NULL;
}

void Array::add(int input) {
    src.push_back(input);
}

void Array::sort(int _lb_, int _rb_) {
    parameter *_input_ = setInput(ref(src), _lb_, _rb_);
    quickSort(_input_);
}

void Array::sort() {
    parameter *_input_ = setInput(ref(src), 0, src.size()-1);
    quickSort(_input_);
}

void Array::show(int _lb_, int _rb_) {
    cout << src[_lb_];
    for (int i = _lb_+1; i <= _rb_; i++) cout << ", " << src[i];
    cout << endl;
}

void Array::show() {
    show(0, src.size()-1);
}

int Array::size() {
    return src.size();
}

bool Array::isEmpty() {
    return src.empty();
}