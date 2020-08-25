#pragma once
#include "GameObject.h"
class Pipe :
    public GameObject
{
public:
    Pipe();
    ~Pipe();
    std::string getType();
};


