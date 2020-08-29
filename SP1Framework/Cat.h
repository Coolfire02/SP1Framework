#pragma once
#include "GameObject.h"

class Cat : public GameObject
{
public:
    std::string getType();
    Cat();
    ~Cat();

    Cat* clone() const { return new Cat(*this); };
};

