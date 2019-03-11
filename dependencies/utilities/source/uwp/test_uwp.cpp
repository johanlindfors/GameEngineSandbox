#include "test.h"

using std::string;

string Person::GetName() {
	return firstName + " " + lastName;
}