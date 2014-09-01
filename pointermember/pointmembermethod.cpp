#include <iostream>

using namespace std;

class A {
public:
	int print();
};

int A::print()
{
	cout<<"test pointmembermethod program"<<endl;
}

typedef int (A::*_func)();

int main(int argc, char * argv[])
{
	A test;
	_func func;
	func = &A::print;
	(test.*func)();
	return 0;
}
