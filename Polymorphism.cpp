#include <iostream>

using namespace std;

//목적 : 

class Base {
public:
	virtual void display() { cout << "Base" << endl; }
};

class Derived : public Base {
public:
	void display() { cout << "Deriver" << endl; }
};

int main() {
	Base* ptr = new Derived;
	ptr->display();
}