#define _CRT_SECURE_NO_WARNINGS
#pragma once
#pragma warning(disable : 4996)
#include <iostream>


using namespace std;

class String {
private:
	char* str;
	int length;
public:

	static const int limit = 100;

	//Constructor without parameters
	String() {
		length = 0;
		str = new char[1];
		str[0] = '\0';
	}

	//Constructors with parameters
	String(const char* symb) {
		length = std::strlen(symb);
		str = new char[length + 1];
		std::strcpy(str, symb);
	}

	String(const String& myString) {
		length = myString.length;
		str = new char[length + 1];
		std::strcpy(str, myString.str);
	}

	//Destructor
	~String() {
		delete[] str;
	}

	//Returns the length of a string
	int function_length() {
		return length;
	}

	//Checking if a string is empty
	bool empty() {
		if (function_length() > 0)
			return true;
		else return false;
	}

	//Returns the last character
	char last_symb(String myString) {
		char symb = myString[length - 1];
		return symb;
	}

	//Removes the last character
	void pop_last_symb() {
		str[length - 1] = '\0';
		length--;
	}

	//Working with an array
	char& operator[](int i) {
		return str[i];
	}

	//Overloading the assignment operator when 2 objects of a class
	String& operator=(const String& myString) {
		delete[] str;
		length = myString.length;
		str = new char[length + 1];
		std::strcpy(str, myString.str);
		return *this;
	}

	//Overloading the assignment operator when 1 is an object of a class and the other is a variable of type char
	String& operator=(const char symb) {
		delete[] str;
		length = std::strlen(&symb);
		str = new char[length + 1];
		std::strcpy(str, &symb);
		return *this;
	}

	//Overloading the assignment operator when 1 is a class object and the other is quoted directly
	String& operator=(const char* symb) {
		delete[] str;
		length = std::strlen(symb);
		str = new char[length + 1];
		std::strcpy(str, symb);
		return *this;
	}

	//Overloading the sum operator when 2 class objects
	friend String operator+(const String& str1, const String& str2) {
		String temp;
		delete[] temp.str;
		temp.length = str1.length + str2.length;
		temp.str = new char[temp.length + 1];
		std::strcpy(temp.str, str1.str);
		std::strcpy(temp.str + str1.length, str2.str);
		return temp;
	}

	//Overloading the summation operator when 1 is an object of a class and the other is a variable of type char
	friend String operator+(const String& str1, const char symb) {
		String temp;
		delete[] temp.str;
		temp.length = str1.length + sizeof(symb);
		temp.str = new char[temp.length + 1];
		std::strcpy(temp.str, str1.str);
		std::strcpy(temp.str + str1.length, &symb);
		return temp;
	}

	//Overloading the sum operator when 1 is a class object and the other is quoted directly
	friend String operator+(const String& str1, const char* symb) {
		String temp;
		delete[] temp.str;
		temp.length = str1.length + sizeof(symb);
		temp.str = new char[temp.length + 1];
		std::strcpy(temp.str, str1.str);
		std::strcpy(temp.str + str1.length, symb);
		return temp;
	}

	//Overloading the inference statement
	friend ostream& operator<<(ostream& stream, const String& myString) {
		stream << myString.str;
		return stream;
	}

	//Input Operator Overload
	friend istream& operator>>(istream& stream, String& myString) {
		char temp;
		stream.get(temp);
		if (stream)
			myString = temp;
		while (stream && stream.get() != '\n')
			continue;
		return stream;
	}
};