#include <string>

class Person {
private:
	std::string firstName;
	std::string lastName;

public:
	Person(std::string first, std::string last)
		: firstName(first)
		, lastName(last) {

	}

	std::string GetName();
};