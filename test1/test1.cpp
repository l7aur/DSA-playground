#include <iostream>
#include "Employee.h"
#include "Vector.h"
#include "List.h"
#include "Queue.h"
#include "Stack.h"
#include "BSTree.h"
#include "AVLTree.h"
#include "ChainedHashTable.h"

void vectorDemo();
void listDemo();
void queueDemo();
void stackDemo();
void BSTreeDemo();
void AVLTreeDemo();
void ChainedHTDemo();

int main() {
	//vectorDemo();
	//listDemo();
	//queueDemo();
	//stackDemo();
	//BSTreeDemo();
	//AVLTreeDemo();
	ChainedHTDemo();
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
void BSTreeDemo() {
	BSTree<int> t;
	t.insert(5); t.insert(9); t.insert(0); t.insert(2); t.insert(7);
	t.insert(1); t.insert(3); t.insert(8); t.insert(4); t.insert(6);
	std::cout << t << '\n';
	t.remove(4);
	std::cout << t << '\n';
	t.remove(0);
	std::cout << t << '\n';
	t.remove(1);
	std::cout << t << '\n';
	BSTree<int> t2;
	t2 = t;
	std::cout << "copied tree:\n" << t2 << '\n';
	std::cout << t2.findMax() << '\n';
	std::cout << t2.findMin() << '\n';
}
void AVLTreeDemo() {
	AVLTree<int> t;
	t.insert(3); t.insert(2); t.insert(1);
	std::cout << t << '\n';
	t.insert(4); t.insert(5);
	std::cout << t << '\n';
	t.insert(6);
	std::cout << t << '\n';
	t.insert(7);
	std::cout << t << '\n';
	t.insert(16); t.insert(15); t.insert(14);
	std::cout << t << '\n';
	t.insert(13); t.insert(12); t.insert(11);
	t.insert(10); t.insert(8); t.insert(9);
	std::cout << t << '\n';
}
void ChainedHTDemo() {
	ChainedHashTable<Employee> tab{5};
	Employee e{ "Eugen Popescu", 10.2, 54 };
	Employee e1{ "Fugen Oopescu", 100.4, 72 };
	Employee e2{ "Dugen Qopescu", 999.9 , 44 };
	Employee f{ "Mihai Abramovici", 2030.5, 44 };
	Employee f1{ "Ion Abramovici", 2200.5, 53 };
	Employee f2{ "Vasile Abramovici", 2010.5, 13 };
	bool status = tab.insert(e);
	std::cout << ((status == true) ? "Insert succeeded\n" : "Insert failed\n");
	status = tab.insert(e1); 
	std::cout << ((status == true) ? "Insert succeeded\n" : "Insert failed\n");
	status = tab.insert(e2);
	std::cout << ((status == true) ? "Insert succeeded\n" : "Insert failed\n");

	tab.insert(f); tab.insert(f1); tab.insert(f2);
	std::cout << tab << '\n';
	status = tab.remove(e);
	std::cout << ((status == true) ? "Remove succeeded\n" : "Remove failed\n");
	status = tab.remove(f);
	std::cout << ((status == true) ? "Remove succeeded\n" : "Remove failed\n");
	std::cout << tab << '\n';
}