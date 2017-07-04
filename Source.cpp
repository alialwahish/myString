#include <iostream>
#include "myString.h"

using namespace std;
//using namespace main_savitch_4;

void f(main_savitch_4::string);	// pass by value "copy"

int main()
{
	main_savitch_4::string str1("TEST"), str2("Bigger String");

	//str1.test();
	//str2.test();

	//str1 = str2; // reserve called?

	str1.test();

	cout << endl << "Testing Copy Constructor" << endl;
	f(str1);

	cout << "Enter Your Name: ";
	main_savitch_4::getline(cin, str1, '\n');

	// str1 didn't get changed yet
	str1.test();

	return 0;
}

void f(main_savitch_4::string s)
{
	s.test();
}