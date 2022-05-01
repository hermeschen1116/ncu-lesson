#include <iostream>
#include <vector>
#include <pthread.h>
using namespace std;

typedef struct mParameter_t {
    vector<int> *_src_;
    int _lb_;
    int _rb_;
    pthread_mutex_t _rLock_;
} parameter;

parameter *setInput(vector<int> &_src_, int _lb_, int _rb_);
bool isSorted(vector<int> _src_);
void swap(int &n1, int &n2);
void *quickSort(void *_input);

class list_t {
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
    list_t src;
    int tmp;

    for (int i = 0; i < 8; i++) {
        cin >> tmp;
        src.add(tmp);
    }
    src.show();
    src.sort();
    src.show();

    pthread_exit(NULL);
}

parameter *setInput(vector<int> &_src_, int _lb_, int _rb_) {
    parameter *newInput = new parameter;
    newInput->_src_ = &_src_;
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

    if (data->_lb_ < data->_rb_ && !isSorted(*data->_src_)) {
        pthread_mutex_lock(&data->_rLock_);
        pivot = data->_rb_, l = data->_lb_, r = data->_rb_-1;
        while (true) {
            while (l < data->_rb_ and (*data->_src_)[l] < (*data->_src_)[pivot]) ++l;
            while (r > data->_lb_ and (*data->_src_)[r] > (*data->_src_)[pivot]) --r;
            if (l >= r) break;
            swap((*data->_src_)[l], (*data->_src_)[r]);
        }
        swap((*data->_src_)[pivot], (*data->_src_)[l]);
        swap(pivot, l);
        pthread_mutex_unlock(&data->_rLock_);

        input[0] = setInput(*data->_src_, data->_lb_, pivot-1);
        input[1] = setInput(*data->_src_, pivot+1, data->_rb_);
        for (int i = 0; i < 2; i++) {
            pthread_create(&pool[i], NULL, quickSort, (void *)input[i]);
            pthread_join(pool[i], NULL);
        }
        pthread_mutex_destroy(&data->_rLock_);
    }
    return NULL;
}

void list_t::add(int input) {
    src.push_back(input);
}

void list_t::sort(int _lb_, int _rb_) {
    parameter *_input_ = setInput(ref(src), _lb_, _rb_);
    quickSort(_input_);
}

void list_t::sort() {
    parameter *_input_ = setInput(ref(src), 0, src.size()-1);
    quickSort(_input_);
}

void list_t::show(int _lb_, int _rb_) {
    cout << src[_lb_];
    for (int i = _lb_+1; i <= _rb_; i++) cout << ", " << src[i];
    cout << endl;
}

void list_t::show() {
    show(0, src.size()-1);
}

int list_t::size() {
    return src.size();
}

bool list_t::isEmpty() {
    return src.empty();
}