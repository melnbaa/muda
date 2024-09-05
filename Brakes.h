#pragma once
#include "Vehicle.h"

class Brakes : public Vehicle
{
private:
    int quantity;

public:

    Brakes();

    void Set_Quantity(int q) { q = quantity; };

    int Get_Quantity() { return quantity; };

    void Del_Waste();

    virtual void Gen_Part(int t);
};

ostream& operator<<(ostream& os, Brakes& b);
