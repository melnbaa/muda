#include "Chassis.h"

Chassis::Chassis()
{
	quantity = 0;
}

void Chassis::Gen_Part(int t)
{
	// Create an array storing the total number of chassis parts requried for each vehicle type 
	// This is based on vehicle's type given by the variable "t" assigned from Vehicle.Get_Type(*t)
	// Order of array: Car, Truck, Van, SUV 

	int limits[4] = { 1, 2, 1, 1 };

	// Generate (2 * parts required) parts to distribute

	int parts = 2 * limits[t];

	// For loop that loops as many times as the value of parts generated

	for (int i = 0; i <= parts; i++)
	{
		// Generate a random number between 1 and 20

		int n = 1 + rand() % 20;

		// Check if the quantity of the part is already at its maximum required quantity

		if (quantity < limits[t])
		{
			// If the number is from 1-9, add the part to the "passed" category

			if (n >= 1 && n <= 9)
				passed++;

			// If the number equals 10, add the part to the "failed" category

			else if (n == 10)
				failed++;

			// If the number is from 10-15, add the part to the "processed" category
			// Parts stored in the "processed" and "completed" member variables count towards the quantity of chassis parts fitted to the vehicle

			else if (n > 10 && n <= 15)
			{
				processed++;
				quantity++;
			}

			// If the number is from 15-20, add the part to the "completed" category

			else if (n > 15 && n <= 20)
			{
				completed++;
				quantity++;
			}
		}

		// If the quantity of the part is already at its maximum required quantity, add the remaining parts to either passed or failed

		else
		{
			if (n != 20)
				passed++;

			else
				failed++;
		}
	}
}

void Chassis::Del_Waste()
{
	// Set the value of member variable "failed" to zero to eliminate waste produced by the vehicle's production

	failed = 0;
}

ostream& operator<<(ostream& os, Chassis& c)
{
	// Output all member variables (whose values are generated only by using member functions of the Chassis derived class) except for quantity

	os << c.Get_Passed() << setw(12) << c.Get_Failed() << setw(12) << c.Get_Processed()
		<< setw(12) << c.Get_Completed() << setw(12);

	return os;
}
