#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class A;
class B;

class A
{
public:
	A() { cout << "A()" <<endl; }
	~A() { cout << "~A()" <<endl; }
	//shared_ptr<B> pb;
	weak_ptr<B> pb;
};

class B
{
public:
	B() { cout << "B()" <<endl; }
	~B() { cout << "~B()" <<endl; }
	//shared_ptr<A> pa;
	weak_ptr<A> pa;
};

int main()
{
	shared_ptr<A> spa = make_shared<A>();
	shared_ptr<B> spb = make_shared<B>();

	spa->pb = spb;
	spb->pa = spa;
}
