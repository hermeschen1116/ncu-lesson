#include <iostream>

using namespace std;

class action {
public :
    action () = default;
    virtual void print() {
        cout << "You get \"action\"!" << endl;
    };
};

class camp {
public :
    camp () = default;
    virtual void print() {
        cout << "You get \"camp\"!" << endl;
    };
};

class apple {
public :
    apple () = default;
    virtual void print() {
        cout << "You get \"apple\"!" << endl;
    };
};

class n : public action {
public :
    void print() override {
        cout << "You get \"n\"!" << endl;
    }
};

class act : public action {
public :
    void print() override {
        cout << "You get \"act\"!" << endl;
    }
};

class c : public act, public camp {
public :
    void print() override {
        cout << "You get \"c\"!" << endl;
    }
};

class a : public act, public apple {
public :
    void print() override {
        cout << "You get \"a\"!" << endl;
    }
};

//////////////////////////////////////////////
//                                          //
//          以下請不要做任何的更改            //
//                                          //
//////////////////////////////////////////////

int main() {
    a *a1 = new a();
    c *c1 = new c();
    n *n1 = new n();
    a1->print();
    c1->print();
    n1->print();


    a1 = new apple();
    a1->print();


    a1 = new act();
    a1->print();
    c1 = new act();
    c1->print();
    act *a3 = new act();
    a3->print();


    a1 = new action();
    a1->print();
    c1 = new action();
    c1->print();
    a3 = new action();
    a3->print();
    n1 = new action();
    n1->print();


    c1 = new camp();
    c1->print();



    return 0;
}