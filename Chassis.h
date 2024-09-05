#pragma once
#include "Vehicle.h"

// Derived class "Chassis" acting as one of the four vehicle part categories

class Chassis : public Vehicle
{
private:

    // Member variable "quantity" to store the total number of chassis parts *fitted to a vehicle*

    int quantity;

public:

    // Default constructor

    Chassis();

    // Member variable mutator

    void Set_Quantity(int q) { q = quantity; };

     // Member variable accessor

    int Get_Quantity() { return quantity; };

    // Member function that deletes any waste created by the part's generation process

    void Del_Waste();

     // Overridden virtual function

    virtual void Gen_Part(int t);
};

// Overloaded stream insertion operator to output desired information

ostream& operator<<(ostream& os, Chassis& c);
