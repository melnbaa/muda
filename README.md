**Introduction**

Toyota’s car production system was established based on years of continuous improvements, with the objective being to build and deliver vehicles to customers in the most efficient ways possible. One of the key management concepts that Toyota follows is the “Muda” process, which means “waste” in Japanese. This process helps to minimize waste in all forms, as well as efficiently using time, effort, and resources.

The project simulates the “Muda” philosophy that is used in modern-day manufacturing within the automotive business sector. The purpose is to simulate Toyota's production system by making code using C++. In the workplace, the program would act like a user interface that an Automation Engineer would use when evaluating current manufacturing processes and then use them to output generated data to a text file. The program would then read the data from the file and provide the user with menu options to sort through the data against certain fields, as well as identify sources of waste and remove them.

To simulate using the program at different times and/or locations, a new, randomly generated database is created every time the program runs. The generated values are called back into the program using object arrays that store data for each vehicle. Our software can be outsourced to other car manufacturers, as we are simulating one of them; they can change their preferences for their own needs in data collection.

**Class Details**

**Base Class Name:** _Vehicle_

This is the program’s base class, which creates a vehicle object. It contains member variables modified by the base class used to generated a vehicle’s type, model, set its year of production, generate its unique VIN number, and output its build and waste status, as well as member variables modified by each derived class used to output the number of parts that are labelled as “Passed,” “Failed,” “Processed,” and “Completed” for each derived object. It also includes a virtual function which is overridden by each derived class to randomly generate quantities for each part.

<table><tbody><tr><th><p><strong>Vehicle</strong></p></th></tr><tr><td><ul><li>type : string</li><li>name : string</li><li>vin : string</li><li>year : string</li><li>passed : int</li><li>failed : int</li><li>processed : int</li><li>completed : int</li><li>status : string</li><li>waste : string</li></ul></td></tr><tr><td><ul><li>Set_Type(t : string) : void</li><li>Set_Name(n : string) : void</li><li>Set_Year(y : string) : void</li><li>Set_VIN(v : string) : void</li><li>Set_Passed(p : int) : void</li><li>Set_Failed(f : int) : void</li><li>Set_Processed(i : int) : void</li><li>Set_Completed(c : int) : void</li><li>Set_Status(s : string) : void</li><li>Set_Waste(w : string) : void</li><li>Get_Type() : string</li><li>Get_Name() : string</li><li>Get_Year() : string</li><li>Get_VIN() : string</li><li>Get_Passed() : int</li><li>Get_Failed() : int</li><li>Get_Proccesed() : int</li><li>Get_Completed() : int</li><li>Get_Status() : string</li><li>Get_Waste() : string</li><li>Gen_Type(*t : int) : void</li><li>Gen_Name(n : int, *n int) : void</li><li>Get_VIN(t : int, n : int) : void</li><li>Gen_Status(ty : int, processed : int , completed : int) : void</li><li>Gen_Waste(failed : int) : void</li><li>Gen_Part(*t : int) : virtual void</li></ul></td></tr></tbody></table>

Table 1. A UML diagram of class Vehicle

**Function Name:** _Gen_Type(int\* t)_

- This function randomly picks one of the four car types (Car, Truck, Van, or SUV) and passes it as a string into the “type” member variable and in Main.cpp as an integer pointer.

**Function Name:** _Gen_Name(int t, int\* n)_

- This function randomly picks one of the 16 car names based on the type passed in as an argument, then passes the name as a string into the “name” member variable and in Main.cpp as an integer pointer.

**Function Name:** _Gen_VIN(int t, int n)_

- This function generates a random VIN number based on choosing a random character from each of 12 different arrays (taking into account the vehicle type and name passed in as arguments) plus a random six-digit number, then concatenates all strings to the “vin” member variable.

**Function Name:** _Gen_Waste(int failed)_

- This function generates the waste status for a vehicle based on the value of the argument passed in the function (if failed > 0, the function sets the member variable “waste” to “Yes”).

**Function Name:** _Gen_Status(int ty, int processed, int completed)_

- This function passes to the member variable “status” the build status of a vehicle (Queued, In-process, or Complete) based on the sum of the second and third arguments passed into the function and checking it against a value in an array (determined by the value of _ty_) in the function containing the total number of required parts for each vehicle type.

**Function Name:** _Gen_Part()_

- This function is only used in the derived classes to generate random quantities of parts produced for each derived class/object. It has no specification in the base class.

**Derived Class Name:** _Chassis_

This is one of four classes derived from Vehicle. This class generates the number of chassis parts for each category, being “Passed,” “Failed,” “Processed,” and “Completed” to be used in conjunction with its respective vehicle object.

<table><tbody><tr><th><p><strong>Chassis</strong></p></th></tr><tr><td><ul><li>quantity : int</li></ul></td></tr><tr><td><ul><li>Set_Quantity(q : int) : void</li><li>Get_Quantity() : void</li><li>Del_Waste() : void</li><li>Gen_Part(int t) : virtual void</li></ul></td></tr></tbody></table>

Table 2. A UML diagram of class Chassis

**Function Name:** _Del_Waste()_

- This function eliminates a vehicle’s waste by setting the number of produced parts in the “failed” member variable from the Vehicle base class to zero.

**Function Name:** _Gen_Part(int t)_

- This function generates a random number of chassis parts based on the vehicle type passed in as an argument as well as the total number of chassis parts required (stored in an array in the function), then randomly distributes the value among the “passed,” “failed,” “processed,” and “completed” member variables from the Vehicle base class.

**Derived Class Name:** _Engine_

This is one of four classes derived from Vehicle. This class generates the number of engine parts for each category, being “Passed,” “Failed,” “Processed,” and “Completed” to be used in conjunction with its respective vehicle object.

<table><tbody><tr><th><p><strong>Engine</strong></p></th></tr><tr><td><ul><li>quantity : int</li></ul></td></tr><tr><td><ul><li>Set_Quantity(q : int) : void</li><li>Get_Quantity() : void</li><li>Del_Waste() : void</li><li>Gen_Part(int t) : virtual void</li></ul></td></tr></tbody></table>

Table 3. A UML diagram of class Engine

**Function Name:** _Del_Waste()_

- This function eliminates a vehicle’s waste by setting the number of produced parts in the “failed” member variable from the Vehicle base class to zero.

**Function Name:** _Gen_Part(int t)_

- This function generates a random number of engine parts based on the vehicle type passed in as an argument as well as the total number of engine parts required (stored in an array in the function), then randomly distributes the value among the “passed,” “failed,” “processed,” and “completed” member variables from the Vehicle base class.

**Derived Class Name:** _Transmission_

This is one of four classes derived from Vehicle. This class generates the number of transmission parts for each category, being “Passed,” “Failed,” “Processed,” and “Completed” to be used in conjunction with its respective vehicle object.

<table><tbody><tr><th><p><strong>Transmission</strong></p></th></tr><tr><td><ul><li>quantity : int</li></ul></td></tr><tr><td><ul><li>Set_Quantity(q : int) : void</li><li>Get_Quantity() : void</li><li>Del_Waste() : void</li><li>Gen_Part(int t) : virtual void</li></ul></td></tr></tbody></table>

Table 4. A UML diagram of class Transmission

**Function Name:** _Del_Waste()_

- This function eliminates a vehicle’s waste by setting the number of produced parts in the “failed” member variable from the Vehicle base class to zero.

**Function Name:** _Gen_Part(int t)_

- This function generates a random number of chassis parts based on the vehicle type passed in as an argument as well as the total number of transmission parts required (stored in an array in the function), then randomly distributes the value among the “passed,” “failed,” “processed,” and “completed” member variables from the Vehicle base class.

**Derived Class Name:** _Brakes_

This is one of four classes derived from Vehicle. This class generates the number of brake parts for each category, being “Passed,” “Failed,” “Processed,” and “Completed” to be used in conjunction with its respective vehicle object.

<table><tbody><tr><th><p><strong>Brakes</strong></p></th></tr><tr><td><ul><li>quantity : int</li></ul></td></tr><tr><td><ul><li>Set_Quantity(q : int) : void</li><li>Get_Quantity() : void</li><li>Del_Waste() : void</li><li>Gen_Part(int t) : virtual void</li></ul></td></tr></tbody></table>

Table 5. A UML diagram of class Brakes

**Function Name:** _Del_Waste()_

- This function eliminates a vehicle’s waste by setting the number of produced parts in the “failed” member variable from the Vehicle base class to zero.

**Function Name:** _Gen_Part(int t)_

- This function generates a random number of brake parts based on the vehicle type passed in as an argument as well as the total number of brake parts required (stored in an array in the function), then randomly distributes the value among the “passed,” “failed,” “processed,” and “completed” member variables from the Vehicle base class.
