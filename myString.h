// FILE: mystring.h
// CLASS PROVIDED: string
//   This is a simple version of the Standard Library string.
//   It is part of the namespace main_savitch_4, from the textbook
//   "Data Structures and Other Objects Using C++"
//   by Michal Main and Walter Savitch
//
// CONSTRUCTOR for the string class:
//   string(const char str[ ] = "") -- default argument is the empty string.
//     Precondition: str is an ordinary null-terminated string.
//     Postcondition: The string contains the sequence of chars from str.
//
// CONSTANT MEMBER FUNCTIONS for the string class:
//   size_t length( ) const
//     Postcondition: The return value is the number of characters in the
//     string.
//
//   char operator [ ](size_t position) const
//     Precondition: position < length( ).
//     Postcondition: The value returned is the character at the specified
//     position of the string. A string's positions start from 0 at the start
//     of the sequence and go up to length( )-1 at the right end.
//
// MODIFICATION MEMBER FUNCTIONS for the string class:
//   void operator +=(const string& addend)
//     Postcondition: addend has been catenated to the end of the string.
//
//   void operator +=(const char addend[ ])
//     Precondition: addend is an ordinary null-terminated string.
//     Postcondition: addend has been catenated to the end of the string.
//
//   void operator +=(char addend)
//     Postcondition: The single character addend has been catenated to the
//     end of the string.
//
//   void reserve(size_t n)
//     Postcondition: All functions will now work efficiently (without
//     allocating new memory) until n characters are in the string.
//
// NON-MEMBER FUNCTIONS for the string class:
//   string operator +(const string& s1, const string& s2)
//     Postcondition: The string returned is the catenation of s1 and s2.
//
//   istream& operator >>(istream& ins, string& target)
//     Postcondition: A string has been read from the istream ins, and the
//     istream ins is then returned by the function. The reading operation
//     skips white space (i.e., blanks, newlines, tabs) at the start of ins.
//     Then the string is read up to the next white space or the end of the
//     file. The white space character that terminates the string has not
//     been read.
//
//   ostream& operator <<(ostream& outs, const string& source)
//     Postcondition: The sequence of characters in source has been written
//     to outs. The return value is the ostream outs.
//
//   void getline(istream& ins, string& target, char delimiter)
//     Postcondition: A string has been read from the istream ins. The reading
//     operation starts by skipping any white space, then reading all characters
//     (including white space) until the delimiter is read and discarded (but
//     not added to the end of the string). The return value is ins.
//
//  VALUE SEMANTICS for the string class:
//    Assignments and the copy constructor may be used with string objects.
//
//  TOTAL ORDER SEMANTICS for the string class:
//    The six comparison operators (==, !=, >=, <=, >, and <) are implemented
//    for the string class, forming a total order semantics, using the usual
//    lexicographic order on strings.
// 
// DYNAMIC MEMORY usage by the string class: 
//   If there is insufficient dynamic memory then the following functions call
//   new_handler: The constructors, resize, operator +=, operator +, and the
//   assignment operator.

#ifndef MAIN_SAVITCH_CHAPTER4_MYSTRING_H
#define MAIN_SAVITCH_CHAPTER4_MYSTRING_H
#include <cstdlib>  // Provides size_t
#include <iostream>

using namespace std;

namespace main_savitch_4
{
	class string
	{
	public:
		// CONSTRUCTORS and DESTRUCTOR
		string(const char str[] = "");
		string(const string& source);
		~string();
		// MODIFICATION MEMBER FUNCTIONS
		void operator +=(const string& addend);
		void operator +=(const char addend[]);
		void operator +=(char addend);
		void reserve(size_t n);
		void operator =(const string& source);
		// CONSTANT MEMBER FUNCTIONS
		size_t length() const { return current_length; }
		char operator [ ](size_t position) const;
		// FRIEND FUNCTIONS
		friend ostream& operator <<(ostream& outs, const string& source);
		friend bool operator ==(const string& s1, const string& s2);
		friend bool operator !=(const string& s1, const string& s2);
		friend bool operator >=(const string& s1, const string& s2);
		friend bool operator <=(const string& s1, const string& s2);
		friend bool operator > (const string& s1, const string& s2);
		friend bool operator < (const string& s1, const string& s2);

		void test() const;
	private:
		char *sequence;
		size_t allocated;
		size_t current_length;
	};

	
	// NON-MEMBER FUNCTIONS for the string class
	//string operator +(const string& s1, const string& s2);
	istream& operator >> (istream& ins, string& target)
	{
		// our job is to read from ins (think of it as cin >> target)
		
		char temp[100];

		ins >> temp;	// see what's going on
		//cout << temp << " I read this" << endl;

		target = main_savitch_4::string(temp);

		return ins;

	}
	void getline(istream& ins, string& target, char delimiter)
	{
		// let's test out this peek function
		char temp, readChar;

		temp = ins.peek();
		while (temp != delimiter)
		{
			ins.get(readChar);
			
			// echo to screen
			//cout << readChar;
			temp = ins.peek();
		}

	}
	

	string::string(const string& source)
	{
		// copy source into my data
		// we have not been through a constructor so
		// we have to allocate the array
		current_length = source.current_length;
		allocated = source.allocated;

		// this was happending by default
		// sequence = source.sequence;

		// create array
		sequence = new char[allocated];

		// copy contents
		strcpy_s(sequence, allocated, source.sequence);
	}

	void string::operator =(const string& source)
	{
		// a = b
		// check if we have enough 'allocated' to store b's chars
		if (allocated < (source.current_length + 1))
			reserve(source.current_length + 1);	// need more room

		current_length = source.current_length;

		strcpy_s(sequence, allocated, source.sequence);
	}

	void string::reserve(size_t n)
	{
		// create a string n big and copy data to new string
		char *newString = new char[n];

		// move data to new string
		strcpy_s(newString, n, sequence);
		
		// does current_length change?
		allocated = n;

		// free up old array
		delete[] sequence;

		sequence = newString;
	}

	string::~string()
	{
		delete[] sequence;
	}

	void string::test() const
	{
		cout << "sequence = " << sequence << endl
			<< "allocated = " << allocated << endl
			<< "current_length = " << current_length << endl
			<< "address = " << int(sequence) << endl;
	}

	// class implementation
	string::string(const char str[])
	{
		current_length = strlen(str);
		allocated = current_length + 1;
		sequence = new char[allocated];

		// copy str into my new string
		strcpy_s(sequence, allocated, str);
	}

}

#endif
