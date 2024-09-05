#pragma once
#include "Vehicle.h"

class Transmission : public Vehicle
{
private:
    int quantity;

public:

    Transmission();

    void Set_Quantity(int q) { q = quantity; };

    int Get_Quantity() { return quantity; };

    void Del_Waste();

    virtual void Gen_Part(int t);
};

ostream& operator<<(ostream& os, Transmission& t);
