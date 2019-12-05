#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Person : public std::enable_shared_from_this<Person>
{
public:
	Person(const std::string& name):name_(name)	{}
	~Person(){std::cout << "~Person()" << name_ << std::endl; }

	std::string getName() const
	{
		return name_;
	}

	void setFather(std::shared_ptr<Person> f)
	{
		m_father = f;
		if(f)
		{
			f->m_kids.emplace_back(shared_from_this());
		}
	}

	void setMother(std::shared_ptr<Person> m)
	{
		m_mother = m;
		if(m)
		{
			m->m_kids.emplace_back(shared_from_this());
		}
	}

	std::shared_ptr<Person> getKid(size_t idx)
	{
		if(idx < m_kids.size())
		{
			std::weak_ptr<Person> p = m_kids.at(idx);
			if(!p.expired())
			{
				return p.lock();
			}
		}
		return nullptr;
	}
private:
	std::string name_;
	std::shared_ptr<Person> m_father;
	std::shared_ptr<Person> m_mother;
	std::vector<std::weak_ptr<Person>> m_kids;
};

int main()
{
	using namespace std;
	shared_ptr<Person> jack{make_shared<Person>("jack")};
	shared_ptr<Person> lucy{make_shared<Person>("lucy")};	
	shared_ptr<Person> john{make_shared<Person>("john")};

	john->setFather(jack);
	john->setMother(lucy);
	


	auto p = jack->getKid(0);
	if(p)
	{
		cout << p->getName() << endl;
	}
}


