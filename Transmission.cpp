#include "Transmission.h"

Transmission::Transmission()
{
    quantity = 0;
}

void Transmission::Gen_Part(int t)
{ 
	// Create an array storing the total number of transmission parts required for each vehicle type

	int limits[4] = { 4, 10, 6, 8 };

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

void Transmission::Del_Waste()
{
	failed = 0;
}

ostream& operator<<(ostream& os, Transmission& t)
{
	os << t.Get_Passed() << setw(11) << t.Get_Failed() << setw(11) << t.Get_Processed()
		<< setw(11) << t.Get_Completed() << setw(11);
	 
	return os;
}
