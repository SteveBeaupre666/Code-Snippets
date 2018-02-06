#include "Windows.h"

class Class_A {
public:
	int Add(int a, int b){
		return a + b;
	}
};

// Extend class A Add() method
class Class_B : public Class_A {
public:
	int Add(int a, int b){

		Class_A *p = (Class_A*)this;

		int res = p->Add(a, b) * 2;
		
		return res;
	}
};

int main()
{
	Class_A a;
	Class_B b;

	int res_a = a.Add(3, 7);
	int res_b = b.Add(3, 7);

	return 0;
}