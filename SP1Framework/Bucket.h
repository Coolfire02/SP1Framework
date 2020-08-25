#pragma once
#include "GameObject.h"
class Bucket : 
	public GameObject
{
public:
	std::string getType();
	Bucket();
	~Bucket();

	Bucket* clone() const { return new Bucket(*this); };
};

