/*
Name:Alexandra Zuluaga					Z#: 23432285
Course: Foundations of Computer Science (COP3014)
Due Date: 4/23/19		Due Time: 11:59pm
Total Points: 20
Assignment #11: call_stats8.cpp


*/

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "call_class.h"

using namespace std;

//driver to test the functionality of your class.
int main()
{
	cout << "TEST1: Testing the Default Constructor, is_full and double_size\n";
	call_class MyClass;
	cout << "Finish TEST1: testing the default constructor\n\n\n\n";

	cout << "Test2: Testing add, double_size, process, and is_full() \n";
	//MyClass.add();
	cout << "Finish TEST2\n\n\n\n";

	cout << "Test3: Testing operator-, serach, and is_empty\n";
	MyClass - "5617278899" - "9546321555" - "1234567890";
	cout << "Finish TEST3\n\n\n\n";

	cout << "Test4: Testing operator<<\n\n";
	cout << MyClass << endl;
	cout << "Finish TEST4\n\n\n\n";

	cout << "Test5: Testing copy constructor\n\n";
	call_class YourClass = MyClass;
	cout << YourClass << endl;
	cout << "Finish TEST5\n\n\n\n";

	cout << "The destructor will be called automatically\n";
	system("pause");
	return 0;
}