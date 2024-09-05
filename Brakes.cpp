#include "Brakes.h"

Brakes::Brakes()
{
    quantity = 0;
}

void Brakes::Gen_Part(int t)
{
	// Create an array storing the total number of brake parts required for each vehicle type 

	int limits[4] = { 2, 8, 4, 6 };

	int parts = 2 * limits[t];	

	for (int i = 0; i <= parts; i++)
	{
		int n = 1 + rand() % 20;

		if (quantity < limits[t])
		{
			if (n >= 1 && n <= 9)
				passed++;

			else if (n == 10)
				failed++;

			else if (n > 10 && n <= 15)
			{
				processed++;
				quantity++;
			}

			else if (n > 15 && n <= 20)
			{
				completed++;
				quantity++;
			}
		}

		else
		{
			if (n != 20)
				passed++;

			else
				failed++;
		}
	}
}

void Brakes::Del_Waste()
{
	failed = 0;
}

ostream& operator<<(ostream& os, Brakes& b)
{
	os << b.Get_Passed() << setw(11) << b.Get_Failed() << setw(11) << b.Get_Processed()
		<< setw(11) << b.Get_Completed();

	return os;
}
