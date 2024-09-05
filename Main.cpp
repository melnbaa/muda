#include "Vehicle.h"
#include "Chassis.h"
#include "Engine.h"
#include "Transmission.h"
#include "Brakes.h"

#include <fstream>
#include <windows.h>

// Prototypes for functions

void Create_Database(Vehicle vehicles[], Chassis chas[], Engine eng[], Transmission trans[], Brakes brake[], int SIZE);
void Read_Database(Vehicle vehicles[], Chassis chas[], Engine eng[], Transmission trans[], Brakes brake[], int SIZE);

void Gen_Parts(Vehicle vehicles[], Chassis chas[], Engine eng[], Transmission trans[], Brakes brake[], int i, int* t, int* n);
void Add_Parts(int* pass_qnty, int* fail_qnty, int* proc_qnty, int* comp_qnty, Chassis chas[], Engine eng[], Transmission trans[], Brakes brake[], int i);

int ConvertType(string type);

string Add_Spaces(string par, int limit);

int main()
{
	// Set the size of the database (number of rows)

	const int SIZE = 551;

	// Randomizing the timer so "Gen_Part()" member functions can be randomized

	srand(int(time(NULL)));

	cout << "\n********************************************** Welcome to Toyota Production System Ver. 1.0 ***********************************************" << endl;

	// Each row of the database consists of (in order):
	// - the vehicle's type, name, year, and VIN number from the Vehicle base class
	// - the number of parts passed, failed, processed, and completed from each derived class (Chassis, Engine, Transmission, and Brakes)
	// - the total of parts passed, failed, processed, and completed
	// - the vehicle's build status and waste status from the Vehicle base class

	Vehicle vehicles[SIZE];
	Chassis chas[SIZE];
	Engine eng[SIZE];
	Transmission trans[SIZE];
	Brakes brake[SIZE];

	Create_Database(vehicles, chas, eng, trans, brake, SIZE);

	Read_Database(vehicles, chas, eng, trans, brake, SIZE);
}

// Function for populating the object arrays and outputting their data to the file

void Create_Database(Vehicle vehicles[], Chassis chas[], Engine eng[], Transmission trans[], Brakes brake[], int SIZE)
{
	// Opening the file
	
	ofstream outFile;

	outFile.open("Muda.txt");

	// Time/loading delay aesthetics

	cout << "\nAcessing MUDA (vehicle) database";

	Sleep(1000); cout << ".";
	Sleep(1000); cout << ".";
	Sleep(1000); cout << "." << endl;
	Sleep(1000);

	// Outputting headings for the file

	outFile << "VEHICLE TYPE" << setw(7) << "MODEL" << setw(15)
		<< "YEAR" << setw(12) << "VIN NUMBER" << setw(19)

		<< "CHASSIS(P)" << setw(12) << "CHASSIS(F)" << setw(12)
		<< "CHASSIS(I)" << setw(12) << "CHASSIS(C)" << setw(11)

		<< "ENGINE(P)" << setw(11) << "ENGINE(F)" << setw(11)
		<< "ENGINE(I)" << setw(11) << "ENGINE(C)" << setw(11)

		<< "TRANSM(P)" << setw(11) << "TRANSM(F)" << setw(11)
		<< "TRANSM(I)" << setw(11) << "TRANSM(C)" << setw(11)

		<< "BRAKES(P)" << setw(11) << "BRAKES(F)" << setw(11)
		<< "BRAKES(I)" << setw(11) << "BRAKES(C)" << setw(14)

		<< "TOTAL PASSED" << setw(14) << "TOTAL FAILED" << setw(14)
		<< "TOTAL PROCES" << setw(14) << "TOTAL COMPLE" << setw(14)

		<< "BUILD STATUS" << setw(7) << "WASTE" << endl;

	// For loop that generates data for the object arrays 

	for (int i = 0; i < SIZE; i++)
	{
		int t = 0;
		int n = 0;

		int pass_qnty = 0;
		int fail_qnty = 0;
		int proc_qnty = 0;
		int comp_qnty = 0;

		// Generating vehicle data

		Gen_Parts(vehicles, chas, eng, trans, brake, i, &t, &n);

		// Adding together passed, failed, processed, and completed parts to get total quantities for each category

		Add_Parts(&pass_qnty, &fail_qnty, &proc_qnty, &comp_qnty, chas, eng, trans, brake, i);

		vehicles[i].Gen_Status(t, proc_qnty, comp_qnty);
		vehicles[i].Gen_Waste(fail_qnty);

		// Outputting the generated vehicle data

		outFile << vehicles[i] << chas[i] << eng[i] << trans[i] << brake[i] << setw(12)
			<< pass_qnty << setw(13) << fail_qnty << setw(14) << proc_qnty << setw(14) << comp_qnty
			<< setw(23) << vehicles[i].Get_Status() << setw(7) << vehicles[i].Get_Waste() << endl;
	}

	cout << "\nVehicle database loaded successfully ";
	
	// Variables and functions used to output the current date and time

	time_t result = time(NULL);

	char str[26];

	ctime_s(str, sizeof str, &result);

	printf("%s", str);

	outFile.close();
}

// Function for reading the newly populated object arrays and filtering through data

void Read_Database(Vehicle vehicles[], Chassis chas[], Engine eng[], Transmission trans[], Brakes brake[], int SIZE)
{
	bool exit = false;

	// Do-while loop until that iterates until "exit" = true/the user exits the program by hitting a key

	do
	{
		// Menu display options

		const char stars[140] = "*******************************************************************************************************************************************";

		cout << "\n1. Display entire database" << endl;
		cout << "2. Search by parameter" << endl
			<< "  i.   Vehicle type" << endl
			<< "  ii.  Vehicle model" << endl
			<< "  iii. Build status" << endl
			<< "  iv.  Waste status" << endl
			<< "3. Display vehicle data from VIN number" << endl
			<< "4. Exit program" << endl;

		int option;

		// Prevent the user cannot input an invalid option

		do
		{
			cout << "\nSelect display option: ";
			cin >> option;

			if (option < 1 || option > 4)
				cout << "Invalid option selected." << endl;
		} while (option < 1 || option > 4);

		cout << endl;

		const string headings = "VEHICLE TYPE  MODEL           YEAR  VIN NUMBER         CHASSIS  ENGINE  TRANSM  BRAKES  PASSED  FAILED  PROCES  COMPLE  BUILD STATUS  WASTE";

		// Strings for storing:
		// - the user's inputted parameter to search data for
		// - the last six digits of a vehicle's VIN number to search for inputted by the user

		string par;
		string seq;

		// A integer to keep track of the number of lines where a parameter is found

		int count = 0;

		// Integers used as arguments in the "Add_Spaces()" function to dictate how many more spaces must be added to the user's inputted string

		int t_size = 13;
		int m_size = 15;
		int s_size = 11;

		// Placeholder integers for storing the total number of passed, failed, processed, and completed parts

		int pass_qnty = 0;
		int fail_qnty = 0;
		int proc_qnty = 0;
		int comp_qnty = 0;

		switch (option)
		{
		case 1:

			cout << headings << endl;
			cout << stars << endl;

			// Output the entire database, in the order:
			// - vehicle type, name, year, and VIN number
			// - total quantities of each part/derived class
			// - total number of passed, failed, processed, and completed parts
			// - vehicle's build and waste statuses

			for (int i = 0; i < SIZE; i++)
			{
				Add_Parts(&pass_qnty, &fail_qnty, &proc_qnty, &comp_qnty, chas, eng, trans, brake, i);

				cout << vehicles[i].Get_Type() << setw(16) << vehicles[i].Get_Name() << setw(6) << vehicles[i].Get_Year() << setw(19) << vehicles[i].Get_VIN()
					<< setw(3) << chas[i].Get_Quantity() << setw(9) << eng[i].Get_Quantity() << setw(9) << trans[i].Get_Quantity() << setw(7) << brake[i].Get_Quantity()
					<< setw(9) << pass_qnty << setw(7) << fail_qnty << setw(9) << proc_qnty << setw(8) << comp_qnty
					<< setw(16) << vehicles[i].Get_Status() << setw(7) << vehicles[i].Get_Waste() << endl;
			}

			cout << stars << endl;

			break;

		case 2:

			// Ask the user to input a string; this can be a vehicle's:
			// - type (Car, Truck, Van, or SUV)
			// - name/model
			// - build status (Queued, In-Process, or Completed)
			// - waste status ("Yes" or "No")

			cout << "Enter search parameter: ";
			getline(cin.ignore(), par);

			cout << endl;

			count = 0;

			// Search the "vehicles" object array for the string

			for (int i = 0; i < SIZE; i++)
			{
				if (vehicles[i].Get_Type() == Add_Spaces(par, t_size) || vehicles[i].Get_Name() == Add_Spaces(par, m_size)
					|| vehicles[i].Get_Status() == Add_Spaces(par, s_size) || vehicles[i].Get_Waste() == par)
					count++;
			}

			// If the string could not be found anywhere, output an error message

			if (count == 0)
				cout << "No vehicles of given parameter found." << endl;

			// Output all data from each line the data is found on

			else
			{
				cout << headings << endl;
				cout << stars << endl;

				for (int i = 0; i < SIZE; i++)
				{
					if (vehicles[i].Get_Type() == Add_Spaces(par, t_size) || vehicles[i].Get_Name() == Add_Spaces(par, m_size) || vehicles[i].Get_Status() == Add_Spaces(par, s_size) || vehicles[i].Get_Waste() == par)
					{
						Add_Parts(&pass_qnty, &fail_qnty, &proc_qnty, &comp_qnty, chas, eng, trans, brake, i);

						cout << vehicles[i].Get_Type() << setw(16) << vehicles[i].Get_Name() << setw(6) << vehicles[i].Get_Year() << setw(19) << vehicles[i].Get_VIN()
							<< setw(3) << chas[i].Get_Quantity() << setw(9) << eng[i].Get_Quantity() << setw(9) << trans[i].Get_Quantity() << setw(7) << brake[i].Get_Quantity()
							<< setw(9) << pass_qnty << setw(7) << fail_qnty << setw(9) << proc_qnty << setw(8) << comp_qnty
							<< setw(16) << vehicles[i].Get_Status() << setw(7) << vehicles[i].Get_Waste() << endl;
					}
				}

				cout << stars << endl;

				// Output the number of lines the string is found on

				cout << "\nNumber of vehicles containing given parameter: " << count << " / " << SIZE << endl;
			}

			break;

		case 3:

			// Ask the user to input the last six digits of a vehicle's VIN number; ensure it is no less nor greater than six characters in length

			do
			{
				cout << "Enter last six digits of the vehicle's VIN number: ";
				cin >> seq;

				if (seq.length() < 6 || seq.length() > 6)
					cout << "Error. Sequential number must be 6 digits in length." << endl << endl;
			} while (seq.length() < 6 || seq.length() > 6);

			count = 0;

			// Search the "vehicles" object array for the string

			for (int i = 0; i < SIZE; i++)
			{
				if (vehicles[i].Get_VIN().find(seq) != std::string::npos)
					count++;
			}

			if (count == 0)
				cout << "No vehicle with given sequential number found." << endl;

			else
			{
				for (int i = 0; i < SIZE; i++)
				{
					if (vehicles[i].Get_VIN().find(seq) != std::string::npos)
					{
						// Create a 2D array, where each row stores the number of required parts for each vehicle type

						int limits[4][4] = {
							{ 1, 2, 1, 1 },    // Chassis part limits
							{ 4, 8, 6, 4 },   // Engine part limits
							{ 4, 10, 6, 8 }, // Transmission part limits
							{ 2, 8, 4, 6 }  // Brake part limits
						};

						Add_Parts(&pass_qnty, &fail_qnty, &proc_qnty, &comp_qnty, chas, eng, trans, brake, i);

						// Output the line the string is found on in a vertical format

						cout << "\nVehicle type: " << vehicles[i].Get_Type() << endl
							<< "Vehicle model: " << vehicles[i].Get_Name() << endl
							<< "Year: " << vehicles[i].Get_Year() << endl
							<< "VIN number: " << vehicles[i].Get_VIN() << endl

							<< "\nChassis parts: " << chas[i].Get_Quantity() << " / " << limits[0][ConvertType(vehicles[i].Get_Type())] << endl
							<< "Engine parts: " << eng[i].Get_Quantity() << " / " << limits[1][ConvertType(vehicles[i].Get_Type())] << endl
							<< "Transmission parts: " << trans[i].Get_Quantity() << " / " << limits[2][ConvertType(vehicles[i].Get_Type())] << endl
							<< "Brake parts: " << brake[i].Get_Quantity() << " / " << limits[3][ConvertType(vehicles[i].Get_Type())] << endl

							<< "\nPassed parts: " << pass_qnty << endl << "Failed parts: " << fail_qnty << endl
							<< "Processed parts: " << proc_qnty << endl << "Completed parts: " << comp_qnty << endl

							<< "\nBuild status: " << vehicles[i].Get_Status() << endl << "Waste status: " << vehicles[i].Get_Waste() << endl;

						// An "if" statement that executes if the vehicle contains waste (fail_qnty > 0)

						if (vehicles[i].Get_Waste() == "Yes")
						{
							string ans;

							// Ask the user if they want to remove the waste

							cout << "\nThis vehicle has wasted parts. Remove waste? (Y/N): ";
							cin >> ans;

							if (ans == "Y")
							{
								cout << "\nRemoving waste";

								Sleep(1000); cout << ".";
								Sleep(1000); cout << ".";
								Sleep(1000); cout << "." << endl;
								Sleep(1000);

								// Execute each object's "Del_Waste()" member function to set each of their "failed" parts to zero

								chas[i].Del_Waste();
								eng[i].Del_Waste();
								trans[i].Del_Waste();
								brake[i].Del_Waste();

								// Update the waste status of the vehicle

								vehicles[i].Set_Waste("No");

								cout << "\nWaste removed successfully." << endl;
							}

							else
								break;
						}
					}
				}
			}

			break;

		case 4:

			// If the user enters the "4" key, the program ends
			// Output the time the user ended the program

			cout << "Session ended ";
				
			time_t result = time(NULL);

			char str[26];

			ctime_s(str, sizeof str, &result);

			printf("%s", str);

			exit = true;

			break;
		}

	} while (exit != true);
}

// Function that run each object's "Gen_..."/randomization member functions

void Gen_Parts(Vehicle vehicles[], Chassis chas[], Engine eng[], Transmission trans[], Brakes brake[], int i, int* t, int* n)
{
	vehicles[i].Gen_Type(t);
	vehicles[i].Gen_Name(*t, n);
	vehicles[i].Set_Year("2023");
	vehicles[i].Gen_VIN(*t, *n);

	chas[i].Gen_Part(*t);
	eng[i].Gen_Part(*t);
	trans[i].Gen_Part(*t);
	brake[i].Gen_Part(*t);
}

// Function that adds each derived object's number of passed, failed, processed, and completed parts to get the total quantity in each category

void Add_Parts(int* pass_qnty, int* fail_qnty, int* proc_qnty, int* comp_qnty, Chassis chas[], Engine eng[], Transmission trans[], Brakes brake[], int i)
{
	*pass_qnty = chas[i].Get_Passed() + eng[i].Get_Passed() + trans[i].Get_Passed() + brake[i].Get_Passed();
	*fail_qnty = chas[i].Get_Failed() + eng[i].Get_Failed() + trans[i].Get_Failed() + brake[i].Get_Failed();
	*proc_qnty = chas[i].Get_Processed() + eng[i].Get_Processed() + trans[i].Get_Processed() + brake[i].Get_Processed();
	*comp_qnty = chas[i].Get_Completed() + eng[i].Get_Completed() + trans[i].Get_Completed() + brake[i].Get_Completed();
}

// Function that converts a vehicle's type given by a string from Vehicle.Get_Type() into an integer

int ConvertType(string type)
{
	if (type == "Car         ")
		return 0;

	else if(type == "Truck       ")
		return 1;

	else if (type == "Van         ")
		return 2;

	else if (type == "SUV         ")
		return 3;
}

// Function that adds spaces to the user's inputted string/parameter to consider the formatting of the file
// The number of spaces added is based on the length of the string inputted and the width of the coloumn it falls under in the file

string Add_Spaces(string par, int limit)
{
	for (int i = par.length(); i < limit - 1; i++)
		par += " ";

	return par;
}
