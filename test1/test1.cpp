#include <iostream>
#include "Vector.h"
#include "List.h"

void vectorDemo();
void listDemo();

int main() {
	//vectorDemo();
	listDemo();
	return 0;
}

void vectorDemo() {
	Vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);

	std::cout << v << '\n';
	std::cout << *(v.end() - 1) << '\n';
	std::cout << *v.begin() << ' ' << v.front() << '\n';

	Vector<std::string> s;
	s.push_back("aurel");
	s.push_back("mitica");
	s.push_back("marcel");

	s.pop_back();
	std::cout << s << '\n';
	std::cout << s[1];
}

void listDemo() {
	List<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	std::cout << l << '\n';
	l.pop_front();
	l.push_front(-1);
	l.push_front(3);
	std::cout << l << '\n';
	l.erase(l.begin());
	l.erase(++l.begin());
	std::cout << l << '\n';
	l.insert(l.begin(), 5);
	std::cout << l << '\n';

}