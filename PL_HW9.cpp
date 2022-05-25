#include <iostream>

using namespace std;

class a {
public :
    virtual void print() {
        cout << "You get \"a\"!" << endl;
    }
};

class apple : public a {
public :
    void print() override {
        cout << "You get \"apple\"!" << endl;
    };
};

class c {
public :
    virtual void print() {
        cout << "You get \"c\"!" << endl;
    }
};

class act : public a, public c {
public :
    void print() override {
        cout << "You get \"act\"!" << endl;
    }
};

class camp : public c {
public :
    void print() override {
        cout << "You get \"camp\"!" << endl;
    };
};

class n {
public :
    virtual void print() {
        cout << "You get \"n\"!" << endl;
    }
};

class action : public act, public n {
public :
    void print() override {
        cout << "You get \"action\"!" << endl;
    };
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