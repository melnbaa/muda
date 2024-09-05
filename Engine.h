#pragma once
#include "Vehicle.h"

// Comments for "Engine," "Transmission," and "Brakes" are omitted; code structures are identical

class Engine : public Vehicle
{
private:
    int quantity;

public:
    Engine();

    void Set_Quantity(int q) { q = quantity; };

    int Get_Quantity() { return quantity; };

    void Del_Waste();
    
    virtual void Gen_Part(int t);
};

ostream& operator<<(ostream& os, Engine& e);
