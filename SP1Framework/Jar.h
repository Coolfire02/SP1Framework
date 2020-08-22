#pragma once
#include "GameObject.h"
class Jar :
    public GameObject
{
public:
    std::string getType();
    Jar();
    ~Jar();
};

