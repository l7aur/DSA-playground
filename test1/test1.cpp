#include <iostream>
#include "Vector.h"
#include "List.h"
#include "Queue.h"
#include "Stack.h"

void vectorDemo();
void listDemo();
void queueDemo();
void stackDemo();

int main() {
	//vectorDemo();
	//listDemo();
	//queueDemo();
	stackDemo();
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

void queueDemo() {
	Queue<int> q;
	q.insert(2);
	q.pop();
	q.insert(5); q.insert(10);
	std::cout << q << '\n';
	q.insert(20);
	q.pop();
	std::cout << q << '\n';
	
	Queue<std::string> q2;
	q2.insert("a"); q2.insert("bx"); q2.insert("cx");
	std::cout << q2 << '\n';
	q2.pop(); q2.pop(); q2.pop();
	std::cout << q2 << '\n';
	q2.insert("hmm"); q2.insert("hmm"); q2.insert("hmmx");
	std::cout << q2 << '\n';

	Queue<int> q3;
	q3.insert(13); q3.insert(23); q3.insert(33); q3.insert(-100);
	std::cout << q << '\n';
	q = q3;
	std::cout << "q: " << q << "\nq3: " << q3 << '\n';

}

void stackDemo() {
	Stack<int> s;
	s.push(30);
	s.push(10);
	s.pop();
	std::cout << s << '\n';
	s.push(3);
	s.push(3);
	s.push(-1);
	s.pop();
	std::cout << s << '\n';

	Stack<std::string> s2;
	s2.push("europa");
	s2.push("asia");
	s2.pop();
	std::cout << s2 << '\n';
	s2.push("america");
	std::cout << s2 << '\n';
}