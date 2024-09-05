#include "Engine.h"

Engine::Engine()
{
    quantity = 0;
}

void Engine::Gen_Part(int t)
{
	// Create an array storing the total number of engine parts required for each vehicle type

	int limits[4] = { 4, 8, 6, 4 };

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

void Engine::Del_Waste()
{
	failed = 0;
}

ostream& operator<<(ostream& os, Engine& e)
 {
	os << e.Get_Passed() << setw(11) << e.Get_Failed() << setw(11) << e.Get_Processed()
		<< setw(11) << e.Get_Completed() << setw(11);

	return os; 
}
