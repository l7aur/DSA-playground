#pragma once

#include <iostream>
#include <string>
#include "Hash.h"

class Employee {
public:
	Employee(std::string n, double s, int a) : name(n), salary(s), seniority(a) {}
	Employee() : name("Default"), salary(-1.0), seniority(-1) {}
	const std::string& getName() const { return name; }
	const double& getSalary() const { return salary; }
	const int& getSeniority() const { return seniority; }
	bool operator==(const Employee& rhs) const { return getName() == rhs.getName(); }
	bool operator!=(const Employee& rhs) const { return !(*this == rhs); }
private:
	std::string name;
	double salary;
	int seniority;
};

std::ostream& operator<<(std::ostream& out, const Employee& e) {
	out << "{ " << e.getName() << ", " << e.getSalary() << ", " << e.getSeniority() << " }";
	return out;
}

template<>
class Hash<Employee> {
public:
	size_t operator() (const Employee& item) {
		static Hash<std::string> h;
		return h(item.getName());
	}
};