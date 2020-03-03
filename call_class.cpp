#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include "call_class.h"

using namespace std;

/************************************************************************************************************************************/
//Name: default constructor
//Precondition: 
//Postcondition: 
//Decription: Reads the data file of call information (cell number, relays and call length) into the dynamic array of call record, 
//call_DB. If the count because equal to the size the function double_size is called and the memory allocated to call_DB is doubled.
/************************************************************************************************************************************/
call_class::call_class()
{
	count = 0;
	size = 5;
	call_DB = new call_record[size];
	ifstream in;
	in.open("callstats_data.txt");
	if (in.fail()) {
		cout << "The Input file failed to open correctly!\n";
		exit(1);
	}
	while (!in.eof()) {
		if (is_full())
			double_size();
		in >> call_DB[count].firstname >> call_DB[count].lastname
			>> call_DB[count].cell_number >> call_DB[count].relays
			>> call_DB[count].call_length;
		count++;
	}
	in.close();
	process();
}

/************************************************************************************************************************************/
//Name: copy constructor
//Precondition: 
//Postcondition: 
//Decription: performs a deep copy.
/************************************************************************************************************************************/
call_class::call_class(const call_class & original) {
	count = original.count;
	size = original.size;
	call_DB = new call_record[size];
	for (int i = 0; i < count; i++) {
		call_DB[i].firstname = original.call_DB[i].firstname;
		call_DB[i].lastname = original.call_DB[i].lastname;
		call_DB[i].cell_number = original.call_DB[i].cell_number;
		call_DB[i].relays = original.call_DB[i].relays;
		call_DB[i].call_length = original.call_DB[i].call_length;
		call_DB[i].net_cost = original.call_DB[i].net_cost;
		call_DB[i].tax_rate = original.call_DB[i].tax_rate;
		call_DB[i].call_tax = original.call_DB[i].call_tax;
		call_DB[i].total_cost = original.call_DB[i].total_cost;
	}
}

/***********************************************************************************************************************************/
//Name: is_empty
//Precondition: 
//Postcondition: 
//Decription: returns true if call_DB is empty
/**********************************************************************************************************************************/
bool call_class::is_empty()
{
	return count == 0;
}

/**********************************************************************************************************************************/
//Name: is_full 
//Precondition: 
//Postcondition: 
//Decription: returns true if call_DB is full
/*********************************************************************************************************************************/
bool call_class::is_full()
{
	return count == size;
}

/**********************************************************************************************************************************/
//Name: search
//Precondition: 
//Postcondition: 
//Decription: locates key in call_DB if it is there; otherwise -1 is returned
/*********************************************************************************************************************************/
int call_class::search(const string key)
{
	int index = -1;
	for (int i = 0; i < count; i++) {
		if (call_DB[i].cell_number == key) {
			index = i;
			break;
		}
	}
	return index;
}

/*********************************************************************************************************************************/
//Name: add
//Precondition: 
//Postcondition: 
//Decription: adds the information for a call to call_DB; if call_DB is full, double_size is called to increase the size of call_DB.
/********************************************************************************************************************************/
void call_class::add()
{
	if (is_full())
		double_size();
	cout << "Please enter the first and last name seperated by a space:\n";
	cin >> call_DB[count].firstname >> call_DB[count].lastname;
	cout << "Please enter the cell phone number:\n";
	cin >> call_DB[count].cell_number;
	cout << "Please enter the number of relays:\n";
	cin >> call_DB[count].relays;
	cout << "Please enter the call length in minutes:\n";
	cin >> call_DB[count].call_length;
	count++;
	process();
}

/********************************************************************************************************************************/
//Name: operator-
//Precondition: 
//Postcondition: 
//Decription: remove key from call_DB if it is there.
/*******************************************************************************************************************************/
call_class & call_class::operator-(const string key)
{
	int location = search(key);
	while (location != -1) {
		for (int j = location; j < count - 1; j++) {
			call_DB[j] = call_DB[j + 1];
		}
		count--;
		location = search(key);
	}
	return *this;
}

/******************************************************************************************************************************/
//Name: double_size
//Precondition: 
//Postcondition: 
//Decription: doubles the size (capacity) of call_DB
/******************************************************************************************************************************/
void call_class::double_size()
{
	size *= 2;
	call_record *temp = new call_record[size];

	for (int i = 0; i < count; i++)
	{
		temp[i] = call_DB[i];
	}

	delete[] call_DB;
	call_DB = temp;
}


/******************************************************************************************************************************/
//Name: process
//Precondition: 
//Postcondition: 
//Decription: calculate the net cost, tax rate, call tax and total cost for every call record in call_DB.
/*****************************************************************************************************************************/
void call_class::process()
{
	for (int i = 0; i < count; i++) {
		call_DB[i].net_cost = call_DB[i].relays / 50.0 * .40 * call_DB[i].call_length;

		if (call_DB[i].relays >= 0 && call_DB[i].relays <= 5)
			call_DB[i].tax_rate = 0.01;
		else if (call_DB[i].relays >= 6 && call_DB[i].relays <= 11)
			call_DB[i].tax_rate = 0.03;
		else if (call_DB[i].relays >= 12 && call_DB[i].relays <= 20)
			call_DB[i].tax_rate = 0.05;
		else if (call_DB[i].relays >= 21 && call_DB[i].relays <= 50)
			call_DB[i].tax_rate = 0.08;
		else
			call_DB[i].tax_rate = 0.12;
		call_DB[i].call_tax = call_DB[i].net_cost * call_DB[i].tax_rate;
		call_DB[i].total_cost = call_DB[i].net_cost + call_DB[i].call_tax;
	}
}


/****************************************************************************************************************************/
//Name: operator<<
//Precondition: 
//Postcondition: 
//Decription: Overloading operator<< as a friend function. Prints every field of every call_record in call_DB 
//                   formatted to the screen and a file called "stats7_output.txt".
/***************************************************************************************************************************/
ostream & operator<<(ostream & out, call_class & Org)
{
	out.setf(ios::showpoint);
	out.setf(ios::fixed);
	out.precision(2);
	for (int i = 0; i < Org.count; i++)
	{
		out << left << setw(10) << Org.call_DB[i].firstname;
		out << left << setw(10) << Org.call_DB[i].lastname;
		out << left << setw(20) << Org.call_DB[i].cell_number;
		out << left << setw(10) << Org.call_DB[i].relays;
		out << left << setw(10) << Org.call_DB[i].call_length;
		out << left << setw(10) << Org.call_DB[i].net_cost;
		out << left << setw(10) << Org.call_DB[i].tax_rate;
		out << left << setw(10) << Org.call_DB[i].call_tax;
		out << left << setw(10) << Org.call_DB[i].total_cost;
		out << endl;
	}

	//Put code to OPEN and CLOSE an ofstream and print to the file "stats7_output.txt".
	ofstream ofile;
	ofile.open("stats7_output.txt");

	if (ofile.fail()) {
		cout << "The output file failed to open correctly";
		exit(1);
	}

	for (int i = 0; i < Org.count; i++)
	{
		ofile << left << setw(10) << Org.call_DB[i].firstname;
		ofile << left << setw(10) << Org.call_DB[i].lastname;
		ofile << left << setw(20) << Org.call_DB[i].cell_number;
		ofile << left << setw(10) << Org.call_DB[i].relays;
		ofile << left << setw(10) << Org.call_DB[i].call_length;
		ofile << left << setw(10) << Org.call_DB[i].net_cost;
		ofile << left << setw(10) << Org.call_DB[i].tax_rate;
		ofile << left << setw(10) << Org.call_DB[i].call_tax;
		ofile << left << setw(10) << Org.call_DB[i].total_cost;
		ofile << endl;
	}

	ofile.close();

	return out;  //must have this statement
}

/****************************************************************************************************************************/
//Name: destructor
//Precondition: 
//Postcondition: 
//Decription: de-allocates all memory allocated to call_DB.  This should be the last function to be called before the program
//            is exited.
/***************************************************************************************************************************/
call_class::~call_class()
{
	delete[] call_DB;
}