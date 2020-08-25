#pragma once
#include "GameObject.h"
class Pipe :
    public GameObject
{
public:
    Pipe();
    ~Pipe();
    std::string getType();
    
    Pipe* clone() const { return new Pipe(*this); };
};


