#pragma once

class Driver
{
public:
    
    const int id;
    
    Driver(int id_);

    int getID() const;

private:
    
    int workTime{120};

};