#include <iostream>
#include <memory>

class BadExample
{
public:
	std::shared_ptr<BadExample> getptr()
	{
		return std::shared_ptr<BadExample>(this);
	}

	~BadExample(){ std::cout << "~BadExample()" << std::endl;}
};

class EnableSharedPtrExample : public 		std::enable_shared_from_this<EnableSharedPtrExample>
{
public:
	std::shared_ptr<EnableSharedPtrExample> getptr()
	{
		return shared_from_this();
	}

	~EnableSharedPtrExample()
	{ 
		std::cout << "~EnableSharedPtrExample()" << std::endl;
	}
};

int main()
{
	std::shared_ptr<EnableSharedPtrExample> bp1(new EnableSharedPtrExample());
	std::shared_ptr<EnableSharedPtrExample> bp2 = bp1->getptr();

	std::cout << "bp1.use_count()" << bp1.use_count() << std::endl;
	std::cout << "bp2.use_count()" << bp2.use_count() << std::endl;
}

