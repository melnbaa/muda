#pragma once
#include <iostream>
#include <ostream>
#include <time.h>
#include <string>
#include <iomanip>

using namespace std;

// Base class "Vehicle"

class Vehicle
{
protected:

	// Initializing strings for a vehicle's type, model/name, VIN number, and year produced

	string type;
	string name;
	string vin;
	string year;

	// Initializing integers for the number of parts passed, failed, processed, and completed

	int passed;
	int failed;
	int processed;
	int completed;

	// Initializing strings for a vehicle's build status, and whether or not it contains waste (if failed > 0)

	string status;
	string waste;

public:

	// Default constructor

	Vehicle();

	// Member variable mutators

	void Set_Type(string t) { type = t; };
	void Set_Name(string n) { name = n; };
	void Set_Year(string y) { year = y; };
	void Set_VIN(string v) { vin = v; };

	void Set_Passed(int p) { passed = p; };
	void Set_Failed(int f) { failed = f; };
	void Set_Processed(int i) { processed = i; };
	void Set_Completed(int c) { completed = c; };

	void Set_Status(string s) { status = s; };
	void Set_Waste(string w) { waste = w; };

	// Member variable accessors

	string Get_Type() { return type; };
	string Get_Name() { return name; };
	string Get_Year() { return year; };
	string Get_VIN() { return vin; };

	int Get_Passed() { return passed; };
	int Get_Failed() { return failed; };
	int Get_Processed() { return processed; };
	int Get_Completed() { return completed; };

	string Get_Status() { return status; };
	string Get_Waste() { return waste; };
	
	// Member functions to generate random values for each field (being the vehicle's type, name, VIN number, and generating its build and waste status, respectively, based on the previously generated type and part quantities)

	void Gen_Type(int* t);
	void Gen_Name(int t, int* n);
	void Gen_VIN(int t, int n);

	void Gen_Status(int ty, int processed, int completed);
	void Gen_Waste(int failed);

	// Virtual member function to be used in derived classes only to generate random quantities for each part (being chassis, engine, transmission, and brakes)

	virtual void Gen_Part(int* t);
};

// Overloaded stream insertion operator to output desired information

ostream& operator<<(ostream& os, Vehicle& v);
